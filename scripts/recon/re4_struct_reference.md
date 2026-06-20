# RE4 (re4_tweaks) engine struct reference for God Hand

**Purpose.** God Hand and Resident Evil 4 share engine lineage (Capcom
Production Studio 4, internally `bio4`). The community project
[re4_tweaks](https://github.com/nipkownix/re4_tweaks) has reverse-engineered a
large set of the RE4 engine's C++ structs. This document distills the structs
that correspond to God Hand's known engine classes, so they can **seed** God
Hand struct definitions while carving.

- **Source:** `re4_tweaks` `dllmain/SDK/`, commit
  `1dd35a42262e1f83613d43bd6ba2e9f88c4d69b2`, retrieved 2026-06-19.
- **Raw headers copied to:** `scripts/recon/re4_sdk_headers/` (external,
  third-party, **not** part of the God Hand build).

---

## ⚠️ Confidence / portability caveats (READ FIRST)

1. **RE4_tweaks targets the RE4 PC port, which is x86 (32-bit) here.** PS2 is
   also **32-bit**, so **pointer sizes match (4 bytes)** — this is the good
   news, and is why field offsets transfer surprisingly well.
2. **BUT the compilers differ.** RE4 PC = MSVC; God Hand PS2 = an EE GCC
   toolchain. Default struct **packing, vtable layout, base-class padding, and
   bitfield ordering can differ.** Treat every offset as a *hypothesis*.
3. **The RE4 structs themselves are reverse-engineered**, with several fields
   marked `TODO`, `_unk_`, `_mb_` ("maybe"), or guessed sizes (e.g. `cParts`
   carries a `// TODO: check size`). They are not authoritative even for RE4.
4. **God Hand is a *separate game*.** Classes were forked/extended; God Hand
   adds members RE4 never had, and vice-versa. RE4's `cParts` union, `cModel`
   tail, `cEm`, `cObjWep`, etc. are very likely to diverge.
5. **Some God Hand classes have no RE4 analogue here.** `cMotCamera`,
   `cPlCamera`, `cCollisionSolidManage`, `tagEFF_PARAM`, `cEsp`, `cSofdec`
   (struct) are **not** present in the re4_tweaks SDK. Only behavioral hooks
   exist for `cSofdec`. For the camera/motion split see the `MOTION_INFO` +
   `ATTACH_CAMERA` + `CAMERA`/`cCamera` discussion below.

### How to use this

These offsets are a **starting template**, not byte-truth. The God Hand decomp
is byte-exact: when you carve a function, the *instruction* load/store offsets
(e.g. `lwc1 $f0, 0xC4($s0)`) are ground truth. Use this doc to **guess a field
name/type for an offset you already see in the asm**, then confirm the struct
size and neighbouring fields against the real accesses. If an RE4 offset
contradicts a God Hand instruction, the **instruction wins**.

---

## Core math types

### `cVec` ⇐ RE4 `Vec` (aka `tagVec`, `Point3d`)

> **God Hand calls this `cVec`.** RE4 calls it `Vec`. **3 floats, size 0x0C.**
> Note: there is **no `w` component** in the engine's primary vector type — it
> is x/y/z only. (God Hand functions that look like they touch a 4th float are
> usually operating on a `Quaternion` or a matrix row, not `cVec`.)

```c
struct Vec {       // God Hand: cVec
    float x;       // 0x00
    float y;       // 0x04
    float z;       // 0x08
};                 // sizeof = 0x0C
```

Related: `SVEC { int16 x,y,z; }` size 0x06 (compressed vector).

### `cMatrix` ⇐ RE4 `Mtx` / `Mtx44`

> **God Hand calls this `cMatrix`.** RE4 uses two typedefs. The **primary
> engine matrix is 3×4 (3 rows of 4 floats = 0x30 bytes)** — a GameCube-style
> affine transform (rotation/scale in the 3×3 part + translation in the 4th
> column). The full 4×4 (0x40) is used mainly for projection.

```c
typedef float Mtx  [3][4];   // God Hand: cMatrix  -- sizeof = 0x30  (PRIMARY)
typedef float Mtx44[4][4];   //                    -- sizeof = 0x40  (projection)
typedef float ROMtx[4][3];   // "row-ordered"      -- sizeof = 0x30
```

This is the key thing to verify for God Hand's
`MtxInverse(cMatrix&, const cMatrix&)`, `MtxInitCoord`, etc.: a `cMatrix` is
almost certainly **0x30 bytes (3×4 floats)**, *not* 0x40, unless God Hand
specifically uses a projection matrix. Confirm by the stride between matrices
in arrays and the largest offset touched (`0x2C` = last element of a 3×4).

God Hand confirmed math symbols (from `config/symbol_addrs.txt`):
`MtxInitCoord`, `Quaternion_SetVectorRotation`, plus the carving target
`MtxInverse`. RE4 math free-functions (`gc_math.h`) that map by concept:
`MTXConcat(a,b,out)`, `MTXMultVec`, `MTXMultVecSR`, `VECAdd`, `VECScale`,
`VECSubtract`, `VECDotProduct`.

### `Quaternion` ⇐ RE4 `tagQuaternion`

> Confirmed present in God Hand (`Quaternion_SetVectorRotation`). **4 floats,
> size 0x10.**

```c
typedef struct tagQuaternion {   // God Hand: Quaternion
    float x;   // 0x00
    float y;   // 0x04
    float z;   // 0x08
    float w;   // 0x0C
} Quaternion;                    // sizeof = 0x10
```

---

## Object / scene-graph hierarchy

RE4's hierarchy is: `cUnit` → `cCoord` → (`cModel`, `cParts`) → `cEm`/`cObj`
→ … God Hand's `cModel`/`cParts`/`cObj`/`cCamera` strongly correspond. **The
exact offsets below are the single most useful part of this doc** because God
Hand reuses the same field names (`cModel_calcParts`, `cParts_setRotationOrder`,
`cObj_setId`, etc. exist verbatim in God Hand symbols).

### `cUnit` (base, has vtable) — size 0x0C

```c
class cUnit {
    /* vtable */            // 0x00  (virtual dtor + beginEvent + endEvent)
    uint32_t be_flag_4;     // 0x04  (UNIT_BE_FLAG bitmask; see enum below)
    cUnit*   pNext_8;       // 0x08
};                          // sizeof = 0x0C
```
`UNIT_BE_FLAG`: ALIVE=0x1, TRANS=0x2, MOVE=0x20, DEAD=0x200, DESTRUCT=0x400,
NO_SUSPEND=0x800, DISABLEMOTION=0x4000, … (full list in `cUnit.h`).

### `cCoord : cUnit` — size 0xC4  (transform node)

```c
class cCoord : public cUnit {       // base occupies 0x00..0x0C
    Mtx     mat_C;          // 0x0C  world matrix      (0x30)
    Mtx     l_mat_3C;       // 0x3C  local matrix      (0x30)
    cCoord* pParent_6C;     // 0x6C
    Vec     world_70;       // 0x70
    Vec     world_old_7C;   // 0x7C
    Vec     world_old2_88;  // 0x88
    Vec     pos_94;         // 0x94
    Vec     ang_A0;         // 0xA0
    Vec     scale_AC;       // 0xAC
    Vec     r_scale_B8;     // 0xB8
    /* virtual matUpdate() */
};                          // sizeof = 0xC4
```

### `cModel : cCoord` — size 0x324 (RE4)

The head of this class (through ~`pModelInfo_15C`) is the highest-value mapping;
the tail (`MOTION_INFO`, `cAtariInfo`, state) is the most likely to diverge in
God Hand. Key offsets:

```c
class cModel : public cCoord {     // cCoord occupies 0x00..0xC4
    Mtx       mtx_C4;            // 0xC4  (0x30)
    cParts*   childParts_F4;     // 0xF4  -- linked list head of parts
    uint32_t  guid_F8;           // 0xF8
    uint8_t   r_no_0_FC;         // 0xFC  routine selectors r0..r3
    uint8_t   r_no_1_FD;         // 0xFD
    uint8_t   r_no_2_FE;         // 0xFE
    uint8_t   r_no_3_FF;         // 0xFF
    uint8_t   id_100;            // 0x100
    uint8_t   type_101;          // 0x101
    uint8_t   nParts_102;        // 0x102
    uint8_t   alpha_omit_103;    // 0x103
    Vec       speed_104;         // 0x104
    Vec       pos_old_110;       // 0x110
    Vec       Wall_norm_11C;     // 0x11C
    Vec*      pFloor_norm_128;   // 0x128
    // ... shader/cullmode/refract bytes 0x12C..0x13B ...
    cModelInfo* pModelInfo_15C;  // 0x15C
    cModelInfo* pShadowModelInfo_160; // 0x160
    cLightInfo  LightInfo_164;   // 0x164 (0x74)
    MOTION_INFO Motion_1D8;      // 0x1D8 (0xD0)  <-- see below
    MOTION_INFO* pMotionB_2A8;   // 0x2A8
    int16_t*    pXFlip_2AC;      // 0x2AC
    uint32_t*   pDblJnt_2B0;     // 0x2B0
    cAtariInfo  atari_2B4;       // 0x2B4 (0x4C)  collision info
    Vec*        inscreen_pos_300;// 0x300
    uint32_t    pPath_304;       // 0x304
    FOOTSHADOW_TBL* pFsdTbl_308; // 0x308
    cModelState State_30C;       // 0x30C (0x10)
    // ... 0x31C..0x323 misc ...
    /* virtual move(); setNoSuspend(BOOL); */
};                               // sizeof = 0x324 (RE4)
```
God Hand confirmed members touching this: `cModel_calcParts`,
`cModel_getMeshPtr`, `cModel_setMeshDisplay`.

### `cParts : cCoord` — size 0x1D8 (RE4, **size marked TODO**)

```c
class cParts : public cCoord {     // cCoord occupies 0x00..0xC4
    Mtx     hokan_mat_C4;       // 0xC4  interpolation matrix (0x30)
    cParts* nextParts_F4;       // 0xF4  -- next sibling part (linked list)
    Mtx     lt_inv_mat_F8;      // 0xF8  (0x30)
    union { /* per-parts payload starting 0x128:
              IK data / world_ang / PEN_INFO / kaboom / PBOMB_INFO */ };
    uint32_t flag_1C0;          // 0x1C0
    uint8_t  unk_1C4[20];       // 0x1C4
};                              // sizeof = 0x1D8  (TODO: verify)
```
God Hand confirmed: `cParts_setRotationOrder`. The `0x128` union is highly
game-specific; **do not trust the union layout for God Hand** — only the
`mat_C4` / `nextParts_F4` head is reliable.

### `cObj : cModel` — size 0x32C (RE4)

```c
class cObj : public cModel {       // cModel occupies 0x00..0x324
    uint32_t m_StatusFlag_324;  // 0x324
    int32_t  m_BlockNo_328;     // 0x328
};                              // sizeof = 0x32C
```
God Hand has many `cObj*` symbols (`cObj_setId`, `cObjSimple_*`,
`cObjPtrArrayWrapper_insert`, …). God Hand's `cObjSimple`/weapon variants are
NOT in the RE4 SDK as-is — `cObjWep` (size 0x76C) is the closest RE4 analogue
(see `re4_sdk_headers/objWep.h`).

---

## Motion / camera

> **God Hand split:** `cMotBase`-family, `cMotCamera`, `cCamera`, `cPlCamera`.
> RE4 SDK has: a small `cMotBase`, a `MOTION_INFO` POD embedded in `cModel`, an
> `ATTACH_CAMERA` POD, and the `CAMERA`/`cCamera` classes. **There is no
> `cMotCamera` and no `cPlCamera` in the RE4 SDK** — God Hand's
> `cMotCamera::setMotion(...)` has no direct RE4 struct, but the camera-from-
> motion data it manipulates is almost certainly `ATTACH_CAMERA` (note
> `MOTION_INFO.attachCamera_CC` points to one).

### `cMotBase` — size 0x38 (RE4)

> RE4's `cMotBase` is a **thin** class (just model ptr + pos/ang + interp byte).
> God Hand's `cMotBase`-family is likely richer; use this only as the head.

```c
class cMotBase {
    cModel* pMod_0;       // 0x00
    Vec     pos_4;        // 0x04
    Vec     ang_10;       // 0x10
    Vec     pos_old_1C;   // 0x1C
    Vec     ang_old_28;   // 0x28
    uint8_t hokan_34;     // 0x34
    uint8_t dummy61_35;   // 0x35
    uint8_t dummy62_36;   // 0x36
    uint8_t dummy63_37;   // 0x37
};                        // sizeof = 0x38
```

### `MOTION_INFO` — size 0xD0 (POD, embedded at `cModel+0x1D8`)

The actual animation/keyframe state. Notable fields:
`Mot_frame_24`, `Mot_frame_max_20`, `Joint_num_30`, `pJoint_no_34`,
`Mot_state_42`, `Mot_flag_44`, pos/ang vectors `0x48..0xA4`, sequence data
`pSeq_top_A8`/`Seq_AC`/`Seq_frame_B8`, `Brate_C8`, and crucially
`ATTACH_CAMERA* attachCamera_CC` (0xCC). See `re4_sdk_headers/model.h`.

### `ATTACH_CAMERA` — size 0x98 (camera bone attached to a model)

```c
struct ATTACH_CAMERA {
    uint8_t cam_jnt_0[5];     // 0x00 joint indices
    uint8_t cam_flag_5;       // 0x05
    uint8_t cam_int_6;        // 0x06
    Mtx*    p_mat_8;          // 0x08
    Mtx     mat_C;            // 0x0C (0x30)
    Vec     camera_data_3C[5];// 0x3C
    uint16_t history_78[5][3];// 0x78
};                            // sizeof = 0x98
```

### `CAMERA` — size 0xF8 / `cCamera`

```c
class CAMERA {
    Mtx          mat_0;        // 0x00 (0x30)
    Mtx          v_mat_30;     // 0x30 view matrix (0x30)
    int          ProjType_60;  // 0x60
    Mtx44        ProjMat_64;   // 0x64 projection (0x40)  <-- 4x4 here!
    CAMERA_POINT CamPoint_A4;  // 0xA4 {Vec Campos; Vec Target; float Roll; float Fovy;}
    Vec          Up_C4;        // 0xC4
    Vec          Look_D0;      // 0xD0
    Vec          Right_DC;     // 0xDC
    Vec          Ang_E8;       // 0xE8
    float        Distance_F4;  // 0xF4
};                             // sizeof = 0xF8

class cCamera {                // God Hand: cCamera (confirmed symbols)
    /* vtable: dtor, move() */ // 0x00
    CAMERA camData_4;          // 0x04   (NB: CAMERA embedded at +4 after vptr)
};
```
God Hand confirmed symbols: `cCamera_setMode`, `cCamera__calcRotation`,
`cCamera_resetVib`. **Caveat:** RE4's `cCamera` puts `CAMERA` at +0x04 (one
vptr). Verify God Hand's vtable count — if God Hand has more virtuals or a
different base, the `+0x04` shifts.

