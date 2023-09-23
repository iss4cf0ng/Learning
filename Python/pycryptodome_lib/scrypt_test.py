import hashlib
from Crypto.Protocol.KDF import scrypt

HMAC = hashlib.scrypt(b'password', salt=b'salt', n=2**14, r=8, p=1)
result = HMAC.hex()
print(result)
result = scrypt('password', 'salt', 64, N=2**14, r=8, p=1)
print(result.hex())