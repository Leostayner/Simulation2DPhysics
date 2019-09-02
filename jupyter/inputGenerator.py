import random

n = 100
tmp = ""
b = 10

tmp += "4000 4000 0.01\n"
tmp += str(n) + "\n"

for i in range(n):
    tmp += str(random.randrange(2, 10)) + " " 
    tmp += str(random.randrange(2, 8)) + " " 
    tmp += str(random.randrange(2, 8)) + " "
    tmp += str(b + random.randrange(-2, 4)) + " "
    tmp += str(b + random.randrange(-2, 4)) + " "
    tmp += str(random.randrange(-100, 100)) + " "
    tmp += str(random.randrange(-100, 100)) + "\n"
    b += 40

tmp += "0.01 100 10000"
f = open("input4.txt", "a")
f.write(tmp)