// clang-format off
// Auto-generated file. Do not edit!
//   Template: src/x32-packw/gio-simd.c.in
//   Generator: tools/xngen
//
// Copyright 2024 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.


#include <assert.h>
#include <stddef.h>
#include <stdint.h>

#include "src/xnnpack/simd/s32-hvx.h"

#include "src/xnnpack/intrinsics-polyfill.h"
#include "src/xnnpack/packw.h"

static XNN_INLINE xnn_simd_s32_t
xnn_load_tail_no_oob_s32(const int32_t* input, size_t num_elements) {
  assert(num_elements <= xnn_simd_size_s32);
  int32_t buf[32];
  for (size_t i = 0; i < num_elements; ++i) {
    buf[i] = input[i];
  }
  return xnn_loadu_s32((const int32_t*) &buf[0]);
}


// Pack pre-transposed weights (GIO) for use by f32-gemm
void xnn_x32_packw_gemm_gio_ukernel_x32__hvx_u2(
  size_t g,                  // Batch size (outer loop).  usually 1
  size_t nc,                 // Number of columns and typically large
  size_t kc,                 // Number of rows and typically small
  size_t nr,                 // Matches gemm and is a multiple of vector sizes
  size_t kr,                 // unused - must be 1
  size_t sr,                 // unused - must be 1
  size_t k_stride,           // Elements per row (typically same as nc)
  const uint32_t* weights,   // Weights to pack. unaligned, unpadded
  const uint32_t* bias,      // Bias to pack. unaligned, unpadded, can be NULL
  const void* scale,         // unused
  uint32_t* packed_weights,  // packed weights output buffer - aligned, padded
  size_t extra_bytes,        // number of extra bytes between weights. aligned
  const void* params)        // unused
{
  assert(g != 0);
  assert(nc != 0);
  assert(kc != 0);
  assert(nr == 32);   // This kernel is for NR=32
  assert(kr == 1);
  assert(sr == 1);
  assert(k_stride != 0);
  assert(weights != NULL);
  assert(packed_weights != NULL);

  const xnn_simd_s32_t vzero = xnn_set1_s32(0);
  const int32_t* b = (const int32_t*) bias;
  int32_t* packed_w = (int32_t*) packed_weights;
  do {
    // NC main loop multiple of 32
    const int32_t* w = (const int32_t*) weights;
    size_t n = nc;

    for (; n >= 32; n -= 32) {
      if XNN_LIKELY(b != NULL) {
        const xnn_simd_s32_t vb0 = xnn_loadu_s32(b + 0);
        xnn_storeu_s32(packed_w + 0, vb0);
        b += 32;
      } else {
        xnn_storeu_s32(packed_w + 0, vzero);
      }
      packed_w += 32;

      // KC main loop 2x32
      size_t k = kc;
      for (; k >= 2; k -= 2) {
        const xnn_simd_s32_t v0_0 = xnn_loadu_s32(w + 0 + 0 * k_stride);
        const xnn_simd_s32_t v0_1 = xnn_loadu_s32(w + 0 + 1 * k_stride);
        xnn_storeu_s32(packed_w + 0, v0_0);
        xnn_storeu_s32(packed_w + 32, v0_1);
        w += k_stride * 2;
        packed_w += 64;
      }

      // KC remainder loop
      for (; k > 0; --k) {
        const xnn_simd_s32_t v0 = xnn_loadu_s32(w + 0);
        xnn_storeu_s32(packed_w + 0, v0);
        w += k_stride;
        packed_w += 32;
      }
      w = w - kc * k_stride + 32;  // Advance to next column of 32 int32_t
    }

    // NC remainder (1..31)
    if XNN_UNLIKELY(n != 0) {
      assert(n >= 1);
      assert(n <= 31);

      // Prepare count for valid 32-bit elements (depends on n).
      const size_t vcount0 = n;

      if XNN_LIKELY(b != NULL) {
        const xnn_simd_s32_t vb0 = xnn_load_tail_no_oob_s32(b + 0, vcount0);
        xnn_storeu_s32(packed_w + 0, vb0);
        b += n;
      } else {
        xnn_storeu_s32(packed_w + 0, vzero);
      }
      packed_w += 32;

      // KC main loop
      for (size_t k = kc; k > 0; --k) {
        const xnn_simd_s32_t v0 = xnn_load_tail_no_oob_s32(w + 0, vcount0);
        xnn_storeu_s32(packed_w + 0, v0);
        w += k_stride;
        packed_w += 32;
      }
    }
    weights += nc * kc;
  } while (--g != 0);
}

