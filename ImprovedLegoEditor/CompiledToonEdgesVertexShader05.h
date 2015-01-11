#if 0
//
// Generated by Microsoft (R) HLSL Shader Compiler 9.30.9200.16384
//
//
///
// Buffer Definitions: 
//
// cbuffer cbPerScene
// {
//
//   float OutlineWidth;                // Offset:    0 Size:     4
//   float3 Padding;                    // Offset:    4 Size:    12 [unused]
//
// }
//
// cbuffer cbPerFrame
// {
//
//   row_major float4x4 ViewProjection; // Offset:    0 Size:    64
//
// }
//
//
// Resource Bindings:
//
// Name                                 Type  Format         Dim Slot Elements
// ------------------------------ ---------- ------- ----------- ---- --------
// cbPerScene                        cbuffer      NA          NA    0        1
// cbPerFrame                        cbuffer      NA          NA    1        1
//
//
//
// Input signature:
//
// Name                 Index   Mask Register SysValue  Format   Used
// -------------------- ----- ------ -------- -------- ------- ------
// POSITION                 0   xyzw        0     NONE   float   xyzw
// NORMAL                   0   xyz         1     NONE   float   xyz 
// AVGNORMAL                0   xyz         2     NONE   float       
// TEXCOORD                 0   xy          3     NONE   float       
// WORLD                    0   xyzw        4     NONE   float   xyzw
// WORLD                    1   xyzw        5     NONE   float   xyzw
// WORLD                    2   xyzw        6     NONE   float   xyzw
// WORLD                    3   xyzw        7     NONE   float   xyzw
// COLOUR                   0   xyzw        8     NONE   float       
//
//
// Output signature:
//
// Name                 Index   Mask Register SysValue  Format   Used
// -------------------- ----- ------ -------- -------- ------- ------
// SV_POSITION              0   xyzw        0      POS   float   xyzw
//
//
// Constant buffer to DX9 shader constant mappings:
//
// Target Reg Buffer  Start Reg # of Regs        Data Conversion
// ---------- ------- --------- --------- ----------------------
// c1         cb0             0         1  ( FLT, FLT, FLT, FLT)
// c2         cb1             0         4  ( FLT, FLT, FLT, FLT)
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
    dcl_texcoord v0
    dcl_texcoord1 v1
    dcl_texcoord4 v4
    dcl_texcoord5 v5
    dcl_texcoord6 v6
    dcl_texcoord7 v7
    mul r0, v5.y, c3
    mad r0, v5.x, c2, r0
    mad r0, v5.z, c4, r0
    mad r0, v5.w, c5, r0
    mul r1.xyz, r0, v1.y
    mul r0, r0, v0.y
    mul r2, v4.y, c3
    mad r2, v4.x, c2, r2
    mad r2, v4.z, c4, r2
    mad r2, v4.w, c5, r2
    mad r1.xyz, v1.x, r2, r1
    mad r0, v0.x, r2, r0
    mul r2, v6.y, c3
    mad r2, v6.x, c2, r2
    mad r2, v6.z, c4, r2
    mad r2, v6.w, c5, r2
    mad r1.xyz, v1.z, r2, r1
    mad r0, v0.z, r2, r0
    dp3 r1.z, r1, r1
    rsq r1.z, r1.z
    mul r1.xy, r1.z, r1
    mul r2, v7.y, c3
    mad r2, v7.x, c2, r2
    mad r2, v7.z, c4, r2
    mad r2, v7.w, c5, r2
    mad r0, v0.w, r2, r0
    mul r1.xy, r0.z, r1
    mad r0.xy, r1, c1.x, r0
    mad oPos.xy, r0.w, c0, r0
    mov oPos.zw, r0

