/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#pragma once

// IFC Canvas (patch 07, empty-path counters): raw trigger counts for the five
// e408b654 paths that return an EMPTY geometry for a whole representation item
// without a fault, so the element they belong to silently renders nothing:
//
//   tapered                 ExtrudeTapered (operations/geometryutils.h): the
//                           incompatible-composite, incompatible-boundary /
//                           direction, and mismatched-sample-count returns;
//   sectioned               SectionedSurfaceRings' early returns
//                           (operations/bim-geometry/utils.h) and the
//                           GetCrossSections3D faces / positions count mismatch
//                           of IFCSECTIONEDSOLID and IFCSECTIONEDSURFACE
//                           (IfcGeometryLoader.cpp);
//   sweptDiskReversal       SweepCircular's whole-bar return on a (near-)reversal
//                           of the directrix, dot < -0.999999
//                           (operations/bim-geometry/utils.h);
//   fixedReferenceParallel  SweepFixedReference's return when the FixedReference
//                           is parallel to the directrix tangent
//                           (operations/geometryutils.h);
//   faceIndex               an IfcTriangulatedFaceSet CoordIndex outside its point
//                           list (IfcGeometryProcessor.cpp; this return stores NO
//                           geometry, so the item has no placed geometry at all).
//
// Each site increments its counter immediately before its existing `return`;
// no control flow changes and no geometry changes. The counts are RAW triggers
// (one element can fire a path several times, e.g. a count mismatch in
// GetCrossSections3D followed by SectionedSurfaceRings' `< 2 sections` return),
// so a consumer computes per-ELEMENT attribution from deltas: snapshot
// IfcCanvasEmptyPathCountersTLS() before IfcGeometryProcessor::GetFlatMesh and
// diff after it (IfcCanvasEmptyPathMask).
//
// Why thread_local (the patch-01 IfcCancellation.h precedent): the sites are
// free inline functions in namespaces webifc::geometry and bimGeometry that hold
// no IfcGeometryProcessor handle, and web-ifc meshes one element at a time on
// the calling thread, so per-thread delta accounting around one GetFlatMesh is
// exact for that element and two documents meshed on two threads never mix.
//
// Mapped-item visit log: a repeat of an IfcRepresentationMap that the
// representation-map memo (patch 02) serves without recursing re-meshes
// nothing, so no counter moves for it. IfcGeometryProcessor::GetMeshUncached
// therefore opens an IfcCanvasEmptyPathMappedItemScope for every IFCMAPPEDITEM
// it visits: the scope records {mapped item express id, mask of the counters
// that grew while the item was meshed} in IfcCanvasEmptyPathVisitLogTLS() when
// it closes (including on a throw). A visit with mask 0 is how a consumer
// recognises a memo-served repeat and replays the mask it recorded for the
// same map earlier. The scope never reads or moves the loader's tape.

#include <cstddef>
#include <cstdint>
#include <vector>

// Marker: a consumer that includes this header can rely on the counters.
#define IFCCANVAS_WEBIFC_EMPTY_PATH_COUNTERS 1

namespace webifc::geometry
{
    // Raw trigger counts, per thread, monotonically increasing (never reset by
    // the kernel; consumers diff snapshots). uint32_t wraps after 4e9 triggers,
    // and IfcCanvasEmptyPathMask compares with `!=`, so a wrap is still a delta.
    struct IfcCanvasEmptyPathCounters
    {
        uint32_t tapered = 0;
        uint32_t sectioned = 0;
        uint32_t sweptDiskReversal = 0;
        uint32_t fixedReferenceParallel = 0;
        uint32_t faceIndex = 0;
    };

    // Bit of each path in a fired mask.
    enum : uint8_t
    {
        kIfcCanvasEmptyPathTapered = 1u << 0,
        kIfcCanvasEmptyPathSectioned = 1u << 1,
        kIfcCanvasEmptyPathSweptDiskReversal = 1u << 2,
        kIfcCanvasEmptyPathFixedReferenceParallel = 1u << 3,
        kIfcCanvasEmptyPathFaceIndex = 1u << 4,
    };

