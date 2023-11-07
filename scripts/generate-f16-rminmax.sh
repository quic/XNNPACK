#!/bin/sh
# Copyright 2023 Google LLC
#
# This source code is licensed under the BSD-style license found in the
# LICENSE file in the root directory of this source tree.

################################### ARM NEONFP16ARITH ##################################
tools/xngen src/f16-rminmax/neonfp16arith.c.in -D BATCH_TILE=8  -D ACCUMULATORS=1 -D OP=MAX -o src/f16-rminmax/gen/f16-rmax-neonfp16arith-u8.c &
tools/xngen src/f16-rminmax/neonfp16arith.c.in -D BATCH_TILE=16 -D ACCUMULATORS=1 -D OP=MAX -o src/f16-rminmax/gen/f16-rmax-neonfp16arith-u16-acc1.c &
tools/xngen src/f16-rminmax/neonfp16arith.c.in -D BATCH_TILE=16 -D ACCUMULATORS=2 -D OP=MAX -o src/f16-rminmax/gen/f16-rmax-neonfp16arith-u16-acc2.c &
tools/xngen src/f16-rminmax/neonfp16arith.c.in -D BATCH_TILE=24 -D ACCUMULATORS=1 -D OP=MAX -o src/f16-rminmax/gen/f16-rmax-neonfp16arith-u24.c &
tools/xngen src/f16-rminmax/neonfp16arith.c.in -D BATCH_TILE=24 -D ACCUMULATORS=2 -D OP=MAX -o src/f16-rminmax/gen/f16-rmax-neonfp16arith-u24-acc2.c &
tools/xngen src/f16-rminmax/neonfp16arith.c.in -D BATCH_TILE=24 -D ACCUMULATORS=3 -D OP=MAX -o src/f16-rminmax/gen/f16-rmax-neonfp16arith-u24-acc3.c &
tools/xngen src/f16-rminmax/neonfp16arith.c.in -D BATCH_TILE=32 -D ACCUMULATORS=1 -D OP=MAX -o src/f16-rminmax/gen/f16-rmax-neonfp16arith-u32.c &
tools/xngen src/f16-rminmax/neonfp16arith.c.in -D BATCH_TILE=32 -D ACCUMULATORS=2 -D OP=MAX -o src/f16-rminmax/gen/f16-rmax-neonfp16arith-u32-acc2.c &
tools/xngen src/f16-rminmax/neonfp16arith.c.in -D BATCH_TILE=32 -D ACCUMULATORS=4 -D OP=MAX -o src/f16-rminmax/gen/f16-rmax-neonfp16arith-u32-acc4.c &
tools/xngen src/f16-rminmax/neonfp16arith.c.in -D BATCH_TILE=64 -D ACCUMULATORS=1 -D OP=MAX -o src/f16-rminmax/gen/f16-rmax-neonfp16arith-u64.c &
tools/xngen src/f16-rminmax/neonfp16arith.c.in -D BATCH_TILE=64 -D ACCUMULATORS=2 -D OP=MAX -o src/f16-rminmax/gen/f16-rmax-neonfp16arith-u64-acc2.c &
tools/xngen src/f16-rminmax/neonfp16arith.c.in -D BATCH_TILE=64 -D ACCUMULATORS=4 -D OP=MAX -o src/f16-rminmax/gen/f16-rmax-neonfp16arith-u64-acc4.c &

