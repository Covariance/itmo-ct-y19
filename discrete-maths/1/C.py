def toBin(a, ln):
    cnt = 0
    retv = []
    while (cnt < ln):
        retv.append(a % 2);
        a //= 2
        cnt += 1
    retv.reverse()
    return ''.join(map(str, retv))

def checkLinear(val, n):
    polynom = []
    
    def checkConjunct(values, conjunct):
        a = list(values)
        b = list(conjunct)
        for i in range(len(a)):
            if b[i] == '1' and a[i] == '0':
                return 0
        return 1
    
    def checkZhigalkin(values):
        sum = 0
        for conjunct in polynom:
            if conjunct[1] == '1':
                sum += checkConjunct(values, conjunct[0])
        if sum % 2 == 0:
            return 0
        return 1
    
    def isLoneConjunct(values):
        isMet = False
        for sym in values:
            if sym == '1':
                if isMet:
                    return False
                isMet = True
        return True
    
    for i in range(2 ** n):
        s = toBin(i, n)
        if not checkZhigalkin(s) == val[i]:
            if not isLoneConjunct(s):
                return False
            polynom.append([s, '1'])
        else:
            polynom.append([s, '0'])
            
    return True

def checkSelfDuality(val, n):
    if n == 0:
        return False
    for i in range(2 ** (n - 1)):
        if val[i] == val[2 ** n - i - 1]:
            return False
    return True

def checkMonotonous(val, n):
    def isMaj(v1, v2):
        for i in range(n):
            if v1[i] < v2[i]:
                return False
        return True 
    
    for i in range(2 ** n):
        for j in range(2 ** n):
            a = toBin(i, n)
            b = toBin(j, n)
            if isMaj(a, b) and val[i] < val[j]:
                return False
    return True

def savesZero(val, n):
    return (val[0] == 0)

def savesOne(val, n):
    return (val[2 ** n - 1] == 1)

n = int(input())

zero = True
one = True
mono = True
linear = True
dual = True

debug =False

for i in range(n):
    s = input().split()
    vals = [int(x) for x in s[1]]
    ns = int(s[0])
    if debug:
        print(savesZero(vals, ns))
        print(savesOne(vals, ns))
        print(checkMonotonous(vals, ns))
        print(checkLinear(vals, ns))
        print(checkSelfDuality(vals, ns))
    if zero:
        zero = savesZero(vals, ns)
    if one:
        one = savesOne(vals, ns)
    if mono:
        mono = checkMonotonous(vals, ns)
    if linear:
        linear = checkLinear(vals, ns)
    if dual:
        dual = checkSelfDuality(vals, ns)
        
if not zero and not one and not mono and not linear and not dual:
    print("YES")
else:
    print("NO")
            