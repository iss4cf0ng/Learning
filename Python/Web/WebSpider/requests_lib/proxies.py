import requests

proxies = {
    'http' : 'http://111.231.81.109:3128',
    'https' : 'https://111.231.81.109:1080',
}

r = requests.get('https://docs.python.org', proxies=proxies)