import sys

sys.stdin = open('nextbrackets.in', 'r')
sys.stdout = open('nextbrackets.out', 'w')

s = [(1 if x == '(' else -1) for x in input()]
bal = [0 for x in s]
for i in range(1, len(s)):
    bal[i] = bal[i - 1] + s[i - 1]


def choose():
    is_last = True
    for item in bal:
        if not item == 0 and not item == 1:
            is_last = False
            break
    if is_last:
        print("-")
    else:
        gen_next()


def print_seq(arr):
    for br in arr:
        if br == 1:
            print(end='(')
        else:
            print(end=')')


def gen_next():
    for i in range(len(s) - 1, -1, -1):
        if s[i] == 1 and not bal[i] == 0:
            print_seq(s[:i])
            print(end=')')
            bl = bal[i] - 1
            cnt = (len(s) - i - 1 - bl) // 2
            for j in range(cnt):
                print(end='(')
            for j in range(cnt + bl):
                print(end=')')
            return


choose()

sys.stdout.close()
sys.stdin.close()