// approximately 30 instruction slots used
vs_4_0
dcl_constantbuffer cb0[1], immediateIndexed
dcl_constantbuffer cb1[4], immediateIndexed
dcl_input v0.xyzw
dcl_input v1.xyz
dcl_input v4.xyzw
dcl_input v5.xyzw
dcl_input v6.xyzw
dcl_input v7.xyzw
dcl_output_siv o0.xyzw, position
dcl_temps 3
mul r0.xyzw, v5.yyyy, cb1[1].xyzw
mad r0.xyzw, v5.xxxx, cb1[0].xyzw, r0.xyzw
mad r0.xyzw, v5.zzzz, cb1[2].xyzw, r0.xyzw
mad r0.xyzw, v5.wwww, cb1[3].xyzw, r0.xyzw
mul r1.xyz, r0.xyzx, v1.yyyy
mul r0.xyzw, r0.xyzw, v0.yyyy
mul r2.xyzw, v4.yyyy, cb1[1].xyzw
mad r2.xyzw, v4.xxxx, cb1[0].xyzw, r2.xyzw
mad r2.xyzw, v4.zzzz, cb1[2].xyzw, r2.xyzw
mad r2.xyzw, v4.wwww, cb1[3].xyzw, r2.xyzw
mad r1.xyz, v1.xxxx, r2.xyzx, r1.xyzx
mad r0.xyzw, v0.xxxx, r2.xyzw, r0.xyzw
mul r2.xyzw, v6.yyyy, cb1[1].xyzw
mad r2.xyzw, v6.xxxx, cb1[0].xyzw, r2.xyzw
mad r2.xyzw, v6.zzzz, cb1[2].xyzw, r2.xyzw
mad r2.xyzw, v6.wwww, cb1[3].xyzw, r2.xyzw
mad r1.xyz, v1.zzzz, r2.xyzx, r1.xyzx
mad r0.xyzw, v0.zzzz, r2.xyzw, r0.xyzw
dp3 r1.z, r1.xyzx, r1.xyzx
rsq r1.z, r1.z
mul r1.xy, r1.zzzz, r1.xyxx
mul r2.xyzw, v7.yyyy, cb1[1].xyzw
mad r2.xyzw, v7.xxxx, cb1[0].xyzw, r2.xyzw
mad r2.xyzw, v7.zzzz, cb1[2].xyzw, r2.xyzw
mad r2.xyzw, v7.wwww, cb1[3].xyzw, r2.xyzw
mad r0.xyzw, v0.wwww, r2.xyzw, r0.xyzw
mul r1.xy, r0.zzzz, r1.xyxx
mad o0.xy, r1.xyxx, cb0[0].xxxx, r0.xyxx
mov o0.zw, r0.zzzw
ret 
// Approximately 30 instruction slots used
#endif

