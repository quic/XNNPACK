// Auto-generated file. Do not edit!
//   Template: src/f32-vsqrt/avx-sqrt.c.in
//   Generator: tools/xngen
//
// Copyright 2020 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include <assert.h>

#include <immintrin.h>

#include "src/xnnpack/common.h"
#include "src/xnnpack/vunary.h"


void xnn_f32_vsqrt_ukernel__avx_sqrt_u32(
    size_t batch,
    const float* input,
    float* output,
    const struct xnn_f32_default_params params[restrict XNN_MIN_ELEMENTS(1)])
{
  static const int32_t mask_table[14] = {-1, -1, -1, -1, -1, -1, -1, 0, 0, 0, 0, 0, 0, 0};

  assert(batch != 0);
  assert(batch % sizeof(float) == 0);
  assert(input != NULL);
  assert(output != NULL);

  for (; batch >= 32 * sizeof(float); batch -= 32 * sizeof(float)) {
    const __m256 vx01234567 = _mm256_loadu_ps(input);
    const __m256 vx89ABCDEF = _mm256_loadu_ps(input + 8);
    const __m256 vxGHIJKLMN = _mm256_loadu_ps(input + 16);
    const __m256 vxOPQRSTUV = _mm256_loadu_ps(input + 24);
    input += 32;

    const __m256 vy01234567 = _mm256_sqrt_ps(vx01234567);
    const __m256 vy89ABCDEF = _mm256_sqrt_ps(vx89ABCDEF);
    const __m256 vyGHIJKLMN = _mm256_sqrt_ps(vxGHIJKLMN);
    const __m256 vyOPQRSTUV = _mm256_sqrt_ps(vxOPQRSTUV);

    _mm256_storeu_ps(output, vy01234567);
    _mm256_storeu_ps(output + 8, vy89ABCDEF);
    _mm256_storeu_ps(output + 16, vyGHIJKLMN);
    _mm256_storeu_ps(output + 24, vyOPQRSTUV);
    output += 32;
  }
  for (; batch >= 8 * sizeof(float); batch -= 8 * sizeof(float)) {
    const __m256 vx = _mm256_loadu_ps(input);
    input += 8;
    const __m256 vy = _mm256_sqrt_ps(vx);
    _mm256_storeu_ps(output, vy);
    output += 8;
  }
  if XNN_UNLIKELY(batch != 0) {
    assert(batch >= 1 * sizeof(float));
    assert(batch <= 7 * sizeof(float));
    const __m256i vmask = _mm256_loadu_si256((const __m256i*) ((uintptr_t) &mask_table[7] - batch));

    const __m256 vx = _mm256_maskload_ps(input, vmask);
    const __m256 vy = _mm256_sqrt_ps(vx);

    __m128 vy_lo = _mm256_castps256_ps128(vy);
    if (batch & (4 * sizeof(float))) {
      _mm_storeu_ps(output, vy_lo);
      vy_lo = _mm256_extractf128_ps(vy, 1);
      output += 4;
    }
    if (batch & (2 * sizeof(float))) {
      _mm_storel_pi((__m64*) output, vy_lo);
      vy_lo = _mm_movehl_ps(vy_lo, vy_lo);
      output += 2;
    }
    if (batch & (1 * sizeof(float))) {
      _mm_store_ss(output, vy_lo);
    }
  }
}
