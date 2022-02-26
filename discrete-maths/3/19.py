import sys

sys.stdin = open('num2brackets2.in', 'r')
sys.stdout = open('num2brackets2.out', 'w')

n, k = map(int, input().split(' '))

len_bal = [[0 for x in range(n + 1)] for y in range(2 * n + 1)]
len_bal[0][0] = 1
for i in range(2 * n):
    for j in range(n + 1):
        if j < n:
            len_bal[i + 1][j + 1] = len_bal[i + 1][j + 1] + len_bal[i][j]
        if j > 0:
            len_bal[i + 1][j - 1] = len_bal[i + 1][j - 1] + len_bal[i][j]

build = []
stack = []


def find2(bal, cur_num, cur_pos):
    if cur_pos == -1:
        return
    cur = 0
    if bal + 1 <= n:
        cur = len_bal[cur_pos][bal + 1] * (2 ** ((cur_pos - bal - 1) / 2))
    else:
        cur = 0
    if cur >= cur_num:
        build.append('(')
        stack.append('(')
        find2(bal + 1, cur_num, cur_pos - 1)
        return
    cur_num -= cur
    if len(stack) > 0 and stack[-1] == '(' and bal - 1 >= 0:
        cur = len_bal[cur_pos][bal - 1] * (2 ** ((cur_pos - bal + 1) / 2))
    else:
        cur = 0
    if cur >= cur_num:
        build.append(')')
        stack.pop(-1)
        find2(bal - 1, cur_num, cur_pos - 1)
        return
    cur_num -= cur
    if bal + 1 <= n:
        cur = len_bal[cur_pos][bal + 1] * (2 ** ((cur_pos - bal - 1) / 2))
    else:
        cur = 0
    if cur >= cur_num:
        build.append('[')
        stack.append('[')
        find2(bal + 1, cur_num, cur_pos - 1)
        return
    cur_num -= cur
    build.append(']')
    stack.pop(-1)
    find2(bal - 1, cur_num, cur_pos - 1)
    return


find2(0, k + 1, 2 * n - 1)

for item in build:
    print(item, end='')

sys.stdout.close()
sys.stdin.close()
