#!/bin/bash

SRC_DIR="."

# Compile all .c files into .o and extract .text -> .bin
find "$SRC_DIR" -type f -name "*.c" | while read -r file; do
    dir=$(dirname "$file")
    filename=$(basename -- "$file")
    name="${filename%.c}"

    i686-w64-mingw32-gcc -shared -o "$dir/$name.dll" "$dir/$name.c" -Wl,--out-implib,"$dir/$name.lib" -static-libgcc
done

# Compile all .cpp files
find "$SRC_DIR" -type f -name "*.cpp" | while read -r file; do
    dir=$(dirname "$file")
    filename=$(basename -- "$file")
    name="${filename%.cpp}"

    echo "Compiling C++: $file -> $dir/$name.exe"

    i686-w64-mingw32-g++ -o "$dir/$name.exe" "$file" -lsetupapi -static
done

# Compile all .asm files
find "$SRC_DIR" -type f -name "*.asm" | while read -r file; do
    dir=$(dirname "$file")
    filename=$(basename -- "$file")
    name="${filename%.asm}"

    echo "Compiling ASM: $file -> $dir/$name.bin"

    nasm -f bin "$file" -o "$dir/$name.bin"
done