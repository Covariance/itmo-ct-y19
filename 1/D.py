def toBin(a):
    cnt = 0
    retv = []
    while (cnt < 33):
        retv.append(a % 2);
        a //= 2
        cnt += 1
    return retv

n = int(input())
values = [toBin(int(x)) for x in input().split(' ')]
param = [[values[y][x] for y in range(n)] for x in range(33)]
s = toBin(int(input()))

for i in range(33):
    for j in range(33):
        if (param[i] == param[j] and s[i] != s[j]):
            print("Impossible")
            exit(0)

ans = []    
for i in range(33):
    if s[i] == 1:
        st = chr(40)
        for j in range(n):
            if j != 0:
                st += chr(38)
            if param[i][j] == 0:
                st += chr(126)
            st += str(j + 1)
        st += chr(41)
        ans.append(st)

if len(ans) == 0:
    sans = "1&(~1)";
    print(sans)
    exit(0)

for i in range(len(ans)):
    if not i == 0:
        print(chr(124), end = "")
    print(ans[i], end = "")