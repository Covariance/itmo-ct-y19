import sys

sys.stdin = open('nextmultiperm.in', 'r')
sys.stdout = open('nextmultiperm.out', 'w')

n = int(input())
s = [int(x) for x in input().split(' ')]


def is_last():
    if len(s) == 1:
        return True
    for i in range(1, len(s)):
        if s[i] > s[i - 1]:
            return False
    return True


def choose():
    if is_last():
        for i in range(len(s)):
            print(0, end=' ')
        return
    gen_next2()


def gen_next2():
    for i in range(n - 2, -1, -1):
        if s[i] < s[i + 1]:
            j = i + 1
            while j < n - 1 and s[j + 1] > s[i]:
                j += 1
            t = s[i]
            s[i] = s[j]
            s[j] = t
            for item in s[:i + 1]:
                print(item, end=' ')
            for item in s[n - 1:i:-1]:
                print(item, end=' ')
            return


choose()

sys.stdout.close()
sys.stdin.close()
