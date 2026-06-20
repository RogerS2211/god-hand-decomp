/* God Hand engine types, distilled from the RE4 re4_tweaks SDK
 * (scripts/recon/re4_struct_reference.md). Ghidra: File > Parse C Source.
 *
 * CAVEAT: these are a HYPOTHESIS. The matching decomp is byte-exact, so when a
 * God Hand instruction's load/store offset contradicts a field here, the
 * INSTRUCTION wins. RE4 is x86 but also 32-bit, so pointer sizes match; struct
 * packing / vtable layout may differ. Verify offsets against the asm as you carve.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

typedef struct cVec       { float x, y, z; } cVec;             /* 0x0C */
typedef struct Quaternion { float x, y, z, w; } Quaternion;   /* 0x10 */
typedef struct SVEC       { short x, y, z; } SVEC;            /* 0x06 (compressed) */

typedef float cMatrix[3][4];   /* 0x30  PRIMARY (3x4 affine, GameCube-style) */
typedef float Mtx44[4][4];     /* 0x40  projection only */

/* Scene-graph base hierarchy (sizes from RE4; offsets to verify vs asm). */
typedef struct cUnit {         /* 0x0C  base, has vtable */
    void *vtable;              /* 0x00 */
    u32   be_flag_4;           /* 0x04  UNIT_BE_FLAG bitmask */
    u32   field_8;             /* 0x08 */
} cUnit;

/* UNIT_BE_FLAG: ALIVE=0x1 TRANS=0x2 MOVE=0x20 DEAD=0x200 DESTRUCT=0x400 */

typedef struct cCoord {        /* 0xC4  cCoord : cUnit  (transform node) */
    cUnit     base;            /* 0x00 */
    u8        body[184];        /* 0x0C..0xC4 */
} cCoord;

typedef struct cModel {        /* 0x324 cModel : cCoord */
    cCoord    base;            /* 0x00 */
    u8        body[52];          /* 0xC4..0xF8 */
    u32       guid_F8;         /* 0xF8 */
    u8        r_no_0_FC;       /* 0xFC  routine selectors r0..r3 */
    u8        r_no_1_FD;       /* 0xFD */
    u8        r_no_2_FE;       /* 0xFE */
    u8        r_no_3_FF;       /* 0xFF */
    u8        tail[548];         /* 0x100..0x324 */
} cModel;
