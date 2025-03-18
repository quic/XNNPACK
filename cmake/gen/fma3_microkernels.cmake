# Copyright 2022 Google LLC
#
# This source code is licensed under the BSD-style license found in the
# LICENSE file in the root directory of this source tree.
#
# Description: microkernel filename lists for fma3
#
# Auto-generated file. Do not edit!
#   Generator: tools/update-microkernels.py


SET(PROD_FMA3_MICROKERNEL_SRCS
  src/f16-dwconv/gen/f16-dwconv-3p16c-minmax-fma3.c
  src/f16-dwconv/gen/f16-dwconv-4p16c-minmax-fma3.c
  src/f16-dwconv/gen/f16-dwconv-9p16c-minmax-fma3.c
  src/f16-dwconv/gen/f16-dwconv-25p8c-minmax-fma3-acc2.c
  src/f16-ibilinear/gen/f16-ibilinear-fma3-c8.c
  src/f16-vmulcaddc/gen/f16-vmulcaddc-c8-minmax-fma3-2x.c
  src/f16-vtanh/gen/f16-vtanh-fma3-polynomial-p19h9t2-u32.c
  src/f32-dwconv/gen/f32-dwconv-3p16c-minmax-fma3.c
  src/f32-dwconv/gen/f32-dwconv-4p16c-minmax-fma3.c
  src/f32-dwconv/gen/f32-dwconv-9p16c-minmax-fma3.c
  src/f32-dwconv/gen/f32-dwconv-25p16c-minmax-fma3.c
  src/f32-gemm/gen/f32-gemm-1x8-minmax-fma3-broadcast.c
  src/f32-gemm/gen/f32-gemm-1x16-minmax-fma3-broadcast.c
  src/f32-gemm/gen/f32-gemm-1x16s4-minmax-fma3-broadcast.c
  src/f32-gemm/gen/f32-gemm-4x8-minmax-fma3-broadcast.c
  src/f32-gemm/gen/f32-gemm-4x16s4-minmax-fma3-broadcast.c
  src/f32-gemm/gen/f32-gemm-5x8-minmax-fma3-broadcast.c
  src/f32-gemm/gen/f32-gemm-5x16-minmax-fma3-broadcast.c
  src/f32-gemm/gen/f32-gemm-10x8-minmax-fma3-broadcast.c
  src/f32-igemm/gen/f32-igemm-1x8-minmax-fma3-broadcast.c
  src/f32-igemm/gen/f32-igemm-1x16-minmax-fma3-broadcast.c
  src/f32-igemm/gen/f32-igemm-1x16s4-minmax-fma3-broadcast.c
  src/f32-igemm/gen/f32-igemm-4x8-minmax-fma3-broadcast.c
  src/f32-igemm/gen/f32-igemm-4x16s4-minmax-fma3-broadcast.c
  src/f32-igemm/gen/f32-igemm-5x8-minmax-fma3-broadcast.c
  src/f32-igemm/gen/f32-igemm-5x16-minmax-fma3-broadcast-prfm.c
  src/f32-igemm/gen/f32-igemm-10x8-minmax-fma3-broadcast.c
  src/f32-qc4w-gemm/gen/f32-qc4w-gemm-1x16-minmax-fma3-broadcast.c
  src/f32-qc4w-gemm/gen/f32-qc4w-gemm-3x16-minmax-fma3-broadcast.c
  src/f32-qc8w-gemm/gen/f32-qc8w-gemm-1x16-minmax-fma3-broadcast.c
  src/f32-qc8w-gemm/gen/f32-qc8w-gemm-5x16-minmax-fma3-broadcast.c
  src/f32-vapproxgelu/gen/f32-vapproxgelu-fma3-rational-12-10-div.c
  src/f32-vcmul/gen/f32-vcmul-fma3-u16.c
  src/f32-vcos/gen/f32-vcos-fma3-rational-5-4-div.c
  src/f32-vgelu/gen/f32-vgelu-fma3-rational-12-10-div.c
  src/f32-vhswish/gen/f32-vhswish-fma3-u16.c
  src/f32-vlog/gen/f32-vlog-fma3-rational-3-3-div.c
  src/f32-vrsqrt/gen/f32-vrsqrt-fma3-rsqrt-u16.c
  src/f32-vsin/gen/f32-vsin-fma3-rational-5-4-div.c
  src/f32-vsqrt/gen/f32-vsqrt-fma3-rsqrt-u16.c
  src/f32-vtanh/gen/f32-vtanh-fma3-rational-9-8-div.c)

