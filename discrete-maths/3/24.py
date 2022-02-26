import sys

sys.stdin = open('nextperm.in', 'r')
sys.stdout = open('nextperm.out', 'w')

n = int(input())
s = [int(x) for x in input().split(' ')]
sprev = [x for x in s]
snext = [x for x in s]


def next_perm(arr):
    for i in range(n - 2, -1, -1):
        if arr[i] < arr[i + 1]:
            mn = i + 1;
            for j in range(i + 1, n):
                if arr[mn] > arr[j] > arr[i]:
                    mn = j
            t = arr[i]
            arr[i] = arr[mn]
            arr[mn] = t
            for item in arr[:i + 1]:
                print(item, end=' ')

            for item in arr[:i:-1]:
                print(item, end=' ')
            return
    for i in range(n):
        print(0, end=' ')
    return


def prev_perm(arr):
    for i in range(n - 2, -1, -1):
        if arr[i] > arr[i + 1]:
            mx = i + 1
            for j in range(i + 1, n):
                if (arr[j] > arr[mx]) and (arr[j] < arr[i]):
                    mx = j
            t = arr[i]
            arr[i] = arr[mx]
            arr[mx] = t
            for item in arr[:i + 1]:
                print(item, end=' ')

            for item in arr[:i:-1]:
                print(item, end=' ')
            return
    for i in range(n):
        print(0, end=' ')
    return


prev_perm(sprev)
print()
next_perm(snext)

sys.stdout.close()
sys.stdin.close()
