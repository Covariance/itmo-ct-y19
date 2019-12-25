import sys

sys.stdin = open('num2perm.in', 'r')
sys.stdout = open('num2perm.out', 'w')

n, k = map(int, input().split(' '))
build = []

fct = [1]
for i in range(n):
    fct.append(fct[-1] * (i + 1))

used = [False for x in range(n)]


def find3(cur_item, left):
    if cur_item > n:
        return
    skip = left // fct[n - cur_item]
    left %= fct[n - cur_item]
    for i in range(n):
        if not used[i]:
            if skip == 0:
                build.append(i + 1)
                used[i] = True
                find3(cur_item + 1, left)
            skip -= 1
    return


find3(1, k)

for item in build:
    print(item, end=' ')

sys.stdout.close()
sys.stdin.close()
