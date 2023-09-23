import requests
import json

url_get = 'https://www.httpbin.org/get'
url_post = 'https://www.httpbin.org/post'
form_data = {
    'gender' : 'M',
    'page' : '1'
}

r_get = requests.get(url_get, params=form_data)
print(r_get.url)
print('-' * 50)
r_post = requests.post(url_post, data=json.dumps(form_data))
print(r_post.url)
print('-' * 20)
print(r_post.text)