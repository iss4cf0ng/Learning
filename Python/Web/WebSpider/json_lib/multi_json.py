import json

obj = '{"Asian":[{"Japan":"Tokyo"},{"USA":"LA"}]}'
json_obj = json.loads(obj)
print(json_obj)
print(json_obj["Asian"])
print(json_obj["Asian"][0])
print(json_obj["Asian"][0]["Japan"])

obj = '{"Asian":\
    [{"Japan":"Tokyo"},\
        {"USA":"LA"}]\
            }'
print(json_obj)
print(json_obj["Asian"])
print(json_obj["Asian"][0])
print(json_obj["Asian"][0]["Japan"])