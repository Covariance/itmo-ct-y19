import sys

sys.stdin = open('gray.in', 'r')
sys.stdout = open('gray.out', 'w')

n = int(input())

for i in range(2 ** n):
    for j in range(n, 0, -1):
        print(((i + 2 ** (j - 1)) // (2 ** j)) % 2, end='')
    print()

sys.stdout.close()
sys.stdin.close()
