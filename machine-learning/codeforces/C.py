import math
from typing import Callable
import numpy as np
    
# kernels
def uniform(u: float) -> float:
    return .5

def triangular(u: float) -> float:
    return (1 - np.abs(u))

def epanechnikov(u: float) -> float:
    return (3 / 4) * (1 - u ** 2)

def quartic(u: float) -> float:
    return (15 / 16) * (1 - u ** 2) ** 2

def triweight(u: float) -> float:
    return (35 / 32) * (1 - u ** 2) ** 3

def tricube(u: float) -> float:
    return (70 / 81) * (1 - np.abs(u) ** 3) ** 3

def gaussian(u: float) -> float:
    return (1 / np.sqrt(2 * math.pi)) * np.exp(-(u ** 2 / 2))

def cosine(u: float) -> float:
    return math.pi / 4 * np.cos(math.pi * u / 2)

def logistic(u: float) -> float:
    return 1 / (2 + np.exp(u) + np.exp(-u))

def sigmoid(u: float) -> float:
    return 2 / (math.pi) / (np.exp(u) + np.exp(-u))

def make_kernel(fun: Callable[[float], float]) -> Callable[[float], float]:
    def kernel(u: float) -> float:
        return fun(u) if u < 1 else 0.
    
    return kernel


# metrics
def euclid(p1: np.ndarray, p2: np.ndarray) -> float:
    return np.sqrt(((p1 - p2) ** 2).sum())

def manhattan(p1: np.ndarray, p2: np.ndarray) -> float:
    return np.abs(p1 - p2).sum()

def chebyshev(p1: np.ndarray, p2: np.ndarray) -> float:
    return np.max(np.abs(p1 - p2))


def get_kernel(kernel: str) -> Callable[[float], float]:
    if kernel == 'uniform':
        return make_kernel(uniform)
        
    if kernel == 'triangular':
        return make_kernel(triangular)
        
    if kernel == 'epanechnikov':
        return make_kernel(epanechnikov)
        
    if kernel == 'quartic':
        return make_kernel(quartic)
        
    if kernel == 'triweight':
        return make_kernel(triweight)
        
    if kernel == 'tricube':
        return make_kernel(tricube)
        
    if kernel == 'gaussian':
        return gaussian
        
    if kernel == 'cosine':
        return make_kernel(cosine)
        
    if kernel == 'logistic':
        return logistic
        
    if kernel == 'sigmoid':
        return sigmoid
        
    raise NameError(f'unknown kernel type: {kernel}')
        
def get_metric(metric: str) -> Callable[[np.ndarray, np.ndarray], float]:
    if metric == 'euclidean':
        return euclid
        
    if metric == 'manhattan':
        return manhattan
        
    if metric == 'chebyshev':
        return chebyshev
        
    raise NameError(f'unknown metric: {metric}')


if __name__ == '__main__':
    n, _ = map(int, input().split())
    
    X, y = [], []
    for _ in range(n):
        obj = list(map(int, input().split()))
        X.append(obj[:-1])
        y.append(obj[-1])
    
    Xnp, ynp = np.array(X), np.array(y)
    query = np.array(list(map(int, input().split())))
    
    metric = get_metric(input())
    kernel = get_kernel(input())
    window_type = input()
    window_param = int(input())
    
    sorted_points = sorted(list(map(lambda elem: (elem[0], elem[1], metric(elem[0], query)), zip(Xnp, ynp))), key=lambda x: x[2])
    
    p = window_param if window_type == 'fixed' else sorted_points[window_param][2]
    
    if p == 0:
        if sorted_points[0][0] == query:
            neighbours = map(lambda e: e[1], filter(lambda elem: elem[0] == query, sorted_points))
            res = np.array(neighbours).mean()
        else:
            res = ynp.mean()
    else:
        def process(element):
            kern = kernel(element[2] / p)
            return (element[1] * kern, kern)

        x, y = map(sum, zip(*map(process, sorted_points)))
        
        if y == 0:
            res = ynp.mean()
        else:
            res = x / y

    print(f'{res:.10f}')
