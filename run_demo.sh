#!/usr/bin/env bash
# same as setup_hemeLB.sh but for running the demo
# source setup_hemeLB.sh

cd "$(dirname "$0")"

mkdir -p build && cd build
cmake ../src
make -j 36

srun -n 2 ./demo_write

cd ..
python check.py
