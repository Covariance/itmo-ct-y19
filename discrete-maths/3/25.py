import sys

sys.stdin = open('nextchoose.in', 'r')
sys.stdout = open('nextchoose.out', 'w')

n, k = map(int, input().split(' '))
s = [int(x) for x in input().split(' ')]


def next_choose():
    s.append(n + 1)
    for i in range(k - 1, -1, -1):
        if s[i + 1] - s[i] >= 2:
            s[i] += 1
            for item in s[:i]:
                print(item, end=' ')
            print(s[i], end=' ')
            for j in range(i + 1, k):
                s[j] = s[i] + 1
                print(s[j], end=' ')
            return
    print(-1)
    return


def next_choose_2():
    s2 = [x for x in s]
    s2.append(n + 1)
    suf = k - 1
    while s2[suf + 1] - s2[suf] < 2 and suf >= 0:
        suf -= 1
    if suf != -1:
        s2[suf] += 1
        for i in range(suf + 1, k):
            s2[i] = s2[i - 1] + 1
        for i in range(k):
            print(s2[i], end=' ')
    else:
        print(-1)


next_choose_2()

sys.stdout.close()
sys.stdin.close()
