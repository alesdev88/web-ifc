/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#pragma once

// Cooperative meshing-cancellation hook for IfcGeometryProcessor.
//
// Motivation: a single pathological element can spin inside GetFlatMesh for an
// unbounded amount of WALL TIME with memory bounded — an iteration/convergence
// blowup, not an allocation blowup (measured: one IfcFlowController meshed for
// >= 109 minutes and never returned, holding ~660 MB flat). A live CPU sample
// of the actually-spinning process proved the wedge is in `mapbox::earcut`'s
// `earcutLinked`/`cureLocalIntersections` (ear-clipping triangulation of a
// degenerate face polygon during faceted-BRep triangulation) — NOT this
// library's own mesh-boolean pipeline (the in-tree fuzzybools engine), which
// was the first hypothesis and was falsified (comprehensive fuzzybools-only
// hooks alone still hung the reproducing case for >8 min). A production
// integration cannot hang forever on one element, so a caller needs to install
// a per-element time budget (or a whole-document cancel) that the long-running
// geometry loops — earcut's (load-bearing for the measured class; hooked into
// the FetchContent'd mapbox/earcut.hpp by the consumer's build, since earcut
// ships outside this header's own translation units) and, defensively,
// fuzzybools' (a different, unobserved wedge class) — observe cooperatively
// and abort.
//
// Design (why a thread_local predicate rather than a member threaded through
// signatures): the fuzzybools wedge loops live in header-only free functions in
// namespace `fuzzybools` (operations/boolean-utils/*) which hold no
// IfcGeometryProcessor handle; earcut's loops are similarly free functions with
// no such handle. Passing a predicate down through every signature would be a
// large, non-upstreamable churn. web-ifc meshes one element at a time on the
// calling thread, so a thread_local predicate is the call-graph-cheap choice:
// IfcGeometryProcessor installs it for the duration of one GetFlatMesh (via
// CancellationScope) and the loop heads call CheckCancellation() — an O(1)
// predicate read. When no predicate is installed the check is a single null
// test, so builds/consumers that never set one pay nothing and behave exactly
// as before.
//
// On trip the check throws MeshingCancelled, which unwinds pure C++ frames back
// to the caller's per-element try/catch. It must never be allowed to cross into
// a frame that is not exception-safe; the ObjC++ bridge (WebIFCBridge.mm)
// catches it around the same call it already isolates per-element meshing
// faults with.

#include <functional>
#include <stdexcept>

namespace webifc::geometry
{
    // Dedicated exception thrown when a cooperative cancellation predicate trips
    // inside the geometry pipeline. Distinct type so callers can tell a
    // deliberate budget/cancel abort apart from a genuine meshing fault.
    struct MeshingCancelled : public std::runtime_error
    {
        MeshingCancelled()
            : std::runtime_error("web-ifc meshing cancelled (per-element time budget or document cancel)") {}
    };

    // The thread-local cancellation predicate. Empty by default (no cancel).
    // Returns a reference so CancellationScope can save/restore it.
    inline std::function<bool()> &CancellationPredicateTLS()
    {
        thread_local std::function<bool()> pred;
        return pred;
    }

    // Loop-head hook: throws MeshingCancelled iff a predicate is installed AND
    // it returns true. Cheap enough to sit at the head of the boolean pipeline's
    // outer per-face / per-plane loops.
    inline void CheckCancellation()
    {
        const std::function<bool()> &pred = CancellationPredicateTLS();
        if (pred && pred())
        {
            throw MeshingCancelled();
        }
    }

    // RAII installer — arms the thread-local predicate for the current scope and
    // restores the previous one on exit (nested GetFlatMesh calls are safe). An
    // empty `pred` installs "no cancellation" for the scope.
    struct CancellationScope
    {
        std::function<bool()> _prev;
        explicit CancellationScope(std::function<bool()> pred)
        {
            std::function<bool()> &slot = CancellationPredicateTLS();
            _prev = std::move(slot);
            slot = std::move(pred);
        }
        ~CancellationScope()
        {
            CancellationPredicateTLS() = std::move(_prev);
        }
        CancellationScope(const CancellationScope &) = delete;
        CancellationScope &operator=(const CancellationScope &) = delete;
    };
}
