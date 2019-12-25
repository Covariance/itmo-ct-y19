import sys

sys.stdin = open('vectors.in', 'r')
sys.stdout = open('vectors.out', 'w')

n = int(input())
f = [1, 2]
for i in range(n - 2):
    f.append(f[i] + f[i + 1])

ln = f[n - 2] + f[n - 1]
print(ln)
res = []
for i in range(ln):
    st = ""
    arr = [0] * n
    num = i
    j = n - 1
    while j >= 0:
        if num >= f[j]:
            num -= f[j]
            arr[j] = 1
            j -= 1
        j -= 1
    for ch in arr:
        st += str(ch)
    res.append(st)
res.sort()
for entry in res:
    print(entry)

sys.stdout.close()
sys.stdin.close()
