import pandas as pd

years = range(2020, 2023)
washington = pd.Series([20, 21, 19], index=years)
hongkong = pd.Series([25, 26, 27], index=years)
singapore = pd.Series([30, 29, 31], index=years)
citydf = pd.concat([washington, hongkong, singapore]) # Default axis = 0
print(type(citydf))
print(citydf)
citydf = pd.concat([washington, hongkong, singapore], axis=1)
print(citydf)
cities = ['washington', 'hongkong', 'singapore']
citydf.columns = cities
print(citydf)

washington.name = 'Washington'
hongkong.name = 'Hong Kong'
singapore.name = 'Singapore'
citydf = pd.concat([washington, hongkong, singapore], axis=1)
print(citydf)

data = [{'apple' : 50, 'orange' : 30, 'Grapes' : 80}, {'apple' : 50}, {'Banana' : 20}]
fruits = pd.DataFrame(data)
print(fruits)

cities = {
    'country' : ['American', 'China', 'Japan'],
    'town' : ['Los Angle', 'Beijing', 'Tokyo'],
    'population' : ['1000', '1000', '1000']
}
citydf = pd.DataFrame(cities)
print(citydf)

# Index
row_index = ['first', 'second', 'third']
citydf = pd.DataFrame(cities, index=row_index)
print(citydf)

# Column -> Index
citydf = pd.DataFrame(cities, columns=['town', 'population'], index=cities['country'])
print(citydf)