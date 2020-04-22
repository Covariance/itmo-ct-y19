# Постройте конечный автомат для языка слов над бинарным алфавитом,
# в которых число нулей кратно 3 или которые представляют собой
# двоичную запись чисел кратных 5. Сделайте вывод из последних
# двух заданий.

import matplotlib.pyplot as plt
import networkx as nx
import math as m


def vert(first_pos, second_pos):
    return str(first_pos) + ':' + str(second_pos)


positions = []
cur_pos = 0
for alpha in range(15):
    positions.append(
        (
            100 + m.sin(-m.pi / 2 + 2 * m.pi * alpha / 15) * 100,
            100 + m.cos(-m.pi / 2 + 2 * m.pi * alpha / 15) * 100
        )
    )

color = []
g = nx.DiGraph()
for i in range(5):
    for j in range(3):
        g.add_node(vert(i, j), pos=positions[cur_pos])
        cur_pos += 1
        color.append('red' if i == 0 or j == 0 else 'gray')

edgeLabels = {}

for i in range(5):
    for j in range(3):
        for ch in range(2):
            fr = vert(i, j)
            to = vert((2 * i + ch) % 5, (j + 1) % 3 if ch == 0 else j)
            g.add_edge(fr, to, tp=ch)

pos = nx.get_node_attributes(g, 'pos')
nx.draw(g, pos, with_labels=True, node_color=color)
labels = nx.get_edge_attributes(g, 'tp')
nx.draw_networkx_edge_labels(g, pos, edge_labels=labels)
plt.axis('off')
plt.show()
