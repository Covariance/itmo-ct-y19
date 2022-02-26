import sys

sys.stdin = open('nextvector.in', 'r')
sys.stdout = open('nextvector.out', 'w')

s = [x for x in input()]
sprev = [x for x in s]
snext = [x for x in sprev]

i = 0
while i != len(sprev) and sprev[len(sprev) - i - 1] == '0':
    sprev[len(sprev) - i - 1] = '1'
    i += 1
if i == len(sprev):
    print("-")
else:
    sprev[len(sprev) - i - 1] = '0'
    print(''.join(sprev))

i = 0
while i != len(snext) and snext[len(snext) - i - 1] == '1':
    snext[len(snext) - i - 1] = '0'
    i += 1
if i == len(snext):
    print("-")
else:
    snext[len(snext) - i - 1] = '1'
    print(''.join(snext))

sys.stdout.close()
sys.stdin.close()
