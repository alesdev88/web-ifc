/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#pragma once
#include <unordered_set> // IFC Canvas: _activeBooleans (boolean cycle guard, see below)

#include <glm/glm.hpp>
#include <string>
#include <cstdint>
#include <functional>
#include "representation/geometry.h"
#include "../parsing/IfcLoader.h"
#include "../cache/IfcCache.h"
#include "../schema/IfcSchemaManager.h"
#include "IfcGeometryLoader.h"
#include "IfcCancellation.h"

namespace fuzzybools
{
  struct Geometry;
}

namespace webifc::geometry
{

  // this class performs the processing of raw geometry data from the geometry loader to produce meshes

  struct IfcGeometrySettings
  {
    bool _coordinateToOrigin = false;
    bool _optimize_profiles = true;
    bool _exportPolylines = false;
    uint16_t _circleSegments = 12;
    double TOLERANCE_PLANE_INTERSECTION = 1.0E-04;
    double TOLERANCE_PLANE_DEVIATION = 1.0E-04;
    double TOLERANCE_BACK_DEVIATION_DISTANCE = 1.0E-04;
    double TOLERANCE_INSIDE_OUTSIDE_PERIMETER = 1.0E-10;
    double TOLERANCE_BOUNDING_BOX = 1.0E-02;
    uint16_t _BOOLEAN_UNION_THRESHOLD = 150;
  };

  class booleanManager
  {
  public:
    IfcGeometry BoolProcess(const std::vector<IfcGeometry> &firstGeoms, std::vector<IfcGeometry> &secondGeoms, std::string op, IfcGeometrySettings _settings);

  private:
    fuzzybools::Geometry convertToEngine(Geometry geom);
    IfcGeometry convertToWebIfc(fuzzybools::Geometry geom);
    IfcGeometry Union(IfcGeometry firstOperator, IfcGeometry secondOperator);
    IfcGeometry Subtract(IfcGeometry firstOperator, IfcGeometry secondOperator);
  };

  class IfcGeometryProcessor
  {
  public:
    IfcGeometryProcessor(webifc::parsing::IfcLoader &loader, const webifc::schema::IfcSchemaManager &schemaManager, uint16_t circleSegments, bool coordinateToOrigin, double TOLERANCE_PLANE_INTERSECTION, double TOLERANCE_PLANE_DEVIATION, double TOLERANCE_BACK_DEVIATION_DISTANCE, double TOLERANCE_INSIDE_OUTSIDE_PERIMETER, double TOLERANCE_SCALAR_EQUALITY, double PLANE_REFIT_ITERATIONS, double BOOLEAN_UNION_THRESHOLD);
    IfcGeometry &GetGeometry(uint32_t expressID);
    IfcGeometryLoader& GetLoader();
    IfcFlatMesh GetFlatMesh(uint32_t expressID, bool applyLinearScalingFactor = true);
    IfcComposedMesh GetMesh(uint32_t expressID);
    // Install a cooperative cancellation predicate observed by the long-running
    // geometry loops (see IfcCancellation.h). It is armed for the duration of
    // each GetFlatMesh call and checked at the boolean pipeline's outer loop
    // heads; a `true` return aborts meshing by throwing MeshingCancelled. Pass an
    // empty std::function to disable. Not thread-safe against a concurrent
    // GetFlatMesh on the same processor (web-ifc meshes one element at a time).
    void SetCancellationCheck(std::function<bool()> check);
    void SetTransformation(const std::array<double, 16> &val);
    std::array<double, 16> GetFlatCoordinationMatrix() const;
    glm::dmat4 GetCoordinationMatrix() const;
    void Clear(bool keepMappedRepresentations = false);
    IfcGeometryProcessor *Clone(const webifc::parsing::IfcLoader &loader) const;

