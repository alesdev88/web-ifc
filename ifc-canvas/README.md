# IFC Canvas modifications to web-ifc: IFC Canvas 1.2.0 to 1.3.0

This repository is a fork of [ThatOpen web-ifc](https://github.com/ThatOpen/engine_web-ifc).
Tag `ifc-canvas-1.3.0` is the Source Code Form of the MPL-2.0 Covered
Software (web-ifc) as modified by IFC Canvas, an iPad app for viewing IFC
building models by Aleš Dolenec, for every IFC Canvas release from 1.2.0 to
1.3.0. These releases compile web-ifc's C++ geometry kernel into the app as a
static library, and every one of them links the same library (build 406, an
internal test build listed below, linked a separately compiled one); every
modification it contains is published here, as commits on top of the
upstream revision it is based on.

- Tag `ifc-canvas-1.3.0` (this tree): the web-ifc source of IFC Canvas 1.2.0
  to 1.3.0.
- Branch `ifc-canvas`: the current IFC Canvas modifications. Its
  `ifc-canvas/README.md` has the complete table of IFC Canvas releases and the
  tag that holds the source of each. The commits of this tag are not on that
  branch, because they are based on an older upstream revision.

## Releases and internal test builds covered by this tag

| IFC Canvas releases | Builds | IFC Canvas release commits (private app repository) | Source |
| --- | --- | --- | --- |
| 1.2.0 to 1.3.0 | 404 to 443 (406: see below) | `731fc98a361e6973b585091c6bca68f42b4c1101` (1.2.0) to `ea288bb4c7f115652e8ae347b5c9292a948111e9` (1.3.0) | upstream `61384fe61da64feebdd49eb3d319971e0b4bff81` + the 2 commits below + the earcut patch below |

Every IFC Canvas release in this range and every internal test build number
known to carry a kernel built from this tag's source: 1.2.0 (builds 404, 405;
and 406, an internal test build, not distributed), 1.2.1 (build 407),
1.2.2 (builds 408-410), 1.2.3 (builds 411, 415), 1.2.4 (build 412),
1.2.5 (builds 413, 414, 416-419), 1.2.6 (builds 420-424),
1.2.7 (builds 425-429), 1.2.8 (builds 430-435), 1.2.9 (builds 436-439),
1.2.10 (builds 440-442), 1.3.0 (build 443). Every build number from 404 to
443 is listed.

Build 406 was an internal test build, not distributed: the 1.2.0 (build 405)
app tree, installed only on the developer's own test iPad on 2026-09-20. Its
kernel source is in this repository either way, as the app's records leave
open which of the two it was: this tag, or its commit 1 below
(`8970df68b8bf770d3c79ddaa5c7e52a80acfb4db`) plus `earcut-4811a2b.patch`. It
was compiled with the extra flag `-ffp-contract=off`, which changes no
source.

### Provenance of `ifc-canvas-1.3.0`

The IFC Canvas release commits are commits of the IFC Canvas app repository,
not of this one. That repository is private, so the app commit ids in this
file cannot be resolved publicly; they are recorded only as provenance
anchors. At each release commit, web-ifc is pinned to upstream
`61384fe61da64feebdd49eb3d319971e0b4bff81` (upstream `main` of 2026-09-15, not
tagged upstream; its `package.json` version is 0.0.78), and the app's build
script (`Scripts/build_webifc.sh`, a file of that private repository) applies
the two web-ifc patch files listed below with `git apply` before configuring,
in shell glob order, and applies the earcut patch file with `git apply` inside
the fetched earcut source after configuring. The static library that all of
these releases link was built at the app commit
`5f33278c658f56618a1e0b503dd1da6d6707eece`, before the first release of this
range, from these same three files. Those patch files are not part of this
repository, so their SHA-256 values are recorded here. Each web-ifc patch file
is one commit here, applied unchanged with `git apply` in the same order. The
earcut patch file is published as
[`earcut-4811a2b.patch`](earcut-4811a2b.patch): everything from its first
`diff --git` line on is byte-identical to the released file, and only the
explanatory preamble above that line was rewritten.

