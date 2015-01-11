#if 0
//
// Generated by Microsoft (R) HLSL Shader Compiler 9.30.9200.16384
//
//
///
// Buffer Definitions: 
//
// cbuffer cbPerFrame
// {
//
//   row_major float4x4 ViewProjection; // Offset:    0 Size:    64
//   float3 ViewPosition;               // Offset:   64 Size:    12
//   float Padding;                     // Offset:   76 Size:     4 [unused]
//
// }
//
//
// Resource Bindings:
//
// Name                                 Type  Format         Dim Slot Elements
// ------------------------------ ---------- ------- ----------- ---- --------
// cbPerFrame                        cbuffer      NA          NA    0        1
//
//
//
// Input signature:
//
// Name                 Index   Mask Register SysValue  Format   Used
// -------------------- ----- ------ -------- -------- ------- ------
// POSITION                 0   xyzw        0     NONE   float   xyz 
// NORMAL                   0   xyz         1     NONE   float   xyz 
// AVGNORMAL                0   xyz         2     NONE   float       
// TEXCOORD                 0   xy          3     NONE   float       
// WORLD                    0   xyzw        4     NONE   float   xyzw
// WORLD                    1   xyzw        5     NONE   float   xyzw
// WORLD                    2   xyzw        6     NONE   float   xyzw
// WORLD                    3   xyzw        7     NONE   float   xyzw
// COLOUR                   0   xyzw        8     NONE   float   xyzw
//
//
// Output signature:
//
// Name                 Index   Mask Register SysValue  Format   Used
// -------------------- ----- ------ -------- -------- ------- ------
// SV_POSITION              0   xyzw        0      POS   float   xyzw
// COLOUR                   0   xyzw        1     NONE   float   xyzw
// NORMAL                   0   xyz         2     NONE   float   xyz 
// EDGEPROX                 0      w        2     NONE   float      w
//
//
// Constant buffer to DX9 shader constant mappings:
//
// Target Reg Buffer  Start Reg # of Regs        Data Conversion
// ---------- ------- --------- --------- ----------------------
// c1         cb0             0         5  ( FLT, FLT, FLT, FLT)
//
//
// Runtime generated constant mappings:
//
// Target Reg                               Constant Description
// ---------- --------------------------------------------------
// c0                              Vertex Shader position offset
//
//
// Level9 shader bytecode:
//
    vs_2_x
    def c6, 0, 1, 0, 0
    dcl_texcoord v0
    dcl_texcoord1 v1
    dcl_texcoord4 v4
    dcl_texcoord5 v5
    dcl_texcoord6 v6
    dcl_texcoord7 v7
    dcl_normal v8
    mov r0.xyz, v1
    mul r1.xyz, r0.y, v5
    mad r0.xyw, r0.x, v4.xyzz, r1.xyzz
    mad r0.xyz, r0.z, v6, r0.xyww
    nrm r1.xyz, r0
    mov oT1.xyz, r0
    mov r0.xyz, v0
    mul r2, r0.y, v5
    mad r2, r0.x, v4, r2
    mad r0, r0.z, v6, r2
    add r0, r0, v7
    add r2.xyz, -r0, c5
    nrm r3.xyz, r2
    dp3 r1.x, r1, r3
    max r1.x, r1.x, c6.x
    min oT1.w, r1.x, c6.y
    mul r1, r0.y, c2
    mad r1, r0.x, c1, r1
    mad r1, r0.z, c3, r1
    mad r0, r0.w, c4, r1
    mad oPos.xy, r0.w, c0, r0
    mov oPos.zw, r0
    mov oT0, v8

