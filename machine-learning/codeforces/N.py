k, n = int(input()), int(input())

elems = [list(map(int, input().split())) for _ in range(n)]

second_moment = sum(map(lambda xy: xy[1] * xy[1] / n, elems))

exp_y_x = [[0, 0] for _ in range(k)]

for x, y in elems:
    exp_y_x[x - 1][0] += y / n
    exp_y_x[x - 1][1] += 1. / n


exp_cond = sum(map(lambda ey_p : ey_p[0] * ey_p[0] / ey_p[1], filter(lambda ey_p: ey_p[1] != 0, exp_y_x)))

print(second_moment - exp_cond)