tools/xngen src/f16-rminmax/neonfp16arith.c.in -D BATCH_TILE=8  -D ACCUMULATORS=1 -D OP=MIN -o src/f16-rminmax/gen/f16-rmin-neonfp16arith-u8.c &
tools/xngen src/f16-rminmax/neonfp16arith.c.in -D BATCH_TILE=16 -D ACCUMULATORS=1 -D OP=MIN -o src/f16-rminmax/gen/f16-rmin-neonfp16arith-u16-acc1.c &
tools/xngen src/f16-rminmax/neonfp16arith.c.in -D BATCH_TILE=16 -D ACCUMULATORS=2 -D OP=MIN -o src/f16-rminmax/gen/f16-rmin-neonfp16arith-u16-acc2.c &
tools/xngen src/f16-rminmax/neonfp16arith.c.in -D BATCH_TILE=24 -D ACCUMULATORS=1 -D OP=MIN -o src/f16-rminmax/gen/f16-rmin-neonfp16arith-u24.c &
tools/xngen src/f16-rminmax/neonfp16arith.c.in -D BATCH_TILE=24 -D ACCUMULATORS=2 -D OP=MIN -o src/f16-rminmax/gen/f16-rmin-neonfp16arith-u24-acc2.c &
tools/xngen src/f16-rminmax/neonfp16arith.c.in -D BATCH_TILE=24 -D ACCUMULATORS=3 -D OP=MIN -o src/f16-rminmax/gen/f16-rmin-neonfp16arith-u24-acc3.c &
tools/xngen src/f16-rminmax/neonfp16arith.c.in -D BATCH_TILE=32 -D ACCUMULATORS=1 -D OP=MIN -o src/f16-rminmax/gen/f16-rmin-neonfp16arith-u32.c &
tools/xngen src/f16-rminmax/neonfp16arith.c.in -D BATCH_TILE=32 -D ACCUMULATORS=2 -D OP=MIN -o src/f16-rminmax/gen/f16-rmin-neonfp16arith-u32-acc2.c &
tools/xngen src/f16-rminmax/neonfp16arith.c.in -D BATCH_TILE=32 -D ACCUMULATORS=4 -D OP=MIN -o src/f16-rminmax/gen/f16-rmin-neonfp16arith-u32-acc4.c &
tools/xngen src/f16-rminmax/neonfp16arith.c.in -D BATCH_TILE=64 -D ACCUMULATORS=1 -D OP=MIN -o src/f16-rminmax/gen/f16-rmin-neonfp16arith-u64.c &
tools/xngen src/f16-rminmax/neonfp16arith.c.in -D BATCH_TILE=64 -D ACCUMULATORS=2 -D OP=MIN -o src/f16-rminmax/gen/f16-rmin-neonfp16arith-u64-acc2.c &
tools/xngen src/f16-rminmax/neonfp16arith.c.in -D BATCH_TILE=64 -D ACCUMULATORS=4 -D OP=MIN -o src/f16-rminmax/gen/f16-rmin-neonfp16arith-u64-acc4.c &

tools/xngen src/f16-rminmax/neonfp16arith.c.in -D BATCH_TILE=8  -D ACCUMULATORS=1 -D OP=MINMAX -o src/f16-rminmax/gen/f16-rminmax-neonfp16arith-u8.c &
tools/xngen src/f16-rminmax/neonfp16arith.c.in -D BATCH_TILE=16 -D ACCUMULATORS=1 -D OP=MINMAX -o src/f16-rminmax/gen/f16-rminmax-neonfp16arith-u16-acc1.c &
tools/xngen src/f16-rminmax/neonfp16arith.c.in -D BATCH_TILE=16 -D ACCUMULATORS=2 -D OP=MINMAX -o src/f16-rminmax/gen/f16-rminmax-neonfp16arith-u16-acc2.c &
tools/xngen src/f16-rminmax/neonfp16arith.c.in -D BATCH_TILE=24 -D ACCUMULATORS=1 -D OP=MINMAX -o src/f16-rminmax/gen/f16-rminmax-neonfp16arith-u24.c &
tools/xngen src/f16-rminmax/neonfp16arith.c.in -D BATCH_TILE=24 -D ACCUMULATORS=2 -D OP=MINMAX -o src/f16-rminmax/gen/f16-rminmax-neonfp16arith-u24-acc2.c &
tools/xngen src/f16-rminmax/neonfp16arith.c.in -D BATCH_TILE=24 -D ACCUMULATORS=3 -D OP=MINMAX -o src/f16-rminmax/gen/f16-rminmax-neonfp16arith-u24-acc3.c &
tools/xngen src/f16-rminmax/neonfp16arith.c.in -D BATCH_TILE=32 -D ACCUMULATORS=1 -D OP=MINMAX -o src/f16-rminmax/gen/f16-rminmax-neonfp16arith-u32.c &
tools/xngen src/f16-rminmax/neonfp16arith.c.in -D BATCH_TILE=32 -D ACCUMULATORS=2 -D OP=MINMAX -o src/f16-rminmax/gen/f16-rminmax-neonfp16arith-u32-acc2.c &
tools/xngen src/f16-rminmax/neonfp16arith.c.in -D BATCH_TILE=32 -D ACCUMULATORS=4 -D OP=MINMAX -o src/f16-rminmax/gen/f16-rminmax-neonfp16arith-u32-acc4.c &
tools/xngen src/f16-rminmax/neonfp16arith.c.in -D BATCH_TILE=64 -D ACCUMULATORS=1 -D OP=MINMAX -o src/f16-rminmax/gen/f16-rminmax-neonfp16arith-u64.c &
tools/xngen src/f16-rminmax/neonfp16arith.c.in -D BATCH_TILE=64 -D ACCUMULATORS=2 -D OP=MINMAX -o src/f16-rminmax/gen/f16-rminmax-neonfp16arith-u64-acc2.c &
tools/xngen src/f16-rminmax/neonfp16arith.c.in -D BATCH_TILE=64 -D ACCUMULATORS=4 -D OP=MINMAX -o src/f16-rminmax/gen/f16-rminmax-neonfp16arith-u64-acc4.c &
