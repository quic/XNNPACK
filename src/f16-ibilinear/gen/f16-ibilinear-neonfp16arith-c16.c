// clang-format off
// Auto-generated file. Do not edit!
//   Template: src/f16-ibilinear/neonfp16arith.c.in
//   Generator: tools/xngen
//
// Copyright 2022 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include <assert.h>

#include <arm_neon.h>

#include "src/xnnpack/common.h"
#include "src/xnnpack/ibilinear.h"
#include "src/xnnpack/math.h"


void xnn_f16_ibilinear_ukernel__neonfp16arith_c16(
    size_t output_pixels,
    size_t channels,
    const xnn_float16** restrict input,
    size_t input_offset,
    const xnn_float16* restrict weights,
    xnn_float16* restrict output,
    size_t output_increment) XNN_OOB_READS
{
  assert(output_pixels != 0);
  assert(channels != 0);
  assert(channels % sizeof(uint16_t) == 0);

  uint16_t* o = (uint16_t*) output;
  do {
    const uint16_t* i0 = (const uint16_t*) ((uintptr_t) input[0] + input_offset);
    const uint16_t* i1 = (const uint16_t*) ((uintptr_t) input[1] + input_offset);
    const uint16_t* i2 = (const uint16_t*) ((uintptr_t) input[2] + input_offset);
    const uint16_t* i3 = (const uint16_t*) ((uintptr_t) input[3] + input_offset);
    input += 4;

    const float16x8_t valphah = vreinterpretq_f16_u16(vld1q_dup_u16((const uint16_t*)weights)); weights = weights + 1;
    const float16x8_t valphav = vreinterpretq_f16_u16(vld1q_dup_u16((const uint16_t*)weights)); weights = weights + 1;

    size_t c = channels;
    for (; c >= 16 * sizeof(uint16_t); c -= 16 * sizeof(uint16_t)) {
      const float16x8_t vtl456789AB = vreinterpretq_f16_u16(vld1q_u16(i0)); i0 += 8;
      const float16x8_t vtr456789AB = vreinterpretq_f16_u16(vld1q_u16(i1)); i1 += 8;
      const float16x8_t vbl456789AB = vreinterpretq_f16_u16(vld1q_u16(i2)); i2 += 8;
      const float16x8_t vbr456789AB = vreinterpretq_f16_u16(vld1q_u16(i3)); i3 += 8;
      const float16x8_t vtlCDEFGHIJ = vreinterpretq_f16_u16(vld1q_u16(i0)); i0 += 8;
      const float16x8_t vtrCDEFGHIJ = vreinterpretq_f16_u16(vld1q_u16(i1)); i1 += 8;
      const float16x8_t vblCDEFGHIJ = vreinterpretq_f16_u16(vld1q_u16(i2)); i2 += 8;
      const float16x8_t vbrCDEFGHIJ = vreinterpretq_f16_u16(vld1q_u16(i3)); i3 += 8;

      const float16x8_t vtd456789AB = vsubq_f16(vtr456789AB, vtl456789AB);
      const float16x8_t vbd456789AB = vsubq_f16(vbr456789AB, vbl456789AB);
      const float16x8_t vtdCDEFGHIJ = vsubq_f16(vtrCDEFGHIJ, vtlCDEFGHIJ);
      const float16x8_t vbdCDEFGHIJ = vsubq_f16(vbrCDEFGHIJ, vblCDEFGHIJ);

      const float16x8_t vt456789AB = vfmaq_f16(vtl456789AB, vtd456789AB, valphah);
      const float16x8_t vb456789AB = vfmaq_f16(vbl456789AB, vbd456789AB, valphah);
      const float16x8_t vtCDEFGHIJ = vfmaq_f16(vtlCDEFGHIJ, vtdCDEFGHIJ, valphah);
      const float16x8_t vbCDEFGHIJ = vfmaq_f16(vblCDEFGHIJ, vbdCDEFGHIJ, valphah);

      const float16x8_t vd456789AB = vsubq_f16(vb456789AB, vt456789AB);
      const float16x8_t vdCDEFGHIJ = vsubq_f16(vbCDEFGHIJ, vtCDEFGHIJ);

      const float16x8_t vo456789AB = vfmaq_f16(vt456789AB, vd456789AB, valphav);
      const float16x8_t voCDEFGHIJ = vfmaq_f16(vtCDEFGHIJ, vdCDEFGHIJ, valphav);

      vst1q_u16(o, vreinterpretq_u16_f16(vo456789AB)); o += 8;
      vst1q_u16(o, vreinterpretq_u16_f16(voCDEFGHIJ)); o += 8;
    }
    for (; c >= 8 * sizeof(uint16_t); c -= 8 * sizeof(uint16_t)) {
      const float16x8_t vtl = vreinterpretq_f16_u16(vld1q_u16(i0)); i0 += 8;
      const float16x8_t vtr = vreinterpretq_f16_u16(vld1q_u16(i1)); i1 += 8;
      const float16x8_t vbl = vreinterpretq_f16_u16(vld1q_u16(i2)); i2 += 8;
      const float16x8_t vbr = vreinterpretq_f16_u16(vld1q_u16(i3)); i3 += 8;

      const float16x8_t vtd = vsubq_f16(vtr, vtl);
      const float16x8_t vbd = vsubq_f16(vbr, vbl);

      const float16x8_t vt = vfmaq_f16(vtl, vtd, valphah);
      const float16x8_t vb = vfmaq_f16(vbl, vbd, valphah);

      const float16x8_t vd = vsubq_f16(vb, vt);

      const float16x8_t vo = vfmaq_f16(vt, vd, valphav);

      vst1q_u16(o, vreinterpretq_u16_f16(vo)); o += 8;
    }
    if XNN_UNLIKELY(c != 0) {
      const float16x8_t vtl = vreinterpretq_f16_u16(vld1q_u16(i0));
      const float16x8_t vtr = vreinterpretq_f16_u16(vld1q_u16(i1));
      const float16x8_t vbl = vreinterpretq_f16_u16(vld1q_u16(i2));
      const float16x8_t vbr = vreinterpretq_f16_u16(vld1q_u16(i3));

      const float16x8_t vtd = vsubq_f16(vtr, vtl);
      const float16x8_t vbd = vsubq_f16(vbr, vbl);

      const float16x8_t vt = vfmaq_f16(vtl, vtd, valphah);
      const float16x8_t vb = vfmaq_f16(vbl, vbd, valphah);

      const float16x8_t vd = vsubq_f16(vb, vt);

      float16x8_t vo = vfmaq_f16(vt, vd, valphav);

      float16x4_t vo_lo = vget_low_f16(vo);
      if (c & (4 * sizeof(uint16_t))) {
        vst1_u16(o, vreinterpret_u16_f16(vo_lo)); o += 4;
        vo_lo = vget_high_f16(vo);
      }
      if (c & (2 * sizeof(uint16_t))) {
        vst1_lane_u32((void*) o, vreinterpret_u32_f16(vo_lo), 0); o += 2;
        vo_lo = vext_f16(vo_lo, vo_lo, 2);
      }
      if (c & (1 * sizeof(uint16_t))) {
        vst1_lane_u16(o, vreinterpret_u16_f16(vo_lo), 0); o += 1;
      }
    }

    o = (uint16_t*) ((uintptr_t) o + output_increment);
  } while (--output_pixels != 0);
}
