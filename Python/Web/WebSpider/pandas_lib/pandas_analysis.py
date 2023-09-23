import pandas as pd

cities = {
    'Country' : ['China', 'China', 'Thailand', 'Japan', 'Singapore'],
    'Town' : ['Beijing', 'Shanghai', 'Bangkok', 'Tokyo', 'Singapore'],
    'Population' : [2000, 2300, 900, 1600, 600]
}
df = pd.DataFrame(cities, columns=['Town', 'Population'], index=cities['Country'])
print(df)
print('-' * 100)
print(df.at['Japan','Town'])
print('-' * 10)
print(df.at['China', 'Town'])
print('-' * 10)
print(df.iat[2,0])
print('-' * 10)
print(df.loc['Singapore'])
print(df.loc['Japan'])
print('-' * 10)
print(df.loc['China' : 'Thailand', 'Town' : 'Population'])