Larger camera machinery (`CameraControl` @ 0x788, `CameraSmooth`,
`CameraQuasiFPS`, the `CAMERA_DATA`/`CUT_INFO`/`AREA_DATA` cut system) is in
`re4_sdk_headers/cam_ctrl.h`. God Hand's `cPlCamera`/`cMotCamera` likely
correspond *behaviorally* to pieces of this, but **no name-level RE4 match
exists** — use these only to recognize field *patterns* (e.g. a camera with
two matrices + projection + up/look/right basis vectors + roll/fovy).

---

## Collision / atari

### `cAtariInfo` — size 0x4C (embedded at `cModel+0x2B4`)

```c
struct cAtariInfo {
    Vec      m_offset_0;     // 0x00
    float    m_radius_C;     // 0x0C
    float    m_radius2_10;   // 0x10
    float    m_height_14;    // 0x14
    int16_t  m_parts_no_18;  // 0x18
    uint16_t m_flag_1A;      // 0x1A  (SAT_TYPE bitmask)
    float    m_radius_n_1C;  // 0x1C
    float    m_radius2_n_20; // 0x20
    uint16_t m_hokan_24;     // 0x24
    uint16_t m_stat_26;      // 0x26
    cModel*  m_pMod_28;      // 0x28
    float    m_radius3_2C;   // 0x2C
    Vec      m_Pos_30;       // 0x30
    Vec      m_oldPos_3C;    // 0x3C
    cAtariInfo* m_pList_48;  // 0x48
};                           // sizeof = 0x4C
```
`SAT_TYPE` flags (collision-attribute bitmask): SAT_CK_FLOOR=0x40,
SAT_CK_WALL=0x80, SAT_TYPE_PL=0x1000, SAT_TYPE_EM=0x2000, … (see
`re4_sdk_headers/atariInfo.h`). God Hand's `cCollisionSolidManage` has **no**
direct RE4 struct, but `cAtariInfo` is the per-object collision record it would
manage.