// Pack pre-transposed weights (GIO) for use by f32-gemm
void xnn_x32_packw_gemm_gio_ukernel_x64__hvx_u2(
  size_t g,                  // Batch size (outer loop).  usually 1
  size_t nc,                 // Number of columns and typically large
  size_t kc,                 // Number of rows and typically small
  size_t nr,                 // Matches gemm and is a multiple of vector sizes
  size_t kr,                 // unused - must be 1
  size_t sr,                 // unused - must be 1
  size_t k_stride,           // Elements per row (typically same as nc)
  const uint32_t* weights,   // Weights to pack. unaligned, unpadded
  const uint32_t* bias,      // Bias to pack. unaligned, unpadded, can be NULL
  const void* scale,         // unused
  uint32_t* packed_weights,  // packed weights output buffer - aligned, padded
  size_t extra_bytes,        // number of extra bytes between weights. aligned
  const void* params)        // unused
{
  assert(g != 0);
  assert(nc != 0);
  assert(kc != 0);
  assert(nr == 64);   // This kernel is for NR=64
  assert(kr == 1);
  assert(sr == 1);
  assert(k_stride != 0);
  assert(weights != NULL);
  assert(packed_weights != NULL);

  const xnn_simd_s32_t vzero = xnn_set1_s32(0);
  const int32_t* b = (const int32_t*) bias;
  int32_t* packed_w = (int32_t*) packed_weights;
  do {
    // NC main loop multiple of 64
    const int32_t* w = (const int32_t*) weights;
    size_t n = nc;

    for (; n >= 64; n -= 64) {
      if XNN_LIKELY(b != NULL) {
        const xnn_simd_s32_t vb0 = xnn_loadu_s32(b + 0);
        const xnn_simd_s32_t vb1 = xnn_loadu_s32(b + 32);
        xnn_storeu_s32(packed_w + 0, vb0);
        xnn_storeu_s32(packed_w + 32, vb1);
        b += 64;
      } else {
        xnn_storeu_s32(packed_w + 0, vzero);
        xnn_storeu_s32(packed_w + 32, vzero);
      }
      packed_w += 64;

      // KC main loop 2x64
      size_t k = kc;
      for (; k >= 2; k -= 2) {
        const xnn_simd_s32_t v0_0 = xnn_loadu_s32(w + 0 + 0 * k_stride);
        const xnn_simd_s32_t v1_0 = xnn_loadu_s32(w + 32 + 0 * k_stride);
        const xnn_simd_s32_t v0_1 = xnn_loadu_s32(w + 0 + 1 * k_stride);
        const xnn_simd_s32_t v1_1 = xnn_loadu_s32(w + 32 + 1 * k_stride);
        xnn_storeu_s32(packed_w + 0, v0_0);
        xnn_storeu_s32(packed_w + 32, v1_0);
        xnn_storeu_s32(packed_w + 64, v0_1);
        xnn_storeu_s32(packed_w + 96, v1_1);
        w += k_stride * 2;
        packed_w += 128;
      }

      // KC remainder loop
      for (; k > 0; --k) {
        const xnn_simd_s32_t v0 = xnn_loadu_s32(w + 0);
        const xnn_simd_s32_t v1 = xnn_loadu_s32(w + 32);
        xnn_storeu_s32(packed_w + 0, v0);
        xnn_storeu_s32(packed_w + 32, v1);
        w += k_stride;
        packed_w += 64;
      }
      w = w - kc * k_stride + 64;  // Advance to next column of 64 int32_t
    }

    // NC remainder (1..63)
    if XNN_UNLIKELY(n != 0) {
      assert(n >= 1);
      assert(n <= 63);

      // Prepare count for valid 32-bit elements (depends on n).
      const size_t vcount0 = (int) (n - 0) < 0 ? 0 : ((int) (n - 0) > 32 ? 32 : n - 0);
      const size_t vcount1 = (int) (n - 32) < 0 ? 0 : ((int) (n - 32) > 32 ? 32 : n - 32);

      if XNN_LIKELY(b != NULL) {
        const xnn_simd_s32_t vb0 = xnn_load_tail_no_oob_s32(b + 0, vcount0);
        const xnn_simd_s32_t vb1 = xnn_load_tail_no_oob_s32(b + 32, vcount1);
        xnn_storeu_s32(packed_w + 0, vb0);
        xnn_storeu_s32(packed_w + 32, vb1);
        b += n;
      } else {
        xnn_storeu_s32(packed_w + 0, vzero);
        xnn_storeu_s32(packed_w + 32, vzero);
      }
      packed_w += 64;

      // KC main loop
      for (size_t k = kc; k > 0; --k) {
        const xnn_simd_s32_t v0 = xnn_load_tail_no_oob_s32(w + 0, vcount0);
        const xnn_simd_s32_t v1 = xnn_load_tail_no_oob_s32(w + 32, vcount1);
        xnn_storeu_s32(packed_w + 0, v0);
        xnn_storeu_s32(packed_w + 32, v1);
        w += k_stride;
        packed_w += 64;
      }
    }
    weights += nc * kc;
  } while (--g != 0);
}

