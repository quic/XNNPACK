// Copyright (c) Facebook, Inc. and its affiliates.
// All rights reserved.
//
// Copyright 2019 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.
//
// Auto-generated file. Do not edit!
//   Specification: test/bf16-gemm-minmax.yaml
//   Generator: tools/generate-gemm-test.py

#include <cstddef>
#include <functional>
#include <string>
#include <vector>

#include <gtest/gtest.h>
#include "xnnpack/allocator.h"
#include "xnnpack/common.h"
#include "xnnpack/gemm.h"
#include "xnnpack/igemm.h"
#include "xnnpack/isa-checks.h"
#include "xnnpack/microparams-init.h"
#include "xnnpack/pack.h"
#include "xnnpack/packw.h"
#include "xnnpack/ppmm.h"
#include "xnnpack/requantization.h"
#include "gemm-microkernel-tester.h"
#include "next_prime.h"

namespace {

std::vector<GemmTestParams> CreateTests1(
    size_t k_block, size_t adj_k_block,
    size_t mr, size_t nr, size_t kr, size_t sr,
    bool is_igemm,
    bool unsigned_inputs,
    std::function<void(GemmMicrokernelTester& tester)> test_func,
    std::function<void()> isa_check = nullptr) {
  std::string kbs = std::to_string(k_block);
  std::string kb2s = std::to_string(k_block * 2);
  std::string akbs = std::to_string(adj_k_block);
  std::string nrs = std::to_string(nr);

  const GemmMicrokernelTester tester = GemmMicrokernelTester()
      .mr(mr).nr(nr).kr(kr).sr(sr).unsigned_inputs(unsigned_inputs);

  std::vector<GemmTestParams> gemm_tests;
  gemm_tests.reserve(42);

  gemm_tests.push_back(GemmTestParams(
      "k_eq_" + kbs,
      tester.clone()
          .m(mr).n(nr).k(k_block)
      , test_func, isa_check));
  if (!is_igemm) {
    gemm_tests.push_back(GemmTestParams(
        "k_eq_" + kbs + "_strided_a",
        tester.clone()
            .m(mr).n(nr).k(k_block)
            .a_stride(xnnpack::NextPrime(k_block + 1))
        , test_func, isa_check));
  }
  gemm_tests.push_back(GemmTestParams(
      "k_eq_" + kbs + "_subtile",
      tester.clone()
          .k(k_block)
      , test_func, isa_check)
      .loop_n(1, nr)
      .loop_m(1, mr));
  gemm_tests.push_back(GemmTestParams(
      "k_eq_" + kbs + "_subtile_m",
      tester.clone()
          .n(nr).k(k_block)
      , test_func, isa_check)
      .loop_m(1, mr));
  gemm_tests.push_back(GemmTestParams(
      "k_eq_" + kbs + "_subtile_n",
      tester.clone()
          .m(mr).k(k_block)
      , test_func, isa_check)
      .loop_n(1, nr));
  if (k_block > 1) {
    gemm_tests.push_back(GemmTestParams(
        "k_lt_" + akbs,
        tester.clone()
            .m(mr).n(nr)
        , test_func, isa_check)
        .loop_k(1, adj_k_block - 1));
    if (!is_igemm) {
      gemm_tests.push_back(GemmTestParams(
          "k_lt_" + akbs + "_strided_a",
          tester.clone()
              .m(mr).n(nr)
              .a_stride(xnnpack::NextPrime(adj_k_block + 1))
          , test_func, isa_check)
          .loop_k(1, adj_k_block - 1));
    }
    gemm_tests.push_back(GemmTestParams(
        "k_lt_" + akbs + "_subtile",
        tester.clone()
        , test_func, isa_check)
        .loop_k(1, adj_k_block - 1)
        .loop_n(1, nr)
        .loop_m(1, mr));
  }
  gemm_tests.push_back(GemmTestParams(
      "k_gt_" + akbs,
      tester.clone()
          .m(mr).n(nr)
      , test_func, isa_check)
      .loop_k(adj_k_block + 1, adj_k_block * 2 - 1, k_block));
  if (is_igemm) {
    gemm_tests.push_back(GemmTestParams(
        "k_gt_" + akbs + "_strided_a",
        tester.clone()
            .m(mr).n(nr)
            .a_stride(xnnpack::NextPrime(adj_k_block * 2 + 1))
      , test_func, isa_check)
      .loop_k(adj_k_block + 1, adj_k_block * 2 - 1, k_block));
  }
  gemm_tests.push_back(GemmTestParams(
      "k_gt_" + akbs + "_subtile",
      tester.clone()
      , test_func, isa_check)
      .loop_k(adj_k_block + 1, adj_k_block * 2 - 1, k_block)
      .loop_n(1, nr)
      .loop_m(1, mr));
  if (k_block > 1) {
    gemm_tests.push_back(GemmTestParams(
        "k_div_" + kbs,
        tester.clone()
            .m(mr).n(nr)
        , test_func, isa_check)
        .loop_k(adj_k_block + k_block, k_block * 5, k_block));
    if (is_igemm) {
      gemm_tests.push_back(GemmTestParams(
          "k_div_" + kbs + "_strided_a",
          tester.clone()
              .m(mr).n(nr)
              .a_stride(xnnpack::NextPrime(k_block * 3 + 1))
          , test_func, isa_check)
          .loop_k(adj_k_block + k_block, k_block * 3, k_block));
    }
    gemm_tests.push_back(GemmTestParams(
        "k_div_" + kbs + "_subtile",
        tester.clone()
        , test_func, isa_check)
        .loop_k(adj_k_block + k_block, k_block * 5, k_block)
        .loop_n(1, nr)
        .loop_m(1, mr));
  }
  gemm_tests.push_back(GemmTestParams(
      "n_gt_" + nrs,
      tester.clone()
          .m(mr)
      , test_func, isa_check)
      .loop_n(nr + 1, nr * 2 - 1)
      .loop_k(1, k_block * 3, k_block + 1));
  if (!is_igemm) {
    gemm_tests.push_back(GemmTestParams(
        "n_gt_" + nrs + "_strided_a",
        tester.clone()
            .m(mr)
            .a_stride(xnnpack::NextPrime(k_block * 3 + 1))
        , test_func, isa_check)
        .loop_n(nr + 1, nr * 2 - 1)
        .loop_k(1, k_block * 3, k_block));
  }
  gemm_tests.push_back(GemmTestParams(
      "n_gt_" + nrs + "_subtile",
      tester.clone()
      , test_func, isa_check)
      .loop_n(nr + 1, nr * 2 - 1)
      .loop_k(1, k_block * 3, k_block + 1)
      .loop_m(1, mr));
  gemm_tests.push_back(GemmTestParams(
      "n_div_" + nrs,
      tester.clone()
          .m(mr)
      , test_func, isa_check)
      .loop_n(nr * 2, nr * 3, nr)
      .loop_k(1, k_block * 3, k_block + 1));
  if (!is_igemm) {
    gemm_tests.push_back(GemmTestParams(
        "n_div_" + nrs + "_strided_a",
        tester.clone()
            .m(mr)
            .a_stride(xnnpack::NextPrime(k_block * 3 + 1))
        , test_func, isa_check)
        .loop_n(nr * 2, nr * 3, nr)
        .loop_k(1, k_block * 3, k_block));
  }
  gemm_tests.push_back(GemmTestParams(
      "n_div_" + nrs + "_subtile",
      tester.clone()
      , test_func, isa_check)
      .loop_n(nr * 2, nr * 3, nr)
      .loop_k(1, k_block * 3, k_block + 1)
      .loop_m(1, mr));
  if (is_igemm) {
    gemm_tests.push_back(GemmTestParams(
        "small_kernel",
        tester.clone()
            .m(mr).n(nr).ks(3)
        , test_func, isa_check)
        .loop_k(1, k_block * 3, k_block + 1));
    gemm_tests.push_back(GemmTestParams(
        "small_kernel_subtile",
        tester.clone()
            .ks(3)
        , test_func, isa_check)
        .loop_k(1, k_block * 3, k_block + 1)
        .loop_n(1, nr)
        .loop_m(1, mr));
    gemm_tests.push_back(GemmTestParams(
        "n_gt_" + nrs + "_small_kernel",
        tester.clone()
            .m(mr).ks(3)
        , test_func, isa_check)
        .loop_n(nr + 1, nr * 2 - 1)
        .loop_k(1, k_block * 3, k_block + 1));
    gemm_tests.push_back(GemmTestParams(
        "n_div_" + nrs + "_small_kernel",
        tester.clone()
            .m(mr).ks(3)
        , test_func, isa_check)
        .loop_n(nr * 2, nr * 3, nr)
        .loop_k(1, k_block * 3, k_block + 1));
  }
  gemm_tests.push_back(GemmTestParams(
      "strided_cm_subtile",
      tester.clone()
          .mr(mr).nr(nr).kr(kr).sr(sr)
          .cm_stride(xnnpack::NextPrime(nr + 1))
      , test_func, isa_check)
      .loop_k(1, k_block * 3, k_block + 1)
      .loop_n(1, nr)
      .loop_m(1, mr));
  if (is_igemm) {
    gemm_tests.push_back(GemmTestParams(
        "a_offset",
        tester.clone()
            .m(mr).n(nr).ks(3)
            .a_offset(xnnpack::NextPrime(mr * k_block * 3 + 1))
        , test_func, isa_check)
        .loop_k(1, k_block * 3, k_block + 1));
    gemm_tests.push_back(GemmTestParams(
        "zero",
        tester.clone()
            .m(mr).n(nr).ks(3)
            .a_offset(xnnpack::NextPrime(mr * k_block * 3 + 1))
        , test_func, isa_check)
        .loop_k(1, k_block * 3, k_block + 1)
        .loop_zi(0, mr - 1));
  }
  gemm_tests.push_back(GemmTestParams(
      "qmin",
      tester.clone()
          .m(mr).n(nr).k(k_block).qmin(128)
      , test_func, isa_check));
  gemm_tests.push_back(GemmTestParams(
      "qmax",
      tester.clone()
          .m(mr).n(nr).k(k_block).qmax(128)
      , test_func, isa_check));
  gemm_tests.push_back(GemmTestParams(
      "strided_cm",
      tester.clone()
          .m(mr).n(nr).k(k_block)
          .cm_stride(xnnpack::NextPrime(nr + 1))
      , test_func, isa_check));

  return gemm_tests;
}

}  // namespace


