// Auto-generated file. Do not edit!
//   Template: src/f32-raddextexp/avx512f-p5-scalef.c.in
//   Generator: tools/xngen
//
// Copyright 2019 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include <assert.h>
#include <math.h>

#include <immintrin.h>

#include "src/xnnpack/common.h"
#include "src/xnnpack/intrinsics-polyfill.h"
#include "src/xnnpack/raddextexp.h"


void xnn_f32_raddextexp_ukernel__avx512f_p5_scalef_u64(
    size_t batch,
    const float* input,
    float* sum)
{
  assert(batch != 0);
  assert(batch % sizeof(float) == 0);
  assert(input != NULL);
  assert(sum != NULL);

  const __m512 vlog2e = _mm512_set1_ps(0x1.715476p+0f);
  const __m512 vminus_ln2_hi = _mm512_set1_ps(-0x1.62E43p-1f);
  const __m512 vminus_ln2_lo = _mm512_set1_ps(0x1.05C61p-29f);

  const __m512 vc0 = _mm512_set1_ps(1.0f);
  const __m512 vc1 = _mm512_set1_ps(0x1.FFFFF6p-1f);
  const __m512 vc2 = _mm512_set1_ps(0x1.FFFDC6p-2f);
  const __m512 vc3 = _mm512_set1_ps(0x1.555A80p-3f);
  const __m512 vc4 = _mm512_set1_ps(0x1.573A1Ap-5f);
  const __m512 vc5 = _mm512_set1_ps(0x1.0F9F9Cp-7f);

  const __m512 vminus_inf = _mm512_set1_ps(-INFINITY);

  __m512 vaccv0 = _mm512_setzero_ps();
  __m512 vacce0 = vminus_inf;
  for (; batch >= 64 * sizeof(float); batch -= 64 * sizeof(float)) {
    // Load 64 (4x16) inputs at a time.
    const __m512 vx0 = _mm512_loadu_ps(input);
    const __m512 vx1 = _mm512_loadu_ps(input + 16);
    const __m512 vx2 = _mm512_loadu_ps(input + 32);
    const __m512 vx3 = _mm512_loadu_ps(input + 48);
    input += 64;

    // Compute reduced argument batch := round(input / log(2)).
    const __m512 vn0 = _mm512_roundscale_ps(_mm512_mul_ps(vx0, vlog2e), 0);
    const __m512 vn1 = _mm512_roundscale_ps(_mm512_mul_ps(vx1, vlog2e), 0);
    const __m512 vn2 = _mm512_roundscale_ps(_mm512_mul_ps(vx2, vlog2e), 0);
    const __m512 vn3 = _mm512_roundscale_ps(_mm512_mul_ps(vx3, vlog2e), 0);

    // Compute reduced argument t := input - batch * log(2).
    // Use Cody-Waite range reduction method (note two constants to represent log(2)) to improve accuracy.
    __m512 vt0 = _mm512_fmadd_ps(vn0, vminus_ln2_hi, vx0);
    __m512 vt1 = _mm512_fmadd_ps(vn1, vminus_ln2_hi, vx1);
    __m512 vt2 = _mm512_fmadd_ps(vn2, vminus_ln2_hi, vx2);
    __m512 vt3 = _mm512_fmadd_ps(vn3, vminus_ln2_hi, vx3);

    vt0 = _mm512_fmadd_ps(vn0, vminus_ln2_lo, vt0);
    vt1 = _mm512_fmadd_ps(vn1, vminus_ln2_lo, vt1);
    vt2 = _mm512_fmadd_ps(vn2, vminus_ln2_lo, vt2);
    vt3 = _mm512_fmadd_ps(vn3, vminus_ln2_lo, vt3);

    // Compute degree-5 polynomial approximation for exp(t) on [-log(2)/2, log(2)/2].
    __m512 vp0 = _mm512_fmadd_ps(vc5, vt0, vc4);
    __m512 vp1 = _mm512_fmadd_ps(vc5, vt1, vc4);
    __m512 vp2 = _mm512_fmadd_ps(vc5, vt2, vc4);
    __m512 vp3 = _mm512_fmadd_ps(vc5, vt3, vc4);

    vp0 = _mm512_fmadd_ps(vp0, vt0, vc3);
    vp1 = _mm512_fmadd_ps(vp1, vt1, vc3);
    vp2 = _mm512_fmadd_ps(vp2, vt2, vc3);
    vp3 = _mm512_fmadd_ps(vp3, vt3, vc3);

    vp0 = _mm512_fmadd_ps(vp0, vt0, vc2);
    vp1 = _mm512_fmadd_ps(vp1, vt1, vc2);
    vp2 = _mm512_fmadd_ps(vp2, vt2, vc2);
    vp3 = _mm512_fmadd_ps(vp3, vt3, vc2);

    vp0 = _mm512_fmadd_ps(vp0, vt0, vc1);
    vp1 = _mm512_fmadd_ps(vp1, vt1, vc1);
    vp2 = _mm512_fmadd_ps(vp2, vt2, vc1);
    vp3 = _mm512_fmadd_ps(vp3, vt3, vc1);

    vp0 = _mm512_fmadd_ps(vp0, vt0, vc0);
    vp1 = _mm512_fmadd_ps(vp1, vt1, vc0);
    vp2 = _mm512_fmadd_ps(vp2, vt2, vc0);
    vp3 = _mm512_fmadd_ps(vp3, vt3, vc0);

    // Accumulate "extended" floating-point numbers in ("mantissa", "exponent") representation where
    //  - vnX is "exponent"
    //  - vpX is "mantissa"
    //
    // exp2(ae) * av + exp2(be) * bv =
    //   = exp2(max(ae, be)) * exp2(ae - max(ae, be)) * av + exp2(max(ae, be)) * exp2(be - max(ae, be)) * bv
    //   = exp2(max_e) * (exp2(ae - max_e) * av + exp2(be - max_e) * bv)
    //   = exp2(max_e) * (exp2(delta_ae) * av + exp2(delta_be) * bv)
    //
    // For computational efficiency we add three "extended" floating-point numbers at a time.
    __m512 vmax_e0 = _mm512_max_ps(vacce0, vn0);
    vmax_e0 = _mm512_max_ps(vmax_e0, vn1);
    vmax_e0 = _mm512_max_ps(vmax_e0, vn2);
    vmax_e0 = _mm512_max_ps(vmax_e0, vn3);

    const __m512 vdelta_acce0 = _mm512_sub_ps(vacce0, vmax_e0);
    const __m512 vdelta_e0 = _mm512_sub_ps(vn0, vmax_e0);
    const __m512 vdelta_e1 = _mm512_sub_ps(vn1, vmax_e0);
    const __m512 vdelta_e2 = _mm512_sub_ps(vn2, vmax_e0);
    const __m512 vdelta_e3 = _mm512_sub_ps(vn3, vmax_e0);

    // Update accumulated "mantissa" and "exponent" values
    vaccv0 = _mm512_scalef_ps(vaccv0, vdelta_acce0);
    vaccv0 = _mm512_add_ps(vaccv0, _mm512_scalef_ps(vp0, vdelta_e0));
    vaccv0 = _mm512_add_ps(vaccv0, _mm512_scalef_ps(vp1, vdelta_e1));
    vaccv0 = _mm512_add_ps(vaccv0, _mm512_scalef_ps(vp2, vdelta_e2));
    vaccv0 = _mm512_add_ps(vaccv0, _mm512_scalef_ps(vp3, vdelta_e3));

    vacce0 = vmax_e0;
  }

  // Reduce partial sums of "extended" floating-point numbers into a single "extended" SIMD vector of sums.
  __m512 vaccv = vaccv0;
  __m512 vacce = vacce0;

  for (; batch >= 16 * sizeof(float); batch -= 16 * sizeof(float)) {
    // Load 16 inputs at a time.
    const __m512 vx = _mm512_loadu_ps(input);
    input += 16;

    // Compute reduced argument batch := round(input / log(2)).
    const __m512 vn = _mm512_roundscale_ps(_mm512_mul_ps(vx, vlog2e), 0);

    // Compute reduced argument t := input - batch * log(2).
    // Use Cody-Waite range reduction method (note two constants to represent log(2)) to improve accuracy.
    __m512 vt = _mm512_fmadd_ps(vn, vminus_ln2_hi, vx);
    vt = _mm512_fmadd_ps(vn, vminus_ln2_lo, vt);

    // Compute degree-5 polynomial approximation for exp(t) on [-log(2)/2, log(2)/2].
    __m512 vp = _mm512_fmadd_ps(vc5, vt, vc4);
    vp = _mm512_fmadd_ps(vp, vt, vc3);
    vp = _mm512_fmadd_ps(vp, vt, vc2);
    vp = _mm512_fmadd_ps(vp, vt, vc1);
    vp = _mm512_fmadd_ps(vp, vt, vc0);

    // Accumulate "extended" floating-point numbers in ("mantissa", "exponent") representation.
    const __m512 vmax_e = _mm512_max_ps(vacce, vn);
    const __m512 vdelta_acce = _mm512_sub_ps(vacce, vmax_e);
    const __m512 vdelta_e = _mm512_sub_ps(vn, vmax_e);
    vaccv = _mm512_scalef_ps(vaccv, vdelta_acce);
    vaccv = _mm512_add_ps(vaccv, _mm512_scalef_ps(vp, vdelta_e));

    vacce = vmax_e;
  }
  if XNN_UNLIKELY(batch != 0) {
    // Prepare mask for valid 32-bit batch (depends on batch).
    batch >>= XNN_LOG2_SIZEOF_FLOAT;
    const __mmask16 vmask = _cvtu32_mask16((uint32_t) ((UINT32_C(1) << batch) - UINT32_C(1)));

    // Load up to 15 inputs at a time.
    const __m512 vx = _mm512_maskz_loadu_ps(vmask, input);

    // Compute reduced argument batch := round(input / log(2)).
    const __m512 vn = _mm512_roundscale_ps(_mm512_mul_ps(vx, vlog2e), 0);

    // Compute reduced argument t := input - batch * log(2).
    // Use Cody-Waite range reduction method (note two constants to represent log(2)) to improve accuracy.
    __m512 vt = _mm512_fmadd_ps(vn, vminus_ln2_hi, vx);
    vt = _mm512_fmadd_ps(vn, vminus_ln2_lo, vt);

    // Compute degree-5 polynomial approximation for exp(t) on [-log(2)/2, log(2)/2].
    __m512 vp = _mm512_fmadd_ps(vc5, vt, vc4);
    vp = _mm512_fmadd_ps(vp, vt, vc3);
    vp = _mm512_fmadd_ps(vp, vt, vc2);
    vp = _mm512_fmadd_ps(vp, vt, vc1);
    vp = _mm512_fmadd_ps(vp, vt, vc0);

    // Accumulate "extended" floating-point numbers in ("mantissa", "exponent") representation.
    const __m512 vmax_e = _mm512_mask_max_ps(vacce, vmask, vacce, vn);
    const __m512 vdelta_acce = _mm512_sub_ps(vacce, vmax_e);
    const __m512 vdelta_e = _mm512_sub_ps(vn, vmax_e);
    vaccv = _mm512_mask_scalef_ps(vaccv, vmask, vaccv, vdelta_acce);
    vaccv = _mm512_mask_add_ps(vaccv, vmask, vaccv, _mm512_maskz_scalef_ps(vmask, vp, vdelta_e));
    vacce = vmax_e;
  }

  // Reduce partial sums of "extended" floating-point numbers into a single "extended" floating-point sum.
  const float vmax_acce = _mm512_reduce_max_ps(vacce);
  const __m512 vdelta_acce = _mm512_sub_ps(vacce, _mm512_set1_ps(vmax_acce));

  sum[0] = _mm512_reduce_add_ps(_mm512_scalef_ps(vaccv, vdelta_acce));
  sum[1] = vmax_acce;
}
