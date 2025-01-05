// Copyright 2022 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include <stddef.h>

#if XNN_ENABLE_CPUINFO
#include <cpuinfo.h>
#endif  // XNN_ENABLE_CPUINFO

#include "xnnpack/common.h"

#if _WIN32
  #include <windows.h>

  #ifndef PF_ARM_V82_DP_INSTRUCTIONS_AVAILABLE
    #define PF_ARM_V82_DP_INSTRUCTIONS_AVAILABLE 43
  #endif
#endif
#if XNN_ARCH_X86_64 && defined(__linux__) && !defined(CHROMIUM)
#include <sys/syscall.h>
#include <unistd.h>

#define XFEATURE_XTILEDATA 18
#define ARCH_REQ_XCOMP_PERM 0x1023
#endif
#if XNN_ENABLE_CPUINFO
  #include <cpuinfo.h>
#endif  // XNN_ENABLE_CPUINFO

#if XNN_ARCH_RISCV
#include <inttypes.h>
#include <sys/auxv.h>

#define COMPAT_HWCAP_ISA_V (1 << ('V' - 'A'))
#endif

#if XNN_ARCH_PPC64
  #include <sys/auxv.h>
#endif

#if XNN_ARCH_WASM || XNN_ARCH_WASMSIMD || XNN_ARCH_WASMRELAXEDSIMD
#include <math.h>
#endif

#if XNN_ARCH_WASMRELAXEDSIMD
#include <wasm_simd128.h>
#endif

#include "xnnpack/hardware-config.h"
#include "xnnpack/init-once.h"
#include "xnnpack/log.h"

#if XNN_ARCH_X86_64 && defined(__linux__) && !defined(CHROMIUM)
ssize_t xnn_syscall(size_t rax, size_t rdi, size_t rsi, size_t rdx) {
  __asm (
    "syscall"
    : "+a" (rax)
    : "D"(rdi), "S"(rsi), "d"(rdx)
    : "rcx", "r11", "memory"
  );
  return rax;
}
#endif

static struct xnn_hardware_config hardware_config = {0};

XNN_INIT_ONCE_GUARD(hardware);

