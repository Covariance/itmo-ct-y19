import sys

sys.stdin = open('choose2num.in', 'r')
sys.stdout = open('choose2num.out', 'w')

n, k = map(int, input().split(' '))
build = [int(x) - 1 for x in input().split()]

cnk = [[0 for j in range(n + 1)] for i in range(n + 1)]

for i in range(n + 1):
    cnk[0][i] = 0
    cnk[i][0] = 1

for i in range(1, n + 1):
    for j in range(1, n + 1):
        cnk[i][j] = cnk[i - 1][j] + cnk[i - 1][j - 1]


def find(last_digit, left_item, cur_item):
    cur_num = 0
    if left_item == 0:
        return 0
    for i in range(last_digit + 1, n):
        if build[cur_item] != i:
            cur_num += cnk[n - i - 1][left_item - 1]
        else:
            build.append(i + 1)
            cur_num += find(i, left_item - 1, cur_item + 1)
            return cur_num


print(find(-1, k, 0))

sys.stdout.close()
sys.stdin.close()
