s = ""
n = 5
while n>0:
    n-=1
    if (n%2) == 0:
        continue
    a = ['foo', 'bar', 'baz' ]
    for x in a:
        s += str(n) + x
        if len(a) <2:
            break
print(s)