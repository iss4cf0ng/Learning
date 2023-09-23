import pandas as pd
import numpy as np

s1 = pd.Series([11, 22, 33, 44, 55])
print(s1)
print('-' * 50)

my_dict = {'USA' : 'washington', 'Japan' : 'Yokyo'}
s2 = pd.Series(my_dict)
print(s2)
print('-' * 50)

s3 = pd.Series(np.arange(0, 7, 2))
print(s3)
print('-' * 50)

my_index = [3, 5, 7]
price = [100, 200, 300]
s4 = pd.Series(price, index=my_index)
print(s4)
print('-' * 50)

fruits = ['Orange', 'Bananan', 'Apple']
price = [30, 20, 50]
s5 = pd.Series(price, index=fruits)
print(s5)
print('-' * 50)

s6 = pd.Series(10, index=[1, 3, 5])
print(s6)
print('-' * 50)

s7 = pd.Series([0, 1, 2, 3, 4, 5])
print(s7[2:5])
print('-' * 50)

x = pd.Series([1, 2])
y = pd.Series([3, 4])
print(x + y)
print('-' * 50)

x = pd.Series([1, 5, 9])
y = pd.Series([2, 4, 10])
print(x > y)