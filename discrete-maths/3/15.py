import sys

sys.stdin = open('num2choose.in', 'r')
sys.stdout = open('num2choose.out', 'w')

n, k, m = map(int, input().split(' '))
build = []

used = [False for x in range(n)]

cnk = [[0 for j in range(n + 1)] for i in range(n + 1)]

for i in range(n + 1):
    cnk[0][i] = 0
    cnk[i][0] = 1

for i in range(1, n + 1):
    for j in range(1, n + 1):
        cnk[i][j] = cnk[i - 1][j] + cnk[i - 1][j - 1]


def find(last_digit, left_item, cur_count):
    if left_item == 0:
        return
    for i in range(last_digit + 1, n):
        if cur_count >= cnk[n - i - 1][left_item - 1]:
            cur_count -= cnk[n - i - 1][left_item - 1]
        else:
            build.append(i + 1)
            find(i, left_item - 1, cur_count)
            return


find(-1, k, m)
for item in build:
    print(item, end=' ')

sys.stdout.close()
sys.stdin.close()
