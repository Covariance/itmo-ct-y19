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
        return '0'
    return '1'

n = int(input())

for i in range(2 ** n):
    s = input().split()
    if not checkZhigalkin(s[0]) == s[1]:
        polynom.append([s[0], '1'])
    else:
        polynom.append([s[0], '0'])
        
for string in polynom:
    print(' '.join(string))
    
    