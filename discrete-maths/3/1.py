import sys

sys.stdin = open('allvectors.in', 'r')
sys.stdout = open('allvectors.out', 'w')

n = int(input())

arr = [0] * n

for symb in arr:
    print(symb, end='')
print()

for i in range(2 ** n - 1):
    cnt = 0
    while (arr[n - cnt - 1] == 1):
        arr[n - cnt - 1] = 0
        cnt += 1
    arr[n - cnt - 1] = 1
    for symb in arr:
        print(symb, end='')
    print()

sys.stdout.close()
sys.stdin.close()