    // One IfcMappedItem visit: the item's express id and the paths that fired
    // while GetMeshUncached meshed it (0 = nothing fired: a memo-served repeat,
    // or a map that holds no empty path).
    struct IfcCanvasEmptyPathVisit
    {
        uint32_t mappedItemID;
        uint8_t firedMask;
    };

    inline IfcCanvasEmptyPathCounters &IfcCanvasEmptyPathCountersTLS()
    {
        thread_local IfcCanvasEmptyPathCounters counters;
        return counters;
    }

    // Completed visits since the consumer last cleared it (the bridge clears it
    // before each element's GetFlatMesh). Grows by one entry per IfcMappedItem.
    inline std::vector<IfcCanvasEmptyPathVisit> &IfcCanvasEmptyPathVisitLogTLS()
    {
        thread_local std::vector<IfcCanvasEmptyPathVisit> visits;
        return visits;
    }

    // A mapped-item scope that is still open on this thread: the item's id and
    // the counters when it opened (nested maps nest the scopes). Kept off the
    // GetMeshUncached frame, so the scope object itself is one byte.
    struct IfcCanvasEmptyPathOpenScope
    {
        IfcCanvasEmptyPathCounters before;
        uint32_t mappedItemID;
    };

    inline std::vector<IfcCanvasEmptyPathOpenScope> &IfcCanvasEmptyPathOpenScopesTLS()
    {
        thread_local std::vector<IfcCanvasEmptyPathOpenScope> open;
        return open;
    }

    inline uint8_t IfcCanvasEmptyPathMask(const IfcCanvasEmptyPathCounters &before, const IfcCanvasEmptyPathCounters &after)
    {
        uint8_t mask = 0;
        if (after.tapered != before.tapered) mask |= kIfcCanvasEmptyPathTapered;
        if (after.sectioned != before.sectioned) mask |= kIfcCanvasEmptyPathSectioned;
        if (after.sweptDiskReversal != before.sweptDiskReversal) mask |= kIfcCanvasEmptyPathSweptDiskReversal;
        if (after.fixedReferenceParallel != before.fixedReferenceParallel) mask |= kIfcCanvasEmptyPathFixedReferenceParallel;
        if (after.faceIndex != before.faceIndex) mask |= kIfcCanvasEmptyPathFaceIndex;
        return mask;
    }

    // RAII scope GetMeshUncached opens for an IFCMAPPEDITEM (armed == false for
    // every other line type: a no-op). The destructor runs on every exit,
    // a MeshingCancelled or fault throw included, and never throws: if the log
    // cannot grow, the visit is dropped (the consumer then under-attributes
    // that one repeat; it never over-counts).
    class IfcCanvasEmptyPathMappedItemScope
    {
    public:
        IfcCanvasEmptyPathMappedItemScope(bool armed, uint32_t mappedItemID)
            : _armed(armed)
        {
            if (_armed)
            {
                IfcCanvasEmptyPathOpenScopesTLS().push_back(
                    IfcCanvasEmptyPathOpenScope{IfcCanvasEmptyPathCountersTLS(), mappedItemID});
            }
        }

        ~IfcCanvasEmptyPathMappedItemScope()
        {
            if (!_armed)
            {
                return;
            }
            auto &open = IfcCanvasEmptyPathOpenScopesTLS();
            if (open.empty())
            {
                return;
            }
            const IfcCanvasEmptyPathOpenScope scope = open.back();
            open.pop_back();
            const uint8_t mask = IfcCanvasEmptyPathMask(scope.before, IfcCanvasEmptyPathCountersTLS());
            try
            {
                IfcCanvasEmptyPathVisitLogTLS().push_back(IfcCanvasEmptyPathVisit{scope.mappedItemID, mask});
            }
            catch (...)
            {
            }
        }

        IfcCanvasEmptyPathMappedItemScope(const IfcCanvasEmptyPathMappedItemScope &) = delete;
        IfcCanvasEmptyPathMappedItemScope &operator=(const IfcCanvasEmptyPathMappedItemScope &) = delete;

    private:
        bool _armed;
    };
}
