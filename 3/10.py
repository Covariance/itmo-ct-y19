import sys

sys.stdin = open('partition.in', 'r')
sys.stdout = open('partition.out', 'w')

n = int(input())


def gen(curn, last_part, build):
    if curn == 0:
        print(build[0], end='')
        for i in range(1, len(build)):
            print("+", end='')
            print(build[i], end='')
        print()
    else:
        for i in range(last_part, curn + 1):
            nb = [x for x in build]
            nb.append(i)
            gen(curn - i, i, nb)


gen(n, 1, [])
sys.stdout.close()
sys.stdin.close()