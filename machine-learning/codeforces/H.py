from __future__ import annotations
from typing import List, Tuple
import numpy as np

class Node:
    def __init__(self, inputs: List[Node]):
        self.inputs = inputs
        self.value = np.array([[]])

    def compute(self):
        raise NotImplementedError
    
    def spread_diff(self):
        raise NotImplementedError

    def initialize_diff(self):
        self.diff = np.zeros_like(self.value)
        
    def read_diff(self):
        for i in range(self.diff.shape[0]):
            vals = list(map(int, input().split()))
            for j in range(self.diff.shape[1]):
                self.diff[i][j] = vals[j]

             
class Var(Node):
    def __init__(self):
        super().__init__([])
    
    def set_data(self, value: np.ndarray):
        self.value = value
        
    def compute(self):
        self.initialize_diff()
        
    def spread_diff(self):
        pass


class Tnh(Node):
    def __init__(self, source: Node):
        super().__init__([source])
        
    def compute(self):
        self.value = np.tanh(self.inputs[0].value)
        self.initialize_diff()
        
    def spread_diff(self):
        for i in range(self.diff.shape[0]):
            for j in range(self.diff.shape[1]):
                cur_value = self.value[i][j]
                self.inputs[0].diff[i][j] += self.diff[i][j] * (1 - cur_value * cur_value)
                
class RLU(Node):
    def __init__(self, alpha: float, source: Node):
        super().__init__([source])
        self.alpha = alpha
        
    def compute(self):
        self.value = self.inputs[0].value
        self.value = (self.value < 0) * (self.value / self.alpha) + (self.value >= 0) * self.value
        self.initialize_diff()
        
    def spread_diff(self):
        for i in range(self.diff.shape[0]):
            for j in range(self.diff.shape[1]):
                cur_input = self.value[i][j]
                
                mult = 1. if cur_input >= 0 else 1. / self.alpha
                
                self.inputs[0].diff[i][j] += self.diff[i][j] * mult
                
class Mul(Node):
    def __init__(self, a: Node, b: Node):
        super().__init__([a, b])
        
    def compute(self):
        a = self.inputs[0].value
        b = self.inputs[1].value
        
        n, m, k = a.shape[0], a.shape[1], b.shape[1]
        
        self.value = np.zeros((n, k), dtype=float)
        
        for i in range(n):
            for j in range(k):
                for t in range(m):
                    self.value[i][j] += a[i][t] * b[t][j]
        
        self.initialize_diff()
        
    def spread_diff(self):
        a = self.inputs[0].value
        b = self.inputs[1].value
        
        da = self.inputs[0].diff
        db = self.inputs[1].diff
        
        n, m, k = a.shape[0], a.shape[1], b.shape[1]
        
        for i in range(n):
            for j in range(m):
                da[i][j] += sum([self.diff[i][t] * b[j][t] for t in range(k)])
                
        for i in range(m):
            for j in range(k):
                db[i][j] += sum([a[t][i] * self.diff[t][j] for t in range(n)])

                
class Sum(Node):
    def compute(self):
        n, m = self.inputs[0].value.shape
        
        self.value = np.zeros_like(self.inputs[0].value)
        
        for input in self.inputs:
            for i in range(n):
                for j in range(m):
                    self.value[i][j] += input.value[i][j]
            
        self.initialize_diff()
        
    def spread_diff(self):
        for i in range(self.diff.shape[0]):
            for j in range(self.diff.shape[1]):
                for input in self.inputs:
                    input.diff[i][j] += self.diff[i][j]

class Had(Node):
    def compute(self):
        n, m = self.inputs[0].value.shape
        
        self.value = np.ones_like(self.inputs[0].value)
        
        for input in self.inputs:
            for i in range(n):
                for j in range(m):
                    self.value[i][j] *= input.value[i][j]
        
        self.initialize_diff()
        
    def spread_diff(self):
        for i in range(self.value.shape[0]):
            for j in range(self.value.shape[1]):
                for k in range(len(self.inputs)):
                    mult = 1.
                    for t in range(len(self.inputs)):
                        if t != k:
                            mult *= self.inputs[t].value[i][j]
                    self.inputs[k].diff[i][j] += self.diff[i][j] * mult


class Network:
    def __init__(self):
        self.nodes: List[Node] = []
        
    def get_node(self, idx: int) -> Node:
        return self.nodes[idx]
    
    def get_nodes(self, idxs: List[int]) -> List[Node]:
        return [self.nodes[idx] for idx in idxs]
    
    def add_node(self, node: Node):
        self.nodes.append(node)
        
    def print_node(self, idx: int):
        for row in self.nodes[idx].value:
            print(' '.join(map(str, row)))
        
    def print_diff(self, idx: int):
        for row in self.nodes[idx].diff:
            print(' '.join(map(str, row)))
            
    def compute(self):
        for node in self.nodes:
            node.compute()
            
    def backprop(self):
        for node in reversed(self.nodes):
            node.spread_diff()


if __name__ == '__main__':
    n, m, k = map(int, input().split())
    
    input_sizes: List[Tuple[int, int]] = []
    net = Network()
    
    for _ in range(n):
        line = input().split()
        
        typ = line[0]
        args = line[1:]
        
        if typ == 'var':
            a, b = map(int, args)
            input_sizes.append((a, b))
            net.add_node(Var())
            
        if typ == 'tnh':
            x = int(args[0]) - 1
            net.add_node(Tnh(net.get_node(x)))

        if typ == 'rlu':
            alpha, x = float(args[0]), int(args[1]) - 1
            net.add_node(RLU(alpha, net.get_node(x)))
            
        if typ == 'mul':
            a, b = int(args[0]) - 1, int(args[1]) - 1
            net.add_node(Mul(net.get_node(a), net.get_node(b)))
            
        if typ == 'sum':
            xs = list(map(lambda x: int(x) - 1, args[1:]))
            net.add_node(Sum(net.get_nodes(xs)))
            
        if typ == 'had':
            xs = list(map(lambda x: int(x) - 1, args[1:]))
            net.add_node(Had(net.get_nodes(xs)))
            
    for i, input_size in enumerate(input_sizes):
        inp = np.zeros(input_size)
        
        for a in range(input_size[0]):
            line = list(map(float, input().split()))
            for b in range(input_size[1]):
                inp[a][b] = line[b]
                
        net.nodes[i].set_data(inp)
        
    net.compute()
    
    for i in range(n - k, n):
        net.print_node(i)
        
    for i in range(n - k, n):
        net.nodes[i].read_diff()
        
    net.backprop()
    
    for i in range(m):
        net.print_diff(i)
