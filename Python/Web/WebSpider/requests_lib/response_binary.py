import requests

url = 'http://httpbin.org/image/jpeg'
r = requests.get(url)
img = r.content

fn = 'output.jpg'
with open(fn, 'wb') as fout:
    fout.write(img)