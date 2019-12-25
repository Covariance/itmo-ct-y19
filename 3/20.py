import sys

sys.stdin = open('brackets2num2.in', 'r')
sys.stdout = open('brackets2num2.out', 'w')

build = [br for br in input()]
n = len(build) // 2

len_bal = [[0 for x in range(n + 1)] for y in range(2 * n + 1)]
len_bal[0][0] = 1
for i in range(2 * n):
    for j in range(n + 1):
        if j < n:
            len_bal[i + 1][j + 1] = len_bal[i + 1][j + 1] + len_bal[i][j]
        if j > 0:
            len_bal[i + 1][j - 1] = len_bal[i + 1][j - 1] + len_bal[i][j]

stack = []


def find(bal, cur_pos):
    if cur_pos == 2 * n - 1:
        return 0
    ret_val = 0
    if bal < n:
        cur = len_bal[2 * n - cur_pos - 1][bal + 1] * (2 ** ((2 * n - cur_pos - 1 - bal) // 2))
    else:
        cur = 0
    if build[cur_pos] == '(':
        stack.append('(')
        return ret_val + find(bal + 1, cur_pos + 1)
    ret_val += cur
    if len(stack) > 0 and stack[-1] == '(' and bal - 1 >= 0:
        cur = len_bal[2 * n - cur_pos - 1][bal - 1] * (2 ** ((2 * n - cur_pos + 1 - bal) // 2))
    else:
        cur = 0
    if build[cur_pos] == ')':
        stack.pop(-1)
        return ret_val + find(bal - 1, cur_pos + 1)
    ret_val += cur
    if bal + 1 <= n:
        cur = len_bal[2 * n - cur_pos - 1][bal + 1] * (2 ** ((2 * n - cur_pos - 1 - bal) // 2))
    else:
        cur = 0
    if build[cur_pos] == '[':
        stack.append('[')
        return ret_val + find(bal + 1, cur_pos + 1)
    ret_val += cur
    stack.pop(-1)
    return ret_val + find(bal - 1, cur_pos + 1)


print(round(find(0, 0)))

sys.stdout.close()
sys.stdin.close()