---

## Container template

### `cManager<T>` — size 0x1C (vtable + array bookkeeping)

```c
template<class T> class cManager {
    /* vtable */            // 0x00
    T*       m_Array_4;     // 0x04  contiguous block of T (stride = m_blockSize_C)
    uint32_t m_nArray_8;    // 0x08  count
    uint32_t m_blockSize_C; // 0x0C  per-entry stride in bytes
    uint8_t  m_DieTimelag_10;//0x10
    T*       m_pAlive_14;   // 0x14
    T*       m_pAliveBack_18;//0x18
};                          // sizeof = 0x1C
```
Manager subclasses (`cEmMgr`, `cObjMgr`, `cLightMgr`) add `m_nMaxActiveWork`
at 0x1C → size 0x20. Useful for recognizing God Hand's global manager objects.

---

## Inventory of copied RE4 SDK headers

(in `scripts/recon/re4_sdk_headers/`; full set is at re4_tweaks `dllmain/SDK/`)

| file            | key God-Hand-relevant types                                   |
|-----------------|---------------------------------------------------------------|
| `basic_types.h` | **Vec(cVec)**, SVEC, **Quaternion**, **Mtx/Mtx44(cMatrix)**   |
| `gc_math.h`     | MTXConcat/MTXMultVec/VECAdd… (free math fns)                  |
| `cUnit.h`       | cUnit base + UNIT_BE_FLAG                                      |
| `cCoord.h`      | cCoord transform node                                          |
| `cMotBase.h`    | cMotBase (thin)                                               |
| `model.h`       | **cModel, cParts**, cModelInfo, cModelData, **MOTION_INFO**, cLightInfo, cBoundingBox, PEN_INFO |
| `camera.h`      | **CAMERA, cCamera**, CAMERA_POINT, **ATTACH_CAMERA**          |
| `cam_ctrl.h`    | CameraControl, CameraSmooth, CameraQuasiFPS, CUT/AREA/CAMERA_DATA |
| `obj.h`         | **cObj**, cObjMgr                                             |
| `objWep.h`      | cObjWep (weapon object; God Hand cObjSimple analogue)        |
| `em.h`          | cEm, cEmMgr, cDmgInfo, YARARE_INFO                            |
| `atariInfo.h`   | **cAtariInfo** + SAT_TYPE                                     |
| `cManager.h`    | cManager<T> template                                          |
| `GXStruct.h`    | GXColor, GXTexObj, fog/aniso enums                            |
| `EtcModel.h`    | ETS_DATA                                                      |

## God Hand classes with NO RE4 SDK analogue

`cMotCamera`, `cPlCamera`, `cCollisionSolidManage`, `tagEFF_PARAM`, `cEsp`,
`cSofdec` (only behavioral hooks exist in re4_tweaks, not a struct). These must
be recovered purely from God Hand's own asm.

---
*Generated 2026-06-19 from re4_tweaks @ 1dd35a4. Hypothesis only — verify every
offset against God Hand's byte-exact instruction stream while carving.*