// approximately 27 instruction slots used
vs_4_0
dcl_constantbuffer cb0[5], immediateIndexed
dcl_input v0.xyz
dcl_input v1.xyz
dcl_input v4.xyzw
dcl_input v5.xyzw
dcl_input v6.xyzw
dcl_input v7.xyzw
dcl_input v8.xyzw
dcl_output_siv o0.xyzw, position
dcl_output o1.xyzw
dcl_output o2.xyz
dcl_output o2.w
dcl_temps 3
mul r0.xyzw, v0.yyyy, v5.xyzw
mad r0.xyzw, v0.xxxx, v4.xyzw, r0.xyzw
mad r0.xyzw, v0.zzzz, v6.xyzw, r0.xyzw
add r0.xyzw, r0.xyzw, v7.xyzw
mul r1.xyzw, r0.yyyy, cb0[1].xyzw
mad r1.xyzw, r0.xxxx, cb0[0].xyzw, r1.xyzw
mad r1.xyzw, r0.zzzz, cb0[2].xyzw, r1.xyzw
mad o0.xyzw, r0.wwww, cb0[3].xyzw, r1.xyzw
add r0.xyz, -r0.xyzx, cb0[4].xyzx
mov o1.xyzw, v8.xyzw
dp3 r0.w, r0.xyzx, r0.xyzx
rsq r0.w, r0.w
mul r0.xyz, r0.wwww, r0.xyzx
mul r1.xyz, v1.yyyy, v5.xyzx
mad r1.xyz, v1.xxxx, v4.xyzx, r1.xyzx
mad r1.xyz, v1.zzzz, v6.xyzx, r1.xyzx
dp3 r0.w, r1.xyzx, r1.xyzx
rsq r0.w, r0.w
mul r2.xyz, r0.wwww, r1.xyzx
mov o2.xyz, r1.xyzx
dp3_sat o2.w, r2.xyzx, r0.xyzx
ret 
// Approximately 22 instruction slots used
#endif

