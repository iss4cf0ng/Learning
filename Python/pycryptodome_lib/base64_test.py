import base64

data = b'ManA'
encode = base64.b64encode(data)
decode = base64.b64decode(encode)

print(encode)
print(decode)