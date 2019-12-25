import sys

sys.stdin = open('choose.in', 'r')
sys.stdout = open('choose.out', 'w')

n, k = map(int, input().split())


def gen(cur_len, build, last_digit):
    if cur_len == k:
        for i in range(k):
            print(build[i], end=' ')
        print()
    else:
        for i in range(last_digit + 1, n):
            nb = [x for x in build]
            nb.append(i + 1)
            gen(cur_len + 1, nb, i)


gen(0, [], -1)
sys.stdout.close()
sys.stdin.close()