#if XNN_ARCH_ARM || XNN_ARCH_ARM64
  INSTANTIATE_TEST_SUITE_P(
      BF16_GEMM_MINMAX_1X4C8__NEONFMA_SHLAND, GemmTest,
      testing::ValuesIn(CreateTests1(
          /*k_block=*/8,
          /*adj_k_block=*/8,
          /*mr=*/1, /*nr=*/4, /*kr=*/8, /*sr=*/1,
          /*is_igemm=*/false,
          /*unsigned_inputs=*/false,
          [](GemmMicrokernelTester& tester) {
            tester.Test(xnn_bf16_gemm_minmax_ukernel_1x4c8__neonfma_shland,
                        xnn_init_bf16_minmax_scalar_params,
                        xnn_pack_f16_gemm_goi_w);
          },
          []() {
            TEST_REQUIRES_ARM_NEON_FMA;
          })),
      [](const testing::TestParamInfo<GemmTest::ParamType>& info) {
        return info.param.test_name;
      });

  INSTANTIATE_TEST_SUITE_P(
      BF16_GEMM_MINMAX_2X4C8__NEONFMA_SHLAND, GemmTest,
      testing::ValuesIn(CreateTests1(
          /*k_block=*/8,
          /*adj_k_block=*/8,
          /*mr=*/2, /*nr=*/4, /*kr=*/8, /*sr=*/1,
          /*is_igemm=*/false,
          /*unsigned_inputs=*/false,
          [](GemmMicrokernelTester& tester) {
            tester.Test(xnn_bf16_gemm_minmax_ukernel_2x4c8__neonfma_shland,
                        xnn_init_bf16_minmax_scalar_params,
                        xnn_pack_f16_gemm_goi_w);
          },
          []() {
            TEST_REQUIRES_ARM_NEON_FMA;
          })),
      [](const testing::TestParamInfo<GemmTest::ParamType>& info) {
        return info.param.test_name;
      });

  INSTANTIATE_TEST_SUITE_P(
      BF16_GEMM_MINMAX_3X4C8__NEONFMA_SHLAND, GemmTest,
      testing::ValuesIn(CreateTests1(
          /*k_block=*/8,
          /*adj_k_block=*/8,
          /*mr=*/3, /*nr=*/4, /*kr=*/8, /*sr=*/1,
          /*is_igemm=*/false,
          /*unsigned_inputs=*/false,
          [](GemmMicrokernelTester& tester) {
            tester.Test(xnn_bf16_gemm_minmax_ukernel_3x4c8__neonfma_shland,
                        xnn_init_bf16_minmax_scalar_params,
                        xnn_pack_f16_gemm_goi_w);
          },
          []() {
            TEST_REQUIRES_ARM_NEON_FMA;
          })),
      [](const testing::TestParamInfo<GemmTest::ParamType>& info) {
        return info.param.test_name;
      });

  INSTANTIATE_TEST_SUITE_P(
      BF16_GEMM_MINMAX_4X4C8__NEONFMA_SHLAND, GemmTest,
      testing::ValuesIn(CreateTests1(
          /*k_block=*/8,
          /*adj_k_block=*/8,
          /*mr=*/4, /*nr=*/4, /*kr=*/8, /*sr=*/1,
          /*is_igemm=*/false,
          /*unsigned_inputs=*/false,
          [](GemmMicrokernelTester& tester) {
            tester.Test(xnn_bf16_gemm_minmax_ukernel_4x4c8__neonfma_shland,
                        xnn_init_bf16_minmax_scalar_params,
                        xnn_pack_f16_gemm_goi_w);
          },
          []() {
            TEST_REQUIRES_ARM_NEON_FMA;
          })),
      [](const testing::TestParamInfo<GemmTest::ParamType>& info) {
        return info.param.test_name;
      });

  INSTANTIATE_TEST_SUITE_P(
      BF16_GEMM_MINMAX_5X4C8__NEONFMA_SHLAND, GemmTest,
      testing::ValuesIn(CreateTests1(
          /*k_block=*/8,
          /*adj_k_block=*/8,
          /*mr=*/5, /*nr=*/4, /*kr=*/8, /*sr=*/1,
          /*is_igemm=*/false,
          /*unsigned_inputs=*/false,
          [](GemmMicrokernelTester& tester) {
            tester.Test(xnn_bf16_gemm_minmax_ukernel_5x4c8__neonfma_shland,
                        xnn_init_bf16_minmax_scalar_params,
                        xnn_pack_f16_gemm_goi_w);
          },
          []() {
            TEST_REQUIRES_ARM_NEON_FMA;
          })),
      [](const testing::TestParamInfo<GemmTest::ParamType>& info) {
        return info.param.test_name;
      });

  INSTANTIATE_TEST_SUITE_P(
      BF16_GEMM_MINMAX_1X4C8__NEONFMA_ZIP, GemmTest,
      testing::ValuesIn(CreateTests1(
          /*k_block=*/8,
          /*adj_k_block=*/8,
          /*mr=*/1, /*nr=*/4, /*kr=*/8, /*sr=*/1,
          /*is_igemm=*/false,
          /*unsigned_inputs=*/false,
          [](GemmMicrokernelTester& tester) {
            tester.Test(xnn_bf16_gemm_minmax_ukernel_1x4c8__neonfma_zip,
                        xnn_init_bf16_minmax_scalar_params,
                        xnn_pack_f16_gemm_goi_w);
          },
          []() {
            TEST_REQUIRES_ARM_NEON_FMA;
          })),
      [](const testing::TestParamInfo<GemmTest::ParamType>& info) {
        return info.param.test_name;
      });

  INSTANTIATE_TEST_SUITE_P(
      BF16_GEMM_MINMAX_2X4C8__NEONFMA_ZIP, GemmTest,
      testing::ValuesIn(CreateTests1(
          /*k_block=*/8,
          /*adj_k_block=*/8,
          /*mr=*/2, /*nr=*/4, /*kr=*/8, /*sr=*/1,
          /*is_igemm=*/false,
          /*unsigned_inputs=*/false,
          [](GemmMicrokernelTester& tester) {
            tester.Test(xnn_bf16_gemm_minmax_ukernel_2x4c8__neonfma_zip,
                        xnn_init_bf16_minmax_scalar_params,
                        xnn_pack_f16_gemm_goi_w);
          },
          []() {
            TEST_REQUIRES_ARM_NEON_FMA;
          })),
      [](const testing::TestParamInfo<GemmTest::ParamType>& info) {
        return info.param.test_name;
      });

  INSTANTIATE_TEST_SUITE_P(
      BF16_GEMM_MINMAX_3X4C8__NEONFMA_ZIP, GemmTest,
      testing::ValuesIn(CreateTests1(
          /*k_block=*/8,
          /*adj_k_block=*/8,
          /*mr=*/3, /*nr=*/4, /*kr=*/8, /*sr=*/1,
          /*is_igemm=*/false,
          /*unsigned_inputs=*/false,
          [](GemmMicrokernelTester& tester) {
            tester.Test(xnn_bf16_gemm_minmax_ukernel_3x4c8__neonfma_zip,
                        xnn_init_bf16_minmax_scalar_params,
                        xnn_pack_f16_gemm_goi_w);
          },
          []() {
            TEST_REQUIRES_ARM_NEON_FMA;
          })),
      [](const testing::TestParamInfo<GemmTest::ParamType>& info) {
        return info.param.test_name;
      });

  INSTANTIATE_TEST_SUITE_P(
      BF16_GEMM_MINMAX_4X4C8__NEONFMA_ZIP, GemmTest,
      testing::ValuesIn(CreateTests1(
          /*k_block=*/8,
          /*adj_k_block=*/8,
          /*mr=*/4, /*nr=*/4, /*kr=*/8, /*sr=*/1,
          /*is_igemm=*/false,
          /*unsigned_inputs=*/false,
          [](GemmMicrokernelTester& tester) {
            tester.Test(xnn_bf16_gemm_minmax_ukernel_4x4c8__neonfma_zip,
                        xnn_init_bf16_minmax_scalar_params,
                        xnn_pack_f16_gemm_goi_w);
          },
          []() {
            TEST_REQUIRES_ARM_NEON_FMA;
          })),
      [](const testing::TestParamInfo<GemmTest::ParamType>& info) {
        return info.param.test_name;
      });

  INSTANTIATE_TEST_SUITE_P(
      BF16_GEMM_MINMAX_5X4C8__NEONFMA_ZIP, GemmTest,
      testing::ValuesIn(CreateTests1(
          /*k_block=*/8,
          /*adj_k_block=*/8,
          /*mr=*/5, /*nr=*/4, /*kr=*/8, /*sr=*/1,
          /*is_igemm=*/false,
          /*unsigned_inputs=*/false,
          [](GemmMicrokernelTester& tester) {
            tester.Test(xnn_bf16_gemm_minmax_ukernel_5x4c8__neonfma_zip,
                        xnn_init_bf16_minmax_scalar_params,
                        xnn_pack_f16_gemm_goi_w);
          },
          []() {
            TEST_REQUIRES_ARM_NEON_FMA;
          })),
      [](const testing::TestParamInfo<GemmTest::ParamType>& info) {
        return info.param.test_name;
      });
