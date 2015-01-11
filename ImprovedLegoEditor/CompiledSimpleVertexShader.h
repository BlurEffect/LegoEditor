#if 0
//
// Generated by Microsoft (R) HLSL Shader Compiler 9.30.9200.16384
//
//
///
// Buffer Definitions: 
//
// cbuffer PerFrameBuffer
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
// PerFrameBuffer                    cbuffer      NA          NA    0        1
//
//
//
// Input signature:
//
// Name                 Index   Mask Register SysValue  Format   Used
// -------------------- ----- ------ -------- -------- ------- ------
// POSITION                 0   xyzw        0     NONE   float   xyzw
// NORMAL                   0   xyz         1     NONE   float       
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
//
//
// Constant buffer to DX9 shader constant mappings:
//
// Target Reg Buffer  Start Reg # of Regs        Data Conversion
// ---------- ------- --------- --------- ----------------------
// c1         cb0             0         4  ( FLT, FLT, FLT, FLT)
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
    dcl_texcoord4 v4
    dcl_texcoord5 v5
    dcl_texcoord6 v6
    dcl_texcoord7 v7
    dcl_normal v8
    mul r0, v5.y, c2
    mad r0, v5.x, c1, r0
    mad r0, v5.z, c3, r0
    mad r0, v5.w, c4, r0
    mul r0, r0, v0.y
    mul r1, v4.y, c2
    mad r1, v4.x, c1, r1
    mad r1, v4.z, c3, r1
    mad r1, v4.w, c4, r1
    mad r0, v0.x, r1, r0
    mul r1, v6.y, c2
    mad r1, v6.x, c1, r1
    mad r1, v6.z, c3, r1
    mad r1, v6.w, c4, r1
    mad r0, v0.z, r1, r0
    mul r1, v7.y, c2
    mad r1, v7.x, c1, r1
    mad r1, v7.z, c3, r1
    mad r1, v7.w, c4, r1
    mad r0, v0.w, r1, r0
    mad oPos.xy, r0.w, c0, r0
    mov oPos.zw, r0
    mov oT0, v8

// approximately 23 instruction slots used
vs_4_0
dcl_constantbuffer cb0[4], immediateIndexed
dcl_input v0.xyzw
dcl_input v4.xyzw
dcl_input v5.xyzw
dcl_input v6.xyzw
dcl_input v7.xyzw
dcl_input v8.xyzw
dcl_output_siv o0.xyzw, position
dcl_output o1.xyzw
dcl_temps 2
mul r0.xyzw, v5.yyyy, cb0[1].xyzw
mad r0.xyzw, v5.xxxx, cb0[0].xyzw, r0.xyzw
mad r0.xyzw, v5.zzzz, cb0[2].xyzw, r0.xyzw
mad r0.xyzw, v5.wwww, cb0[3].xyzw, r0.xyzw
mul r0.xyzw, r0.xyzw, v0.yyyy
mul r1.xyzw, v4.yyyy, cb0[1].xyzw
mad r1.xyzw, v4.xxxx, cb0[0].xyzw, r1.xyzw
mad r1.xyzw, v4.zzzz, cb0[2].xyzw, r1.xyzw
mad r1.xyzw, v4.wwww, cb0[3].xyzw, r1.xyzw
mad r0.xyzw, v0.xxxx, r1.xyzw, r0.xyzw
mul r1.xyzw, v6.yyyy, cb0[1].xyzw
mad r1.xyzw, v6.xxxx, cb0[0].xyzw, r1.xyzw
mad r1.xyzw, v6.zzzz, cb0[2].xyzw, r1.xyzw
mad r1.xyzw, v6.wwww, cb0[3].xyzw, r1.xyzw
mad r0.xyzw, v0.zzzz, r1.xyzw, r0.xyzw
mul r1.xyzw, v7.yyyy, cb0[1].xyzw
mad r1.xyzw, v7.xxxx, cb0[0].xyzw, r1.xyzw
mad r1.xyzw, v7.zzzz, cb0[2].xyzw, r1.xyzw
mad r1.xyzw, v7.wwww, cb0[3].xyzw, r1.xyzw
mad o0.xyzw, v0.wwww, r1.xyzw, r0.xyzw
mov o1.xyzw, v8.xyzw
ret 
// Approximately 22 instruction slots used
#endif

