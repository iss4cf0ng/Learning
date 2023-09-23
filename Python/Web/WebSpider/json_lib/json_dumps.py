import json

list_nums = [5, 10, 20, 1]
tuple_nums = (1, 5, 10, 9)
json_data1 = json.dumps(list_nums)
json_data2 = json.dumps(tuple_nums)
print(json_data1)
print(json_data1)
print(type(json_data1))
print('------')

players = {
    'Stephen Curry' : 'Golden State Warriors',
    'Kevin Durant' : 'Golden State Warriors',
}
json_obj1 = json.dumps(players)
json_obj2 = json.dumps(players, sort_keys=True)
print(json_obj1)
print(json_obj2)
print(json_obj1 == json_obj2)
print('------')

json_obj1 = json.dumps(players, sort_keys=True, indent=4)
print(json_obj1)