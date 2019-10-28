g = []
u = []
n = 0

def dfs(v, p, ancestor):
    if v == notV(ancestor):
        return True
    u[v] = True
    retv = False
    for nv in g[v]:
        if not u[nv] and nv != p:
            retv = retv or dfs(nv, v, ancestor)
    return retv

def norm(val):
    if val < 0:
        val = n - val
    val -= 1
    return val

def notV(val):
    if val < n:
        return val + n
    return val - n

w = input().split()
n = int(w[0])
m = int(w[1])
g = [[] for x in range(2*n)]



for i in range(m):
    w = input().split()
    a = norm(int(w[0]))
    b = norm(int(w[1]))
    g[notV(a)].append(b)
    g[notV(b)].append(a)

for i in range(n):
    u = [False for x in range(2*n)]
    a = dfs(i, -1, i)
    u = [False for x in range(2*n)]
    b = dfs(n + i, -1, n + i)
    if a and b:
        print("YES")
        exit(0)
    
print("NO")