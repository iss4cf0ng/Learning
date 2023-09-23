import hashlib

md5 = hashlib.md5()
byte = b'md5 test'
md5.update(byte)
result = md5.hexdigest()
print(result)