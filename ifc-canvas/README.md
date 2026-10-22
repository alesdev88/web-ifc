# IFC Canvas modifications to web-ifc: IFC Canvas 0.96.4 to 1.1.24

This repository is a fork of [ThatOpen web-ifc](https://github.com/ThatOpen/engine_web-ifc).
Tag `ifc-canvas-1.1.24` is the Source Code Form of the MPL-2.0 Covered
Software (web-ifc) as modified by IFC Canvas, an iPad app for viewing IFC
building models by Aleš Dolenec, for every IFC Canvas release from 0.96.4 to
1.1.24. These releases compile web-ifc's C++ geometry kernel into the app as a
static library, and all of them link the same library; every modification it
contains is published here, as commits on top of the upstream revision it is
based on.

- Tag `ifc-canvas-1.1.24` (this tree): the web-ifc source of IFC Canvas 0.96.4
  to 1.1.24.
- Branch `ifc-canvas`: the current IFC Canvas modifications. Its
  `ifc-canvas/README.md` has the complete table of IFC Canvas releases and the
  tag that holds the source of each. The commits of this tag are not on that
  branch, because they are based on an older upstream revision.

## Releases covered by this tag

| IFC Canvas releases | Builds | IFC Canvas release commits (private app repository) | Source |
| --- | --- | --- | --- |
| 0.96.4 to 1.1.24 | 268 to 403 | `f4caef78825a0e033bfb4b16ebb7e686c051e5a4` (0.96.4) to `180fff158b9ad3440cc2f62892861f986c7cdfbe` (1.1.24) | upstream `f26c4beef0a668ebdb180d2b95a94097a1e21cef` (tag `0.77`) + the 2 commits below + the earcut patch below |

Every version and build number in this range: 0.96.4 (build 268),
0.96.5 (build 269), 0.97.0 (build 270), 0.97.1 (build 271), 0.98.0 (build 272),
0.98.1 (build 273), 0.98.2 (build 274), 0.98.3 (build 275), 0.99.0 (build 275),
0.99.1 (build 276), 0.99.2 (build 277), 0.99.3 (build 278), 0.99.4 (build 279),
0.99.5 (build 280), 0.99.6 (build 281), 0.99.7 (build 282),
0.99.8 (build 283, reserved), 0.99.9 (build 284, reserved),
0.99.10 (build 285), 0.99.11 (build 286), 0.99.12 (build 287),
0.99.13 (build 288), 0.99.14 (build 289), 0.99.15 (build 290),
0.99.16 (build 291), 0.99.17 (build 292), 0.99.18 (build 293),
0.99.19 (build 294), 0.99.20 (build 295), 0.99.21 (build 296),
0.99.22 (build 297), 0.99.23 (build 298), 0.99.24 (build 299),
0.99.25 (build 300), 0.99.26 (build 301), 0.99.27 (build 302),
0.99.28 (build 303), 0.99.29 (build 304), 0.99.30 (build 305),
0.99.31 (build 306), 0.99.32 (build 307), 0.99.33 (build 308),
0.99.34 (build 309), 0.99.35 (build 310), 0.99.36 (build 311),
0.99.37 (build 312), 0.99.38 (build 313), 0.99.39 (build 314),
0.99.40 (build 315), 0.100.0 (build 316), 0.100.1 (build 317),
0.101.0 (build 318), 0.101.1 (build 319, reserved), 0.101.2 (build 320),
0.101.3 (build 321), 0.101.4 (build 322), 0.101.5 (build 323),
0.101.6 (build 324), 0.101.7 (build 325), 0.101.8 (build 326),
0.101.9 (build 327), 0.101.10 (build 328), 0.101.11 (build 329),
0.101.12 (build 330), 0.101.13 (build 331), 0.101.14 (build 332),
0.101.15 (build 333), 0.101.16 (build 334), 0.101.17 (build 335),
0.101.18 (build 336), 0.102.0 (build 337), 0.102.1 (build 338),
0.102.2 (build 339), 0.102.3 (build 340), 0.102.4 (build 341),
0.103.0 (build 342), 0.103.1 (build 343), 0.103.2 (build 344),
0.103.3 (build 345), 0.104.0 (build 346), 0.104.1 (build 347),
0.105.0 (build 348), 0.105.1 (build 349), 0.105.2 (build 350),
0.105.3 (build 351), 1.0.0 (build 352), 1.0.1 (build 353), 1.0.2 (build 354),
1.0.3 (build 355), 1.0.4 (build 356), 1.0.5 (build 357), 1.0.6 (build 358),
1.0.7 (build 359), 1.0.8 (build 360), 1.0.9 (build 361), 1.0.10 (build 362),
1.0.11 (build 363), 1.0.12 (build 364), 1.0.13 (build 365), 1.1.0 (build 366),
1.1.1 (builds 367-369), 1.1.2 (build 370), 1.1.3 (build 371),
1.1.4 (build 372), 1.1.5 (build 373), 1.1.6 (build 374), 1.1.7 (build 375),
1.1.8 (builds 376, 377), 1.1.9 (build 378), 1.1.10 (build 379),
1.1.11 (build 380), 1.1.12 (build 381), 1.1.13 (build 382),
1.1.14 (build 383), 1.1.15 (build 384), 1.1.16 (build 385),
1.1.17 (build 386), 1.1.18 (build 387), 1.1.19 (build 388),
1.1.20 (build 389), 1.1.21 (builds 390-397, 399, 400, 402),
1.1.22 (build 398), 1.1.23 (build 401), 1.1.24 (build 403).
Every build number from 268 to 403 is listed.

Builds 283, 284 and 319 are the numbers that the app's version notes reserve
for 0.99.8, 0.99.9 and 0.101.1, but no commit ever set them: the changes of
0.99.8 and 0.99.9 were committed with 0.99.10 (build 285), and those of
0.101.1 with 0.101.2 (build 320). The static library is the same at the
commits on both sides of these numbers (builds 282 and 285, 318 and 320), so
any binary that carried one of them links the same static library as the
releases of this tag.

### Provenance of `ifc-canvas-1.1.24`

The IFC Canvas release commits are commits of the IFC Canvas app repository,
not of this one. That repository is private, so the app commit ids in this
file cannot be resolved publicly; they are recorded only as provenance
anchors. At each release commit, web-ifc is pinned to upstream
`f26c4beef0a668ebdb180d2b95a94097a1e21cef` (tag `0.77`), and the app's build
script (`Scripts/build_webifc.sh`, a file of that private repository) applies
the web-ifc patch file listed below with `git apply` before configuring, and
after configuring changes the fetched `mapbox/earcut.hpp` with four `perl`
substitutions. That patch file is not part of this repository, so its SHA-256
is recorded here.

The static library that all of these releases link was built at the app
commit `ddda3d735bb474acc22880bc9d61d5598284d5c5`, before the first release of
this range. The patch file it was built from was then replaced by a revision
that differs from it only in `//` comment lines, and that revision is the one
every release commit of the range carries. Both revisions are published, as
two commits, each made with `git apply` of the released file as the build
script applies it:

| Released patch file | SHA-256 of the released file | Published here as |
| --- | --- | --- |
| `web-ifc-0.77-cooperative-cancel-and-winding-ub.patch`, the revision the static library was built from | `d1ff2287f5f67429a683066355516e3da104004104179eaefd0c388c88e27871` | commit 1 below |
| `web-ifc-0.77-cooperative-cancel-and-winding-ub.patch`, the revision every release commit 0.96.4 to 1.1.24 carries | `7d1cf0041875c33ff567ae20d2d750f405493e006df34ffff27f892ce8da2ac4` | commit 2 below (its tree is upstream `f26c4bee` plus this revision alone) |
| none: four `perl` substitutions in `Scripts/build_webifc.sh` | | [`earcut-4811a2b.patch`](earcut-4811a2b.patch), generated from them (item 3 below) |

## Modifications in `ifc-canvas-1.1.24`

Both commits change C++ geometry sources under `src/cpp/web-ifc/geometry/`
only.

1. `05ab8e0c333e63c4423e64b986372c48aa84d8c0` IFC Canvas: add cooperative meshing cancellation hook

   Add a cooperative cancellation hook to IfcGeometryProcessor, so a caller can abort an element whose meshing does not finish (time budget or cancel). The new header IfcCancellation.h provides a thread-local predicate, a CheckCancellation() check and a MeshingCancelled exception; the predicate set by SetCancellationCheck() is armed for each GetFlatMesh() call and checked at its entry and at the outer loops of the fuzzybools boolean pipeline. IfcPlacedGeometry::transformation is now initialised to identity. This is the revision of the patch file that the static library was compiled from.

2. `4721e4550e2319fe723fd9768671814e4d2e7c2e` IFC Canvas: revise the comments of the cancellation hook

   Comment-only revision of the previous commit; no code line changes. The comments now record that the long-running loops observed in practice are mapbox/earcut's ear-clipping loops, which the build hooks separately (item 3), and that the fuzzybools checks are defensive. This revision of the patch file replaced the previous one and is the file every release commit of IFC Canvas 0.96.4 to 1.1.24 carries; the static library was not rebuilt for it.

3. [`earcut-4811a2b.patch`](earcut-4811a2b.patch), a change to mapbox/earcut.hpp

   earcut.hpp is not part of this repository: web-ifc's CMake build fetches it
   with FetchContent at commit `4811a2b69b91f6127a75e780de6e2113609ddabb`, so
   the change cannot be a commit here. It adds three cooperative cancellation
   checks that call `webifc::geometry::CheckCancellation()` (at the entry of
   `earcutLinked()`, and every 1024 iterations of its ear-slicing loop and of
   the `cureLocalIntersections()` walk), so a per-element time budget can
   abort a triangulation that does not terminate.

   In these releases the build script made the change without a patch file,
   with these four substitutions on `include/mapbox/earcut.hpp` of the fetched
   earcut source, run after configuring and before building:

   ```sh
   perl -0777 -pi -e 's/\nnamespace mapbox \{/\n#include <web-ifc\/geometry\/IfcCancellation.h>\n\nnamespace mapbox {/' "$hpp"
   perl -0777 -pi -e 's/(Earcut<N>::earcutLinked\(Node\* ear, int pass\) \{\n\s*if \(!ear\) return;\n)/$1    ::webifc::geometry::CheckCancellation();\n/' "$hpp"
   perl -0777 -pi -e 's/(while \(ear->prev != ear->next\) \{\n\s*iterations\+\+;\n)/$1        if ((iterations & 1023) == 0) ::webifc::geometry::CheckCancellation();\n/' "$hpp"
   perl -0777 -pi -e 's/(Earcut<N>::cureLocalIntersections\(Node\* start\) \{\n\s*Node\* p = start;\n)(\s*do \{\n)/${1}    unsigned long long _webifcCancelIt = 0;\n$2        if ((++_webifcCancelIt & 1023) == 0) ::webifc::geometry::CheckCancellation();\n/' "$hpp"
   ```

   `earcut-4811a2b.patch` was generated by running these four lines unchanged
   on earcut.hpp at `4811a2b` and diffing the result against the unmodified
   file. Applying it to that file (with `git apply` or `patch -p1`)
   reproduces their output byte for byte (git blob
   `e87540bd4c5376d6d54b3b1229684df996a4314b`). IFC Canvas 1.2.0 to 1.3.0
   apply the same change from a patch file, with the same result.

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
git checkout ifc-canvas-1.1.24
git log --oneline f26c4beef0a668ebdb180d2b95a94097a1e21cef..ifc-canvas-1.1.24   # the modifications
git diff f26c4beef0a668ebdb180d2b95a94097a1e21cef ifc-canvas-1.1.24 -- src       # the full source diff
```

Commit 1 (`05ab8e0c333e63c4423e64b986372c48aa84d8c0`) is the source exactly as
the static library was compiled; it differs from the tag only in `//` comment
lines, in the README banner and in `ifc-canvas/`.

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
  artem-ogre/CDT at commit `4d0c9026b8ec846fe544897e7111f8f9080d5f8a`.

## Contact

IFC Canvas support: https://ifccanvas.app/support
