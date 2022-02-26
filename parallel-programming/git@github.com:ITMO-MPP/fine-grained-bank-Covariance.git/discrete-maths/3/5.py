import sys

sys.stdin = open('telemetry.in', 'r')
sys.stdout = open('telemetry.out', 'w')

n, k = map(int, input().split())

for i in range(k ** n):
    for j in range(n, 0, -1):
        l = i // k ** j
        if l % 2 == 0:
            print(i // k ** (j - 1) % k, end='')
        else:
            print(k - (i // k ** (j - 1)) % k - 1, end='')
    print()

sys.stdout.close()
sys.stdin.close()
