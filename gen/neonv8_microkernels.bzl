"""
Microkernel filenames lists for neonv8.

Auto-generated file. Do not edit!
  Generator: tools/update-microkernels.py
"""

PROD_NEONV8_MICROKERNEL_SRCS = [
    "src/f32-qs8-vcvt/gen/f32-qs8-vcvt-neonv8-u32.c",
    "src/f32-qu8-vcvt/gen/f32-qu8-vcvt-neonv8-u32.c",
    "src/f32-vrnd/gen/f32-vrndd-neonv8-u8.c",
    "src/f32-vrnd/gen/f32-vrndne-neonv8-u8.c",
    "src/f32-vrnd/gen/f32-vrndu-neonv8-u8.c",
    "src/f32-vrnd/gen/f32-vrndz-neonv8-u8.c",
    "src/qs8-qc8w-dwconv/gen/qs8-qc8w-dwconv-3p16c-minmax-fp32-neonv8-mla8-ld64.c",
    "src/qs8-qc8w-dwconv/gen/qs8-qc8w-dwconv-3p16c-minmax-fp32-neonv8-mla8-ld128.c",
    "src/qs8-qc8w-dwconv/gen/qs8-qc8w-dwconv-9p16c-minmax-fp32-neonv8-mla8-ld64.c",
    "src/qs8-qc8w-dwconv/gen/qs8-qc8w-dwconv-25p8c-minmax-fp32-neonv8-mla8-ld64.c",
    "src/qs8-qc8w-dwconv/gen/qs8-qc8w-dwconv-25p16c-minmax-fp32-neonv8-mla8-ld64.c",
    "src/qs8-qc8w-gemm/gen/qs8-qc8w-gemm-1x8c2s4-minmax-fp32-neonv8-mlal.c",
    "src/qs8-qc8w-gemm/gen/qs8-qc8w-gemm-1x16-minmax-fp32-neonv8-mlal-lane.c",
    "src/qs8-qc8w-gemm/gen/qs8-qc8w-gemm-2x8c2s4-minmax-fp32-neonv8-mlal.c",
    "src/qs8-qc8w-igemm/gen/qs8-qc8w-igemm-1x8c2s4-minmax-fp32-neonv8-mlal.c",
    "src/qs8-qc8w-igemm/gen/qs8-qc8w-igemm-1x16-minmax-fp32-neonv8-mlal-lane.c",
    "src/qs8-qc8w-igemm/gen/qs8-qc8w-igemm-2x8c2s4-minmax-fp32-neonv8-mlal.c",
]

