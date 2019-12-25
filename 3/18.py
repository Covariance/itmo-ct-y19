import sys

sys.stdin = open('brackets2num.in', 'r')
sys.stdout = open('brackets2num.out', 'w')

build = input()

n = len(build) // 2

len_bal = [[0 for y in range(n + 2)] for x in range(2 * n + 4)]

len_bal[0][0] = 1

for i in range(1, 2 * n + 4):
    for j in range(n + 2):
        if j > 0:
            len_bal[i][j] += len_bal[i - 1][j - 1]
        if j < n:
            len_bal[i][j] += len_bal[i - 1][j + 1]


def find(cur_pos, bal):
    cur_num = 0
    if cur_pos == 2 * n:
        return 0
    subtract = len_bal[2 * n - (cur_pos + 1)][bal + 1]
    if build[cur_pos] == '(':
        return find(cur_pos + 1, bal + 1)
    else:
        return subtract + find(cur_pos + 1, bal - 1)


print(find(0, 0))

sys.stdout.close()
sys.stdin.close()
