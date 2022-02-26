# Постройте конечный автомат для языка слов над бинарным алфавитом,
# которые представляют собой развернутую двоичную запись чисел
# кратных 5 (сначала на вход подаются младшие разряды).

import matplotlib.pyplot as plt
import networkx as nx
import math as m


def vert(first_pos, second_pos):
    return str(first_pos) + ':' + str(second_pos)


def angled(alpha):
    return 100 * m.cos(alpha), 200 * m.sin(alpha)


leftovers = [1, 2, 4, 3]
color = []

g = nx.DiGraph()
for leftover in range(4):
    for cur_leftover in range(5):
        # pos=(100 + 100 * leftover, 100 + 100 * cur_leftover)
        g.add_node(vert(leftover, cur_leftover), pos=angled((leftover * 5 + cur_leftover) / 10 * m.pi))
        color.append('red' if cur_leftover == 0 else 'gray')

for leftover in range(4):
    for cur_leftover in range(5):
        for ch in range(2):
            fr = vert(leftover, cur_leftover)
            to = vert((leftover + 1) % 4, (cur_leftover + leftovers[leftover]) % 5 if ch == 1 else cur_leftover)
            g.add_edge(fr, to, tp=ch)

pos = nx.get_node_attributes(g, 'pos')
plt.figure(3, figsize=(12, 12))
nx.draw(g, pos, with_labels=True, node_color=color)
labels = nx.get_edge_attributes(g, 'tp')
nx.draw_networkx_edge_labels(g, pos, edge_labels=labels)
plt.show()
