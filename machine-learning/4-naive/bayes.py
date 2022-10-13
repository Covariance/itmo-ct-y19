import numpy as np
from fractions import Fraction
from sklearn.base import BaseEstimator, ClassifierMixin

class BayesClassifier(BaseEstimator, ClassifierMixin):
    def __init__(self, alpha=1, lambdas=[1, 1]):
        self.alpha = alpha
        self.lambdas = lambdas
        self._classes_cnt = len(lambdas)
    
    def _get_prob(self, cur_class, word):
        zero_numinator = self.alpha
        zero_denuminator = self._classes_prob[cur_class][0] + self.alpha * self._distinct_words[cur_class]
        zero_prob = np.array([zero_numinator, zero_denuminator])
        return self._words_prob[cur_class].get(word, zero_prob)

    def fit(self, X, y):
        self._classes_prob = np.zeros((self._classes_cnt, 2), dtype=int)
        self._distinct_words = np.zeros(self._classes_cnt, dtype=int)
        self._words_prob = [{}] * self._classes_cnt
        
        default_word_prob = np.array([self.alpha, 0], dtype=int)
        for i in range(X.shape[0]):
            cur_words = set(X[i])
            cur_class = y[i]
            for word in cur_words:
                self._words_prob[cur_class].setdefault(word, default_word_prob)
                self._words_prob[cur_class][word][0] += 1
            self._classes_prob[cur_class][0] += 1
            
        for cur_class in range(self._classes_cnt):
            distinct = len(self._words_prob[cur_class])
            self._distinct_words[cur_class] = distinct
            self._classes_prob[cur_class][1] = self._classes_cnt
            for word in self._words_prob[cur_class].keys():
                self._words_prob[cur_class][word][1] = self._classes_prob[cur_class][0] + distinct * self.alpha

    def _predict_one(self, cur_msg):
        metrics = np.log(self._classes_prob)
        cur_words = set(cur_msg)
        for cur_class in range(self._classes_cnt):
            metrics[cur_class][0] += np.log(self.lambdas[cur_class])
            for word in cur_words:
                metrics[cur_class] += np.log(self._get_prob(cur_class, word))
        return np.argmax(metrics[0] - metrics[1])

    def predict(self, X):
        return np.vectorize(self._predict_one)(X)
