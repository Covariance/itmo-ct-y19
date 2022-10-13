from copy import deepcopy
from sklearn.metrics import zero_one_loss
from math import log, isclose, exp


class AdaBoost():
    def __init__(self, base_clf, clfs_cnt):
        self.base_clf = base_clf
        self.clfs_cnt = clfs_cnt
        
    def fit(self, X, y):
        cnt, dim = X.shape
        sample_weight = np.repeat(1 / cnt, cnt)
        self.clfs_ = [deepcopy(self.base_clf) for _ in range(self.clfs_cnt)]
        self.clf_weights_ = []
        source = self.clfs_
        
        for clf in source:
            clf.fit(X, y, sample_weight)
            y_pred = clf.predict(X)
            # print(y == y_pred)
            # print(y_pred)
            # print(np.sum(y_pred == -y))
            weighted_error = np.array(y_pred == -y) * sample_weight
            weighted_error = np.sum(weighted_error)
            # print(weighted_error)
            if isclose(weighted_error, 0):
                self.clfs_ = [clf]
                self.clf_weights_ = [1]
                break
            elif isclose(weighted_error, 1):
                self.clfs_ = [clf]
                self.clf_weights_ = [-1]
                break
            alpha = 0.5 * log((1 - weighted_error) / weighted_error)
            self.clf_weights_.append(alpha)
            sample_weight = sample_weight * np.exp(-alpha * (y * y_pred))
            sample_weight /= np.sum(sample_weight)
            # print(sample_weight)

        self.clf_weights_ = np.array(self.clf_weights_)
        self.clfs_ = np.array(self.clfs_)
        
    def predict(self, X):
        return self.predict_prefix(X, len(self.clfs_))
        
    def predict_prefix(self, X, idx):
        cnt, dim = X.shape
        answers = np.zeros(cnt)
        for i in range(idx):
            clf = self.clfs_[i]
            w = self.clf_weights_[i]
            answers += w * clf.predict(X)
        return np.sign(answers)
