import sys

sys.stdin = open('nextpartition.in', 'r')
sys.stdout = open('nextpartition.out', 'w')

s = [int(x) for x in input().split('=')[1].split('+')]
sm = 0
for item in s:
    sm += item


def choose_option():
    if len(s) == 1:
        print("No solution")
        return
    stl = try_this_length()
    if len(stl) == 0:
        gen_length_minus_one()
        return
    print(str(sm) + '=' + str(stl[0]), end='')
    for item in stl[1:]:
        print('+' + str(item), end='')


def try_this_length():
    sum = 0
    for i in range(1, len(s) + 1):
        sum += s[-i]
        if sum >= i * (s[-i] + 1):
            res = s[:-i]
            while sum >= 2 * (s[-i] + 1):
                res.append(s[-i] + 1)
                sum -= s[-i] + 1
            if sum > 0:
                res.append(sum)
            return res
    return []


def gen_length_minus_one():
    print(str(sm) + '=', end='')
    for i in range(len(s) - 2):
        print(str(s[i]), end='+')
    print(s[-2] + s[-1])


def gen2():
    if len(s) == 1:
        print("No solution")
        return
    if s[-1] - 1 < s[-2] + 1:
        gen_length_minus_one()
        return
    new_sm = s[-1] - 1
    add = s[-2] + 1
    s[-2] += 1
    del s[-1]
    while 2 * add <= new_sm:
        s.append(add)
        new_sm -= add
    if new_sm > 0:
        s.append(new_sm)
    print(str(sm) + '=' + str(s[0]), end='')
    for item in s[1:]:
        print('+' + str(item), end='')


gen2()

sys.stdout.close()
sys.stdin.close()