#endif  // XNN_ARCH_ARM || XNN_ARCH_ARM64


#if XNN_ENABLE_ARM_BF16 && (XNN_ARCH_ARM || XNN_ARCH_ARM64)
  INSTANTIATE_TEST_SUITE_P(
      BF16_GEMM_MINMAX_1X8C2__NEONBF16_BFDOT_LANE_LD128, GemmTest,
      testing::ValuesIn(CreateTests1(
          /*k_block=*/8,
          /*adj_k_block=*/8,
          /*mr=*/1, /*nr=*/8, /*kr=*/2, /*sr=*/1,
          /*is_igemm=*/false,
          /*unsigned_inputs=*/false,
          [](GemmMicrokernelTester& tester) {
            tester.Test(xnn_bf16_gemm_minmax_ukernel_1x8c2__neonbf16_bfdot_lane_ld128,
                        xnn_init_bf16_minmax_scalar_params,
                        xnn_pack_f16_gemm_goi_w);
          },
          []() {
            TEST_REQUIRES_ARM_NEON_BF16;
          })),
      [](const testing::TestParamInfo<GemmTest::ParamType>& info) {
        return info.param.test_name;
      });

  INSTANTIATE_TEST_SUITE_P(
      BF16_GEMM_MINMAX_4X8C2__NEONBF16_BFDOT_LANE_LD128, GemmTest,
      testing::ValuesIn(CreateTests1(
          /*k_block=*/8,
          /*adj_k_block=*/8,
          /*mr=*/4, /*nr=*/8, /*kr=*/2, /*sr=*/1,
          /*is_igemm=*/false,
          /*unsigned_inputs=*/false,
          [](GemmMicrokernelTester& tester) {
            tester.Test(xnn_bf16_gemm_minmax_ukernel_4x8c2__neonbf16_bfdot_lane_ld128,
                        xnn_init_bf16_minmax_scalar_params,
                        xnn_pack_f16_gemm_goi_w);
          },
          []() {
            TEST_REQUIRES_ARM_NEON_BF16;
          })),
      [](const testing::TestParamInfo<GemmTest::ParamType>& info) {
        return info.param.test_name;
      });

  INSTANTIATE_TEST_SUITE_P(
      BF16_GEMM_MINMAX_5X8C2__NEONBF16_BFDOT_LANE_LD128, GemmTest,
      testing::ValuesIn(CreateTests1(
          /*k_block=*/8,
          /*adj_k_block=*/8,
          /*mr=*/5, /*nr=*/8, /*kr=*/2, /*sr=*/1,
          /*is_igemm=*/false,
          /*unsigned_inputs=*/false,
          [](GemmMicrokernelTester& tester) {
            tester.Test(xnn_bf16_gemm_minmax_ukernel_5x8c2__neonbf16_bfdot_lane_ld128,
                        xnn_init_bf16_minmax_scalar_params,
                        xnn_pack_f16_gemm_goi_w);
          },
          []() {
            TEST_REQUIRES_ARM_NEON_BF16;
          })),
      [](const testing::TestParamInfo<GemmTest::ParamType>& info) {
        return info.param.test_name;
      });

  INSTANTIATE_TEST_SUITE_P(
      BF16_GEMM_MINMAX_6X8C2__NEONBF16_BFDOT_LANE_LD128, GemmTest,
      testing::ValuesIn(CreateTests1(
          /*k_block=*/8,
          /*adj_k_block=*/8,
          /*mr=*/6, /*nr=*/8, /*kr=*/2, /*sr=*/1,
          /*is_igemm=*/false,
          /*unsigned_inputs=*/false,
          [](GemmMicrokernelTester& tester) {
            tester.Test(xnn_bf16_gemm_minmax_ukernel_6x8c2__neonbf16_bfdot_lane_ld128,
                        xnn_init_bf16_minmax_scalar_params,
                        xnn_pack_f16_gemm_goi_w);
          },
          []() {
            TEST_REQUIRES_ARM_NEON_BF16;
          })),
      [](const testing::TestParamInfo<GemmTest::ParamType>& info) {
        return info.param.test_name;
      });

  INSTANTIATE_TEST_SUITE_P(
      BF16_GEMM_MINMAX_1X4C8__NEONBF16_BFDOT, GemmTest,
      testing::ValuesIn(CreateTests1(
          /*k_block=*/8,
          /*adj_k_block=*/8,
          /*mr=*/1, /*nr=*/4, /*kr=*/8, /*sr=*/1,
          /*is_igemm=*/false,
          /*unsigned_inputs=*/false,
          [](GemmMicrokernelTester& tester) {
            tester.Test(xnn_bf16_gemm_minmax_ukernel_1x4c8__neonbf16_bfdot,
                        xnn_init_bf16_minmax_scalar_params,
                        xnn_pack_f16_gemm_goi_w);
          },
          []() {
            TEST_REQUIRES_ARM_NEON_BF16;
          })),
      [](const testing::TestParamInfo<GemmTest::ParamType>& info) {
        return info.param.test_name;
      });

  INSTANTIATE_TEST_SUITE_P(
      BF16_GEMM_MINMAX_2X4C8__NEONBF16_BFDOT, GemmTest,
      testing::ValuesIn(CreateTests1(
          /*k_block=*/8,
          /*adj_k_block=*/8,
          /*mr=*/2, /*nr=*/4, /*kr=*/8, /*sr=*/1,
          /*is_igemm=*/false,
          /*unsigned_inputs=*/false,
          [](GemmMicrokernelTester& tester) {
            tester.Test(xnn_bf16_gemm_minmax_ukernel_2x4c8__neonbf16_bfdot,
                        xnn_init_bf16_minmax_scalar_params,
                        xnn_pack_f16_gemm_goi_w);
          },
          []() {
            TEST_REQUIRES_ARM_NEON_BF16;
          })),
      [](const testing::TestParamInfo<GemmTest::ParamType>& info) {
        return info.param.test_name;
      });

  INSTANTIATE_TEST_SUITE_P(
      BF16_GEMM_MINMAX_3X4C8__NEONBF16_BFDOT, GemmTest,
      testing::ValuesIn(CreateTests1(
          /*k_block=*/8,
          /*adj_k_block=*/8,
          /*mr=*/3, /*nr=*/4, /*kr=*/8, /*sr=*/1,
          /*is_igemm=*/false,
          /*unsigned_inputs=*/false,
          [](GemmMicrokernelTester& tester) {
            tester.Test(xnn_bf16_gemm_minmax_ukernel_3x4c8__neonbf16_bfdot,
                        xnn_init_bf16_minmax_scalar_params,
                        xnn_pack_f16_gemm_goi_w);
          },
          []() {
            TEST_REQUIRES_ARM_NEON_BF16;
          })),
      [](const testing::TestParamInfo<GemmTest::ParamType>& info) {
        return info.param.test_name;
      });

  INSTANTIATE_TEST_SUITE_P(
      BF16_GEMM_MINMAX_4X4C8__NEONBF16_BFDOT, GemmTest,
      testing::ValuesIn(CreateTests1(
          /*k_block=*/8,
          /*adj_k_block=*/8,
          /*mr=*/4, /*nr=*/4, /*kr=*/8, /*sr=*/1,
          /*is_igemm=*/false,
          /*unsigned_inputs=*/false,
          [](GemmMicrokernelTester& tester) {
            tester.Test(xnn_bf16_gemm_minmax_ukernel_4x4c8__neonbf16_bfdot,
                        xnn_init_bf16_minmax_scalar_params,
                        xnn_pack_f16_gemm_goi_w);
          },
          []() {
            TEST_REQUIRES_ARM_NEON_BF16;
          })),
      [](const testing::TestParamInfo<GemmTest::ParamType>& info) {
        return info.param.test_name;
      });

  INSTANTIATE_TEST_SUITE_P(
      BF16_GEMM_MINMAX_5X4C8__NEONBF16_BFDOT, GemmTest,
      testing::ValuesIn(CreateTests1(
          /*k_block=*/8,
          /*adj_k_block=*/8,
          /*mr=*/5, /*nr=*/4, /*kr=*/8, /*sr=*/1,
          /*is_igemm=*/false,
          /*unsigned_inputs=*/false,
          [](GemmMicrokernelTester& tester) {
            tester.Test(xnn_bf16_gemm_minmax_ukernel_5x4c8__neonbf16_bfdot,
                        xnn_init_bf16_minmax_scalar_params,
                        xnn_pack_f16_gemm_goi_w);
          },
          []() {
            TEST_REQUIRES_ARM_NEON_BF16;
          })),
      [](const testing::TestParamInfo<GemmTest::ParamType>& info) {
        return info.param.test_name;
      });

  INSTANTIATE_TEST_SUITE_P(
      BF16_GEMM_MINMAX_1X4C8__NEONBF16_BFMLAL, GemmTest,
      testing::ValuesIn(CreateTests1(
          /*k_block=*/8,
          /*adj_k_block=*/8,
          /*mr=*/1, /*nr=*/4, /*kr=*/8, /*sr=*/1,
          /*is_igemm=*/false,
          /*unsigned_inputs=*/false,
          [](GemmMicrokernelTester& tester) {
            tester.Test(xnn_bf16_gemm_minmax_ukernel_1x4c8__neonbf16_bfmlal,
                        xnn_init_bf16_minmax_scalar_params,
                        xnn_pack_f16_gemm_goi_w);
          },
          []() {
            TEST_REQUIRES_ARM_NEON_BF16;
          })),
      [](const testing::TestParamInfo<GemmTest::ParamType>& info) {
        return info.param.test_name;
      });

  INSTANTIATE_TEST_SUITE_P(
      BF16_GEMM_MINMAX_2X4C8__NEONBF16_BFMLAL, GemmTest,
      testing::ValuesIn(CreateTests1(
          /*k_block=*/8,
          /*adj_k_block=*/8,
          /*mr=*/2, /*nr=*/4, /*kr=*/8, /*sr=*/1,
          /*is_igemm=*/false,
          /*unsigned_inputs=*/false,
          [](GemmMicrokernelTester& tester) {
            tester.Test(xnn_bf16_gemm_minmax_ukernel_2x4c8__neonbf16_bfmlal,
                        xnn_init_bf16_minmax_scalar_params,
                        xnn_pack_f16_gemm_goi_w);
          },
          []() {
            TEST_REQUIRES_ARM_NEON_BF16;
          })),
      [](const testing::TestParamInfo<GemmTest::ParamType>& info) {
        return info.param.test_name;
      });

  INSTANTIATE_TEST_SUITE_P(
      BF16_GEMM_MINMAX_3X4C8__NEONBF16_BFMLAL, GemmTest,
      testing::ValuesIn(CreateTests1(
          /*k_block=*/8,
          /*adj_k_block=*/8,
          /*mr=*/3, /*nr=*/4, /*kr=*/8, /*sr=*/1,
          /*is_igemm=*/false,
          /*unsigned_inputs=*/false,
          [](GemmMicrokernelTester& tester) {
            tester.Test(xnn_bf16_gemm_minmax_ukernel_3x4c8__neonbf16_bfmlal,
                        xnn_init_bf16_minmax_scalar_params,
                        xnn_pack_f16_gemm_goi_w);
          },
          []() {
            TEST_REQUIRES_ARM_NEON_BF16;
          })),
      [](const testing::TestParamInfo<GemmTest::ParamType>& info) {
        return info.param.test_name;
      });

  INSTANTIATE_TEST_SUITE_P(
      BF16_GEMM_MINMAX_4X4C8__NEONBF16_BFMLAL, GemmTest,
      testing::ValuesIn(CreateTests1(
          /*k_block=*/8,
          /*adj_k_block=*/8,
          /*mr=*/4, /*nr=*/4, /*kr=*/8, /*sr=*/1,
          /*is_igemm=*/false,
          /*unsigned_inputs=*/false,
          [](GemmMicrokernelTester& tester) {
            tester.Test(xnn_bf16_gemm_minmax_ukernel_4x4c8__neonbf16_bfmlal,
                        xnn_init_bf16_minmax_scalar_params,
                        xnn_pack_f16_gemm_goi_w);
          },
          []() {
            TEST_REQUIRES_ARM_NEON_BF16;
          })),
      [](const testing::TestParamInfo<GemmTest::ParamType>& info) {
        return info.param.test_name;
      });

  INSTANTIATE_TEST_SUITE_P(
      BF16_GEMM_MINMAX_5X4C8__NEONBF16_BFMLAL, GemmTest,
      testing::ValuesIn(CreateTests1(
          /*k_block=*/8,
          /*adj_k_block=*/8,
          /*mr=*/5, /*nr=*/4, /*kr=*/8, /*sr=*/1,
          /*is_igemm=*/false,
          /*unsigned_inputs=*/false,
          [](GemmMicrokernelTester& tester) {
            tester.Test(xnn_bf16_gemm_minmax_ukernel_5x4c8__neonbf16_bfmlal,
                        xnn_init_bf16_minmax_scalar_params,
                        xnn_pack_f16_gemm_goi_w);
          },
          []() {
            TEST_REQUIRES_ARM_NEON_BF16;
          })),
      [](const testing::TestParamInfo<GemmTest::ParamType>& info) {
        return info.param.test_name;
      });
#endif  // XNN_ENABLE_ARM_BF16 && (XNN_ARCH_ARM || XNN_ARCH_ARM64)
