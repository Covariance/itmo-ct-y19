import sys

sys.stdin = open('perm2num.in', 'r')
sys.stdout = open('perm2num.out', 'w')

n = int(input())
build = [int(x) - 1 for x in input().split()]

fct = [1]
for i in range(n):
    fct.append(fct[-1] * (i + 1))

used = [False for x in range(n)]


def find(cur_item):
    if cur_item == n:
        return 0
    cnt = 0
    for i in range(build[cur_item]):
        if not used[i]:
            cnt += 1
    used[build[cur_item]] = True
    return cnt * fct[n - cur_item - 1] + find(cur_item + 1)


print(find(0))

sys.stdout.close()
sys.stdin.close()
