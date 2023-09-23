import requests

url = 'https://iss4cf0ng.github.io'
response = requests.get(url)
if response.status_code == requests.codes.ok:
    print("OK!")
    print(response.url)
    print('-------')
    print(response.headers)
    print('-------')
    print(response.cookies)
    print('-------')
    print(response.content)
else:
    print("Failed!")