const BYTE g_toonEdgesVertexShader05[] =
{
     68,  88,  66,  67, 147, 216, 
    115, 189,  18,  17,  78,   5, 
    127,  13, 144,  41,  31, 135, 
     53, 225,   1,   0,   0,   0, 
    192,  10,   0,   0,   6,   0, 
      0,   0,  56,   0,   0,   0, 
    244,   2,   0,   0, 120,   7, 
      0,   0, 244,   7,   0,   0, 
    116,   9,   0,   0, 140,  10, 
      0,   0,  65, 111, 110,  57, 
    180,   2,   0,   0, 180,   2, 
      0,   0,   0,   2, 254, 255, 
    116,   2,   0,   0,  64,   0, 
      0,   0,   2,   0,  36,   0, 
      0,   0,  60,   0,   0,   0, 
     60,   0,   0,   0,  36,   0, 
      1,   0,  60,   0,   0,   0, 
      0,   0,   1,   0,   1,   0, 
      0,   0,   0,   0,   1,   0, 
      0,   0,   4,   0,   2,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   1,   2, 254, 255, 
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
      5,   0,   0,   3,   0,   0, 
     15, 128,   5,   0,  85, 144, 
      3,   0, 228, 160,   4,   0, 
      0,   4,   0,   0,  15, 128, 
      5,   0,   0, 144,   2,   0, 
    228, 160,   0,   0, 228, 128, 
      4,   0,   0,   4,   0,   0, 
     15, 128,   5,   0, 170, 144, 
      4,   0, 228, 160,   0,   0, 
    228, 128,   4,   0,   0,   4, 
      0,   0,  15, 128,   5,   0, 
    255, 144,   5,   0, 228, 160, 
      0,   0, 228, 128,   5,   0, 
      0,   3,   1,   0,   7, 128, 
      0,   0, 228, 128,   1,   0, 
     85, 144,   5,   0,   0,   3, 
      0,   0,  15, 128,   0,   0, 
    228, 128,   0,   0,  85, 144, 
      5,   0,   0,   3,   2,   0, 
     15, 128,   4,   0,  85, 144, 
      3,   0, 228, 160,   4,   0, 
      0,   4,   2,   0,  15, 128, 
      4,   0,   0, 144,   2,   0, 
    228, 160,   2,   0, 228, 128, 
      4,   0,   0,   4,   2,   0, 
     15, 128,   4,   0, 170, 144, 
      4,   0, 228, 160,   2,   0, 
    228, 128,   4,   0,   0,   4, 
      2,   0,  15, 128,   4,   0, 
    255, 144,   5,   0, 228, 160, 
      2,   0, 228, 128,   4,   0, 
      0,   4,   1,   0,   7, 128, 
      1,   0,   0, 144,   2,   0, 
    228, 128,   1,   0, 228, 128, 
      4,   0,   0,   4,   0,   0, 
     15, 128,   0,   0,   0, 144, 
      2,   0, 228, 128,   0,   0, 
    228, 128,   5,   0,   0,   3, 
      2,   0,  15, 128,   6,   0, 
     85, 144,   3,   0, 228, 160, 
      4,   0,   0,   4,   2,   0, 
     15, 128,   6,   0,   0, 144, 
      2,   0, 228, 160,   2,   0, 
    228, 128,   4,   0,   0,   4, 
      2,   0,  15, 128,   6,   0, 
    170, 144,   4,   0, 228, 160, 
      2,   0, 228, 128,   4,   0, 
      0,   4,   2,   0,  15, 128, 
      6,   0, 255, 144,   5,   0, 
    228, 160,   2,   0, 228, 128, 
      4,   0,   0,   4,   1,   0, 
      7, 128,   1,   0, 170, 144, 
      2,   0, 228, 128,   1,   0, 
    228, 128,   4,   0,   0,   4, 
      0,   0,  15, 128,   0,   0, 
    170, 144,   2,   0, 228, 128, 
      0,   0, 228, 128,   8,   0, 
      0,   3,   1,   0,   4, 128, 
      1,   0, 228, 128,   1,   0, 
    228, 128,   7,   0,   0,   2, 
      1,   0,   4, 128,   1,   0, 
    170, 128,   5,   0,   0,   3, 
      1,   0,   3, 128,   1,   0, 
    170, 128,   1,   0, 228, 128, 
      5,   0,   0,   3,   2,   0, 
     15, 128,   7,   0,  85, 144, 
      3,   0, 228, 160,   4,   0, 
      0,   4,   2,   0,  15, 128, 
      7,   0,   0, 144,   2,   0, 
    228, 160,   2,   0, 228, 128, 
      4,   0,   0,   4,   2,   0, 
     15, 128,   7,   0, 170, 144, 
      4,   0, 228, 160,   2,   0, 
    228, 128,   4,   0,   0,   4, 
      2,   0,  15, 128,   7,   0, 
    255, 144,   5,   0, 228, 160, 
      2,   0, 228, 128,   4,   0, 
      0,   4,   0,   0,  15, 128, 
      0,   0, 255, 144,   2,   0, 
    228, 128,   0,   0, 228, 128, 
      5,   0,   0,   3,   1,   0, 
      3, 128,   0,   0, 170, 128, 
      1,   0, 228, 128,   4,   0, 
      0,   4,   0,   0,   3, 128, 
      1,   0, 228, 128,   1,   0, 
      0, 160,   0,   0, 228, 128, 
      4,   0,   0,   4,   0,   0, 
      3, 192,   0,   0, 255, 128, 
      0,   0, 228, 160,   0,   0, 
    228, 128,   1,   0,   0,   2, 
      0,   0,  12, 192,   0,   0, 
    228, 128, 255, 255,   0,   0, 
     83,  72,  68,  82, 124,   4, 
      0,   0,  64,   0,   1,   0, 
     31,   1,   0,   0,  89,   0, 
      0,   4,  70, 142,  32,   0, 
      0,   0,   0,   0,   1,   0, 
      0,   0,  89,   0,   0,   4, 
     70, 142,  32,   0,   1,   0, 
      0,   0,   4,   0,   0,   0, 
     95,   0,   0,   3, 242,  16, 
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
    103,   0,   0,   4, 242,  32, 
     16,   0,   0,   0,   0,   0, 
      1,   0,   0,   0, 104,   0, 
      0,   2,   3,   0,   0,   0, 
     56,   0,   0,   8, 242,   0, 
     16,   0,   0,   0,   0,   0, 
     86,  21,  16,   0,   5,   0, 
      0,   0,  70, 142,  32,   0, 
      1,   0,   0,   0,   1,   0, 
      0,   0,  50,   0,   0,  10, 
    242,   0,  16,   0,   0,   0, 
      0,   0,   6,  16,  16,   0, 
      5,   0,   0,   0,  70, 142, 
     32,   0,   1,   0,   0,   0, 
      0,   0,   0,   0,  70,  14, 
     16,   0,   0,   0,   0,   0, 
     50,   0,   0,  10, 242,   0, 
     16,   0,   0,   0,   0,   0, 
    166,  26,  16,   0,   5,   0, 
      0,   0,  70, 142,  32,   0, 
      1,   0,   0,   0,   2,   0, 
      0,   0,  70,  14,  16,   0, 
      0,   0,   0,   0,  50,   0, 
      0,  10, 242,   0,  16,   0, 
      0,   0,   0,   0, 246,  31, 
     16,   0,   5,   0,   0,   0, 
     70, 142,  32,   0,   1,   0, 
      0,   0,   3,   0,   0,   0, 
     70,  14,  16,   0,   0,   0, 
      0,   0,  56,   0,   0,   7, 
    114,   0,  16,   0,   1,   0, 
      0,   0,  70,   2,  16,   0, 
      0,   0,   0,   0,  86,  21, 
     16,   0,   1,   0,   0,   0, 
     56,   0,   0,   7, 242,   0, 
     16,   0,   0,   0,   0,   0, 
     70,  14,  16,   0,   0,   0, 
      0,   0,  86,  21,  16,   0, 
      0,   0,   0,   0,  56,   0, 
      0,   8, 242,   0,  16,   0, 
      2,   0,   0,   0,  86,  21, 
     16,   0,   4,   0,   0,   0, 
     70, 142,  32,   0,   1,   0, 
      0,   0,   1,   0,   0,   0, 
     50,   0,   0,  10, 242,   0, 
     16,   0,   2,   0,   0,   0, 
      6,  16,  16,   0,   4,   0, 
      0,   0,  70, 142,  32,   0, 
      1,   0,   0,   0,   0,   0, 
      0,   0,  70,  14,  16,   0, 
      2,   0,   0,   0,  50,   0, 
      0,  10, 242,   0,  16,   0, 
      2,   0,   0,   0, 166,  26, 
     16,   0,   4,   0,   0,   0, 
     70, 142,  32,   0,   1,   0, 
      0,   0,   2,   0,   0,   0, 
     70,  14,  16,   0,   2,   0, 
      0,   0,  50,   0,   0,  10, 
    242,   0,  16,   0,   2,   0, 
      0,   0, 246,  31,  16,   0, 
      4,   0,   0,   0,  70, 142, 
     32,   0,   1,   0,   0,   0, 
      3,   0,   0,   0,  70,  14, 
     16,   0,   2,   0,   0,   0, 
     50,   0,   0,   9, 114,   0, 
     16,   0,   1,   0,   0,   0, 
      6,  16,  16,   0,   1,   0, 
      0,   0,  70,   2,  16,   0, 
      2,   0,   0,   0,  70,   2, 
     16,   0,   1,   0,   0,   0, 
     50,   0,   0,   9, 242,   0, 
     16,   0,   0,   0,   0,   0, 
      6,  16,  16,   0,   0,   0, 
      0,   0,  70,  14,  16,   0, 
      2,   0,   0,   0,  70,  14, 
     16,   0,   0,   0,   0,   0, 
     56,   0,   0,   8, 242,   0, 
     16,   0,   2,   0,   0,   0, 
     86,  21,  16,   0,   6,   0, 
      0,   0,  70, 142,  32,   0, 
      1,   0,   0,   0,   1,   0, 
      0,   0,  50,   0,   0,  10, 
    242,   0,  16,   0,   2,   0, 
      0,   0,   6,  16,  16,   0, 
      6,   0,   0,   0,  70, 142, 
     32,   0,   1,   0,   0,   0, 
      0,   0,   0,   0,  70,  14, 
     16,   0,   2,   0,   0,   0, 
     50,   0,   0,  10, 242,   0, 
     16,   0,   2,   0,   0,   0, 
    166,  26,  16,   0,   6,   0, 
      0,   0,  70, 142,  32,   0, 
      1,   0,   0,   0,   2,   0, 
      0,   0,  70,  14,  16,   0, 
      2,   0,   0,   0,  50,   0, 
      0,  10, 242,   0,  16,   0, 
      2,   0,   0,   0, 246,  31, 
     16,   0,   6,   0,   0,   0, 
     70, 142,  32,   0,   1,   0, 
      0,   0,   3,   0,   0,   0, 
     70,  14,  16,   0,   2,   0, 
      0,   0,  50,   0,   0,   9, 
    114,   0,  16,   0,   1,   0, 
      0,   0, 166,  26,  16,   0, 
      1,   0,   0,   0,  70,   2, 
     16,   0,   2,   0,   0,   0, 
     70,   2,  16,   0,   1,   0, 
      0,   0,  50,   0,   0,   9, 
    242,   0,  16,   0,   0,   0, 
      0,   0, 166,  26,  16,   0, 
      0,   0,   0,   0,  70,  14, 
     16,   0,   2,   0,   0,   0, 
     70,  14,  16,   0,   0,   0, 
      0,   0,  16,   0,   0,   7, 
     66,   0,  16,   0,   1,   0, 
      0,   0,  70,   2,  16,   0, 
      1,   0,   0,   0,  70,   2, 
     16,   0,   1,   0,   0,   0, 
     68,   0,   0,   5,  66,   0, 
     16,   0,   1,   0,   0,   0, 
     42,   0,  16,   0,   1,   0, 
      0,   0,  56,   0,   0,   7, 
     50,   0,  16,   0,   1,   0, 
      0,   0, 166,  10,  16,   0, 
      1,   0,   0,   0,  70,   0, 
     16,   0,   1,   0,   0,   0, 
     56,   0,   0,   8, 242,   0, 
     16,   0,   2,   0,   0,   0, 
     86,  21,  16,   0,   7,   0, 
      0,   0,  70, 142,  32,   0, 
      1,   0,   0,   0,   1,   0, 
      0,   0,  50,   0,   0,  10, 
    242,   0,  16,   0,   2,   0, 
      0,   0,   6,  16,  16,   0, 
      7,   0,   0,   0,  70, 142, 
     32,   0,   1,   0,   0,   0, 
      0,   0,   0,   0,  70,  14, 
     16,   0,   2,   0,   0,   0, 
     50,   0,   0,  10, 242,   0, 
     16,   0,   2,   0,   0,   0, 
    166,  26,  16,   0,   7,   0, 
      0,   0,  70, 142,  32,   0, 
      1,   0,   0,   0,   2,   0, 
      0,   0,  70,  14,  16,   0, 
      2,   0,   0,   0,  50,   0, 
      0,  10, 242,   0,  16,   0, 
      2,   0,   0,   0, 246,  31, 
     16,   0,   7,   0,   0,   0, 
     70, 142,  32,   0,   1,   0, 
      0,   0,   3,   0,   0,   0, 
     70,  14,  16,   0,   2,   0, 
      0,   0,  50,   0,   0,   9, 
    242,   0,  16,   0,   0,   0, 
      0,   0, 246,  31,  16,   0, 
      0,   0,   0,   0,  70,  14, 
     16,   0,   2,   0,   0,   0, 
     70,  14,  16,   0,   0,   0, 
      0,   0,  56,   0,   0,   7, 
     50,   0,  16,   0,   1,   0, 
      0,   0, 166,  10,  16,   0, 
      0,   0,   0,   0,  70,   0, 
     16,   0,   1,   0,   0,   0, 
     50,   0,   0,  10,  50,  32, 
     16,   0,   0,   0,   0,   0, 
     70,   0,  16,   0,   1,   0, 
      0,   0,   6, 128,  32,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,  70,   0,  16,   0, 
      0,   0,   0,   0,  54,   0, 
      0,   5, 194,  32,  16,   0, 
      0,   0,   0,   0, 166,  14, 
     16,   0,   0,   0,   0,   0, 
     62,   0,   0,   1,  83,  84, 
     65,  84, 116,   0,   0,   0, 
     30,   0,   0,   0,   3,   0, 
      0,   0,   0,   0,   0,   0, 
      7,   0,   0,   0,  10,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   1,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   2,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,  82,  68,  69,  70, 
    120,   1,   0,   0,   2,   0, 
      0,   0, 116,   0,   0,   0, 
      2,   0,   0,   0,  28,   0, 
      0,   0,   0,   4, 254, 255, 
      0,   1,   0,   0,  68,   1, 
      0,   0,  92,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   1,   0,   0,   0, 
      0,   0,   0,   0, 103,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      1,   0,   0,   0,   1,   0, 
      0,   0,   0,   0,   0,   0, 
     99,  98,  80, 101, 114,  83, 
     99, 101, 110, 101,   0,  99, 
     98,  80, 101, 114,  70, 114, 
     97, 109, 101,   0, 171, 171, 
     92,   0,   0,   0,   2,   0, 
      0,   0, 164,   0,   0,   0, 
     16,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
    103,   0,   0,   0,   1,   0, 
      0,   0,  12,   1,   0,   0, 
     64,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
    212,   0,   0,   0,   0,   0, 
      0,   0,   4,   0,   0,   0, 
      2,   0,   0,   0, 228,   0, 
      0,   0,   0,   0,   0,   0, 
    244,   0,   0,   0,   4,   0, 
      0,   0,  12,   0,   0,   0, 
      0,   0,   0,   0, 252,   0, 
      0,   0,   0,   0,   0,   0, 
     79, 117, 116, 108, 105, 110, 
    101,  87, 105, 100, 116, 104, 
      0, 171, 171, 171,   0,   0, 
      3,   0,   1,   0,   1,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,  80,  97, 100, 100, 
    105, 110, 103,   0,   1,   0, 
      3,   0,   1,   0,   3,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,  36,   1,   0,   0, 
      0,   0,   0,   0,  64,   0, 
      0,   0,   2,   0,   0,   0, 
     52,   1,   0,   0,   0,   0, 
      0,   0,  86, 105, 101, 119, 
     80, 114, 111, 106, 101,  99, 
    116, 105, 111, 110,   0, 171, 
      2,   0,   3,   0,   4,   0, 
      4,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,  77, 105, 
     99, 114, 111, 115, 111, 102, 
    116,  32,  40,  82,  41,  32, 
     72,  76,  83,  76,  32,  83, 
    104,  97, 100, 101, 114,  32, 
     67, 111, 109, 112, 105, 108, 
    101, 114,  32,  57,  46,  51, 
     48,  46,  57,  50,  48,  48, 
     46,  49,  54,  51,  56,  52, 
      0, 171,  73,  83,  71,  78, 
     16,   1,   0,   0,   9,   0, 
      0,   0,   8,   0,   0,   0, 
    224,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,   0,   0, 
      0,   0,  15,  15,   0,   0, 
    233,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,   1,   0, 
      0,   0,   7,   7,   0,   0, 
    240,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,   2,   0, 
      0,   0,   7,   0,   0,   0, 
    250,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,   3,   0, 
      0,   0,   3,   0,   0,   0, 
      3,   1,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,   4,   0, 
      0,   0,  15,  15,   0,   0, 
      3,   1,   0,   0,   1,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,   5,   0, 
      0,   0,  15,  15,   0,   0, 
      3,   1,   0,   0,   2,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,   6,   0, 
      0,   0,  15,  15,   0,   0, 
      3,   1,   0,   0,   3,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,   7,   0, 
      0,   0,  15,  15,   0,   0, 
      9,   1,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,   8,   0, 
      0,   0,  15,   0,   0,   0, 
     80,  79,  83,  73,  84,  73, 
     79,  78,   0,  78,  79,  82, 
     77,  65,  76,   0,  65,  86, 
     71,  78,  79,  82,  77,  65, 
     76,   0,  84,  69,  88,  67, 
     79,  79,  82,  68,   0,  87, 
     79,  82,  76,  68,   0,  67, 
     79,  76,  79,  85,  82,   0, 
     79,  83,  71,  78,  44,   0, 
      0,   0,   1,   0,   0,   0, 
      8,   0,   0,   0,  32,   0, 
      0,   0,   0,   0,   0,   0, 
      1,   0,   0,   0,   3,   0, 
      0,   0,   0,   0,   0,   0, 
     15,   0,   0,   0,  83,  86, 
     95,  80,  79,  83,  73,  84, 
     73,  79,  78,   0
};