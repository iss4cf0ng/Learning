import requests, json

headers = {
    'User-Agent' : 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) \
        AppleWebKit/537.36 (KHTML, like Gecko) \
            Chrome/116.0.0.0 Safari/537.36',
}
url = 'https://www.httpbin.org/post'
form_data = {
    'gender' : 'M',
    'page' : '1'
}
r = requests.post(url, json=form_data, headers=headers)
print(r.url)
print('-' * 50)
print(r.request.headers)
print('-' * 50)
print(r.headers)