  protected:
    IfcGeometryProcessor(const IfcGeometrySettings &settings, std::unordered_map<uint32_t, IfcGeometry> expressIDToGeometry, glm::dmat4 transformation, const parsing::IfcLoader &loader, booleanManager boolEngine, const schema::IfcSchemaManager &schemaManager, bool isCoordinated, uint32_t expressIdCyl, uint32_t expressIdRect, glm::dmat4 coordinationMatrix, IfcGeometry predefinedCylinder, IfcGeometry predefinedCube);
    IfcGeometrySettings _settings;
    std::optional<glm::dvec4> GetStyleItemFromExpressId(uint32_t expressID);
    void AddFaceToGeometry(uint32_t expressID, IfcGeometry &geometry);
    IfcGeometry GetBrep(uint32_t expressID);
    IfcGeometry BoolProcess(const std::vector<IfcGeometry> &firstGroups, std::vector<IfcGeometry> &secondGroups, std::string op, IfcGeometrySettings _settings);
    std::unordered_map<uint32_t, IfcGeometry> _expressIDToGeometry;
    struct MappedRepresentation { IfcComposedMesh mesh; std::vector<std::pair<uint32_t, IfcGeometry>> geometries; };
    std::unordered_map<uint32_t, MappedRepresentation> _mappedRepresentations;
    size_t _mappedRepresentationsBytes = 0;
    uint64_t _mappedRepresentationsRevision = 0;
    IfcComposedMesh GetMeshUncached(uint32_t expressID, uint32_t lineType);
    // Cooperative cancellation predicate (see SetCancellationCheck). Empty by
    // default; installed into the thread-local hook around each GetFlatMesh.
    std::function<bool()> _cancellationCheck;
    IfcSurface GetSurface(uint32_t expressID);
    IfcGeometryLoader _geometryLoader;
    glm::dmat4 _transformation = glm::dmat4(1.0);
    const parsing::IfcLoader &_loader;
    webifc::cache::IfcCache _cache;
    booleanManager _boolEngine;
    // IFC Canvas (boolean cycle guard): the boolean results currently being
    // meshed on this call stack (see GetMeshUncached's IFCBOOLEANCLIPPINGRESULT
    // and IFCBOOLEANRESULT cases). Declared here, right after _boolEngine, on
    // purpose: outside the cooperative-cancel patch's member hunk and the
    // repmap-memo patch's header hunk, so each patch's own `git apply --reverse
    // --check` (Scripts/build_webifc.sh's rerun path) still finds its post-image.
    std::unordered_set<uint32_t> _activeBooleans;
    const schema::IfcSchemaManager &_schemaManager;
    bool _isCoordinated = false;
    uint32_t _expressIdCyl = 0;
    uint32_t _expressIdRect = 0;
    glm::dmat4 _coordinationMatrix = glm::dmat4(1.0);
    void AddComposedMeshToFlatMesh(IfcFlatMesh &flatMesh, const IfcComposedMesh &composedMesh, const glm::dmat4 &parentMatrix = glm::dmat4(1), const glm::dvec4 &color = glm::dvec4(1, 1, 1, 1), bool hasColor = false);
    std::vector<uint32_t> Read2DArrayOfThreeIndices();
    void ReadIndexedPolygonalFace(uint32_t expressID, std::vector<IfcBound3D> &bounds, const std::vector<glm::dvec3> &points);
    void ApplyBooleanToMeshChildren(IfcComposedMesh &composedMesh, std::vector<IfcGeometry> &secondGroups, std::string op, IfcGeometrySettings _settings, glm::dmat4 mat);
    IfcGeometry _predefinedCylinder;
    IfcGeometry _predefinedCube;

  public:
    // ---- IFC Canvas (roadmap 46, parse-01): per-IfcRepresentationMap memo ----
    // GetMesh recomputes every leaf of a mapped representation (extrusion,
    // brep, sweep, boolean ...) on EVERY IfcMappedItem visit: the composed tree
    // is rebuilt and each leaf re-tessellated into `_expressIDToGeometry`,
    // although the IfcRepresentationMap's tree is a pure function of the tape.
    // The memo keeps ONE composed tree per map id (ids + placements + colours,
    // no vertex data) between Clear() calls and, on a hit, pushes a copy of
    // that tree instead of recursing; the leaves already sit in
    // `_expressIDToGeometry` from the first visit. Output is byte-identical to
    // the recompute path because (a) AddComposedMeshToFlatMesh's reversal is
    // idempotent through IfcGeometry::reversed and its Normalize() already is,
    // so a shared leaf always ends in the state a fresh leaf would reach for
    // the visiting instance; (b) the memo is bypassed inside ANY boolean or
    // void context (`_boolContextDepth > 0`: the void subtraction of a voided
    // element's own body, the relVoids operands, both operands of
    // IfcBooleanClippingResult / IfcBooleanResult), where the operands must be
    // fresh, un-normalized leaves; (c) a leaf overwritten in place by
    // ApplyBooleanToMeshChildren is recorded in `_booleanTainted`, and any
    // entry that references such a leaf, or a leaf that is no longer present,
    // is dropped on lookup (miss + `invalidated`). Nothing is retained across
    // Clear(): both containers are cleared with the geometry cache.
    // (std::unordered_map / unordered_set / vector reach this header through
    // its own direct includes at this pin: representation/geometry.h,
    // ../schema/IfcSchemaManager.h and ../parsing/IfcLoader.h — kept that way
    // so this patch touches the include block, which the cooperative-cancel
    // patch edits, not at all.)
    struct RepresentationMapMemoStats
    {
      uint64_t hits = 0;
      uint64_t misses = 0;
      uint64_t invalidated = 0;             // entries dropped by the validation on lookup
      uint64_t skippedBooleanContext = 0;   // IfcMappedItem visits bypassed (depth > 0)
    };
    void SetRepresentationMapMemoEnabled(bool enabled);
    RepresentationMapMemoStats GetRepresentationMapMemoStats() const;

  protected:
    struct MapMemoEntry
    {
      IfcComposedMesh mesh;            // the IfcRepresentationMap node's composed tree
      std::vector<uint32_t> leafIDs;   // every hasGeometry node id inside `mesh`
    };
    // RAII ++/-- of `_boolContextDepth`, exception-safe (MeshingCancelled unwinds).
    struct BoolContextScope
    {
      uint32_t &depth;
      explicit BoolContextScope(uint32_t &d) : depth(d) { ++depth; }
      ~BoolContextScope() { --depth; }
      BoolContextScope(const BoolContextScope &) = delete;
      BoolContextScope &operator=(const BoolContextScope &) = delete;
    };
    IfcComposedMesh GetMappedRepresentation(uint32_t mapExpressID);
    static void CollectLeafIDs(const IfcComposedMesh &mesh, std::vector<uint32_t> &leafIDs);
    std::unordered_map<uint32_t, MapMemoEntry> _mapMemo;
    std::unordered_set<uint32_t> _booleanTainted;
    uint32_t _boolContextDepth = 0;
    bool _mapMemoEnabled = true;
    RepresentationMapMemoStats _mapMemoStats;
  };
}