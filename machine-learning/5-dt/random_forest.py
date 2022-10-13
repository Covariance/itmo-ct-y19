import numpy as np
from decision_tree import *

class RandomForestClassifier():
    def __init__(self, n_estimators=100):
        self.n_estimators = n_estimators

    def fit(self, X, y):
        self.estimators = []
        self.estimator_cols = []
        self.K = min(int(np.sqrt(X.shape[0] + 4)), X.shape[1])
        for i in range(self.n_estimators):
            columns = np.array(list(range(X.shape[1])))
            clf = DecisionTree()
            idx = np.random.choice(np.arange(start=0, stop=X.shape[0], step=1, dtype=np.int32),
                                    size=int(X.shape[0]))
            clf.fit(X[idx, :][:, columns], y[idx])
            self.estimators.append(clf)
            self.estimator_cols.append(columns)

    def predict(self, X_test):
        est_results = np.array([self.estimators[i].predict(X_test[:, self.estimator_cols[i]])
                                for i in range(self.n_estimators)])
        results = np.array([max(est_results[:, i], key= lambda x: (est_results[:, i] == x).sum()) for i in range(X_test.shape[0])])
        return results
