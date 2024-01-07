rem ported from Scott's bash script
rem
rem TODO -> move into a makefile
rem

set F256=%~dp0\..\..
set LLVM=%F256%\llvm-mos
set SETTINGS=%LLVM%\mos-platform\f256k\lib\settings.ld
set PATH=%LLVM%\bin;%PATH%

set START=0x2000
echo __f256_start = %START%; > %SETTINGS%

call mos-f256k-clang -fno-builtin-memset -I%F256%\include -I%F256%\f256lib -o pgztest -Os pgztest.c %F256%\f256lib\f256.c

move /y pgztest pgztest.bin

%F256%\header\header pgz 24 pgztest.pgz %START% pgztest.bin %START%

llvm-objdump -d --print-imm-hex pgztest.elf > pgztest.lst
rem hexdump -C pgztest.pgz > pgztest.hex

