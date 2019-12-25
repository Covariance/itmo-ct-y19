import sys

sys.stdin = open('num2brackets.in', 'r')
sys.stdout = open('num2brackets.out', 'w')

n, k = map(int, input().split(' '))
build = []

len_bal = [[0 for y in range(n + 2)] for x in range(2 * n + 4)]

len_bal[0][0] = 1

for i in range(1, 2 * n + 4):
    for j in range(n + 2):
        if j > 0:
            len_bal[i][j] += len_bal[i - 1][j - 1]
        if j < n:
            len_bal[i][j] += len_bal[i - 1][j + 1]


def find(cur_pos, cur_num, bal):
    if cur_pos == 2 * n:
        return
    subtract = len_bal[2 * n - (cur_pos + 1)][bal + 1]
    if cur_num < subtract:
        build.append("(")
        find(cur_pos + 1, cur_num, bal + 1)
    else:
        build.append(")")
        find(cur_pos + 1, cur_num - subtract, bal - 1)


find(0, k, 0)

for item in build:
    print(item, end='')

sys.stdout.close()
sys.stdin.close()
