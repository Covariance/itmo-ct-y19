import numpy as np
from typing import List


def distances(xs: List[int]) -> int:
    xs.sort()
    
    n = len(xs)
    postfix = sum(xs)
    prefix = 0
    
    cum_sum = 0
    
    for i in range(n):
        prefix += xs[i]
        
        cum_sum += postfix - prefix + xs[i] * (2 * i - n + 1)
        
        postfix -= xs[i]

    return cum_sum


def inner_distance(X: List[int], y: List[int]) -> int:
    split = {y_elem : [] for y_elem in set(y)}
    
    for i, x_elem in enumerate(X):
        split[y[i]].append(x_elem)
        
    return sum(distances(xs) for xs in split.values())


def outer_distance(X: List[int], y: List[int]) -> int:
    return distances(list(X)) - inner_distance(X, y)


def stress():
    np.random.seed(42)
    
    def gen():
        size = np.random.randint(10, 20)
        m = np.random.randint(1, 5)
        return list(np.random.randint(0, 100, size)), list(np.random.randint(0, m, size))
    
    def slow_inner_distance(X: List[int], y: List[int]) -> int:
        return sum(np.abs(X[j] - X[i]) for j in range(len(X)) for i in range(len(X)) if y[j] == y[i])
    
    def slow_outer_distance(X: List[int], y: List[int]) -> int:
        return sum(np.abs(X[j] - X[i]) for j in range(len(X)) for i in range(len(X)) if y[j] != y[i])
    
    for _ in range(1_000_000):
        X, y = gen()
        
        sid, fid = slow_inner_distance(X, y), inner_distance(X, y)
        
        assert sid == fid, f'inner:\n{X}\n{y}\n{sid} != {fid}'
        
        sod, fod = slow_outer_distance(X, y), outer_distance(X, y)
        
        assert sod == fod, f'inner:\n{X}\n{y}\n{sod} != {fod}'


if __name__ == '__main__':
    # stress()
    
    m, n = int(input()), int(input())
    
    X, y = zip(*[list(map(int, input().split())) for _ in range(n)])
    
    print(inner_distance(X, y), outer_distance(X, y), sep='\n')
