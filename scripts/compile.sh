#!/bin/bash
# Compile $1.c
set -ex
set -euo pipefail
echo "Compiling $1.c"

# FIXME: not sure why we need to set .text location to 0x8000_0100 instead of 0x8000_0000
# Spike tries to write to 0x7fff_f000 if we set it to 0x8000_0000
riscv64-unknown-elf-gcc -g -static -O0 -march=rv32i -mabi=ilp32 -nostartfiles -Wl,-Ttext=0x80000100 -o $1 start.S $1.c

# SiFive program to prepare an ELF file to a hex dump suitable for verilog's readmem
# needed for FlexPRET simulation
./../../freedom-elf2hex/bin/elf2hex --bit-width 32 --input $1 --output ispmfile

# Copy the file to the simulated location of FlexPRET
cp -f ispmfile ../../flexpret/fpga/obj_dir/ispmfile

# Run the simulation
# cd / && cd flexpret/fpga/obj_dir && ./VCore
