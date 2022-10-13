from __future__ import annotations
from typing import Set, List, Tuple, Dict, Any, Callable, Union
from itertools import product

import numpy as np
from utils import BasicLayer


# kernels
def uniform(u: float) -> float:
    return .5

def triangular(u: float) -> float:
    return (1 - np.abs(u))

def epanechnikov(u: float) -> float:
    return (3 / 4) * (1 - u ** 2)

def quartic(u: float) -> float:
    return (15 / 16) * (1 - u ** 2) ** 2

def make_kernel(fun: Callable[[float], float]) -> Callable[[float], float]:
    def kernel(u: float) -> float:
        return fun(u) if 0 <= u and u <= 1 else 0.
    
    return kernel


# metrics
def euclid(p1: np.ndarray, p2: np.ndarray) -> float:
    return np.sqrt(((p1 - p2) ** 2).sum())

def manhattan(p1: np.ndarray, p2: np.ndarray) -> float:
    return np.abs(p1 - p2).sum()

def chebyshev(p1: np.ndarray, p2: np.ndarray) -> float:
    return np.max(np.abs(p1 - p2))
        

class knnRegression(BasicLayer):
    '''
    kernel: uniform, triangular, epanechnikov, quartic
    metric: euclid, manhattan, chebyshev
    window: fixed, variadic
    window parameter: either 
    '''
    def __init__(self, kernel: str = 'uniform', metric: str = 'euclid', window: str = 'variadic', window_parameter: Union[float, int] = 10):
        super().__init__()
        self.kernel = kernel
        self.metric = metric
        self.window = window
        self.window_parameter = window_parameter
        
    def get_kernel(self) -> Callable[[float], float]:
        if self.kernel == 'uniform':
            return make_kernel(uniform)
        
        if self.kernel == 'triangular':
            return make_kernel(triangular)
        
        if self.kernel == 'epanechnikov':
            return make_kernel(epanechnikov)
        
        if self.kernel == 'quartic':
            return make_kernel(quartic)
        
        raise NameError(f'unknown kernel type: {self.kernel}')
        
        
    def get_metric(self) -> Callable[[np.ndarray, np.ndarray], float]:
        if self.metric == 'euclid':
            return euclid
        
        if self.metric == 'manhattan':
            return manhattan
        
        if self.metric == 'chebyshev':
            return chebyshev
        
        raise NameError(f'unknown metric: {self.metric}')

        
    def get_window(self) -> Callable[[np.ndarray], np.ndarray]:
        if self.window == 'fixed':
            return self._fixed
        
        if self.window == 'variadic':
            return self._variadic
        
        raise NameError(f'unknown window: {self.window}')
        
    def _fixed(self, x: np.ndarray) -> np.ndarray:
        res = np.zeros_like(self.labels[0])
        denom = 0.
    
        for row in range(len(self.points)):
            dst = self.get_metric()(x, self.points[row])
            if dst > self.window_parameter:
                break
            kern = self.get_kernel()(dst / self.window_parameter)
            
            res += kern * self.labels[row]
            denom += kern
        
        if denom == 0.:
            return res
            
        return res / denom
    
    def _variadic(self, x: np.ndarray) -> np.ndarray:
        res = np.zeros_like(self.labels[0])
        denom = 0.
        
        hden = self.get_metric()(x, self.points[self.window_parameter])
        
        for row in range(self.window_parameter):
            kern = self.get_kernel()(self.get_metric()(x, self.points[row]) / hden)
            
            res += kern * self.labels[row]
            denom += kern
        
        if denom == 0.:
            return res
        
        return res / denom
            
        
    def fit(self, X: np.ndarray, y: np.ndarray) -> BasicLayer:
        self.points = X
        self.labels = y
        return self
        

    def transform(self, X: np.ndarray) -> np.ndarray:
        result = []
        
        for x in X:
            distances = np.apply_along_axis(lambda p : self.get_metric()(x, p), 1, self.points)
            
            indices = np.argsort(distances)
            self.points = self.points[indices]
            self.labels = self.labels[indices]
            
            result.append(self.get_window()(x))
        
        return np.stack(result, axis=0)
