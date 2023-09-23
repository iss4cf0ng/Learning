from Crypto.Protocol.KDF import PBKDF2
from Crypto.Hash import SHA256

result = PBKDF2('password', 'salt', 64, 100000, hmac_hash_module=SHA256)
print(result)
print(result.hex())