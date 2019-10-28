
n, k = map(int, input().split())
d = [0] * k
for i in range(k):
    d[i] = list(map(int, input().split()))

val = [-1 for x in range(n)]

def isLone(disjunct):
    isMet = False
    for item in disjunct:
        if not item == -1:
            if isMet:
                return False
            isMet = True
    return isMet

def isEmpty(disjunct):
    for i in range(n):
        if disjunct[i] != -1:
            return False
    return True

def update(ind):
    if isEmpty(d[ind]):
        return True
    retv = False
    for i in range(n):
        if val[i] == d[ind][i] and val[i] != -1:
            retv = True
            for j in range(n):
                d[ind][j] = -1
            break
        if val[i] == -1 and d[ind][i] != -1:
            retv = True
        if val[i] == 1 - d[ind][i]:
            d[ind][i] = -1
    return retv

while True:
    foundLone = False
    for i in range(k):
        if isLone(d[i]):
            foundLone = True
            for j in range(n):
                if d[i][j] == 1:
                    val[j] = 1
                    break
                if d[i][j] == 0:
                    val[j] = 0
                    break
            break
    
    for i in range(k):
        if not update(i):
            print("YES")
            exit(0)
    
    if not foundLone:
        print("NO")
        exit(0)