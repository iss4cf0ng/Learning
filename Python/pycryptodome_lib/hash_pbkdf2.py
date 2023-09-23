import hashlib

HMAC = hashlib.pbkdf2_hmac('sha256', b'password', b'salt', 10000)
result = HMAC.hex()
print(result)