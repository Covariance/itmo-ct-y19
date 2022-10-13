from collections import Counter
import numpy as np

def bincount(y, weights=None):
    if len(y) == 0:
        return np.asarray([])
    min_v = np.min(y)
    res = np.bincount(y - min_v, weights=weights)
    return res[res != 0]

def max_class(y, weights=None):
    if weights is None:
        weights = np.repeat(1 / len(y), len(y))
    res = {}
    for (k, w) in zip(y, weights):
        res[k] = res.get(k, 0) + w
    return max(res, key=res.get)
    
class DecisionTree():
    def __init__(self, max_depth=5):
        self.max_depth = max_depth
        
    def fit(self, X, y, sample_weight=None):
        if sample_weight is None:
            sample_weight = np.repeat(1 / X.shape[0], X.shape[0])
        self.root = self.train_impl(X, y, sample_weight)
        
    def train_impl(self, X, y, sample_weight, cur_depth=0):
        values = np.unique(y, return_counts=True)
        if self.max_depth == cur_depth or len(values) == 1:
            return Leaf(max_class(y, sample_weight))
        best_split = {"feature_idx": None, "score": np.inf, "split_idx": None, "threshold": None}
        
        scores = []
        for feature_idx in range(X.shape[1]):
            sort_idx = X[:, feature_idx].argsort()
            X = X[sort_idx, :]
            y = y[sort_idx]
            sample_weight = sample_weight[sort_idx]
            split_values = np.unique(X[:, feature_idx])
            split_idx = 0
            split_values = np.concatenate((split_values, np.array([split_values[-1] + 1])))
            for value in split_values:
                while split_idx < X.shape[0] and X[split_idx, feature_idx] < value:
                    split_idx += 1
                y_splitted = [(y[:split_idx], sample_weight[:split_idx]), (y[split_idx:], sample_weight[split_idx:])]
                s = [bincount(y_part, weights=weights) / sum(weights) for (y_part, weights) in y_splitted]
                score = sum(sum(y_splitted[i][1]) / sum(sample_weight) * np.sum(s[i] * (1 - s[i])) for i in range(len(s)))
                scores.append(score)
                if best_split["score"] > score:
                    best_split["score"] = score
                    best_split["feature_idx"] = feature_idx
                    best_split["split_idx"] = split_idx
                    best_split["threshold"] = value
                    
        
        split_idx = best_split["split_idx"]
        feature_idx = best_split["feature_idx"]
        if split_idx is not None and split_idx != 0 and split_idx != X.shape[0]:
            sort_idx = X[:, feature_idx].argsort()
            X = X[sort_idx, :]
            y = y[sort_idx]
            sample_weight = sample_weight[sort_idx]
            left = self.train_impl(X[:split_idx], y[:split_idx], sample_weight[:split_idx], cur_depth+1)
            right = self.train_impl(X[split_idx:], y[split_idx:], sample_weight[split_idx:], cur_depth+1)
            return Node(best_split["feature_idx"], best_split["threshold"], left, right)
        else:
            return Leaf(max_class(y, sample_weight))
        
    def predict_one(self, x):
        return self.root.predict(x)
    
    def predict(self, X):
        return np.apply_along_axis(self.predict_one, 1, X)
