import sys

sys.stdin = open('brackets.in', 'r')
sys.stdout = open('brackets.out', 'w')

n = int(input())


def gen(cop, ccl, build):
    if cop + ccl == 2 * n:
        for i in range(2 * n):
            print(build[i], end='')
        print()
    else:
        if cop < n:
            nb = [x for x in build]
            nb.append('(')
            gen(cop + 1, ccl, nb)
        if cop > ccl:
            nb = [x for x in build]
            nb.append(')')
            gen(cop, ccl + 1, nb)


gen(0, 0, [])
sys.stdout.close()
sys.stdin.close()
