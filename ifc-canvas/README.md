# IFC Canvas modifications to web-ifc

This repository is a fork of [ThatOpen web-ifc](https://github.com/ThatOpen/engine_web-ifc).
It is the Source Code Form of the MPL-2.0 Covered Software (web-ifc) as
modified by IFC Canvas, an iPad app for viewing IFC building models by
Aleš Dolenec. IFC Canvas compiles web-ifc's C++ geometry kernel into the app
as a static library; every modification it ships is published here, as
commits on top of the upstream revision it is based on.

- Branch `ifc-canvas`: upstream web-ifc plus the current IFC Canvas
  modifications.
- Tag `ifc-canvas-<version>`: the exact web-ifc source of the IFC Canvas
  releases listed for it in the table below, which all link the same
  static library. A tag is named after the last release it covered when
  it was cut: `ifc-canvas-1.5.0` also covers 1.5.1, which links the same
  kernel. The tags for releases before 1.4.0 are based
  on older upstream revisions, so their commits are not on branch
  `ifc-canvas`.

## Releases and internal test builds

Every IFC Canvas release and every internal test build number known to carry
each kernel, with the web-ifc source it contains:

| IFC Canvas versions | Builds | web-ifc C++ kernel compiled into the app | Kernel source | web-ifc JavaScript API and WebAssembly module |
| --- | --- | --- | --- | --- |
| 0.1.0 to 0.96.2 | 1 to 266 (266: see the notes below) | none in any release | nothing to publish | modified, except in the first 0.1.0 commit (see below): [`web-ifc-0.0.77-api-iife.patch`](web-ifc-0.0.77-api-iife.patch); `web-ifc.wasm` unmodified |
| 0.96.3 | 267 | upstream web-ifc `f26c4beef0a668ebdb180d2b95a94097a1e21cef` (tag `0.77`), **unmodified**, with earcut.hpp `4811a2b69b91f6127a75e780de6e2113609ddabb`, **unmodified** (see the notes below) | no tag: the upstream source at those commits | modified: [`web-ifc-0.0.77-api-iife.patch`](web-ifc-0.0.77-api-iife.patch); `web-ifc.wasm` unmodified |
| 0.96.4 to 1.1.24 | 268 to 403 | upstream `f26c4beef0a668ebdb180d2b95a94097a1e21cef` (tag `0.77`), modified | tag `ifc-canvas-1.1.24` | modified: [`web-ifc-0.0.77-api-iife.patch`](web-ifc-0.0.77-api-iife.patch); `web-ifc.wasm` unmodified |
| 1.2.0 to 1.3.0 | 404 to 443 (406: internal test build, not distributed, see the notes below) | upstream `61384fe61da64feebdd49eb3d319971e0b4bff81`, modified | tag `ifc-canvas-1.3.0` | modified: [`web-ifc-0.0.77-api-iife.patch`](web-ifc-0.0.77-api-iife.patch); `web-ifc.wasm` unmodified |
| 1.4.0 | 444; also 445 and 446 (internal test builds, not distributed) | upstream `e408b65471a6c61569f8a6634df494420ddd3bfc`, modified | tag `ifc-canvas-1.4.0` | modified: [`web-ifc-0.0.77-api-iife.patch`](web-ifc-0.0.77-api-iife.patch); `web-ifc.wasm` unmodified |
| 1.5.0 and 1.5.1 | 448 and 449 | upstream `e408b65471a6c61569f8a6634df494420ddd3bfc`, modified: the 1.4.0 modifications plus three more (see [Modifications in `ifc-canvas-1.5.0`](#modifications-in-ifc-canvas-150)) | tag `ifc-canvas-1.5.0` | modified: [`web-ifc-0.0.77-api-iife.patch`](web-ifc-0.0.77-api-iife.patch); `web-ifc.wasm` unmodified |

Every release, from 0.1.0 (build 1) to 1.5.1, bundles the JavaScript API
`web-ifc-api-iife.js` and the WebAssembly module `web-ifc.wasm` of the npm
package `web-ifc@0.0.77`. The JavaScript API carries one IFC Canvas change
(item 6 below). The patched file has shipped since commit
`03df42c4648ad9643332b620dd2da7e34eb7b7f4` of the private app repository
(2026-05-16, still 0.1.0, build 1) and has not changed since, so the one
patch covers every later build, and each tag includes it; the initial 0.1.0
baseline commit `4b95c28a0e4c999c431a96fe13219d0fda5cecd6` bundled the
unmodified npm file. `web-ifc.wasm` is the unmodified npm file in every
release.

Notes on the table:

- Build 266: the 0.96.2 release commit links no kernel. The four later
  commits of the private app repository that still carry build 266, from
  `2e8f9e5019121a5e98952228df24cfd5ab5e7c48` on, contain the same unmodified
  static library as 0.96.3 (next note), and the app links it from
  `35958be8f91d6190a377c0342d852843dedd69f1` on. A test build made from them, such
  as the Debug build that ran a memory probe on the developer's own test
  iPad on 2026-07-08, before the change to build 267, therefore carried
  upstream web-ifc `f26c4beef0a668ebdb180d2b95a94097a1e21cef` and
  earcut.hpp `4811a2b69b91f6127a75e780de6e2113609ddabb`, both unmodified:
  nothing to publish.
- 0.96.3 (build 267): release commit
  `5687f0a07504ee55428806052e72bda965fab8f4` of the private app repository.
  The static library it links was built and committed at app commit
  `2e8f9e5019121a5e98952228df24cfd5ab5e7c48` and is unchanged at the release
  commit: `libWebIFC.a` SHA-256
  `b00062e05730178f71b4ff64c77d88883739f9d26c1696b7e159307dd4022190`
  (ios-arm64) and
  `74e49f832ca2cca6d3c2b4b22eb9a73ba466fad26e4f803e7227d00d24bc5a64`
  (ios-arm64-simulator). The app's build script, the same file at both
  commits, applies no patch and runs no source edit. Of the later app
  commits that still carry build 267, the last three (from app commit
  `ddda3d735bb474acc22880bc9d61d5598284d5c5` on) instead link the modified
  static library built at that commit, which 0.96.4 (build 268) also
  links; its source is commit `05ab8e0c333e63c4423e64b986372c48aa84d8c0` of
  tag `ifc-canvas-1.1.24` plus that tag's `earcut-4811a2b.patch`.
- Build 406 was an internal test build, not distributed: the 1.2.0 (build
  405) app tree, installed only on the developer's own test iPad on
  2026-09-20. Its kernel source is in this repository either way, as the
  app's records leave open which of the two it was: tag `ifc-canvas-1.3.0`,
  or that tag's commit `8970df68b8bf770d3c79ddaa5c7e52a80acfb4db` plus its
  `earcut-4811a2b.patch`. It was compiled with the extra flag
  `-ffp-contract=off`, which changes no source.
- Builds 445 and 446 were internal test builds, not distributed: the 1.4.0
  app tree plus a viewer fix, with the same kernel as build 444.

Every IFC Canvas release and every internal test build number known to carry
a kernel built from that tag's source, per tag:

- `ifc-canvas-1.1.24`: 0.96.4 (build 268), 0.96.5 (build 269), 0.97.0 (build 270),
  0.97.1 (build 271), 0.98.0 (build 272), 0.98.1 (build 273), 0.98.2 (build 274),
  0.98.3 (build 275), 0.99.0 (build 275), 0.99.1 (build 276), 0.99.2 (build 277),
  0.99.3 (build 278), 0.99.4 (build 279), 0.99.5 (build 280), 0.99.6 (build 281),
  0.99.7 (build 282), 0.99.8 (build 283, reserved), 0.99.9 (build 284, reserved),
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
- `ifc-canvas-1.3.0`: 1.2.0 (builds 404, 405; and 406, an internal test build,
  not distributed), 1.2.1 (build 407),
  1.2.2 (builds 408-410), 1.2.3 (builds 411, 415), 1.2.4 (build 412),
  1.2.5 (builds 413, 414, 416-419), 1.2.6 (builds 420-424),
  1.2.7 (builds 425-429), 1.2.8 (builds 430-435), 1.2.9 (builds 436-439),
  1.2.10 (builds 440-442), 1.3.0 (build 443).
- `ifc-canvas-1.4.0`: 1.4.0 (build 444; and 445 and 446, internal test builds,
  not distributed).
- `ifc-canvas-1.5.0`: 1.5.0 (build 448), 1.5.1 (build 449).

Builds 283, 284 and 319 are the numbers that the app's version notes reserve
for 0.99.8, 0.99.9 and 0.101.1, but no commit ever set them: the changes of
0.99.8 and 0.99.9 were committed with 0.99.10 (build 285), and those of
0.101.1 with 0.101.2 (build 320). The static library is the same at the
commits on both sides of these numbers (builds 282 and 285, 318 and 320), so
any binary that carried one of them links the same static library as the
releases of tag `ifc-canvas-1.1.24`. Together the lists of
`ifc-canvas-1.1.24`, `ifc-canvas-1.3.0` and `ifc-canvas-1.4.0` account for
every build number from 268 to 446. The `ifc-canvas/README.md` of each tag
describes that tag's modifications and how it was derived from the released
patch files.

| Tag | Upstream base | IFC Canvas release commits (private app repository) |
| --- | --- | --- |
| `ifc-canvas-1.1.24` | `f26c4beef0a668ebdb180d2b95a94097a1e21cef` (tag `0.77`) | `f4caef78825a0e033bfb4b16ebb7e686c051e5a4` (0.96.4) to `180fff158b9ad3440cc2f62892861f986c7cdfbe` (1.1.24) |
| `ifc-canvas-1.3.0` | `61384fe61da64feebdd49eb3d319971e0b4bff81` | `731fc98a361e6973b585091c6bca68f42b4c1101` (1.2.0) to `ea288bb4c7f115652e8ae347b5c9292a948111e9` (1.3.0) |
| `ifc-canvas-1.4.0` | `e408b65471a6c61569f8a6634df494420ddd3bfc` | `97d429134a5821e5aceb3020693c6b3bf7e8147c` (1.4.0) |
| `ifc-canvas-1.5.0` | `e408b65471a6c61569f8a6634df494420ddd3bfc` | `bd67e84b6580330537f756172c7baa966c8cf58e` (1.5.0), `d9059c8d72a61d11e7cc6eb59b7e63aa39ef5dc0` (1.5.1) |

### Provenance of `ifc-canvas-1.4.0`

The IFC Canvas release commit is a commit of the IFC Canvas app repository,
not of this one. That repository is private, so the app commit ids in this
file cannot be resolved publicly; they are recorded only as provenance
anchors. At the release commit, web-ifc is pinned to upstream
`e408b65471a6c61569f8a6634df494420ddd3bfc`, and the app's build script
(`Scripts/build_webifc.sh`, a file of that private repository) applies the
five patch files listed below with `git apply` before compiling. Those patch
files are not part of this repository, so their SHA-256 values are recorded
here. Each web-ifc patch file is one commit on `ifc-canvas`, applied unchanged
with `git apply` in the same order. The earcut patch file is published as
[`earcut-c68c8835.patch`](earcut-c68c8835.patch): everything from its first
`diff --git` line on is byte-identical to the released file, and only the
explanatory preamble above that line was rewritten.

| Released patch file | SHA-256 of the released file | Published here as |
| --- | --- | --- |
| `web-ifc-e408b654-01-cooperative-cancel-and-winding-ub.patch` | `13bf7c4fa2848ad30204d973774ac705fb6625f49e839cc47ece5713aef97686` | commit 1 below |
| `web-ifc-e408b654-02-repmap-memo.patch` | `d3380ecc01c0ee92910ca2e1594f345bd7a7f6601d031e88cf648ce1bb82f735` | commit 2 below |
| `web-ifc-e408b654-03-boolean-cycle-guard.patch` | `df808aa9edbe83366e97a24662d63935b13bf4aeffecabae980844ac7cb8f331` | commit 3 below |
| `web-ifc-e408b654-04-swept-disk-indexed-emission.patch` | `873298b467e9bbbba428630dcd383042ce0bacedea473616b8103375b53f65c6` | commit 4 below |
| `earcut-c68c8835-cooperative-cancel-and-nan-sort.patch` | `da8b0662b43fc5e1367083a2dd90c162ea7f0cfb7c5de37f83a234f3c42d4cb9` | `earcut-c68c8835.patch` (same hunks, rewritten preamble) |

## Modifications in `ifc-canvas-1.4.0`

All four commits change C++ geometry sources under `src/cpp/web-ifc/geometry/`
only. The JavaScript API that the app bundles is changed separately, see
item 6. Labels such as `roadmap 46` and `parse-01` in their source comments
are IFC Canvas's own tracking labels and have no public counterpart.

1. `2344afd17f81df660bf52385ea049c58c247c99c` IFC Canvas: add cooperative meshing cancellation hook

   Add a cooperative cancellation hook to IfcGeometryProcessor. The new header IfcCancellation.h provides a thread-local predicate, a CheckCancellation() check and a MeshingCancelled exception. SetCancellationCheck() installs the predicate; it is armed for each GetFlatMesh() call and checked at its entry and at the outer loops of the fuzzybools boolean pipeline, so a caller can abort an element that does not finish (time budget or document cancel). BoolProcess rethrows MeshingCancelled instead of treating it as a CSG failure, and IfcPlacedGeometry::transformation is now initialised to identity.

2. `a877512d898ca633d8bf4c58cd80a0e150f306d1` IFC Canvas: memoise composed meshes per IfcRepresentationMap

   Memoise the composed mesh tree of each IfcRepresentationMap between Clear() calls, so repeated IfcMappedItem instances of one map reuse its tessellated leaves instead of re-meshing them. A hit is validated against the geometry cache and against leaves rewritten by boolean operations; the memo is bypassed in every boolean or opening (void) context, and mapped items always recompute through GetMeshUncached, so it never stacks on upstream's mapped-representation cache. Winding reversal is idempotent (IfcGeometry::reversed), so output equals a full recompute. SetRepresentationMapMemoEnabled(false) disables the memo.

3. `3f70c6cf4c26c860d11c2ff7c1cf8c01e1726c99` IFC Canvas: guard boolean operand recursion against cycles

   Bound the operand recursion of IfcBooleanClippingResult and IfcBooleanResult in GetMeshUncached. The boolean results currently being meshed are tracked in a set; a repeated id (a self- or mutually-referencing boolean) or a nesting depth of 4096 logs an error and yields an empty mesh. Each of the three DIFFERENCE-spine walks also stops at a repeated base id, so malformed cyclic input terminates instead of looping or recursing without bound. Well-formed input is meshed exactly as before.

4. `096304a7ae063d0f64cb24b2eaf0f1d88c785eb2` IFC Canvas: emit IfcSweptDiskSolid sweeps as indexed triangles

   Emit IfcSweptDiskSolid geometry (bimGeometry::SweepCircular) as indexed triangles. Each ring's vertices are added once with a radial normal and shared by the wall quads; cap vertices are added separately with the axial normal. The previous code added three new vertices for every triangle. Vertex positions are the same as before, so a position weld still closes the solid, now with far fewer emitted vertices and less memory. Triangles that the per-vertex AddFace path rejects as degenerate (computeSafeNormal at toleranceAddFace) are skipped the same way before indexing.

5. [`earcut-c68c8835.patch`](earcut-c68c8835.patch), a patch to mapbox/earcut.hpp

   earcut.hpp is not part of this repository: web-ifc's CMake build fetches it
   with FetchContent at commit `c68c8835ccff2b7532d31d8fa8dfcf398f629498`, so
   the change cannot be a commit here. The patch adds three cooperative
   cancellation checks that call `webifc::geometry::CheckCancellation()` (at
   the entry of `earcutLinked()`, and every 1024 iterations of its ear-slicing
   loop and of the `cureLocalIntersections()` walk), so a per-element time
   budget can abort a triangulation that does not terminate. It also folds in
   the `eliminateHoles()` hole-sort comparator of upstream earcut commit
   `c0c5ecb6bd1f43ad1f5b005e846221e524d9214d` ("Guard against degenerate edges
   (#134)"), which compares cross products instead of dividing by an edge
   length that can be zero, so `std::sort` never receives a NaN comparison.

6. [`web-ifc-0.0.77-api-iife.patch`](web-ifc-0.0.77-api-iife.patch), a change to the web-ifc JavaScript API

   Besides the static library, every IFC Canvas release from 0.1.0 to 1.5.1
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
   header records the SHA-256 of the npm file and of the patched file.

   `web-ifc.wasm` is shipped unmodified: it is byte-identical to
   `web-ifc.wasm` of the npm package `web-ifc@0.0.77` (SHA-256
   `392b547232aa63df84961d9d3d6e2a7a259cd832b888830cab2ee30778bf28a0`).
   The npm registry records upstream commit
   `f26c4beef0a668ebdb180d2b95a94097a1e21cef` (tag `0.77`) as the `gitHead`
   of `web-ifc@0.0.77`, so the Source Code Form of the unmodified
   `web-ifc.wasm` and of the unmodified rest of `web-ifc-api-iife.js` is
   upstream web-ifc at that commit.

No other dependency is modified. IFC Canvas patches only earcut.hpp; all
other FetchContent dependencies, including CDT (artem-ogre/CDT, MPL-2.0), are
used unmodified at the commits pinned in `src/cpp/CMakeLists.txt`, so the
Source Code Form of each of them is its upstream repository at that commit.

## Modifications in `ifc-canvas-1.5.0`

IFC Canvas 1.5.0 (build 448; tag `ifc-canvas-1.5.0`) compiles upstream
`e408b65471a6c61569f8a6634df494420ddd3bfc` with the IFC Canvas patches 01 to
07 and the same earcut patch as 1.4.0. Patches 01 to 04 are commits 1 to 4
above, unchanged. Patches 05 to 07 are the three commits below, each the
diff of one IFC Canvas patch file applied unchanged with `git apply` on top
of the patches before it, in the order in which the app's build script
applies them (01 to 07). Each SHA-256 identifies the IFC Canvas patch file,
whose explanatory preamble is not published; `git apply` reads only the
diff. The earcut patch file and the earcut pin
`c68c8835ccff2b7532d31d8fa8dfcf398f629498` are unchanged since 1.4.0, so
[`earcut-c68c8835.patch`](earcut-c68c8835.patch) (item 5) still applies as
published. Labels such as `D16` and `bug-287` in the source comments of these
commits are IFC Canvas's own tracking labels and have no public counterpart.

| IFC Canvas patch file | SHA-256 of the IFC Canvas patch file | Commit | What it changes |
| --- | --- | --- | --- |
| `web-ifc-e408b654-05-boolean-depth-bound.patch` | `04725903aadd806fcea0bbb8859ae721fb10547396afa70647dc144a515d18eb` | `ecb37d9a1ccddf129a4f050c818e84a9ea699bb4` | `GetMeshUncached` returns an empty mesh for a boolean result nested deeper than 1024 booleans, instead of recursing until the stack of the meshing thread overflows. |
| `web-ifc-e408b654-06-tokenizer-ifc4x3-tolerance.patch` | `62d78c674500ed20558358391a805669c6bb8107477995071689db83cea0864e` | `64bf2c56eee15620321cc5174263ecb5dd8fdbae` | Instead of failing the whole file, the tokenizer reads a quoted value that is not a valid STEP binary as one empty argument (`$`), skips a stray quote and counts each case (`IfcLoader::GetToleratedTokenCount()`), changing files under `src/cpp/web-ifc/parsing/` only. |
| `web-ifc-e408b654-07-empty-path-counters.patch` | `16fcd9801d6cfd64382f06f4a394e8f3d5fa2c62eb819fbf75963646d6caaf5d` | `8c1d4cf626cb3e6f35f7f777beb73ebac0f5d2de` | Thread-local counters in a new header, `IfcCanvasEmptyPathCounters.h`, record each time one of five upstream paths leaves a whole representation item empty without an error, without changing any geometry or control flow. |

IFC Canvas 1.5.0 (build 448) carries this kernel. Its release commit is
`bd67e84b6580330537f756172c7baa966c8cf58e` of the private app repository, a
provenance anchor only, like the other app commit ids in this file; at that
commit the app's build script applies the patch files 01 to 07 and the earcut
patch file, each with the SHA-256 recorded in this file. IFC Canvas 1.5.1
(build 449, release commit `d9059c8d72a61d11e7cc6eb59b7e63aa39ef5dc0`)
links the same kernel, built from the same patch files; its changes are
outside web-ifc.

## Reproducing the source and the build

```sh
git clone https://github.com/alesdev88/web-ifc.git
cd web-ifc
git checkout ifc-canvas-1.4.0
git log --oneline e408b65471a6c61569f8a6634df494420ddd3bfc..ifc-canvas-1.4.0   # the modifications
git diff e408b65471a6c61569f8a6634df494420ddd3bfc ifc-canvas-1.4.0 -- src       # the full source diff
```

The patches are the commits: `git format-patch
e408b65471a6c61569f8a6634df494420ddd3bfc..ifc-canvas-1.4.0 -- src` exports
them as patch files. For an earlier release, check out its tag from the table
above instead; its own `ifc-canvas/README.md` gives the matching commands.
For 1.5.0 and 1.5.1, use the tag `ifc-canvas-1.5.0` in place of
`ifc-canvas-1.4.0`; the upstream base is the same.

IFC Canvas compiles web-ifc as an iOS static library with CMake, once per SDK
(`iphoneos` and `iphonesimulator`, arm64, Release), building only the
`web-ifc-library` target. Requirements: CMake 3.28 or later (the minimum that
`src/cpp/CMakeLists.txt` declares), Xcode with the iOS SDKs, git, and network
access at configure time (FetchContent downloads the dependencies). The earcut
patch is applied after configuring (FetchContent has fetched earcut.hpp by
then) and before building:

```sh
cmake -S src/cpp -B build-ios \
  -DCMAKE_SYSTEM_NAME=iOS -DCMAKE_OSX_ARCHITECTURES=arm64 \
  -DCMAKE_OSX_DEPLOYMENT_TARGET=26.0 -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_OSX_SYSROOT=iphoneos -DBUILD_SHARED_LIBS=OFF
git -C build-ios/_deps/earcut-src apply "$PWD/ifc-canvas/earcut-c68c8835.patch"
cmake --build build-ios --config Release --target web-ifc-library
```

The JavaScript API file is reproduced from the npm package:

```sh
curl -LO https://registry.npmjs.org/web-ifc/-/web-ifc-0.0.77.tgz
tar -xzf web-ifc-0.0.77.tgz
cd package && patch -p1 < /path/to/ifc-canvas/web-ifc-0.0.77-api-iife.patch
```

### Reproducing the build of `ifc-canvas-1.5.0`

The kernel of IFC Canvas 1.5.0 is compiled so that no local path of the
source or of the build tree ends up in it: every translation unit gets
`-ffile-prefix-map=<build tree>=/webifc-build` and
`-ffile-prefix-map=<web-ifc source>=/webifc-src`, and the archive is written
by `libtool` with `ZERO_AR_DATE=1`. It is otherwise built as above: Release,
iOS deployment target 26.0, arm64, with Xcode 27.1 (27A9275) and the iOS SDK
27.1 (CMake 4.4.3). A rebuild from this source with the same toolchain, the
same flags and umask 022 (`libtool` records each member's file mode)
therefore reproduces the static library that IFC Canvas links for this
release byte for byte: `libWebIFC.a` SHA-256
`2faf149eb26f43a10c8daa6b6726808327edc23364f1c35ca7c68c565cfab3a5`
(ios-arm64) and
`4ce46f5336bc821db573d07bccaeb04c96664b78a67b6889bce253cfb17d93b7`
(ios-arm64-simulator). The device slice, from the root of this checkout (for
the simulator slice use `iphonesimulator` and a fresh build tree):

```sh
umask 022
SRC="$PWD"
B="$(dirname "$PWD")/webifc-build-ios"   # outside the checkout: the two maps must not nest
cmake -S src/cpp -B "$B" \
  -DCMAKE_SYSTEM_NAME=iOS -DCMAKE_OSX_ARCHITECTURES=arm64 \
  -DCMAKE_OSX_DEPLOYMENT_TARGET=26.0 -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_OSX_SYSROOT=iphoneos -DBUILD_SHARED_LIBS=OFF \
  -DCMAKE_INSTALL_PREFIX="$B/install" \
  -DCMAKE_CXX_FLAGS="-ffile-prefix-map=$B=/webifc-build -ffile-prefix-map=$SRC=/webifc-src"
git -C "$B/_deps/earcut-src" apply "$SRC/ifc-canvas/earcut-c68c8835.patch"
cmake --build "$B" --config Release --target web-ifc-library
cmake --install "$B" --config Release
ZERO_AR_DATE=1 libtool -static -o libWebIFC.a "$B/install/lib/libweb-ifc-library.a"
```

Use paths without spaces here (the IFC Canvas build script double-quotes
each map inside `CMAKE_CXX_FLAGS`), and if a path goes through a symbolic
link, also map its `pwd -P` spelling.

## Licenses

- web-ifc and the IFC Canvas modifications to it (the commits listed
  above, which change files under `src/`, and
  `web-ifc-0.0.77-api-iife.patch`): Mozilla Public License 2.0 (see
  [LICENSE.md](../LICENSE.md)); the upstream license is unchanged.
- earcut.hpp (Mapbox) and `earcut-c68c8835.patch`, the IFC Canvas
  modification to it: ISC License (see
  [LICENSE-earcut-ISC.txt](LICENSE-earcut-ISC.txt)).
- The other FetchContent dependencies are used unmodified under their own
  licenses, among them CDT (MPL-2.0), whose Source Code Form is upstream
  artem-ogre/CDT at commit `2068d015b9db3c92481e869b0c1f669b96a1d70a`.

## Contact

IFC Canvas support: https://ifccanvas.app/support
