import json

json_obj = '{"b":80,"a":25,"c":60}'
dict_obj = json.loads(json_obj)
print(dict_obj)
print(type(dict_obj))