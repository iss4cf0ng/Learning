import requests

url = 'https://www.httpbin.org/html'
r = requests.get(url)
print(r.encoding)
print('-' * 50)
print(r.text)