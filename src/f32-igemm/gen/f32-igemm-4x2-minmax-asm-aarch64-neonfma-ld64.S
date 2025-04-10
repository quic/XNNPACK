// clang-format off
// Auto-generated file. Do not edit!
//   Template: src/f32-igemm/4x2-aarch64-neonfma-ld64.S.in
//   Generator: tools/xngen
//
// Copyright 2021 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include "src/xnnpack/assembly.h"

# void xnn_f32_igemm_minmax_ukernel_4x2__asm_aarch64_neonfma_ld64(
#     size_t mr,                         x0
#     size_t nc,                         x1
#     size_t kc,                         x2 / x0
#     size_t ks,                         x3 / x9
#     const float** restrict a,           x4
#     const float* restrict w,            x5
#     float* restrict c,                  x6
#     size_t cm_stride,                  x7
#     size_t cn_stride,                  [sp] -> x10
#     size_t a_offset,                   [sp + 8] -> x11
#     const float* zero,                 [sp + 16] -> x12
#     const xnn_f32_minmax_params params [sp + 24] -> (x8)

# d8-d15, x19-x30 need to be preserved if used. x18 is reserved by the OS.

# Register usage
# A0  x8  v0
# A1  x13 v1
# A2  x14 v2
# A3  x15 v3
# B    x5 v20 v21
# C   x6  v24 v25
# C   x16 v26 v27
# C   x17 v28 v29
# C   x7  v30 v31
# Clamp v4 v5

BEGIN_FUNCTION xnn_f32_igemm_minmax_ukernel_4x2__asm_aarch64_neonfma_ld64

        # Load cn_stride, a_offset
        LDP         x10, x11, [sp]

        # Load zero, params pointer
        LDP         x12, x8, [sp, 16]

        # Clamp C pointers
        CMP         x0, 2                   // if mr < 2
        ADD         x16, x6, x7             // c1 = c0 + cm_stride
        CSEL        x16, x6, x16, LO        //   c1 = c0

        # Load min/max values
        LD2R        {v4.2s, v5.2s}, [x8]

        ADD         x17, x16, x7            // c2 = c1 + cm_stride
                                            // if mr <= 2
        CSEL        x17, x16, x17, LS       //   c2 = c1

        CMP         x0, 4                   // if mr < 4
        ADD         x7, x17, x7             // c3 = c2 + cm_stride
        CSEL        x7, x17, x7, LO         //   c3 = c2

0:
        # Load initial bias from w into accumulators
        LDR         d24, [x5], 8
        MOV         v26.8b, v24.8b
        MOV         v28.8b, v24.8b
        MOV         v30.8b, v24.8b
        MOVI        v25.2s, 0
        MOVI        v27.2s, 0
        MOVI        v29.2s, 0
        MOVI        v31.2s, 0

        MOV         x9, x3                  // p = ks

1:
        # Load next 4 A pointers
        LDP         x8, x13, [x4], 16
        LDP         x14, x15, [x4], 16

        CMP         x8, x12                 // if a0 == zero
        ADD         x8, x8, x11             // a0 += a_offset
        CSEL        x8, x12, x8, EQ         //   a0 = zero, else += a0 + a_offset
        CMP         x13, x12                // if a1 == zero
        ADD         x13, x13, x11           // a1 += a_offset
        CSEL        x13, x12, x13, EQ       //   a1 = zero, else += a1 + a_offset
        CMP         x14, x12                // if a2 == zero
        ADD         x14, x14, x11           // a2 += a_offset
        CSEL        x14, x12, x14, EQ       //   a2 = zero, else += a2 + a_offset
        CMP         x15, x12                // if a3 == zero
        ADD         x15, x15, x11           // a3 += a_offset
        CSEL        x15, x12, x15, EQ       //   a3 = zero, else += a3 + a_offset

        # Is there at least 2 floats (8 bytes)?
        SUBS        x0, x2, 8               // k = kc - 8
        B.LO        4f

        # Main loop - 2 floats of A (8 bytes)
2:
        LDR         d0, [x8], 8
        LDP         d20, d21, [x5], 16
        LDR         d1, [x13], 8
        LDR         d2, [x14], 8
        LDR         d3, [x15], 8
        SUBS        x0, x0, 8
        FMLA        v24.2s, v20.2s, v0.s[0]
        FMLA        v26.2s, v20.2s, v1.s[0]
        FMLA        v28.2s, v20.2s, v2.s[0]
        FMLA        v30.2s, v20.2s, v3.s[0]
        FMLA        v25.2s, v21.2s, v0.s[1]
        FMLA        v27.2s, v21.2s, v1.s[1]
        FMLA        v29.2s, v21.2s, v2.s[1]
        FMLA        v31.2s, v21.2s, v3.s[1]
        B.HS        2b

        # Is there a remainder?- 1 float of A (4 bytes)
        TBNZ        x0, 2, 4f

3:
        # ks loop
        SUBS        x9, x9, 32              // ks -= MR * sizeof(void*)
        B.HI        1b

        FADD        v24.2s, v24.2s, v25.2s
        FADD        v26.2s, v26.2s, v27.2s
        FADD        v28.2s, v28.2s, v29.2s
        FADD        v30.2s, v30.2s, v31.2s

        # Clamp
        FMAX        v24.2s, v24.2s, v4.2s
        SUBS        x1, x1, 2
        FMAX        v26.2s, v26.2s, v4.2s
        FMAX        v28.2s, v28.2s, v4.2s
        FMAX        v30.2s, v30.2s, v4.2s
        FMIN        v24.2s, v24.2s, v5.2s
        FMIN        v26.2s, v26.2s, v5.2s
        FMIN        v28.2s, v28.2s, v5.2s
        FMIN        v30.2s, v30.2s, v5.2s

        # Store full 4 x 2
        B.LO        5f

        STR         d30, [x7]
        ADD         x7,  x7, x10
        STR         d28, [x17]
        ADD         x17, x17, x10
        STR         d26, [x16]
        ADD         x16, x16, x10
        STR         d24, [x6]
        ADD         x6,  x6, x10

        SUB         x4, x4, x3              // a -= ks

        # nc loop
        B.HI        0b
        RET

        # Remainder- 1 float of A
4:
        LDR         s0, [x8], 4
        LDR         d20, [x5], 8
        LDR         s1, [x13], 4
        LDR         s2, [x14], 4
        LDR         s3, [x15], 4
        FMLA        v24.2s, v20.2s, v0.s[0]
        FMLA        v26.2s, v20.2s, v1.s[0]
        FMLA        v28.2s, v20.2s, v2.s[0]
        FMLA        v30.2s, v20.2s, v3.s[0]
        B           3b

        # Store odd width
5:
        STR         s30,  [x7]
        STR         s28, [x17]
        STR         s26, [x16]
        STR         s24,  [x6]
        RET

END_FUNCTION xnn_f32_igemm_minmax_ukernel_4x2__asm_aarch64_neonfma_ld64

#ifdef __ELF__
.section ".note.GNU-stack","",%progbits
#endif