const BYTE g_toonVertexShader03[] =
{
     68,  88,  66,  67,  20, 248, 
    161, 194, 153, 178, 126, 238, 
    163, 158,  71,  81, 239,  84, 
     89, 228,   1,   0,   0,   0, 
    240,   8,   0,   0,   6,   0, 
      0,   0,  56,   0,   0,   0, 
     92,   2,   0,   0, 140,   5, 
      0,   0,   8,   6,   0,   0, 
     68,   7,   0,   0,  92,   8, 
      0,   0,  65, 111, 110,  57, 
     28,   2,   0,   0,  28,   2, 
      0,   0,   0,   2, 254, 255, 
    232,   1,   0,   0,  52,   0, 
      0,   0,   1,   0,  36,   0, 
      0,   0,  48,   0,   0,   0, 
     48,   0,   0,   0,  36,   0, 
      1,   0,  48,   0,   0,   0, 
      0,   0,   5,   0,   1,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   1,   2, 254, 255, 
     81,   0,   0,   5,   6,   0, 
     15, 160,   0,   0,   0,   0, 
      0,   0, 128,  63,   0,   0, 
      0,   0,   0,   0,   0,   0, 
     31,   0,   0,   2,   5,   0, 
      0, 128,   0,   0,  15, 144, 
     31,   0,   0,   2,   5,   0, 
      1, 128,   1,   0,  15, 144, 
     31,   0,   0,   2,   5,   0, 
      4, 128,   4,   0,  15, 144, 
     31,   0,   0,   2,   5,   0, 
      5, 128,   5,   0,  15, 144, 
     31,   0,   0,   2,   5,   0, 
      6, 128,   6,   0,  15, 144, 
     31,   0,   0,   2,   5,   0, 
      7, 128,   7,   0,  15, 144, 
     31,   0,   0,   2,   3,   0, 
      0, 128,   8,   0,  15, 144, 
      1,   0,   0,   2,   0,   0, 
      7, 128,   1,   0, 228, 144, 
      5,   0,   0,   3,   1,   0, 
      7, 128,   0,   0,  85, 128, 
      5,   0, 228, 144,   4,   0, 
      0,   4,   0,   0,  11, 128, 
      0,   0,   0, 128,   4,   0, 
    164, 144,   1,   0, 164, 128, 
      4,   0,   0,   4,   0,   0, 
      7, 128,   0,   0, 170, 128, 
      6,   0, 228, 144,   0,   0, 
    244, 128,  36,   0,   0,   2, 
      1,   0,   7, 128,   0,   0, 
    228, 128,   1,   0,   0,   2, 
      1,   0,   7, 224,   0,   0, 
    228, 128,   1,   0,   0,   2, 
      0,   0,   7, 128,   0,   0, 
    228, 144,   5,   0,   0,   3, 
      2,   0,  15, 128,   0,   0, 
     85, 128,   5,   0, 228, 144, 
      4,   0,   0,   4,   2,   0, 
     15, 128,   0,   0,   0, 128, 
      4,   0, 228, 144,   2,   0, 
    228, 128,   4,   0,   0,   4, 
      0,   0,  15, 128,   0,   0, 
    170, 128,   6,   0, 228, 144, 
      2,   0, 228, 128,   2,   0, 
      0,   3,   0,   0,  15, 128, 
      0,   0, 228, 128,   7,   0, 
    228, 144,   2,   0,   0,   3, 
      2,   0,   7, 128,   0,   0, 
    228, 129,   5,   0, 228, 160, 
     36,   0,   0,   2,   3,   0, 
      7, 128,   2,   0, 228, 128, 
      8,   0,   0,   3,   1,   0, 
      1, 128,   1,   0, 228, 128, 
      3,   0, 228, 128,  11,   0, 
      0,   3,   1,   0,   1, 128, 
      1,   0,   0, 128,   6,   0, 
      0, 160,  10,   0,   0,   3, 
      1,   0,   8, 224,   1,   0, 
      0, 128,   6,   0,  85, 160, 
      5,   0,   0,   3,   1,   0, 
     15, 128,   0,   0,  85, 128, 
      2,   0, 228, 160,   4,   0, 
      0,   4,   1,   0,  15, 128, 
      0,   0,   0, 128,   1,   0, 
    228, 160,   1,   0, 228, 128, 
      4,   0,   0,   4,   1,   0, 
     15, 128,   0,   0, 170, 128, 
      3,   0, 228, 160,   1,   0, 
    228, 128,   4,   0,   0,   4, 
      0,   0,  15, 128,   0,   0, 
    255, 128,   4,   0, 228, 160, 
      1,   0, 228, 128,   4,   0, 
      0,   4,   0,   0,   3, 192, 
      0,   0, 255, 128,   0,   0, 
    228, 160,   0,   0, 228, 128, 
      1,   0,   0,   2,   0,   0, 
     12, 192,   0,   0, 228, 128, 
      1,   0,   0,   2,   0,   0, 
     15, 224,   8,   0, 228, 144, 
    255, 255,   0,   0,  83,  72, 
     68,  82,  40,   3,   0,   0, 
     64,   0,   1,   0, 202,   0, 
      0,   0,  89,   0,   0,   4, 
     70, 142,  32,   0,   0,   0, 
      0,   0,   5,   0,   0,   0, 
     95,   0,   0,   3, 114,  16, 
     16,   0,   0,   0,   0,   0, 
     95,   0,   0,   3, 114,  16, 
     16,   0,   1,   0,   0,   0, 
     95,   0,   0,   3, 242,  16, 
     16,   0,   4,   0,   0,   0, 
     95,   0,   0,   3, 242,  16, 
     16,   0,   5,   0,   0,   0, 
     95,   0,   0,   3, 242,  16, 
     16,   0,   6,   0,   0,   0, 
     95,   0,   0,   3, 242,  16, 
     16,   0,   7,   0,   0,   0, 
     95,   0,   0,   3, 242,  16, 
     16,   0,   8,   0,   0,   0, 
    103,   0,   0,   4, 242,  32, 
     16,   0,   0,   0,   0,   0, 
      1,   0,   0,   0, 101,   0, 
      0,   3, 242,  32,  16,   0, 
      1,   0,   0,   0, 101,   0, 
      0,   3, 114,  32,  16,   0, 
      2,   0,   0,   0, 101,   0, 
      0,   3, 130,  32,  16,   0, 
      2,   0,   0,   0, 104,   0, 
      0,   2,   3,   0,   0,   0, 
     56,   0,   0,   7, 242,   0, 
     16,   0,   0,   0,   0,   0, 
     86,  21,  16,   0,   0,   0, 
      0,   0,  70,  30,  16,   0, 
      5,   0,   0,   0,  50,   0, 
      0,   9, 242,   0,  16,   0, 
      0,   0,   0,   0,   6,  16, 
     16,   0,   0,   0,   0,   0, 
     70,  30,  16,   0,   4,   0, 
      0,   0,  70,  14,  16,   0, 
      0,   0,   0,   0,  50,   0, 
      0,   9, 242,   0,  16,   0, 
      0,   0,   0,   0, 166,  26, 
     16,   0,   0,   0,   0,   0, 
     70,  30,  16,   0,   6,   0, 
      0,   0,  70,  14,  16,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   7, 242,   0,  16,   0, 
      0,   0,   0,   0,  70,  14, 
     16,   0,   0,   0,   0,   0, 
     70,  30,  16,   0,   7,   0, 
      0,   0,  56,   0,   0,   8, 
    242,   0,  16,   0,   1,   0, 
      0,   0,  86,   5,  16,   0, 
      0,   0,   0,   0,  70, 142, 
     32,   0,   0,   0,   0,   0, 
      1,   0,   0,   0,  50,   0, 
      0,  10, 242,   0,  16,   0, 
      1,   0,   0,   0,   6,   0, 
     16,   0,   0,   0,   0,   0, 
     70, 142,  32,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
     70,  14,  16,   0,   1,   0, 
      0,   0,  50,   0,   0,  10, 
    242,   0,  16,   0,   1,   0, 
      0,   0, 166,  10,  16,   0, 
      0,   0,   0,   0,  70, 142, 
     32,   0,   0,   0,   0,   0, 
      2,   0,   0,   0,  70,  14, 
     16,   0,   1,   0,   0,   0, 
     50,   0,   0,  10, 242,  32, 
     16,   0,   0,   0,   0,   0, 
    246,  15,  16,   0,   0,   0, 
      0,   0,  70, 142,  32,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0,  70,  14,  16,   0, 
      1,   0,   0,   0,   0,   0, 
      0,   9, 114,   0,  16,   0, 
      0,   0,   0,   0,  70,   2, 
     16, 128,  65,   0,   0,   0, 
      0,   0,   0,   0,  70, 130, 
     32,   0,   0,   0,   0,   0, 
      4,   0,   0,   0,  54,   0, 
      0,   5, 242,  32,  16,   0, 
      1,   0,   0,   0,  70,  30, 
     16,   0,   8,   0,   0,   0, 
     16,   0,   0,   7, 130,   0, 
     16,   0,   0,   0,   0,   0, 
     70,   2,  16,   0,   0,   0, 
      0,   0,  70,   2,  16,   0, 
      0,   0,   0,   0,  68,   0, 
      0,   5, 130,   0,  16,   0, 
      0,   0,   0,   0,  58,   0, 
     16,   0,   0,   0,   0,   0, 
     56,   0,   0,   7, 114,   0, 
     16,   0,   0,   0,   0,   0, 
    246,  15,  16,   0,   0,   0, 
      0,   0,  70,   2,  16,   0, 
      0,   0,   0,   0,  56,   0, 
      0,   7, 114,   0,  16,   0, 
      1,   0,   0,   0,  86,  21, 
     16,   0,   1,   0,   0,   0, 
     70,  18,  16,   0,   5,   0, 
      0,   0,  50,   0,   0,   9, 
    114,   0,  16,   0,   1,   0, 
      0,   0,   6,  16,  16,   0, 
      1,   0,   0,   0,  70,  18, 
     16,   0,   4,   0,   0,   0, 
     70,   2,  16,   0,   1,   0, 
      0,   0,  50,   0,   0,   9, 
    114,   0,  16,   0,   1,   0, 
      0,   0, 166,  26,  16,   0, 
      1,   0,   0,   0,  70,  18, 
     16,   0,   6,   0,   0,   0, 
     70,   2,  16,   0,   1,   0, 
      0,   0,  16,   0,   0,   7, 
    130,   0,  16,   0,   0,   0, 
      0,   0,  70,   2,  16,   0, 
      1,   0,   0,   0,  70,   2, 
     16,   0,   1,   0,   0,   0, 
     68,   0,   0,   5, 130,   0, 
     16,   0,   0,   0,   0,   0, 
     58,   0,  16,   0,   0,   0, 
      0,   0,  56,   0,   0,   7, 
    114,   0,  16,   0,   2,   0, 
      0,   0, 246,  15,  16,   0, 
      0,   0,   0,   0,  70,   2, 
     16,   0,   1,   0,   0,   0, 
     54,   0,   0,   5, 114,  32, 
     16,   0,   2,   0,   0,   0, 
     70,   2,  16,   0,   1,   0, 
      0,   0,  16,  32,   0,   7, 
    130,  32,  16,   0,   2,   0, 
      0,   0,  70,   2,  16,   0, 
      2,   0,   0,   0,  70,   2, 
     16,   0,   0,   0,   0,   0, 
     62,   0,   0,   1,  83,  84, 
     65,  84, 116,   0,   0,   0, 
     22,   0,   0,   0,   3,   0, 
      0,   0,   0,   0,   0,   0, 
     11,   0,   0,   0,  12,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   1,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,  82,  68,  69,  70, 
     52,   1,   0,   0,   1,   0, 
      0,   0,  72,   0,   0,   0, 
      1,   0,   0,   0,  28,   0, 
      0,   0,   0,   4, 254, 255, 
      0,   1,   0,   0,   0,   1, 
      0,   0,  60,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   1,   0,   0,   0, 
      0,   0,   0,   0,  99,  98, 
     80, 101, 114,  70, 114,  97, 
    109, 101,   0, 171,  60,   0, 
      0,   0,   3,   0,   0,   0, 
     96,   0,   0,   0,  80,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0, 168,   0, 
      0,   0,   0,   0,   0,   0, 
     64,   0,   0,   0,   2,   0, 
      0,   0, 184,   0,   0,   0, 
      0,   0,   0,   0, 200,   0, 
      0,   0,  64,   0,   0,   0, 
     12,   0,   0,   0,   2,   0, 
      0,   0, 216,   0,   0,   0, 
      0,   0,   0,   0, 232,   0, 
      0,   0,  76,   0,   0,   0, 
      4,   0,   0,   0,   0,   0, 
      0,   0, 240,   0,   0,   0, 
      0,   0,   0,   0,  86, 105, 
    101, 119,  80, 114, 111, 106, 
    101,  99, 116, 105, 111, 110, 
      0, 171,   2,   0,   3,   0, 
      4,   0,   4,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
     86, 105, 101, 119,  80, 111, 
    115, 105, 116, 105, 111, 110, 
      0, 171, 171, 171,   1,   0, 
      3,   0,   1,   0,   3,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,  80,  97, 100, 100, 
    105, 110, 103,   0,   0,   0, 
      3,   0,   1,   0,   1,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,  77, 105,  99, 114, 
    111, 115, 111, 102, 116,  32, 
     40,  82,  41,  32,  72,  76, 
     83,  76,  32,  83, 104,  97, 
    100, 101, 114,  32,  67, 111, 
    109, 112, 105, 108, 101, 114, 
     32,  57,  46,  51,  48,  46, 
     57,  50,  48,  48,  46,  49, 
     54,  51,  56,  52,   0, 171, 
     73,  83,  71,  78,  16,   1, 
      0,   0,   9,   0,   0,   0, 
      8,   0,   0,   0, 224,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0,   0,   0,   0,   0, 
     15,   7,   0,   0, 233,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0,   1,   0,   0,   0, 
      7,   7,   0,   0, 240,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0,   2,   0,   0,   0, 
      7,   0,   0,   0, 250,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0,   3,   0,   0,   0, 
      3,   0,   0,   0,   3,   1, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0,   4,   0,   0,   0, 
     15,  15,   0,   0,   3,   1, 
      0,   0,   1,   0,   0,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0,   5,   0,   0,   0, 
     15,  15,   0,   0,   3,   1, 
      0,   0,   2,   0,   0,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0,   6,   0,   0,   0, 
     15,  15,   0,   0,   3,   1, 
      0,   0,   3,   0,   0,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0,   7,   0,   0,   0, 
     15,  15,   0,   0,   9,   1, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0,   8,   0,   0,   0, 
     15,  15,   0,   0,  80,  79, 
     83,  73,  84,  73,  79,  78, 
      0,  78,  79,  82,  77,  65, 
     76,   0,  65,  86,  71,  78, 
     79,  82,  77,  65,  76,   0, 
     84,  69,  88,  67,  79,  79, 
     82,  68,   0,  87,  79,  82, 
     76,  68,   0,  67,  79,  76, 
     79,  85,  82,   0,  79,  83, 
     71,  78, 140,   0,   0,   0, 
      4,   0,   0,   0,   8,   0, 
      0,   0, 104,   0,   0,   0, 
      0,   0,   0,   0,   1,   0, 
      0,   0,   3,   0,   0,   0, 
      0,   0,   0,   0,  15,   0, 
      0,   0, 116,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
      1,   0,   0,   0,  15,   0, 
      0,   0, 123,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
      2,   0,   0,   0,   7,   8, 
      0,   0, 130,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
      2,   0,   0,   0,   8,   7, 
      0,   0,  83,  86,  95,  80, 
     79,  83,  73,  84,  73,  79, 
     78,   0,  67,  79,  76,  79, 
     85,  82,   0,  78,  79,  82, 
     77,  65,  76,   0,  69,  68, 
     71,  69,  80,  82,  79,  88, 
      0, 171
};