SET(NON_PROD_FMA3_MICROKERNEL_SRCS
  src/f16-dwconv/gen/f16-dwconv-3p8c-minmax-fma3-acc2.c
  src/f16-dwconv/gen/f16-dwconv-3p8c-minmax-fma3.c
  src/f16-dwconv/gen/f16-dwconv-3p16c-minmax-fma3-acc2.c
  src/f16-dwconv/gen/f16-dwconv-3p32c-minmax-fma3-acc2.c
  src/f16-dwconv/gen/f16-dwconv-3p32c-minmax-fma3.c
  src/f16-dwconv/gen/f16-dwconv-4p8c-minmax-fma3-acc2.c
  src/f16-dwconv/gen/f16-dwconv-4p8c-minmax-fma3.c
  src/f16-dwconv/gen/f16-dwconv-4p16c-minmax-fma3-acc2.c
  src/f16-dwconv/gen/f16-dwconv-4p32c-minmax-fma3-acc2.c
  src/f16-dwconv/gen/f16-dwconv-4p32c-minmax-fma3.c
  src/f16-dwconv/gen/f16-dwconv-9p8c-minmax-fma3-acc2.c
  src/f16-dwconv/gen/f16-dwconv-9p8c-minmax-fma3.c
  src/f16-dwconv/gen/f16-dwconv-9p16c-minmax-fma3-acc2.c
  src/f16-dwconv/gen/f16-dwconv-9p32c-minmax-fma3-acc2.c
  src/f16-dwconv/gen/f16-dwconv-9p32c-minmax-fma3.c
  src/f16-dwconv/gen/f16-dwconv-25p8c-minmax-fma3.c
  src/f16-dwconv/gen/f16-dwconv-25p16c-minmax-fma3-acc2.c
  src/f16-dwconv/gen/f16-dwconv-25p16c-minmax-fma3.c
  src/f16-dwconv/gen/f16-dwconv-25p32c-minmax-fma3-acc2.c
  src/f16-dwconv/gen/f16-dwconv-25p32c-minmax-fma3.c
  src/f16-ibilinear/gen/f16-ibilinear-fma3-c16.c
  src/f16-vmulcaddc/gen/f16-vmulcaddc-c16-minmax-fma3-2x.c
  src/f16-vtanh/gen/f16-vtanh-fma3-expm1minus-rr1-p3h2ts-div-u8.c
  src/f16-vtanh/gen/f16-vtanh-fma3-expm1minus-rr1-p3h2ts-div-u16.c
  src/f16-vtanh/gen/f16-vtanh-fma3-expm1minus-rr1-p3h2ts-div-u24.c
  src/f16-vtanh/gen/f16-vtanh-fma3-expm1minus-rr1-p3h2ts-div-u32.c
  src/f16-vtanh/gen/f16-vtanh-fma3-expm1minus-rr1-p3h2ts-rcp-u8.c
  src/f16-vtanh/gen/f16-vtanh-fma3-expm1minus-rr1-p3h2ts-rcp-u16.c
  src/f16-vtanh/gen/f16-vtanh-fma3-expm1minus-rr1-p3h2ts-rcp-u24.c
  src/f16-vtanh/gen/f16-vtanh-fma3-expm1minus-rr1-p3h2ts-rcp-u32.c
  src/f16-vtanh/gen/f16-vtanh-fma3-polynomial-p19h9t2-u8.c
  src/f16-vtanh/gen/f16-vtanh-fma3-polynomial-p19h9t2-u16.c
  src/f16-vtanh/gen/f16-vtanh-fma3-polynomial-p19h9t2-u24.c
  src/f32-dwconv/gen/f32-dwconv-3p8c-minmax-fma3-acc2.c
  src/f32-dwconv/gen/f32-dwconv-3p8c-minmax-fma3.c
  src/f32-dwconv/gen/f32-dwconv-3p16c-minmax-fma3-acc2.c
  src/f32-dwconv/gen/f32-dwconv-4p8c-minmax-fma3-acc2.c
  src/f32-dwconv/gen/f32-dwconv-4p8c-minmax-fma3.c
  src/f32-dwconv/gen/f32-dwconv-4p16c-minmax-fma3-acc2.c
  src/f32-dwconv/gen/f32-dwconv-9p8c-minmax-fma3-acc2.c
  src/f32-dwconv/gen/f32-dwconv-9p8c-minmax-fma3.c
  src/f32-dwconv/gen/f32-dwconv-9p16c-minmax-fma3-acc2.c
  src/f32-dwconv/gen/f32-dwconv-25p8c-minmax-fma3-acc2.c
  src/f32-dwconv/gen/f32-dwconv-25p8c-minmax-fma3.c
  src/f32-dwconv/gen/f32-dwconv-25p16c-minmax-fma3-acc2.c
  src/f32-gemm/gen/f32-gemm-3x16-minmax-fma3-broadcast.c
  src/f32-gemm/gen/f32-gemm-3x16s4-minmax-fma3-broadcast.c
  src/f32-gemm/gen/f32-gemm-4x16-minmax-fma3-broadcast.c
  src/f32-gemm/gen/f32-gemm-5x16s4-minmax-fma3-broadcast.c
  src/f32-gemm/gen/f32-gemm-6x8-minmax-fma3-broadcast.c
  src/f32-gemm/gen/f32-gemm-6x16-minmax-fma3-broadcast.c
  src/f32-gemm/gen/f32-gemm-6x16s4-minmax-fma3-broadcast.c
  src/f32-gemm/gen/f32-gemm-7x8-minmax-fma3-broadcast.c
  src/f32-gemm/gen/f32-gemm-8x8-minmax-fma3-broadcast.c
  src/f32-gemminc/gen/f32-gemminc-1x8-minmax-fma3-broadcast.c
  src/f32-gemminc/gen/f32-gemminc-1x16-minmax-fma3-broadcast.c
  src/f32-gemminc/gen/f32-gemminc-1x16s4-minmax-fma3-broadcast.c
  src/f32-gemminc/gen/f32-gemminc-3x16-minmax-fma3-broadcast.c
  src/f32-gemminc/gen/f32-gemminc-3x16s4-minmax-fma3-broadcast.c
  src/f32-gemminc/gen/f32-gemminc-4x8-minmax-fma3-broadcast.c
  src/f32-gemminc/gen/f32-gemminc-4x16-minmax-fma3-broadcast.c
  src/f32-gemminc/gen/f32-gemminc-4x16s4-minmax-fma3-broadcast.c
  src/f32-gemminc/gen/f32-gemminc-5x8-minmax-fma3-broadcast.c
  src/f32-gemminc/gen/f32-gemminc-5x16-minmax-fma3-broadcast.c
  src/f32-gemminc/gen/f32-gemminc-5x16s4-minmax-fma3-broadcast.c
  src/f32-gemminc/gen/f32-gemminc-6x8-minmax-fma3-broadcast.c
  src/f32-gemminc/gen/f32-gemminc-6x16-minmax-fma3-broadcast.c
  src/f32-gemminc/gen/f32-gemminc-6x16s4-minmax-fma3-broadcast.c
  src/f32-gemminc/gen/f32-gemminc-7x8-minmax-fma3-broadcast.c
  src/f32-gemminc/gen/f32-gemminc-8x8-minmax-fma3-broadcast.c
  src/f32-igemm/gen/f32-igemm-3x16-minmax-fma3-broadcast.c
  src/f32-igemm/gen/f32-igemm-3x16s4-minmax-fma3-broadcast.c
  src/f32-igemm/gen/f32-igemm-4x16-minmax-fma3-broadcast.c
  src/f32-igemm/gen/f32-igemm-5x16-minmax-fma3-broadcast.c
  src/f32-igemm/gen/f32-igemm-5x16s4-minmax-fma3-broadcast.c
  src/f32-igemm/gen/f32-igemm-6x8-minmax-fma3-broadcast.c
  src/f32-igemm/gen/f32-igemm-6x16-minmax-fma3-broadcast-prfm.c
  src/f32-igemm/gen/f32-igemm-6x16-minmax-fma3-broadcast.c
  src/f32-igemm/gen/f32-igemm-6x16s4-minmax-fma3-broadcast.c
  src/f32-igemm/gen/f32-igemm-7x8-minmax-fma3-broadcast.c
  src/f32-igemm/gen/f32-igemm-8x8-minmax-fma3-broadcast.c
  src/f32-qc4w-gemm/gen/f32-qc4w-gemm-2x16-minmax-fma3-broadcast.c
  src/f32-qc4w-gemm/gen/f32-qc4w-gemm-4x16-minmax-fma3-broadcast.c
  src/f32-qc4w-gemm/gen/f32-qc4w-gemm-5x16-minmax-fma3-broadcast.c
  src/f32-qc4w-gemm/gen/f32-qc4w-gemm-6x16-minmax-fma3-broadcast.c
  src/f32-qc4w-gemm/gen/f32-qc4w-gemm-7x16-minmax-fma3-broadcast.c
  src/f32-qc4w-gemm/gen/f32-qc4w-gemm-8x16-minmax-fma3-broadcast.c
  src/f32-qc8w-gemm/gen/f32-qc8w-gemm-2x16-minmax-fma3-broadcast.c
  src/f32-qc8w-gemm/gen/f32-qc8w-gemm-3x16-minmax-fma3-broadcast.c
  src/f32-qc8w-gemm/gen/f32-qc8w-gemm-4x16-minmax-fma3-broadcast.c
  src/f32-qc8w-gemm/gen/f32-qc8w-gemm-6x16-minmax-fma3-broadcast.c
  src/f32-qc8w-gemm/gen/f32-qc8w-gemm-7x16-minmax-fma3-broadcast.c
  src/f32-qc8w-gemm/gen/f32-qc8w-gemm-8x16-minmax-fma3-broadcast.c
  src/f32-vcmul/gen/f32-vcmul-fma3-u8.c
  src/f32-vcmul/gen/f32-vcmul-fma3-u32.c
  src/f32-vcmul/gen/f32-vcmul-fma3-u64.c
  src/f32-vhswish/gen/f32-vhswish-fma3-u8.c
  src/f32-vlog/gen/f32-vlog-fma3-rational-3-3-nr.c
  src/f32-vrsqrt/gen/f32-vrsqrt-fma3-rsqrt-u8.c
  src/f32-vrsqrt/gen/f32-vrsqrt-fma3-rsqrt-u32.c
  src/f32-vsqrt/gen/f32-vsqrt-fma3-rsqrt-u8.c
  src/f32-vsqrt/gen/f32-vsqrt-fma3-rsqrt-u32.c
  src/f32-vtanh/gen/f32-vtanh-fma3-rational-9-8-nr.c)

SET(ALL_FMA3_MICROKERNEL_SRCS ${PROD_FMA3_MICROKERNEL_SRCS} + ${NON_PROD_FMA3_MICROKERNEL_SRCS})
