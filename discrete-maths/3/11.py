import sys

sys.stdin = open('subsets.in', 'r')
sys.stdout = open('subsets.out', 'w')

n = int(input())


def gen(last_looked, build):
    if last_looked == n - 1:
        for i in range(len(build)):
            print(build[i], end=' ')
        print()
    else:
        gen(n - 1, build)
        for i in range(last_looked + 1, n):
            nb = [x for x in build]
            nb.append(i + 1)
            gen(i, nb)


gen(-1, [])
sys.stdout.close()
sys.stdin.close()