NON_PROD_NEONV8_MICROKERNEL_SRCS = [
    "src/f32-qs8-vcvt/gen/f32-qs8-vcvt-neonv8-u8.c",
    "src/f32-qs8-vcvt/gen/f32-qs8-vcvt-neonv8-u16.c",
    "src/f32-qs8-vcvt/gen/f32-qs8-vcvt-neonv8-u24.c",
    "src/f32-qu8-vcvt/gen/f32-qu8-vcvt-neonv8-u8.c",
    "src/f32-qu8-vcvt/gen/f32-qu8-vcvt-neonv8-u16.c",
    "src/f32-qu8-vcvt/gen/f32-qu8-vcvt-neonv8-u24.c",
    "src/f32-vrnd/gen/f32-vrndd-neonv8-u4.c",
    "src/f32-vrnd/gen/f32-vrndne-neonv8-u4.c",
    "src/f32-vrnd/gen/f32-vrndu-neonv8-u4.c",
    "src/f32-vrnd/gen/f32-vrndz-neonv8-u4.c",
    "src/qs8-dwconv/gen/qs8-dwconv-9p8c-minmax-fp32-neonv8-mul16.c",
    "src/qs8-dwconv/gen/qs8-dwconv-9p16c-minmax-fp32-neonv8-mul16.c",
    "src/qs8-dwconv/gen/qs8-dwconv-9p32c-minmax-fp32-neonv8-mul16.c",
    "src/qs8-dwconv/gen/qs8-dwconv-25p8c-minmax-fp32-neonv8-mul16.c",
    "src/qs8-dwconv/gen/qs8-dwconv-25p16c-minmax-fp32-neonv8-mul16.c",
    "src/qs8-dwconv/gen/qs8-dwconv-25p32c-minmax-fp32-neonv8-mul16.c",
    "src/qs8-qc8w-dwconv/gen/qs8-qc8w-dwconv-3p8c-minmax-fp32-neonv8-mla8-ld64.c",
    "src/qs8-qc8w-dwconv/gen/qs8-qc8w-dwconv-9p8c-minmax-fp32-neonv8-mla8-ld64.c",
    "src/qs8-qc8w-dwconv/gen/qs8-qc8w-dwconv-9p8c-minmax-fp32-neonv8-mul8-ld64.c",
    "src/qs8-qc8w-dwconv/gen/qs8-qc8w-dwconv-9p8c-minmax-fp32-neonv8-mul16.c",
    "src/qs8-qc8w-dwconv/gen/qs8-qc8w-dwconv-9p16c-minmax-fp32-neonv8-mla8-ld128.c",
    "src/qs8-qc8w-dwconv/gen/qs8-qc8w-dwconv-9p16c-minmax-fp32-neonv8-mul8-ld64.c",
    "src/qs8-qc8w-dwconv/gen/qs8-qc8w-dwconv-9p16c-minmax-fp32-neonv8-mul8-ld128.c",
    "src/qs8-qc8w-dwconv/gen/qs8-qc8w-dwconv-9p16c-minmax-fp32-neonv8-mul16.c",
    "src/qs8-qc8w-dwconv/gen/qs8-qc8w-dwconv-9p32c-minmax-fp32-neonv8-mul16.c",
    "src/qs8-qc8w-dwconv/gen/qs8-qc8w-dwconv-25p8c-minmax-fp32-neonv8-mul8-ld64.c",
    "src/qs8-qc8w-dwconv/gen/qs8-qc8w-dwconv-25p8c-minmax-fp32-neonv8-mul16.c",
    "src/qs8-qc8w-dwconv/gen/qs8-qc8w-dwconv-25p16c-minmax-fp32-neonv8-mla8-ld128.c",
    "src/qs8-qc8w-dwconv/gen/qs8-qc8w-dwconv-25p16c-minmax-fp32-neonv8-mul8-ld64.c",
    "src/qs8-qc8w-dwconv/gen/qs8-qc8w-dwconv-25p16c-minmax-fp32-neonv8-mul8-ld128.c",
    "src/qs8-qc8w-dwconv/gen/qs8-qc8w-dwconv-25p16c-minmax-fp32-neonv8-mul16.c",
    "src/qs8-qc8w-dwconv/gen/qs8-qc8w-dwconv-25p32c-minmax-fp32-neonv8-mul16.c",
    "src/qs8-qc8w-gemm/gen/qs8-qc8w-gemm-1x8-minmax-fp32-neonv8-mlal-lane-prfm.c",
    "src/qs8-qc8w-gemm/gen/qs8-qc8w-gemm-1x8-minmax-fp32-neonv8-mlal-lane.c",
    "src/qs8-qc8w-gemm/gen/qs8-qc8w-gemm-1x8c2-minmax-fp32-neonv8-mlal-dup.c",
    "src/qs8-qc8w-gemm/gen/qs8-qc8w-gemm-1x8c2-minmax-fp32-neonv8-mlal-ld1r.c",
    "src/qs8-qc8w-gemm/gen/qs8-qc8w-gemm-1x8c2-minmax-fp32-neonv8-mlal-ld2r.c",
    "src/qs8-qc8w-gemm/gen/qs8-qc8w-gemm-1x8c2-minmax-fp32-neonv8-mlal-ld4r.c",
    "src/qs8-qc8w-gemm/gen/qs8-qc8w-gemm-1x8c4-minmax-fp32-neonv8-mlal-dup.c",
    "src/qs8-qc8w-gemm/gen/qs8-qc8w-gemm-1x8c4-minmax-fp32-neonv8-mlal-ld1r.c",
    "src/qs8-qc8w-gemm/gen/qs8-qc8w-gemm-1x8c4-minmax-fp32-neonv8-mlal-ld2r.c",
    "src/qs8-qc8w-gemm/gen/qs8-qc8w-gemm-1x8c4s2-minmax-fp32-neonv8-mlal.c",
    "src/qs8-qc8w-gemm/gen/qs8-qc8w-gemm-1x8c8-minmax-fp32-neonv8-mlal.c",
    "src/qs8-qc8w-gemm/gen/qs8-qc8w-gemm-1x16-minmax-fp32-neonv8-mlal-lane-prfm.c",
    "src/qs8-qc8w-gemm/gen/qs8-qc8w-gemm-2x8-minmax-fp32-neonv8-mlal-lane-prfm.c",
    "src/qs8-qc8w-gemm/gen/qs8-qc8w-gemm-2x8-minmax-fp32-neonv8-mlal-lane.c",
    "src/qs8-qc8w-gemm/gen/qs8-qc8w-gemm-2x8c2-minmax-fp32-neonv8-mlal-dup.c",
    "src/qs8-qc8w-gemm/gen/qs8-qc8w-gemm-2x8c2-minmax-fp32-neonv8-mlal-ld1r.c",
    "src/qs8-qc8w-gemm/gen/qs8-qc8w-gemm-2x8c2-minmax-fp32-neonv8-mlal-ld2r.c",
    "src/qs8-qc8w-gemm/gen/qs8-qc8w-gemm-2x8c2-minmax-fp32-neonv8-mlal-ld4r.c",
    "src/qs8-qc8w-gemm/gen/qs8-qc8w-gemm-2x8c4-minmax-fp32-neonv8-mlal-dup.c",
    "src/qs8-qc8w-gemm/gen/qs8-qc8w-gemm-2x8c4-minmax-fp32-neonv8-mlal-ld1r.c",
    "src/qs8-qc8w-gemm/gen/qs8-qc8w-gemm-2x8c4-minmax-fp32-neonv8-mlal-ld2r.c",
    "src/qs8-qc8w-gemm/gen/qs8-qc8w-gemm-2x8c4s2-minmax-fp32-neonv8-mlal.c",
    "src/qs8-qc8w-gemm/gen/qs8-qc8w-gemm-2x8c8-minmax-fp32-neonv8-mlal.c",
    "src/qs8-qc8w-gemm/gen/qs8-qc8w-gemm-2x16-minmax-fp32-neonv8-mlal-lane-prfm.c",
    "src/qs8-qc8w-gemm/gen/qs8-qc8w-gemm-2x16-minmax-fp32-neonv8-mlal-lane.c",
    "src/qs8-qc8w-gemm/gen/qs8-qc8w-gemm-3x8-minmax-fp32-neonv8-mlal-lane-prfm.c",
    "src/qs8-qc8w-gemm/gen/qs8-qc8w-gemm-3x8-minmax-fp32-neonv8-mlal-lane.c",
    "src/qs8-qc8w-gemm/gen/qs8-qc8w-gemm-3x16-minmax-fp32-neonv8-mlal-lane-prfm.c",
    "src/qs8-qc8w-gemm/gen/qs8-qc8w-gemm-3x16-minmax-fp32-neonv8-mlal-lane.c",
    "src/qs8-qc8w-gemm/gen/qs8-qc8w-gemm-4x8-minmax-fp32-neonv8-mlal-lane-prfm.c",
    "src/qs8-qc8w-gemm/gen/qs8-qc8w-gemm-4x8-minmax-fp32-neonv8-mlal-lane.c",
    "src/qs8-qc8w-gemm/gen/qs8-qc8w-gemm-4x16-minmax-fp32-neonv8-mlal-lane-prfm.c",
    "src/qs8-qc8w-gemm/gen/qs8-qc8w-gemm-4x16-minmax-fp32-neonv8-mlal-lane.c",
    "src/qs8-qc8w-gemm/gen/qs8-qc8w-gemm-6x8-minmax-fp32-neonv8-mlal-lane-prfm.c",
    "src/qs8-qc8w-gemm/gen/qs8-qc8w-gemm-6x8-minmax-fp32-neonv8-mlal-lane.c",
    "src/qs8-qc8w-gemm/gen/qs8-qc8w-gemm-6x16-minmax-fp32-neonv8-mlal-lane-prfm.c",
    "src/qs8-qc8w-gemm/gen/qs8-qc8w-gemm-6x16-minmax-fp32-neonv8-mlal-lane.c",
    "src/qs8-qc8w-igemm/gen/qs8-qc8w-igemm-1x8-minmax-fp32-neonv8-mlal-lane-prfm.c",
    "src/qs8-qc8w-igemm/gen/qs8-qc8w-igemm-1x8-minmax-fp32-neonv8-mlal-lane.c",
    "src/qs8-qc8w-igemm/gen/qs8-qc8w-igemm-1x8c2-minmax-fp32-neonv8-mlal-dup.c",
    "src/qs8-qc8w-igemm/gen/qs8-qc8w-igemm-1x8c2-minmax-fp32-neonv8-mlal-ld1r.c",
    "src/qs8-qc8w-igemm/gen/qs8-qc8w-igemm-1x8c2-minmax-fp32-neonv8-mlal-ld2r.c",
    "src/qs8-qc8w-igemm/gen/qs8-qc8w-igemm-1x8c2-minmax-fp32-neonv8-mlal-ld4r.c",
    "src/qs8-qc8w-igemm/gen/qs8-qc8w-igemm-1x8c4-minmax-fp32-neonv8-mlal-dup.c",
    "src/qs8-qc8w-igemm/gen/qs8-qc8w-igemm-1x8c4-minmax-fp32-neonv8-mlal-ld1r.c",
    "src/qs8-qc8w-igemm/gen/qs8-qc8w-igemm-1x8c4-minmax-fp32-neonv8-mlal-ld2r.c",
    "src/qs8-qc8w-igemm/gen/qs8-qc8w-igemm-1x8c4s2-minmax-fp32-neonv8-mlal.c",
    "src/qs8-qc8w-igemm/gen/qs8-qc8w-igemm-1x8c8-minmax-fp32-neonv8-mlal.c",
    "src/qs8-qc8w-igemm/gen/qs8-qc8w-igemm-1x16-minmax-fp32-neonv8-mlal-lane-prfm.c",
    "src/qs8-qc8w-igemm/gen/qs8-qc8w-igemm-2x8-minmax-fp32-neonv8-mlal-lane-prfm.c",
    "src/qs8-qc8w-igemm/gen/qs8-qc8w-igemm-2x8-minmax-fp32-neonv8-mlal-lane.c",
    "src/qs8-qc8w-igemm/gen/qs8-qc8w-igemm-2x8c2-minmax-fp32-neonv8-mlal-dup.c",
    "src/qs8-qc8w-igemm/gen/qs8-qc8w-igemm-2x8c2-minmax-fp32-neonv8-mlal-ld1r.c",
    "src/qs8-qc8w-igemm/gen/qs8-qc8w-igemm-2x8c2-minmax-fp32-neonv8-mlal-ld2r.c",
    "src/qs8-qc8w-igemm/gen/qs8-qc8w-igemm-2x8c2-minmax-fp32-neonv8-mlal-ld4r.c",
    "src/qs8-qc8w-igemm/gen/qs8-qc8w-igemm-2x8c4-minmax-fp32-neonv8-mlal-dup.c",
    "src/qs8-qc8w-igemm/gen/qs8-qc8w-igemm-2x8c4-minmax-fp32-neonv8-mlal-ld1r.c",
    "src/qs8-qc8w-igemm/gen/qs8-qc8w-igemm-2x8c4-minmax-fp32-neonv8-mlal-ld2r.c",
    "src/qs8-qc8w-igemm/gen/qs8-qc8w-igemm-2x8c4s2-minmax-fp32-neonv8-mlal.c",
    "src/qs8-qc8w-igemm/gen/qs8-qc8w-igemm-2x8c8-minmax-fp32-neonv8-mlal.c",
    "src/qs8-qc8w-igemm/gen/qs8-qc8w-igemm-2x16-minmax-fp32-neonv8-mlal-lane-prfm.c",
    "src/qs8-qc8w-igemm/gen/qs8-qc8w-igemm-2x16-minmax-fp32-neonv8-mlal-lane.c",
    "src/qs8-qc8w-igemm/gen/qs8-qc8w-igemm-3x8-minmax-fp32-neonv8-mlal-lane-prfm.c",
    "src/qs8-qc8w-igemm/gen/qs8-qc8w-igemm-3x8-minmax-fp32-neonv8-mlal-lane.c",
    "src/qs8-qc8w-igemm/gen/qs8-qc8w-igemm-3x16-minmax-fp32-neonv8-mlal-lane-prfm.c",
    "src/qs8-qc8w-igemm/gen/qs8-qc8w-igemm-3x16-minmax-fp32-neonv8-mlal-lane.c",
    "src/qs8-qc8w-igemm/gen/qs8-qc8w-igemm-4x8-minmax-fp32-neonv8-mlal-lane-prfm.c",
    "src/qs8-qc8w-igemm/gen/qs8-qc8w-igemm-4x8-minmax-fp32-neonv8-mlal-lane.c",
    "src/qs8-qc8w-igemm/gen/qs8-qc8w-igemm-4x16-minmax-fp32-neonv8-mlal-lane-prfm.c",
    "src/qs8-qc8w-igemm/gen/qs8-qc8w-igemm-4x16-minmax-fp32-neonv8-mlal-lane.c",
    "src/qs8-qc8w-igemm/gen/qs8-qc8w-igemm-6x8-minmax-fp32-neonv8-mlal-lane-prfm.c",
    "src/qs8-qc8w-igemm/gen/qs8-qc8w-igemm-6x8-minmax-fp32-neonv8-mlal-lane.c",
    "src/qs8-qc8w-igemm/gen/qs8-qc8w-igemm-6x16-minmax-fp32-neonv8-mlal-lane-prfm.c",
    "src/qs8-qc8w-igemm/gen/qs8-qc8w-igemm-6x16-minmax-fp32-neonv8-mlal-lane.c",
    "src/qs8-vmul/gen/qs8-vmul-minmax-fp32-neonv8-ld64-u8.c",
    "src/qs8-vmul/gen/qs8-vmul-minmax-fp32-neonv8-ld64-u16.c",
    "src/qs8-vmul/gen/qs8-vmul-minmax-fp32-neonv8-ld128-u16.c",
    "src/qs8-vmulc/gen/qs8-vmulc-minmax-fp32-neonv8-ld64-u8.c",
    "src/qs8-vmulc/gen/qs8-vmulc-minmax-fp32-neonv8-ld64-u16.c",
    "src/qs8-vmulc/gen/qs8-vmulc-minmax-fp32-neonv8-ld128-u16.c",
    "src/qu8-dwconv/gen/qu8-dwconv-9p8c-minmax-fp32-neonv8-mul16.c",
    "src/qu8-dwconv/gen/qu8-dwconv-9p16c-minmax-fp32-neonv8-mul16.c",
    "src/qu8-dwconv/gen/qu8-dwconv-9p32c-minmax-fp32-neonv8-mul16.c",
    "src/qu8-dwconv/gen/qu8-dwconv-25p8c-minmax-fp32-neonv8-mul16.c",
    "src/qu8-dwconv/gen/qu8-dwconv-25p16c-minmax-fp32-neonv8-mul16.c",
    "src/qu8-dwconv/gen/qu8-dwconv-25p32c-minmax-fp32-neonv8-mul16.c",
    "src/qu8-gemm/gen/qu8-gemm-1x16-minmax-fp32-neonv8-mlal-lane.c",
    "src/qu8-gemm/gen/qu8-gemm-4x16-minmax-fp32-neonv8-mlal-lane.c",
    "src/qu8-igemm/gen/qu8-igemm-1x16-minmax-fp32-neonv8-mlal-lane.c",
    "src/qu8-igemm/gen/qu8-igemm-4x16-minmax-fp32-neonv8-mlal-lane.c",
    "src/qu8-vmul/gen/qu8-vmul-minmax-fp32-neonv8-ld64-u8.c",
    "src/qu8-vmul/gen/qu8-vmul-minmax-fp32-neonv8-ld64-u16.c",
    "src/qu8-vmul/gen/qu8-vmul-minmax-fp32-neonv8-ld128-u16.c",
    "src/qu8-vmulc/gen/qu8-vmulc-minmax-fp32-neonv8-ld64-u8.c",
    "src/qu8-vmulc/gen/qu8-vmulc-minmax-fp32-neonv8-ld64-u16.c",
    "src/qu8-vmulc/gen/qu8-vmulc-minmax-fp32-neonv8-ld128-u16.c",
]

ALL_NEONV8_MICROKERNEL_SRCS = PROD_NEONV8_MICROKERNEL_SRCS + NON_PROD_NEONV8_MICROKERNEL_SRCS
