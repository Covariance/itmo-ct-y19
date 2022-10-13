import numpy as np
from sklearn.base import BaseEstimator, TransformerMixin

class NGrammer(BaseEstimator, TransformerMixin):
    def __init__(self, n=1):
        self.n = n
        
    def fit(self, X, y = None):
        return self
    
    def transform(self, X, y = None):
        res = []
        for line in X:
            line_res = []
            for i in range(len(line) - self.n + 1):
                line_res.append(''.join(line[i:i+self.n]))
            res.append(line_res)
            
        return np.array(res, dtype=object)
