import random

res = []

for n in range(100):
    res.append([random.randint(1,20) for k in range(20)])

print(res)