static void init_hardware_config(void) {
  #if XNN_ARCH_ARM64 || XNN_ARCH_ARM
    #if XNN_PLATFORM_WINDOWS
      SYSTEM_INFO system_info;
      GetSystemInfo(&system_info);
      switch (system_info.wProcessorLevel) {
        case 0x803:  // Kryo 385 Silver
          hardware_config.use_arm_neon_fp16_arith = true;
          break;
        default:
          // Assume that Dot Product support implies FP16 support.
          // ARM manuals don't guarantee that, but it holds in practice.
          hardware_config.use_arm_neon_fp16_arith = !!IsProcessorFeaturePresent(PF_ARM_V82_DP_INSTRUCTIONS_AVAILABLE);
          break;
      }
      hardware_config.use_arm_fp16_arith = hardware_config.use_arm_neon_fp16_arith;

      hardware_config.use_arm_neon_bf16 = false;
      hardware_config.use_arm_neon_dot = !!IsProcessorFeaturePresent(PF_ARM_V82_DP_INSTRUCTIONS_AVAILABLE);
    #else
      hardware_config.use_arm_fp16_arith = cpuinfo_has_arm_fp16_arith();
      hardware_config.use_arm_neon_fp16_arith = cpuinfo_has_arm_neon_fp16_arith();
      hardware_config.use_arm_neon_bf16 = cpuinfo_has_arm_neon_bf16();
      hardware_config.use_arm_neon_dot = cpuinfo_has_arm_neon_dot();
    #endif
    hardware_config.use_arm_vfpv3 = cpuinfo_has_arm_vfpv3();
    hardware_config.use_arm_neon = cpuinfo_has_arm_neon();
    hardware_config.use_arm_neon_fp16 = cpuinfo_has_arm_neon_fp16();
    hardware_config.use_arm_neon_fma = cpuinfo_has_arm_neon_fma();
    hardware_config.use_arm_neon_v8 = cpuinfo_has_arm_neon_v8();
  #endif

  #if XNN_ARCH_ARM
    hardware_config.use_arm_v6 = cpuinfo_has_arm_v6();
    hardware_config.use_arm_vfpv2 = cpuinfo_has_arm_vfpv2();
  #endif

  #if XNN_ARCH_ARM64
    hardware_config.use_arm_neon_i8mm = cpuinfo_has_arm_i8mm();
    hardware_config.use_arm_sve = cpuinfo_has_arm_sve();
    hardware_config.use_arm_sve2 = cpuinfo_has_arm_sve2();
    hardware_config.use_arm_sme = cpuinfo_has_arm_sme();
    hardware_config.use_arm_sme2 = cpuinfo_has_arm_sme2();
  #endif

  #if XNN_ARCH_X86 || XNN_ARCH_X86_64
    hardware_config.use_x86_ssse3 = cpuinfo_has_x86_ssse3();
    hardware_config.use_x86_sse4_1 = cpuinfo_has_x86_sse4_1();
    hardware_config.use_x86_avx = cpuinfo_has_x86_avx();
    hardware_config.use_x86_f16c = cpuinfo_has_x86_f16c();
    hardware_config.use_x86_fma3 = cpuinfo_has_x86_fma3();
    hardware_config.use_x86_avx2 = cpuinfo_has_x86_avx2();
#if XNN_ENABLE_AVX512F
    hardware_config.use_x86_avx512f = cpuinfo_has_x86_avx512f();
#else
    hardware_config.use_x86_avx512f = 0;
#endif
#if XNN_ENABLE_AVX512SKX
    hardware_config.use_x86_avx512skx = hardware_config.use_x86_avx512f &&
      cpuinfo_has_x86_avx512bw() && cpuinfo_has_x86_avx512dq() && cpuinfo_has_x86_avx512vl();
#else
    hardware_config.use_x86_avx512skx = 0;
#endif
#if XNN_ENABLE_AVX512VBMI
    hardware_config.use_x86_avx512vbmi = hardware_config.use_x86_avx512skx && cpuinfo_has_x86_avx512vbmi();
#else
    hardware_config.use_x86_avx512vbmi = 0;
#endif
#if XNN_ENABLE_AVX512VNNI
    hardware_config.use_x86_avx512vnni = hardware_config.use_x86_avx512skx && cpuinfo_has_x86_avx512vnni();
#else
    hardware_config.use_x86_avx512vnni = 0;
#endif
#if XNN_ENABLE_AVX512VNNIGFNI
    hardware_config.use_x86_avx512vnnigfni = hardware_config.use_x86_avx512vnni && cpuinfo_has_x86_gfni();
#else
    hardware_config.use_x86_avx512vnnigfni = 0;
#endif
#if XNN_ENABLE_AVX512FP16
    hardware_config.use_x86_avx512fp16 = cpuinfo_has_x86_avx512fp16();
#else
    hardware_config.use_x86_avx512fp16 = 0;
#endif
#if XNN_ENABLE_AVX512AMX
    hardware_config.use_x86_avx512amx = hardware_config.use_x86_avx512vnnigfni && cpuinfo_has_x86_amx_int8();
#if XNN_ARCH_X86_64 && defined(__linux__) && !defined(CHROMIUM)
    if (hardware_config.use_x86_avx512amx) {
      size_t status = xnn_syscall(SYS_arch_prctl, ARCH_REQ_XCOMP_PERM, XFEATURE_XTILEDATA, 0);
      if (status) {
        xnn_log_info("XFEATURE_XTILEDATA setup is failed, TMUL usage is not allowed");
        hardware_config.use_x86_avx512amx = 0;
      }
    }
#endif
#else
    hardware_config.use_x86_avx512amx = 0;
#endif
#if XNN_ENABLE_AVXVNNI
    hardware_config.use_x86_avxvnni = hardware_config.use_x86_avx2 && cpuinfo_has_x86_avxvnni();
#else
    hardware_config.use_x86_avxvnni = 0;
#endif
#if XNN_ENABLE_AVXVNNIINT8
    hardware_config.use_x86_avxvnniint8 = hardware_config.use_x86_avx2 && cpuinfo_has_x86_avx_vnni_int8();
#else
    hardware_config.use_x86_avxvnniint8 = 0;
#endif
#if XNN_ENABLE_AVX256SKX
    // Using cpuinfo_has_x86_amx_int8 as placeholder for cpuinfo_has_x86_avx10
    hardware_config.use_x86_avx256skx = hardware_config.use_x86_avx512skx || cpuinfo_has_x86_amx_int8();
#else
    hardware_config.use_x86_avx256skx = 0;
#endif
#if XNN_ENABLE_AVX256VNNI
    // Using cpuinfo_has_x86_amx_int8 as placeholder for cpuinfo_has_x86_avx10
    hardware_config.use_x86_avx256vnni = (hardware_config.use_x86_avx512skx && cpuinfo_has_x86_avx512vnni()) || cpuinfo_has_x86_amx_int8();
#else
    hardware_config.use_x86_avx256vnni = 0;
#endif
#if XNN_ENABLE_AVX256VNNIGFNI
    // Using cpuinfo_has_x86_amx_int8 as placeholder for cpuinfo_has_x86_avx10
    hardware_config.use_x86_avx256vnnigfni = hardware_config.use_x86_avx256vnni && cpuinfo_has_x86_gfni();
#else
    hardware_config.use_x86_avx256vnnigfni = 0;
#endif
#endif  // !XNN_ARCH_X86 && !XNN_ARCH_X86_64

#if XNN_ARCH_HEXAGON
#if XNN_ENABLE_HVX
    hardware_config.use_hvx = 1;
#else
    hardware_config.use_hvx = 0;
#endif  // XNN_ENABLE_HVX
#endif  // XNN_ARCH_HEXAGON

  #if XNN_ARCH_RISCV
    const long hwcap = getauxval(AT_HWCAP);
    xnn_log_debug("getauxval(AT_HWCAP) = %08lX", hwcap);
    hardware_config.use_riscv_vector = (hwcap & COMPAT_HWCAP_ISA_V) != 0;

    /* There is no HWCAP for fp16 so disable by default */
    hardware_config.use_riscv_vector_fp16_arith = false;

    if (hardware_config.use_riscv_vector) {
      register uint32_t vlenb __asm__ ("t0");
      __asm__(".word 0xC22022F3"  /* CSRR t0, vlenb */ : "=r" (vlenb));
      hardware_config.vlenb = vlenb;
      xnn_log_info("RISC-V VLENB: %" PRIu32, vlenb);
    }
  #endif

  #if XNN_ARCH_PPC64
    const unsigned long HWCAPs = getauxval(AT_HWCAP);
    const unsigned long HWCAPs_2 = getauxval(AT_HWCAP2);
    if (HWCAPs & PPC_FEATURE_HAS_VSX) {
      hardware_config.use_vsx = 1;
    }
    #if defined PPC_FEATURE2_ARCH_3_1
      if (HWCAPs_2 & PPC_FEATURE2_ARCH_3_1) {
        hardware_config.use_vsx3 = 1;
      }
      if (HWCAPs_2 & PPC_FEATURE2_MMA) {
        hardware_config.use_mma = 1;
      }
    #endif
  #endif

  #if XNN_ARCH_WASM || XNN_ARCH_WASMSIMD || XNN_ARCH_WASMRELAXEDSIMD
    // Unlike most other architectures, on x86/x86-64 when floating-point instructions
    // have no NaN arguments, but produce NaN output, the output NaN has sign bit set.
    // We use it to distinguish x86/x86-64 from other architectures, by doing subtraction
    // of two infinities (must produce NaN per IEEE 754 standard).
    static const volatile float inf = INFINITY;
    hardware_config.is_x86 = signbit(inf - inf);
  #endif  // XNN_ARCH_WASM || XNN_ARCH_WASMSIMD || XNN_ARCH_WASMRELAXEDSIMD

  #if XNN_ARCH_WASMRELAXEDSIMD
    {
      // Check if out-of-bounds behavior of Relaxed Swizzle is consistent with PSHUFB.
      const v128_t table = wasm_i8x16_const(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
      const v128_t index_mask = wasm_i8x16_const_splat(INT8_C(0x8F));
      const volatile v128_t index_increment = wasm_i8x16_const_splat(16);  // volatile to confuse Clang which otherwise mis-compiles
      v128_t index = wasm_i8x16_const(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15);
      v128_t diff = wasm_i8x16_const_splat(0);
      for (uint32_t i = 16; i != 0; i--) {
        const v128_t pshufb_result = wasm_i8x16_swizzle(table, wasm_v128_and(index, index_mask));
        const v128_t relaxed_result = wasm_i8x16_relaxed_swizzle(table, index);
        diff = wasm_v128_or(diff, wasm_v128_xor(pshufb_result, relaxed_result));
        index = wasm_i8x16_add(index, index_increment);
      }
      hardware_config.use_wasm_pshufb = !wasm_v128_any_true(diff);
    }

    {
      // Check out-of-bounds behaviour of Relaxed Integer Dot Product with Accumulation.
      const v128_t int8_input = wasm_i8x16_const(0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0);
      const volatile v128_t xint8_input = wasm_i8x16_const(0, 0, 0, -128, 0, 0, -128, 0, 0, -128, 0, 0, -128, 0, 0, 0);  // volatile to confuse Clang which otherwise ICE's
      const v128_t xint8_output = wasm_i32x4_relaxed_dot_i8x16_i7x16_add(int8_input, xint8_input, wasm_i8x16_const_splat(0));

      const volatile v128_t overflow_input = wasm_i8x16_const(-128, -128, -128, -128, -128, -128, -1, -1, -1, -1, -128, -128, -1, -1, -1, -1);  // volatile to confuse Clang which otherwise ICE's
      const v128_t overflow_output = wasm_i32x4_relaxed_dot_i8x16_i7x16_add(wasm_i8x16_const_splat(-128), overflow_input, wasm_i8x16_const_splat(0));
      hardware_config.use_wasm_sdot = !wasm_v128_any_true(wasm_v128_or(
        wasm_v128_xor(xint8_output, wasm_i32x4_const_splat(-128)),
        wasm_v128_xor(overflow_output, wasm_i32x4_const(65536, 33024, 33024, 512))));
    }
    {
      // Check out-of-bounds behaviour of Relaxed Integer Dot Product with Accumulation with signed and unsigned input (e.g. vpdpbusd).
      const v128_t int8_input = wasm_i8x16_const(0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0);
      const volatile v128_t xint8_input = wasm_i8x16_const(0, 0, 0, -128, 0, 0, -128, 0, 0, -128, 0, 0, -128, 0, 0, 0);  // volatile to confuse Clang which otherwise ICE's
      const v128_t xint8_output = wasm_i32x4_relaxed_dot_i8x16_i7x16_add(int8_input, xint8_input, wasm_i8x16_const_splat(0));

      const volatile v128_t overflow_input = wasm_i8x16_const(-128, -128, -128, -128, -128, -128, -1, -1, -1, -1, -128, -128, -1, -1, -1, -1);  // volatile to confuse Clang which otherwise ICE's
      const v128_t overflow_output = wasm_i32x4_relaxed_dot_i8x16_i7x16_add(wasm_i8x16_const_splat(-128), overflow_input, wasm_i8x16_const_splat(0));
      hardware_config.use_wasm_usdot = !wasm_v128_any_true(wasm_v128_or(
        wasm_v128_xor(xint8_output, wasm_i32x4_const_splat(128)),
        wasm_v128_xor(overflow_output, wasm_i32x4_const(-65536, -98048, -98048, -130560))));
    }
    {
      const v128_t input1 = wasm_i32x4_const(0xF0F0F0F0, 0xAAAAAAAA, 0xCCCCCCCC, 0x99999999);
      const v128_t input2 = wasm_i32x4_const(0x0F0F0F0F, 0x55555555, 0x33333333, 0x66666666);
      v128_t diff = wasm_i8x16_const_splat(0);
      for (uint32_t shift = 0; shift < 32; ++shift) {
        const uint32_t mask = UINT32_C(1) << shift;
        const volatile v128_t vmask = wasm_u32x4_splat(mask);
        const v128_t blendvps_result = wasm_v128_bitselect(input1, input2, wasm_i32x4_shr(vmask, 31));
        const v128_t relaxed_result = wasm_i32x4_relaxed_laneselect(input1, input2, vmask);
        diff = wasm_v128_or(diff, wasm_v128_xor(blendvps_result, relaxed_result));
      }
      hardware_config.use_wasm_blendvps = !wasm_v128_any_true(diff);
    }
    {
      const v128_t input1 = wasm_f32x4_const(16777218.f, 0.f, 0.f, 0.f);
      const v128_t input2 = wasm_f32x4_const(3.f, 0.f, 0.f, 0.f);
      const v128_t input3 = wasm_f32x4_const(3.f, 0.f, 0.f, 0.f);
      v128_t diff = wasm_i8x16_const_splat(0);
      const v128_t relaxed_result = wasm_f32x4_relaxed_madd(input1, input2, input3);
      const v128_t mul_result = wasm_f32x4_add(input3, wasm_f32x4_mul(input1, input2));
      diff = wasm_v128_or(diff, wasm_v128_xor(mul_result, relaxed_result));
      hardware_config.use_wasm_fma = !wasm_v128_any_true(diff);
    }
  #endif  // XNN_ARCH_WASMRELAXEDSIMD

  hardware_config.arch_flags = 0;
  #if XNN_ARCH_ARM
    if (hardware_config.use_arm_v6) hardware_config.arch_flags |= xnn_arch_arm_v6;
    if (hardware_config.use_arm_vfpv2) hardware_config.arch_flags |= xnn_arch_arm_vfpv2;
  #endif  // XNN_ARCH_ARM
  #if XNN_ARCH_ARM || XNN_ARCH_ARM64
    if (hardware_config.use_arm_vfpv3) hardware_config.arch_flags |= xnn_arch_arm_vfpv3;
    if (hardware_config.use_arm_neon) hardware_config.arch_flags |= xnn_arch_arm_neon;
    if (hardware_config.use_arm_neon_fp16) hardware_config.arch_flags |= xnn_arch_arm_neon_fp16;
    if (hardware_config.use_arm_neon_fma) hardware_config.arch_flags |= xnn_arch_arm_neon_fma;
    if (hardware_config.use_arm_neon_v8) hardware_config.arch_flags |= xnn_arch_arm_neon_v8;
    if (hardware_config.use_arm_fp16_arith) hardware_config.arch_flags |= xnn_arch_arm_fp16_arith;
    if (hardware_config.use_arm_neon_fp16_arith) hardware_config.arch_flags |= xnn_arch_arm_neon_fp16_arith;
    if (hardware_config.use_arm_neon_bf16) hardware_config.arch_flags |= xnn_arch_arm_neon_bf16;
    if (hardware_config.use_arm_neon_dot) hardware_config.arch_flags |= xnn_arch_arm_neon_dot;
  #endif  // XNN_ARCH_ARM || XNN_ARCH_ARM64
  #if XNN_ARCH_ARM64
    if (hardware_config.use_arm_neon_i8mm) hardware_config.arch_flags |= xnn_arch_arm_neon_i8mm;
    if (hardware_config.use_arm_sve) hardware_config.arch_flags |= xnn_arch_arm_sve;
    if (hardware_config.use_arm_sve2) hardware_config.arch_flags |= xnn_arch_arm_sve2;
    if (hardware_config.use_arm_sme) hardware_config.arch_flags |= xnn_arch_arm_sme;
    if (hardware_config.use_arm_sme2) hardware_config.arch_flags |= xnn_arch_arm_sme2;
  #endif  // XNN_ARCH_ARM64
  #if XNN_ARCH_X86 || XNN_ARCH_X86_64
    if (hardware_config.use_x86_ssse3) hardware_config.arch_flags |= xnn_arch_x86_ssse3;
    if (hardware_config.use_x86_sse4_1) hardware_config.arch_flags |= xnn_arch_x86_sse4_1;
    if (hardware_config.use_x86_avx) hardware_config.arch_flags |= xnn_arch_x86_avx;
    if (hardware_config.use_x86_f16c) hardware_config.arch_flags |= xnn_arch_x86_f16c;
    if (hardware_config.use_x86_fma3) hardware_config.arch_flags |= xnn_arch_x86_fma3;
    if (hardware_config.use_x86_avx2) hardware_config.arch_flags |= xnn_arch_x86_avx2;
    if (hardware_config.use_x86_avxvnni) hardware_config.arch_flags |= xnn_arch_x86_avxvnni;
    if (hardware_config.use_x86_avxvnniint8) hardware_config.arch_flags |= xnn_arch_x86_avxvnniint8;
    if (hardware_config.use_x86_avx256skx) hardware_config.arch_flags |= xnn_arch_x86_avx256skx;
    if (hardware_config.use_x86_avx256vnni) hardware_config.arch_flags |= xnn_arch_x86_avx256vnni;
    if (hardware_config.use_x86_avx256vnnigfni) hardware_config.arch_flags |= xnn_arch_x86_avx256vnnigfni;
    if (hardware_config.use_x86_avx512f) hardware_config.arch_flags |= xnn_arch_x86_avx512f;
    if (hardware_config.use_x86_avx512vbmi) hardware_config.arch_flags |= xnn_arch_x86_avx512vbmi;
    if (hardware_config.use_x86_avx512skx) hardware_config.arch_flags |= xnn_arch_x86_avx512skx;
    if (hardware_config.use_x86_avx512vnni) hardware_config.arch_flags |= xnn_arch_x86_avx512vnni;
    if (hardware_config.use_x86_avx512vnnigfni) hardware_config.arch_flags |= xnn_arch_x86_avx512vnnigfni;
    if (hardware_config.use_x86_avx512amx) hardware_config.arch_flags |= xnn_arch_x86_avx512amx;
    if (hardware_config.use_x86_avx512fp16) hardware_config.arch_flags |= xnn_arch_x86_avx512fp16;
  #endif
  #if XNN_ARCH_RISCV
    if (hardware_config.use_riscv_vector) hardware_config.arch_flags |= xnn_arch_riscv_vector;
    if (hardware_config.use_riscv_vector_fp16_arith) hardware_config.arch_flags |= xnn_arch_riscv_vector_fp16_arith;
  #endif
  #if XNN_ARCH_PPC64
    if (hardware_config.use_vsx) hardware_config.arch_flags |= xnn_arch_vsx;
    if (hardware_config.use_vsx3) hardware_config.arch_flags |= xnn_arch_vsx3;
    if (hardware_config.use_mma) hardware_config.arch_flags |= xnn_arch_mma;
  #endif
  #if XNN_ARCH_WASM || XNN_ARCH_WASMSIMD || XNN_ARCH_WASMRELAXEDSIMD
    if (hardware_config.is_x86) hardware_config.arch_flags |= xnn_arch_wasm_is_x86;
  #endif  // XNN_ARCH_WASM || XNN_ARCH_WASMSIMD || XNN_ARCH_WASMRELAXEDSIMD
  #if XNN_ARCH_WASMRELAXEDSIMD
    if (hardware_config.use_wasm_blendvps) hardware_config.arch_flags |= xnn_arch_wasm_blendvps;
    if (hardware_config.use_wasm_pshufb) hardware_config.arch_flags |= xnn_arch_wasm_pshufb;
    if (hardware_config.use_wasm_sdot) hardware_config.arch_flags |= xnn_arch_wasm_sdot;
    if (hardware_config.use_wasm_usdot) hardware_config.arch_flags |= xnn_arch_wasm_usdot;
    if (hardware_config.use_wasm_fma) hardware_config.arch_flags |= xnn_arch_wasm_fma;
  #endif  // XNN_ARCH_WASMRELAXEDSIMD
  #if XNN_ARCH_HEXAGON
    if (hardware_config.use_hvx) hardware_config.arch_flags |= xnn_arch_hvx;
  #endif  // XNN_ARCH_HEXAGON

#if XNN_ENABLE_CPUINFO
    // Set the size of the L1 and L2 data caches.
    if (!cpuinfo_initialize()) {
      xnn_log_warning(
          "Failed to initialize cpuinfo, unable to determine L1/L2 data cache "
          "properties.");
    } else {
      const struct cpuinfo_processor* proc_info = cpuinfo_get_processor(0);
      if (proc_info != NULL) {
        // Get the L1 cache information.
        const struct cpuinfo_cache* l1_data_cache = proc_info->cache.l1d;
        if (l1_data_cache != NULL) {
          hardware_config.l1_data_cache_bytes = l1_data_cache->size;
          hardware_config.l1_data_cache_line_size = l1_data_cache->line_size;
          hardware_config.l1_data_cache_associativity =
              l1_data_cache->associativity;
          hardware_config.l1_data_cache_num_sets = l1_data_cache->sets;
          xnn_log_debug(
              "l1_data_cache_bytes=%zu, l1_data_cache_line_size=%zu, "
              "l1_data_cache_associativity=%zu, l1_data_cache_num_sets=%zu.\n",
              hardware_config.l1_data_cache_bytes,
              hardware_config.l1_data_cache_line_size,
              hardware_config.l1_data_cache_associativity,
              hardware_config.l1_data_cache_num_sets);
        } else {
          xnn_log_warning("Unable to determine L1 data cache properties.");
        }

        // Get the L2 cache information.
        const struct cpuinfo_cache* l2_data_cache = proc_info->cache.l2;
        if (l2_data_cache != NULL) {
          hardware_config.l2_data_cache_bytes = l2_data_cache->size;
          hardware_config.l2_data_cache_line_size = l2_data_cache->line_size;
          hardware_config.l2_data_cache_associativity =
              l2_data_cache->associativity;
          hardware_config.l2_data_cache_num_sets = l2_data_cache->sets;
          xnn_log_debug(
              "l2_data_cache_bytes=%zu, l2_data_cache_line_size=%zu, "
              "l2_data_cache_associativity=%zu, l2_data_cache_num_sets=%zu.\n",
              hardware_config.l2_data_cache_bytes,
              hardware_config.l2_data_cache_line_size,
              hardware_config.l2_data_cache_associativity,
              hardware_config.l2_data_cache_num_sets);
        } else {
          xnn_log_warning("Unable to determine L2 data cache properties.");
        }
      } else {
        xnn_log_warning("Unable to determine L1/L2 data cache properties.");
      }
    }
#else
    xnn_log_warning("Unable to determine L1/L2 data cache properties.");
#endif  // XNN_ENABLE_CPUINFO
}

const struct xnn_hardware_config* xnn_init_hardware_config() {
  #if !XNN_PLATFORM_WEB && !XNN_ARCH_RISCV && !XNN_ARCH_PPC64 && XNN_ENABLE_CPUINFO
    if (!cpuinfo_initialize()) {
      xnn_log_error("failed to initialize cpuinfo");
      return NULL;
    }
  #endif  // !XNN_PLATFORM_WEB && !XNN_ARCH_RISCV && !XNN_ARCH_PPC64
  #if XNN_ARCH_ARM
    #if XNN_PLATFORM_MOBILE
      if (!cpuinfo_has_arm_neon()) {
        xnn_log_debug("unsupported hardware: ARM NEON not detected");
        return NULL;
      }
    #else
      if (!cpuinfo_has_arm_v6()) {
        xnn_log_debug("unsupported hardware: ARMv6 not detected");
        return NULL;
      }

      if (!cpuinfo_has_arm_vfpv2() && !cpuinfo_has_arm_vfpv3()) {
        xnn_log_debug("unsupported hardware: VFP FPU not detected");
        return NULL;
      }
    #endif
  #endif  // XNN_ARCH_ARM
  #if XNN_ARCH_X86
    if (!cpuinfo_has_x86_sse2()) {
      xnn_log_debug("unsupported hardware: SSE2 not detected");
      return NULL;
    }
  #endif  // XNN_ARCH_X86

  XNN_INIT_ONCE(hardware);
  return &hardware_config;
}
