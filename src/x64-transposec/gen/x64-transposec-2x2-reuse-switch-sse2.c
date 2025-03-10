// Auto-generated file. Do not edit!
//   Template: src/x32-transposec/sse2.c.in
//   Generator: tools/xngen
//
// Copyright 2021 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include <immintrin.h>

#include <assert.h>

#include "src/xnnpack/common.h"
#include "src/xnnpack/math.h"
#include "src/xnnpack/transpose.h"
#include "src/xnnpack/unaligned.h"


void xnn_x64_transposec_ukernel__2x2_reuse_switch_sse2(
    const uint64_t* input,
    uint64_t* output,
    size_t input_stride,
    size_t output_stride,
    size_t block_width,
    size_t block_height) XNN_OOB_READS
{
  assert(block_width == 1 || output_stride >= block_height * sizeof(uint64_t));
  assert(block_height == 1 || input_stride >= block_width * sizeof(uint64_t));

  const size_t tile_height = 2;
  const size_t tile_width = 2;
  const size_t tile_hbytes = tile_height * sizeof(uint64_t);
  const size_t tile_wbytes = tile_width * sizeof(uint64_t);
  const size_t input_reset = tile_wbytes - round_down_po2(block_height, tile_height) * input_stride;
  const size_t output_reset = tile_width * output_stride - round_down_po2(block_height, 2) * sizeof(uint64_t);

  const uint64_t* i0 = input;
  uint64_t* o = (uint64_t*) output;

  do {
    const size_t rem = min(block_width - 1, 1);
    const size_t oN_stride = rem * output_stride;
    size_t bh = block_height;
    for (; bh >= 2; bh -= 2) {
      const __m128i v1_0 = _mm_loadu_si128((const __m128i*) i0);
      i0 = (uint64_t*) ((uintptr_t) i0 + input_stride);
      const __m128i v1_1 = _mm_loadu_si128((const __m128i*) i0);
      i0 = (uint64_t*) ((uintptr_t) i0 + input_stride);

      const __m128i v0_0 = _mm_unpacklo_epi64(v1_0, v1_1);
      const __m128i v0_1 = _mm_unpackhi_epi64(v1_0, v1_1);




      uint64_t* oN = (uint64_t*) ((uintptr_t) o + oN_stride);
      switch (rem) {
        case 1:
          _mm_storeu_si128((__m128i*) oN, v0_1);
          XNN_FALLTHROUGH
        case 0:
          _mm_storeu_si128((__m128i*) o, v0_0);
          o = (uint64_t*) ((uintptr_t) o + tile_hbytes);
          break;
        default:
          XNN_UNREACHABLE;
      }
    }
    if (bh != 0) {
      const __m128i v1_0 = _mm_loadu_si128((const __m128i*) i0);
      const __m128i v1_1 = _mm_undefined_si128();

      __m128i v0_0 = _mm_unpacklo_epi64(v1_0, v1_1);
      __m128i v0_1 = _mm_unpackhi_epi64(v1_0, v1_1);




      if (bh & 1) {
        uint64_t* oN = (uint64_t*) ((uintptr_t) o + oN_stride);
        switch (rem) {
          case 1:
            _mm_storel_epi64((__m128i*) oN, v0_1);
            XNN_FALLTHROUGH
          case 0:
            _mm_storel_epi64((__m128i*) o, v0_0);
            break;
          default:
            XNN_UNREACHABLE;
        }
      }

    }

    i0 = (const uint64_t*) ((uintptr_t) i0 + input_reset);
    o = (uint64_t*) ((uintptr_t) o + output_reset);
    block_width = doz(block_width, tile_width);
  } while (block_width != 0);
}
