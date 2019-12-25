import sys

sys.stdin = open('num2part.in', 'r')
sys.stdout = open('num2part.out', 'w')

n, k = map(int, input().split(' '))
build = []

cnt = [[0 for x in range(n + 1)] for y in range(n + 1)]

for mn in range(n, 0, -1):
    for sm in range(n + 1):
        if sm == 0:
            cnt[mn][sm] = 1
        elif mn > sm:
            cnt[mn][sm] = 0
        elif mn == sm:
            cnt[mn][sm] = 1
        else:
            cnt[mn][sm] = cnt[mn + 1][sm] + cnt[mn][sm - mn]


def find(last_add, left_sum, cur_num):
    if left_sum == 0:
        return
    for i in range(last_add, n + 1):
        if cur_num > cnt[i][left_sum - i]:
            cur_num -= cnt[i][left_sum - i]
        else:
            build.append(i)
            find(i, left_sum - i, cur_num)
            return


find(1, n, k + 1)

print(build[0], end='')
for item in build[1:]:
    print('+' + str(item), end='')

sys.stdout.close()
sys.stdin.close()
