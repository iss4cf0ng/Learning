def foo(num):
    print('starting...')
    while num < 10000:
        num = num + 1
        yield num

for n in foo(0):
    print(n)