const BYTE g_simpleVertexShader[] =
{
     68,  88,  66,  67,  12, 101, 
    159, 194,  67, 116, 195,  19, 
    201,  90,  98,  11,  71, 193, 
     85,  36,   1,   0,   0,   0, 
    184,   8,   0,   0,   6,   0, 
      0,   0,  56,   0,   0,   0, 
    108,   2,   0,   0, 248,   5, 
      0,   0, 116,   6,   0,   0, 
     76,   7,   0,   0, 100,   8, 
      0,   0,  65, 111, 110,  57, 
     44,   2,   0,   0,  44,   2, 
      0,   0,   0,   2, 254, 255, 
    248,   1,   0,   0,  52,   0, 
      0,   0,   1,   0,  36,   0, 
      0,   0,  48,   0,   0,   0, 
     48,   0,   0,   0,  36,   0, 
      1,   0,  48,   0,   0,   0, 
      0,   0,   4,   0,   1,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   1,   2, 254, 255, 
     31,   0,   0,   2,   5,   0, 
      0, 128,   0,   0,  15, 144, 
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
      5,   0,   0,   3,   0,   0, 
     15, 128,   5,   0,  85, 144, 
      2,   0, 228, 160,   4,   0, 
      0,   4,   0,   0,  15, 128, 
      5,   0,   0, 144,   1,   0, 
    228, 160,   0,   0, 228, 128, 
      4,   0,   0,   4,   0,   0, 
     15, 128,   5,   0, 170, 144, 
      3,   0, 228, 160,   0,   0, 
    228, 128,   4,   0,   0,   4, 
      0,   0,  15, 128,   5,   0, 
    255, 144,   4,   0, 228, 160, 
      0,   0, 228, 128,   5,   0, 
      0,   3,   0,   0,  15, 128, 
      0,   0, 228, 128,   0,   0, 
     85, 144,   5,   0,   0,   3, 
      1,   0,  15, 128,   4,   0, 
     85, 144,   2,   0, 228, 160, 
      4,   0,   0,   4,   1,   0, 
     15, 128,   4,   0,   0, 144, 
      1,   0, 228, 160,   1,   0, 
    228, 128,   4,   0,   0,   4, 
      1,   0,  15, 128,   4,   0, 
    170, 144,   3,   0, 228, 160, 
      1,   0, 228, 128,   4,   0, 
      0,   4,   1,   0,  15, 128, 
      4,   0, 255, 144,   4,   0, 
    228, 160,   1,   0, 228, 128, 
      4,   0,   0,   4,   0,   0, 
     15, 128,   0,   0,   0, 144, 
      1,   0, 228, 128,   0,   0, 
    228, 128,   5,   0,   0,   3, 
      1,   0,  15, 128,   6,   0, 
     85, 144,   2,   0, 228, 160, 
      4,   0,   0,   4,   1,   0, 
     15, 128,   6,   0,   0, 144, 
      1,   0, 228, 160,   1,   0, 
    228, 128,   4,   0,   0,   4, 
      1,   0,  15, 128,   6,   0, 
    170, 144,   3,   0, 228, 160, 
      1,   0, 228, 128,   4,   0, 
      0,   4,   1,   0,  15, 128, 
      6,   0, 255, 144,   4,   0, 
    228, 160,   1,   0, 228, 128, 
      4,   0,   0,   4,   0,   0, 
     15, 128,   0,   0, 170, 144, 
      1,   0, 228, 128,   0,   0, 
    228, 128,   5,   0,   0,   3, 
      1,   0,  15, 128,   7,   0, 
     85, 144,   2,   0, 228, 160, 
      4,   0,   0,   4,   1,   0, 
     15, 128,   7,   0,   0, 144, 
      1,   0, 228, 160,   1,   0, 
    228, 128,   4,   0,   0,   4, 
      1,   0,  15, 128,   7,   0, 
    170, 144,   3,   0, 228, 160, 
      1,   0, 228, 128,   4,   0, 
      0,   4,   1,   0,  15, 128, 
      7,   0, 255, 144,   4,   0, 
    228, 160,   1,   0, 228, 128, 
      4,   0,   0,   4,   0,   0, 
     15, 128,   0,   0, 255, 144, 
      1,   0, 228, 128,   0,   0, 
    228, 128,   4,   0,   0,   4, 
      0,   0,   3, 192,   0,   0, 
    255, 128,   0,   0, 228, 160, 
      0,   0, 228, 128,   1,   0, 
      0,   2,   0,   0,  12, 192, 
      0,   0, 228, 128,   1,   0, 
      0,   2,   0,   0,  15, 224, 
      8,   0, 228, 144, 255, 255, 
      0,   0,  83,  72,  68,  82, 
    132,   3,   0,   0,  64,   0, 
      1,   0, 225,   0,   0,   0, 
     89,   0,   0,   4,  70, 142, 
     32,   0,   0,   0,   0,   0, 
      4,   0,   0,   0,  95,   0, 
      0,   3, 242,  16,  16,   0, 
      0,   0,   0,   0,  95,   0, 
      0,   3, 242,  16,  16,   0, 
      4,   0,   0,   0,  95,   0, 
      0,   3, 242,  16,  16,   0, 
      5,   0,   0,   0,  95,   0, 
      0,   3, 242,  16,  16,   0, 
      6,   0,   0,   0,  95,   0, 
      0,   3, 242,  16,  16,   0, 
      7,   0,   0,   0,  95,   0, 
      0,   3, 242,  16,  16,   0, 
      8,   0,   0,   0, 103,   0, 
      0,   4, 242,  32,  16,   0, 
      0,   0,   0,   0,   1,   0, 
      0,   0, 101,   0,   0,   3, 
    242,  32,  16,   0,   1,   0, 
      0,   0, 104,   0,   0,   2, 
      2,   0,   0,   0,  56,   0, 
      0,   8, 242,   0,  16,   0, 
      0,   0,   0,   0,  86,  21, 
     16,   0,   5,   0,   0,   0, 
     70, 142,  32,   0,   0,   0, 
      0,   0,   1,   0,   0,   0, 
     50,   0,   0,  10, 242,   0, 
     16,   0,   0,   0,   0,   0, 
      6,  16,  16,   0,   5,   0, 
      0,   0,  70, 142,  32,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,  70,  14,  16,   0, 
      0,   0,   0,   0,  50,   0, 
      0,  10, 242,   0,  16,   0, 
      0,   0,   0,   0, 166,  26, 
     16,   0,   5,   0,   0,   0, 
     70, 142,  32,   0,   0,   0, 
      0,   0,   2,   0,   0,   0, 
     70,  14,  16,   0,   0,   0, 
      0,   0,  50,   0,   0,  10, 
    242,   0,  16,   0,   0,   0, 
      0,   0, 246,  31,  16,   0, 
      5,   0,   0,   0,  70, 142, 
     32,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,  70,  14, 
     16,   0,   0,   0,   0,   0, 
     56,   0,   0,   7, 242,   0, 
     16,   0,   0,   0,   0,   0, 
     70,  14,  16,   0,   0,   0, 
      0,   0,  86,  21,  16,   0, 
      0,   0,   0,   0,  56,   0, 
      0,   8, 242,   0,  16,   0, 
      1,   0,   0,   0,  86,  21, 
     16,   0,   4,   0,   0,   0, 
     70, 142,  32,   0,   0,   0, 
      0,   0,   1,   0,   0,   0, 
     50,   0,   0,  10, 242,   0, 
     16,   0,   1,   0,   0,   0, 
      6,  16,  16,   0,   4,   0, 
      0,   0,  70, 142,  32,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,  70,  14,  16,   0, 
      1,   0,   0,   0,  50,   0, 
      0,  10, 242,   0,  16,   0, 
      1,   0,   0,   0, 166,  26, 
     16,   0,   4,   0,   0,   0, 
     70, 142,  32,   0,   0,   0, 
      0,   0,   2,   0,   0,   0, 
     70,  14,  16,   0,   1,   0, 
      0,   0,  50,   0,   0,  10, 
    242,   0,  16,   0,   1,   0, 
      0,   0, 246,  31,  16,   0, 
      4,   0,   0,   0,  70, 142, 
     32,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,  70,  14, 
     16,   0,   1,   0,   0,   0, 
     50,   0,   0,   9, 242,   0, 
     16,   0,   0,   0,   0,   0, 
      6,  16,  16,   0,   0,   0, 
      0,   0,  70,  14,  16,   0, 
      1,   0,   0,   0,  70,  14, 
     16,   0,   0,   0,   0,   0, 
     56,   0,   0,   8, 242,   0, 
     16,   0,   1,   0,   0,   0, 
     86,  21,  16,   0,   6,   0, 
      0,   0,  70, 142,  32,   0, 
      0,   0,   0,   0,   1,   0, 
      0,   0,  50,   0,   0,  10, 
    242,   0,  16,   0,   1,   0, 
      0,   0,   6,  16,  16,   0, 
      6,   0,   0,   0,  70, 142, 
     32,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,  70,  14, 
     16,   0,   1,   0,   0,   0, 
     50,   0,   0,  10, 242,   0, 
     16,   0,   1,   0,   0,   0, 
    166,  26,  16,   0,   6,   0, 
      0,   0,  70, 142,  32,   0, 
      0,   0,   0,   0,   2,   0, 
      0,   0,  70,  14,  16,   0, 
      1,   0,   0,   0,  50,   0, 
      0,  10, 242,   0,  16,   0, 
      1,   0,   0,   0, 246,  31, 
     16,   0,   6,   0,   0,   0, 
     70, 142,  32,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
     70,  14,  16,   0,   1,   0, 
      0,   0,  50,   0,   0,   9, 
    242,   0,  16,   0,   0,   0, 
      0,   0, 166,  26,  16,   0, 
      0,   0,   0,   0,  70,  14, 
     16,   0,   1,   0,   0,   0, 
     70,  14,  16,   0,   0,   0, 
      0,   0,  56,   0,   0,   8, 
    242,   0,  16,   0,   1,   0, 
      0,   0,  86,  21,  16,   0, 
      7,   0,   0,   0,  70, 142, 
     32,   0,   0,   0,   0,   0, 
      1,   0,   0,   0,  50,   0, 
      0,  10, 242,   0,  16,   0, 
      1,   0,   0,   0,   6,  16, 
     16,   0,   7,   0,   0,   0, 
     70, 142,  32,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
     70,  14,  16,   0,   1,   0, 
      0,   0,  50,   0,   0,  10, 
    242,   0,  16,   0,   1,   0, 
      0,   0, 166,  26,  16,   0, 
      7,   0,   0,   0,  70, 142, 
     32,   0,   0,   0,   0,   0, 
      2,   0,   0,   0,  70,  14, 
     16,   0,   1,   0,   0,   0, 
     50,   0,   0,  10, 242,   0, 
     16,   0,   1,   0,   0,   0, 
    246,  31,  16,   0,   7,   0, 
      0,   0,  70, 142,  32,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0,  70,  14,  16,   0, 
      1,   0,   0,   0,  50,   0, 
      0,   9, 242,  32,  16,   0, 
      0,   0,   0,   0, 246,  31, 
     16,   0,   0,   0,   0,   0, 
     70,  14,  16,   0,   1,   0, 
      0,   0,  70,  14,  16,   0, 
      0,   0,   0,   0,  54,   0, 
      0,   5, 242,  32,  16,   0, 
      1,   0,   0,   0,  70,  30, 
     16,   0,   8,   0,   0,   0, 
     62,   0,   0,   1,  83,  84, 
     65,  84, 116,   0,   0,   0, 
     22,   0,   0,   0,   2,   0, 
      0,   0,   0,   0,   0,   0, 
      8,   0,   0,   0,   5,   0, 
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
    208,   0,   0,   0,   1,   0, 
      0,   0,  76,   0,   0,   0, 
      1,   0,   0,   0,  28,   0, 
      0,   0,   0,   4, 254, 255, 
      0,   1,   0,   0, 156,   0, 
      0,   0,  60,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   1,   0,   0,   0, 
      0,   0,   0,   0,  80, 101, 
    114,  70, 114,  97, 109, 101, 
     66, 117, 102, 102, 101, 114, 
      0, 171,  60,   0,   0,   0, 
      1,   0,   0,   0, 100,   0, 
      0,   0,  64,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0, 124,   0,   0,   0, 
      0,   0,   0,   0,  64,   0, 
      0,   0,   2,   0,   0,   0, 
    140,   0,   0,   0,   0,   0, 
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
      0,   0,   7,   0,   0,   0, 
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
      0,   0,  15,  15,   0,   0, 
     80,  79,  83,  73,  84,  73, 
     79,  78,   0,  78,  79,  82, 
     77,  65,  76,   0,  65,  86, 
     71,  78,  79,  82,  77,  65, 
     76,   0,  84,  69,  88,  67, 
     79,  79,  82,  68,   0,  87, 
     79,  82,  76,  68,   0,  67, 
     79,  76,  79,  85,  82,   0, 
     79,  83,  71,  78,  76,   0, 
      0,   0,   2,   0,   0,   0, 
      8,   0,   0,   0,  56,   0, 
      0,   0,   0,   0,   0,   0, 
      1,   0,   0,   0,   3,   0, 
      0,   0,   0,   0,   0,   0, 
     15,   0,   0,   0,  68,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0,   1,   0,   0,   0, 
     15,   0,   0,   0,  83,  86, 
     95,  80,  79,  83,  73,  84, 
     73,  79,  78,   0,  67,  79, 
     76,  79,  85,  82,   0, 171
};
