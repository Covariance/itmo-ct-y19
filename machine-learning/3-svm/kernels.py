import numpy as np

class Linear:
    def __init__(self):
        pass
    
    def __call__(self, x, xs):
        return np.dot(x, xs)
    

class Polynomial:
    def __init__(self, gamma: float, r: float, d: int):
        self.gamma = gamma
        self.r = r
        self.d = d
        
    def __call__(self, x, xs):
        return np.power(self.gamma * np.dot(x, xs) + self.r, self.d)
    

class RBF:
    def __init__(self, gamma):
        self.gamma = gamma
        
    def __call__(self, x, xs):
        return np.exp(-self.gamma * np.power(np.linalg.norm(x - xs), 2))
