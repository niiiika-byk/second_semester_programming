import requests

response = requests.get('http://google.com')
print('Response code: ', response.status_code)