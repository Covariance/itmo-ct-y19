from __future__ import annotations
from typing import Set, List, Tuple, Dict, Any, Callable
from itertools import product

import numpy as np

class BasicLayer:
    def fit(self, X: np.ndarray, y: np.ndarray) -> BasicLayer:
        return self
    
    def transform(self, X: np.ndarray) -> np.ndarray:
        return X
    
    def fit_transform(self, X: np.ndarray, y: np.ndarray) -> np.ndarray:
        return self.fit(X, y).transform(X)

    
class OneHotEncoder(BasicLayer):
    def __init__(self, column: int):
        super().__init__()
        self.column = column
        self.values: Set[str] = set()
    
    def fit(self, X: np.ndarray, y: np.ndarray) -> OneHotEncoder:
        # Record all the different values seen in the given column
        self.values = self.values.union(set(X[self.column]))
        return self
    
    def transform(self, X: np.ndarray) -> np.ndarray:
        result = np.delete(X, self.column, axis=1)
        
        for value in self.values:
            result[f'{self.column}_is_{value}'] = (X[self.column] == value).astype('int32')
        
        return result
    

class Pipeline(BasicLayer):
    def __init__(self, layers: List[Tuple[str, BasicLayer]]):
        super().__init__()
        self.layers = layers
        
    def fit(self, X: np.ndarray, y: np.ndarray) -> Pipeline:
        for _, layer in self.layers:
            X = layer.fit_transform(X, y)
            
        return self
    
    def transform(self, X: np.ndarray) -> np.ndarray:
        for _, layer in self.layers:
            X = layer.transform(X)
            
        return X
    
    def fit_transform(self, X: np.ndarray, y: np.ndarray) -> np.ndarray:
        for _, layer in self.layers:
            X = layer.fit_transform(X, y)
            
        return X

from sklearn.metrics import f1_score

class GridSearch(BasicLayer):
    def __init__(self, pipeline: Pipeline, grid: Dict[Tuple[str, str], List[Any]], scorer: str = 'LOOCV-F1'):
        super().__init__()
        self.pipeline = pipeline
        self.grid = [(key, value) for key, value in grid.items()]
        self.scorer = scorer
        
        
    def _fit_and_score(self, X: np.ndarray, y: np.ndarray) -> float:
        if self.scorer == 'LOOCV-F1':
            preds: bool = []
            for i in range(len(X)):
                preds.append(self.pipeline.fit(np.delete(X, i, axis=0), np.delete(y, i, axis=0)).transform(np.array([X[i]])))
                
            preds = np.array(preds).flatten()
            
            classes = set(y).union(set(preds))
            
            f1_total = 0.
            
            for clazz in classes:
                ys = (preds == clazz)
                tp = ((preds == y) & ys).sum()
                false = (ys != y).sum()
                f1_total += tp / (tp + .5 * false)
            
            # return f1_score(y, preds, average='macro')
            return f1_total / len(classes)
        else:
            return 0
        
    
    def fit(self, X: np.ndarray, y: np.ndarray) -> GridSearch:
        self.history: List[Tuple[Tuple[Any, ...], float]] = []
        
        for values in product(*[value for _, value in self.grid]):
            # Inject values in a pipeline
            for i, value in enumerate(values):
                (step_name, parameter), _ = self.grid[i]
                
                for name, step in self.pipeline.layers:
                    if step_name == name:
                        setattr(step, parameter, value)
                        break
                        
            score = self._fit_and_score(X, y)
            
            if len(self.history) == 0 or self.best_score < score:
                self.best_score = score
                self.best_params = values
            
            self.history.append((values, score))
            print((values, score))
                
        return self
    
    def transform(self, X: np.ndarray) -> np.ndarray:
        raise NotImplementedError
