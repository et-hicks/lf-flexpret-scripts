#!/bin/bash
# Compile $1.c
set -ex
set -euo pipefail
echo "Compiling $1.c"


ispmfile="ispmfile"
dspmfile="dspmfile"
line="00000000"

# FIXME: not sure why we need to set .text location to 0x8000_0100 instead of 0x8000_0000
# Spike tries to write to 0x7fff_f000 if we set it to 0x8000_0000
riscv64-unknown-elf-gcc -g -static -O0 -march=rv32i -mabi=ilp32 -nostartfiles -Wl,-Ttext=0x80000100 -o $1 start.S $1.c

# SiFive program to prepare an ELF file to a hex dump suitable for verilog's readmem
# needed for FlexPRET simulation
./../../freedom-elf2hex/bin/elf2hex --bit-width 32 --input $1 --output $ispmfile
rm -rf $dspmfile

# Scratchpad instruction and memory must be 4096 lins long, so we must append them to be
# this length
lines=$(wc -l < $ispmfile)

python3 ../scripts/to_sp_size.py $ispmfile $lines
python3 ../scripts/to_sp_size.py $dspmfile 0  # need a data SC file, but IDK what goes inside so its zero for now 

# move to the simulation
cd / && cd flexpret/fpga 

# delete the old sim 
rm -rf obj_dir

# recompile the simulation
verilator -Wall -Wno-lint -cc generated-src/Core.v --exe sim_main.cpp

# Build the exe
cd obj_dir && make -f VCore.mk 

# Copy the file to the simulated location of FlexPRET
cp -f ../../../lf-flexpret-scripts/c_test/$ispmfile $ispmfile
cp -f ../../../lf-flexpret-scripts/c_test/$dspmfile $dspmfile

./VCore