// Pack pre-transposed weights (GIO) for use by f32-gemm
void xnn_x32_packw_gemm_gio_ukernel_x96__hvx_u2(
  size_t g,                  // Batch size (outer loop).  usually 1
  size_t nc,                 // Number of columns and typically large
  size_t kc,                 // Number of rows and typically small
  size_t nr,                 // Matches gemm and is a multiple of vector sizes
  size_t kr,                 // unused - must be 1
  size_t sr,                 // unused - must be 1
  size_t k_stride,           // Elements per row (typically same as nc)
  const uint32_t* weights,   // Weights to pack. unaligned, unpadded
  const uint32_t* bias,      // Bias to pack. unaligned, unpadded, can be NULL
  const void* scale,         // unused
  uint32_t* packed_weights,  // packed weights output buffer - aligned, padded
  size_t extra_bytes,        // number of extra bytes between weights. aligned
  const void* params)        // unused
{
  assert(g != 0);
  assert(nc != 0);
  assert(kc != 0);
  assert(nr == 96);   // This kernel is for NR=96
  assert(kr == 1);
  assert(sr == 1);
  assert(k_stride != 0);
  assert(weights != NULL);
  assert(packed_weights != NULL);

  const xnn_simd_s32_t vzero = xnn_set1_s32(0);
  const int32_t* b = (const int32_t*) bias;
  int32_t* packed_w = (int32_t*) packed_weights;
  do {
    // NC main loop multiple of 96
    const int32_t* w = (const int32_t*) weights;
    size_t n = nc;

    for (; n >= 96; n -= 96) {
      if XNN_LIKELY(b != NULL) {
        const xnn_simd_s32_t vb0 = xnn_loadu_s32(b + 0);
        const xnn_simd_s32_t vb1 = xnn_loadu_s32(b + 32);
        const xnn_simd_s32_t vb2 = xnn_loadu_s32(b + 64);
        xnn_storeu_s32(packed_w + 0, vb0);
        xnn_storeu_s32(packed_w + 32, vb1);
        xnn_storeu_s32(packed_w + 64, vb2);
        b += 96;
      } else {
        xnn_storeu_s32(packed_w + 0, vzero);
        xnn_storeu_s32(packed_w + 32, vzero);
        xnn_storeu_s32(packed_w + 64, vzero);
      }
      packed_w += 96;

      // KC main loop 2x96
      size_t k = kc;
      for (; k >= 2; k -= 2) {
        const xnn_simd_s32_t v0_0 = xnn_loadu_s32(w + 0 + 0 * k_stride);
        const xnn_simd_s32_t v1_0 = xnn_loadu_s32(w + 32 + 0 * k_stride);
        const xnn_simd_s32_t v2_0 = xnn_loadu_s32(w + 64 + 0 * k_stride);
        const xnn_simd_s32_t v0_1 = xnn_loadu_s32(w + 0 + 1 * k_stride);
        const xnn_simd_s32_t v1_1 = xnn_loadu_s32(w + 32 + 1 * k_stride);
        const xnn_simd_s32_t v2_1 = xnn_loadu_s32(w + 64 + 1 * k_stride);
        xnn_storeu_s32(packed_w + 0, v0_0);
        xnn_storeu_s32(packed_w + 32, v1_0);
        xnn_storeu_s32(packed_w + 64, v2_0);
        xnn_storeu_s32(packed_w + 96, v0_1);
        xnn_storeu_s32(packed_w + 128, v1_1);
        xnn_storeu_s32(packed_w + 160, v2_1);
        w += k_stride * 2;
        packed_w += 192;
      }

      // KC remainder loop
      for (; k > 0; --k) {
        const xnn_simd_s32_t v0 = xnn_loadu_s32(w + 0);
        const xnn_simd_s32_t v1 = xnn_loadu_s32(w + 32);
        const xnn_simd_s32_t v2 = xnn_loadu_s32(w + 64);
        xnn_storeu_s32(packed_w + 0, v0);
        xnn_storeu_s32(packed_w + 32, v1);
        xnn_storeu_s32(packed_w + 64, v2);
        w += k_stride;
        packed_w += 96;
      }
      w = w - kc * k_stride + 96;  // Advance to next column of 96 int32_t
    }

    // NC remainder (1..95)
    if XNN_UNLIKELY(n != 0) {
      assert(n >= 1);
      assert(n <= 95);

      // Prepare count for valid 32-bit elements (depends on n).
      const size_t vcount0 = (int) (n - 0) < 0 ? 0 : ((int) (n - 0) > 32 ? 32 : n - 0);
      const size_t vcount1 = (int) (n - 32) < 0 ? 0 : ((int) (n - 32) > 32 ? 32 : n - 32);
      const size_t vcount2 = (int) (n - 64) < 0 ? 0 : ((int) (n - 64) > 32 ? 32 : n - 64);

      if XNN_LIKELY(b != NULL) {
        const xnn_simd_s32_t vb0 = xnn_load_tail_no_oob_s32(b + 0, vcount0);
        const xnn_simd_s32_t vb1 = xnn_load_tail_no_oob_s32(b + 32, vcount1);
        const xnn_simd_s32_t vb2 = xnn_load_tail_no_oob_s32(b + 64, vcount2);
        xnn_storeu_s32(packed_w + 0, vb0);
        xnn_storeu_s32(packed_w + 32, vb1);
        xnn_storeu_s32(packed_w + 64, vb2);
        b += n;
      } else {
        xnn_storeu_s32(packed_w + 0, vzero);
        xnn_storeu_s32(packed_w + 32, vzero);
        xnn_storeu_s32(packed_w + 64, vzero);
      }
      packed_w += 96;

      // KC main loop
      for (size_t k = kc; k > 0; --k) {
        const xnn_simd_s32_t v0 = xnn_load_tail_no_oob_s32(w + 0, vcount0);
        const xnn_simd_s32_t v1 = xnn_load_tail_no_oob_s32(w + 32, vcount1);
        const xnn_simd_s32_t v2 = xnn_load_tail_no_oob_s32(w + 64, vcount2);
        xnn_storeu_s32(packed_w + 0, v0);
        xnn_storeu_s32(packed_w + 32, v1);
        xnn_storeu_s32(packed_w + 64, v2);
        w += k_stride;
        packed_w += 96;
      }
    }
    weights += nc * kc;
  } while (--g != 0);
}