| Released patch file | SHA-256 of the released file | Published here as |
| --- | --- | --- |
| `web-ifc-61384fe6-cooperative-cancel-and-winding-ub.patch` | `5729ceb400d30429ecd54a52faf86345641134161c291949f8006fda549f1d66` | commit 1 below |
| `web-ifc-61384fe6-repmap-memo.patch` | `ec7ed52c62b43763a367ad8de1b8deab42e86d4346b15691c70fdd663aef48ce` | commit 2 below |
| `earcut-4811a2b-cooperative-cancel.patch` | `89d14e03ac913b684b55a4debc61b2345cdb14f1dfa1a4e4078dae6d1ed04465` | `earcut-4811a2b.patch` (same hunks, rewritten preamble) |

## Modifications in `ifc-canvas-1.3.0`

Both commits change C++ geometry sources under `src/cpp/web-ifc/geometry/`
only. Labels such as `roadmap 46` and `parse-01` in their source comments
are IFC Canvas's own tracking labels and have no public counterpart.

1. `8970df68b8bf770d3c79ddaa5c7e52a80acfb4db` IFC Canvas: add cooperative meshing cancellation hook

   Add a cooperative cancellation hook to IfcGeometryProcessor, so a caller can abort an element whose meshing does not finish (time budget or cancel). The new header IfcCancellation.h provides a thread-local predicate, a CheckCancellation() check and a MeshingCancelled exception; the predicate set by SetCancellationCheck() is armed for each GetFlatMesh() call and checked at its entry and at the outer loops of the fuzzybools boolean pipeline (earcut's loops are hooked separately, see item 3). IfcPlacedGeometry::transformation is now initialised to identity.

2. `a543ef8da61d2a80ef1a7f7e51d843c3092c70f6` IFC Canvas: memoise composed meshes per IfcRepresentationMap

   Memoise the composed mesh tree of each IfcRepresentationMap between Clear() calls, so repeated IfcMappedItem instances of one map reuse its tessellated leaves instead of re-meshing them. A hit is validated against the geometry cache and against leaves rewritten by boolean operations, and the memo is bypassed in every boolean or opening (void) context. Winding reversal is idempotent (IfcGeometry::reversed), so output equals a full recompute. SetRepresentationMapMemoEnabled(false) disables the memo.

3. [`earcut-4811a2b.patch`](earcut-4811a2b.patch), a patch to mapbox/earcut.hpp

   earcut.hpp is not part of this repository: web-ifc's CMake build fetches it
   with FetchContent at commit `4811a2b69b91f6127a75e780de6e2113609ddabb`, so
   the change cannot be a commit here. The patch adds three cooperative
   cancellation checks that call `webifc::geometry::CheckCancellation()` (at
   the entry of `earcutLinked()`, and every 1024 iterations of its
   ear-slicing loop and of the `cureLocalIntersections()` walk), so a
   per-element time budget can abort a triangulation that does not
   terminate. Applied to earcut.hpp at `4811a2b` it gives git blob
   `e87540bd4c5376d6d54b3b1229684df996a4314b`, the same file that IFC Canvas
   0.96.4 to 1.1.24 produced with an equivalent inline transform.

4. [`web-ifc-0.0.77-api-iife.patch`](web-ifc-0.0.77-api-iife.patch), a change to the web-ifc JavaScript API

   Besides the static library, every IFC Canvas release from 0.1.0 to 1.4.0
   bundles the JavaScript API and the WebAssembly module of the npm package
   `web-ifc@0.0.77` for its embedded web viewer: `web-ifc-api-iife.js` and
   `web-ifc.wasm`. `web-ifc-api-iife.js` carries one IFC Canvas change, made
   directly in that generated bundle, so its diff against the npm file is the
   Source Code Form of the change: in `IfcAPI.Init()`, the options passed to
   the Emscripten module factory are built as a local `moduleConfig`, and
   when `globalThis.__webIfcWasmBinary` is set it is passed as the standard
   Emscripten `wasmBinary` option, so the app can hand over the bytes of
   `web-ifc.wasm` itself instead of having the module fetch the file. When
   the global is not set, behaviour is identical to upstream. The patch
   header records the SHA-256 of the npm file and of the patched file. The
   patched file has shipped since commit
   `03df42c4648ad9643332b620dd2da7e34eb7b7f4` of the private app repository
   (2026-05-16, still 0.1.0, build 1) and has not changed since, so this one
   patch covers every release this tag lists; the initial 0.1.0 baseline
   commit `4b95c28a0e4c999c431a96fe13219d0fda5cecd6` bundled the unmodified
   npm file.

   `web-ifc.wasm` is shipped unmodified: it is byte-identical to
   `web-ifc.wasm` of the npm package `web-ifc@0.0.77` (SHA-256
   `392b547232aa63df84961d9d3d6e2a7a259cd832b888830cab2ee30778bf28a0`).
   The npm registry records upstream commit
   `f26c4beef0a668ebdb180d2b95a94097a1e21cef` (tag `0.77`) as the `gitHead`
   of `web-ifc@0.0.77`, so the Source Code Form of the unmodified
   `web-ifc.wasm` and of the unmodified rest of `web-ifc-api-iife.js` is
   upstream web-ifc at that commit.

No other dependency is modified. IFC Canvas changes only earcut.hpp; all
other FetchContent dependencies, including CDT (artem-ogre/CDT, MPL-2.0), are
used unmodified at the commits pinned in `src/cpp/CMakeLists.txt`, so the
Source Code Form of each of them is its upstream repository at that commit.

## Reproducing the source and the build

```sh
git clone https://github.com/alesdev88/web-ifc.git
cd web-ifc
git checkout ifc-canvas-1.3.0
git log --oneline 61384fe61da64feebdd49eb3d319971e0b4bff81..ifc-canvas-1.3.0   # the modifications
git diff 61384fe61da64feebdd49eb3d319971e0b4bff81 ifc-canvas-1.3.0 -- src       # the full source diff
```

The patches are the commits: `git format-patch
61384fe61da64feebdd49eb3d319971e0b4bff81..ifc-canvas-1.3.0 -- src` exports
them as patch files.

IFC Canvas compiles web-ifc as an iOS static library with CMake, once per SDK
(`iphoneos` and `iphonesimulator`, arm64, Release), building only the
`web-ifc-library` target. Requirements: CMake 3.18 or later (the minimum that
`src/cpp/CMakeLists.txt` declares at this revision), Xcode with the iOS SDKs,
git, and network access at configure time (FetchContent downloads the
dependencies). The earcut patch is applied after configuring (FetchContent
has fetched earcut.hpp by then) and before building:

```sh
cmake -S src/cpp -B build-ios \
  -DCMAKE_SYSTEM_NAME=iOS -DCMAKE_OSX_ARCHITECTURES=arm64 \
  -DCMAKE_OSX_DEPLOYMENT_TARGET=26.0 -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_OSX_SYSROOT=iphoneos
git -C build-ios/_deps/earcut-src apply "$PWD/ifc-canvas/earcut-4811a2b.patch"
cmake --build build-ios --config Release --target web-ifc-library
```

The JavaScript API file is reproduced from the npm package:

```sh
curl -LO https://registry.npmjs.org/web-ifc/-/web-ifc-0.0.77.tgz
tar -xzf web-ifc-0.0.77.tgz
cd package && patch -p1 < /path/to/ifc-canvas/web-ifc-0.0.77-api-iife.patch
```

## Licenses

- web-ifc and the IFC Canvas modifications to it (the two commits listed
  above, which change files under `src/`, and
  `web-ifc-0.0.77-api-iife.patch`): Mozilla Public License 2.0 (see
  [LICENSE.md](../LICENSE.md)); the upstream license is unchanged.
- earcut.hpp (Mapbox) and `earcut-4811a2b.patch`, the IFC Canvas
  modification to it: ISC License (see
  [LICENSE-earcut-ISC.txt](LICENSE-earcut-ISC.txt), the license file of
  earcut.hpp at `4811a2b`).
- The other FetchContent dependencies are used unmodified under their own
  licenses, among them CDT (MPL-2.0), whose Source Code Form is upstream
  artem-ogre/CDT at commit `5a1d702a01b24b33555913b90934fe673d51fc0f`.

## Contact

IFC Canvas support: https://ifccanvas.app/support
