import sys

sys.stdin = open('permutations.in', 'r')
sys.stdout = open('permutations.out', 'w')

n = int(input())


def gen(cur_len, build, can_use):
    if cur_len == n:
        for i in range(n):
            print(build[i], end=' ')
        print()
    else:
        for i in range(n):
            if can_use[i]:
                can_use[i] = False
                new_build = [x for x in build]
                new_build.append(i + 1)
                gen(cur_len + 1, new_build, can_use)
                can_use[i] = True


gen(0, [], [True] * n)
sys.stdout.close()
sys.stdin.close()
