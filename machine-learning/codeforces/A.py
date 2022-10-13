n, m, k = map(int, input().split())

indexed = sorted(enumerate(map(int, input().split())), key=lambda e: e[1])

groups = [[] for _ in range(k)]

for i in range(n):
    groups[i % k].append(indexed[i][0] + 1)

for group in groups:
    print(len(group), *group)
