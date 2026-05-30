#!/bin/bash
set -e
DIR="$(cd "$(dirname "$0")" && pwd)"
cd "$DIR"

# Compile payload.c -> payload.dll
echo "[*] Compiling payload.dll..."
i686-w64-mingw32-gcc -shared -o payload.dll payload.c -Wl,--out-implib,payload.lib -static-libgcc
echo "OK: $(wc -c < payload.dll) bytes"

# Assemble stage1_dll.asm -> stage1_dll.bin
echo "[*] Assembling stage1_dll.asm..."
nasm -f bin stage1_dll.asm -o stage1_dll.bin
echo "    OK: $(wc -c < stage1_dll.bin) bytes"

# Verify string offsets are correct
echo "[*] Verifying string table..."
python3 -c "
data = open('stage1_dll.bin','rb').read()
s = data[5:]  # skip 5-byte call instruction
checks = [
    (0,  b'LoadLibraryA\x00'),
    (13, b'GetProcAddress\x00'),
    (28, b'payload.dll\x00'),
    (40, b'payload_run\x00'),
]
ok = True
for off, expected in checks:
    actual = s[off:off+len(expected)]
    status = 'OK' if actual == expected else 'FAIL'
    if status == 'FAIL': ok = False
    print(f'    EBP+{off:2d}: {status}  {actual}')
if not ok:
    print('ERROR: string offsets are wrong — fix the ASM')
    exit(1)
"

# Generate shellcode.h from the fresh .bin
echo "[*] Generating shellcode.h..."
python3 -c "
data = open('stage1_dll.bin','rb').read()
parts = ['0x{:02x}'.format(b) for b in data]
lines = [', '.join(parts[i:i+12]) for i in range(0, len(parts), 12)]
body  = ',\n'.join('  ' + l for l in lines)
print('unsigned char shellcode[] = {\n' + body + '\n};')
" > shellcode.h
echo "OK: shellcode.h written"

# Compile loader.cpp
echo "[*] Compiling loader.exe..."
i686-w64-mingw32-g++ -o loader.exe loader.cpp -static
echo "OK: $(wc -c < loader.exe) bytes"

echo ""
echo "[+] Build complete."
echo "[+] Copy loader.exe + payload.dll to the same folder on your VM"
echo "[+] then run loader.exe"