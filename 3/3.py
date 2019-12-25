import sys

sys.stdin = open('antigray.in', 'r')
sys.stdout = open('antigray.out', 'w')

n = int(input())

arr = [0] * n
arr[0] = -1

for i in range(3 ** (n - 1)):
    cnt = 0
    while arr[cnt] == 2:
        arr[cnt] = 0
        cnt += 1
    arr[cnt] += 1
    for j in range(n - 1, - 1, -1):
        print(arr[j], end='')
    print()
    for j in range(n - 1, - 1, -1):
        print((arr[j] + 1) % 3, end='')
    print()
    for j in range(n - 1, - 1, -1):
        print((arr[j] + 2) % 3, end='')
    print()

sys.stdout.close()
sys.stdin.close()
