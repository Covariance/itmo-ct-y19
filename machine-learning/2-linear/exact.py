from __future__ import annotations
import numpy as np

class ExactRegressor:
    def __init__(self, ridge_coef: float = 0., fit_intercept: bool = True):
        self.ridge_coef = ridge_coef
        self.fit_intercept = fit_intercept
        
    def fit(self, X: np.ndarray, y: np.ndarray):
        if self.fit_intercept:
            X = np.hstack((X, np.ones((X.shape[0], 1))))
        
        inv = np.linalg.pinv(X.T.dot(X) + self.ridge_coef)
        
        res = inv.dot(X.T).dot(y)

        if self.fit_intercept:
            self.coef = res[:-1]
            self.intercept = res[-1]
        else:
            self.coef = res
            self.intercept = 0.
        return self
    
    def predict(self, X: np.ndarray) -> np.ndarray:        
        return X.dot(self.coef) + self.intercept