// Pack pre-transposed weights (GIO) for use by f32-gemm
void xnn_x32_packw_gemm_gio_ukernel_x128__hvx_u2(
  size_t g,                  // Batch size (outer loop).  usually 1
  size_t nc,                 // Number of columns and typically large
  size_t kc,                 // Number of rows and typically small
  size_t nr,                 // Matches gemm and is a multiple of vector sizes
  size_t kr,                 // unused - must be 1
  size_t sr,                 // unused - must be 1
  size_t k_stride,           // Elements per row (typically same as nc)
  const uint32_t* weights,   // Weights to pack. unaligned, unpadded
  const uint32_t* bias,      // Bias to pack. unaligned, unpadded, can be NULL
  const void* scale,         // unused
  uint32_t* packed_weights,  // packed weights output buffer - aligned, padded
  size_t extra_bytes,        // number of extra bytes between weights. aligned
  const void* params)        // unused
{
  assert(g != 0);
  assert(nc != 0);
  assert(kc != 0);
  assert(nr == 128);   // This kernel is for NR=128
  assert(kr == 1);
  assert(sr == 1);
  assert(k_stride != 0);
  assert(weights != NULL);
  assert(packed_weights != NULL);

  const xnn_simd_s32_t vzero = xnn_set1_s32(0);
  const int32_t* b = (const int32_t*) bias;
  int32_t* packed_w = (int32_t*) packed_weights;
  do {
    // NC main loop multiple of 128
    const int32_t* w = (const int32_t*) weights;
    size_t n = nc;

    for (; n >= 128; n -= 128) {
      if XNN_LIKELY(b != NULL) {
        const xnn_simd_s32_t vb0 = xnn_loadu_s32(b + 0);
        const xnn_simd_s32_t vb1 = xnn_loadu_s32(b + 32);
        const xnn_simd_s32_t vb2 = xnn_loadu_s32(b + 64);
        const xnn_simd_s32_t vb3 = xnn_loadu_s32(b + 96);
        xnn_storeu_s32(packed_w + 0, vb0);
        xnn_storeu_s32(packed_w + 32, vb1);
        xnn_storeu_s32(packed_w + 64, vb2);
        xnn_storeu_s32(packed_w + 96, vb3);
        b += 128;
      } else {
        xnn_storeu_s32(packed_w + 0, vzero);
        xnn_storeu_s32(packed_w + 32, vzero);
        xnn_storeu_s32(packed_w + 64, vzero);
        xnn_storeu_s32(packed_w + 96, vzero);
      }
      packed_w += 128;

      // KC main loop 2x128
      size_t k = kc;
      for (; k >= 2; k -= 2) {
        const xnn_simd_s32_t v0_0 = xnn_loadu_s32(w + 0 + 0 * k_stride);
        const xnn_simd_s32_t v1_0 = xnn_loadu_s32(w + 32 + 0 * k_stride);
        const xnn_simd_s32_t v2_0 = xnn_loadu_s32(w + 64 + 0 * k_stride);
        const xnn_simd_s32_t v3_0 = xnn_loadu_s32(w + 96 + 0 * k_stride);
        const xnn_simd_s32_t v0_1 = xnn_loadu_s32(w + 0 + 1 * k_stride);
        const xnn_simd_s32_t v1_1 = xnn_loadu_s32(w + 32 + 1 * k_stride);
        const xnn_simd_s32_t v2_1 = xnn_loadu_s32(w + 64 + 1 * k_stride);
        const xnn_simd_s32_t v3_1 = xnn_loadu_s32(w + 96 + 1 * k_stride);
        xnn_storeu_s32(packed_w + 0, v0_0);
        xnn_storeu_s32(packed_w + 32, v1_0);
        xnn_storeu_s32(packed_w + 64, v2_0);
        xnn_storeu_s32(packed_w + 96, v3_0);
        xnn_storeu_s32(packed_w + 128, v0_1);
        xnn_storeu_s32(packed_w + 160, v1_1);
        xnn_storeu_s32(packed_w + 192, v2_1);
        xnn_storeu_s32(packed_w + 224, v3_1);
        w += k_stride * 2;
        packed_w += 256;
      }

      // KC remainder loop
      for (; k > 0; --k) {
        const xnn_simd_s32_t v0 = xnn_loadu_s32(w + 0);
        const xnn_simd_s32_t v1 = xnn_loadu_s32(w + 32);
        const xnn_simd_s32_t v2 = xnn_loadu_s32(w + 64);
        const xnn_simd_s32_t v3 = xnn_loadu_s32(w + 96);
        xnn_storeu_s32(packed_w + 0, v0);
        xnn_storeu_s32(packed_w + 32, v1);
        xnn_storeu_s32(packed_w + 64, v2);
        xnn_storeu_s32(packed_w + 96, v3);
        w += k_stride;
        packed_w += 128;
      }
      w = w - kc * k_stride + 128;  // Advance to next column of 128 int32_t
    }

    // NC remainder (1..127)
    if XNN_UNLIKELY(n != 0) {
      assert(n >= 1);
      assert(n <= 127);

      // Prepare count for valid 32-bit elements (depends on n).
      const size_t vcount0 = (int) (n - 0) < 0 ? 0 : ((int) (n - 0) > 32 ? 32 : n - 0);
      const size_t vcount1 = (int) (n - 32) < 0 ? 0 : ((int) (n - 32) > 32 ? 32 : n - 32);
      const size_t vcount2 = (int) (n - 64) < 0 ? 0 : ((int) (n - 64) > 32 ? 32 : n - 64);
      const size_t vcount3 = (int) (n - 96) < 0 ? 0 : ((int) (n - 96) > 32 ? 32 : n - 96);

      if XNN_LIKELY(b != NULL) {
        const xnn_simd_s32_t vb0 = xnn_load_tail_no_oob_s32(b + 0, vcount0);
        const xnn_simd_s32_t vb1 = xnn_load_tail_no_oob_s32(b + 32, vcount1);
        const xnn_simd_s32_t vb2 = xnn_load_tail_no_oob_s32(b + 64, vcount2);
        const xnn_simd_s32_t vb3 = xnn_load_tail_no_oob_s32(b + 96, vcount3);
        xnn_storeu_s32(packed_w + 0, vb0);
        xnn_storeu_s32(packed_w + 32, vb1);
        xnn_storeu_s32(packed_w + 64, vb2);
        xnn_storeu_s32(packed_w + 96, vb3);
        b += n;
      } else {
        xnn_storeu_s32(packed_w + 0, vzero);
        xnn_storeu_s32(packed_w + 32, vzero);
        xnn_storeu_s32(packed_w + 64, vzero);
        xnn_storeu_s32(packed_w + 96, vzero);
      }
      packed_w += 128;

      // KC main loop
      for (size_t k = kc; k > 0; --k) {
        const xnn_simd_s32_t v0 = xnn_load_tail_no_oob_s32(w + 0, vcount0);
        const xnn_simd_s32_t v1 = xnn_load_tail_no_oob_s32(w + 32, vcount1);
        const xnn_simd_s32_t v2 = xnn_load_tail_no_oob_s32(w + 64, vcount2);
        const xnn_simd_s32_t v3 = xnn_load_tail_no_oob_s32(w + 96, vcount3);
        xnn_storeu_s32(packed_w + 0, v0);
        xnn_storeu_s32(packed_w + 32, v1);
        xnn_storeu_s32(packed_w + 64, v2);
        xnn_storeu_s32(packed_w + 96, v3);
        w += k_stride;
        packed_w += 128;
      }
    }
    weights += nc * kc;
  } while (--g != 0);
}
