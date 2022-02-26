# Постройте детерминированный конечный автомат для языка слов
# над бинарным алфавитом, в которых пятый символ с конца - единица.

import matplotlib.pyplot as plt
import networkx as nx
import math as m


def angled(rad, alpha, center):
    return rad * m.cos(alpha) + center[0], rad * m.sin(alpha) + center[1]


def to_bin_str(ln, n):
    b = ''
    for i in range(ln):
        b = str(n % 2) + b
        n = n // 2

    return b


color = []
g = nx.DiGraph()

for i in range(5):
    for j in range(1 << i):
        g.add_node(to_bin_str(i, j), pos=(i * 1000, 2000 - j * 2000 / (1 << i)))
        color.append('gray')
        # переход в родителя, если мы не стартовая вершина
        if not i == 0:
            g.add_edge(to_bin_str(i - 1, j // 2), to_bin_str(i, j))

for i in range(32):
    g.add_node(to_bin_str(5, i), pos=angled(1000, i / 16 * m.pi, (6000, 1000)))
    # переход в родителя с < 5 цифрами
    g.add_edge(to_bin_str(4, i // 2), to_bin_str(5, i))
    color.append('red' if (i & 16) != 0 else 'gray')

for i in range(32):
    for ch in range(2):
        # переход по символу ch
        g.add_edge(to_bin_str(5, i), to_bin_str(5, (2 * i) % 32 + ch), tp=ch)

pos = nx.get_node_attributes(g, 'pos')
plt.figure(3, figsize=(35, 15))
nx.draw_networkx(g, pos, node_size=2000, font_size=18, with_labels=True, node_color=color)
plt.show()
