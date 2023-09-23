import hashlib

data = b'sha256'
sha = hashlib.new('sha256', data)
result = sha.hexdigest()
print(result)