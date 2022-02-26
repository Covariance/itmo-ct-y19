import sys

sys.stdin = open('part2num.in', 'r')
sys.stdout = open('part2num.out', 'w')

build = [int(x) for x in input().split('+')]
sm = 0
for item in build:
    sm += item
n = sm
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


def find(cur_item, last_add, left_sum):
    cur_num = 0
    if left_sum == 0:
        return 0
    for i in range(last_add, n + 1):
        if i != build[cur_item]:
            cur_num += cnt[i][left_sum - i]
        else:
            return cur_num + find(cur_item + 1, i, left_sum - i)


print(find(0, 1, sm))

sys.stdout.close()
sys.stdin.close()
