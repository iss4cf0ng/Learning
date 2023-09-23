import requests, bs4

response = requests.get('https://iss4cf0ng.github.io')
obj_soup = bs4.BeautifulSoup(response.text, 'lxml')
print(type(obj_soup))