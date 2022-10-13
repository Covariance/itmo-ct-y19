import numpy as np
from qpsolvers import solve_qp, available_solvers
from sklearn.base import BaseEstimator, ClassifierMixin
from sklearn.utils.validation import check_X_y, check_array, check_is_fitted

class SVM:
    def __init__(self, kernel, C, is_iterative = False, max_iter = 1_000):
        if not is_iterative and 'cvxopt' not in available_solvers:
            raise Exception('cvxopt not available as qpsolver')
        
        self.kernel = kernel
        self.C = C
        self.is_iterative = is_iterative
        self.max_iter = max_iter
    
    def fit(self, X, y):
        self.X = X
        self.y = y
        self.N = len(y)
        self.kernel_matrix = np.array([[y[i] * y[j] * self.kernel(X[i], X[j]) for j in range(len(y))] for i in range(len(y))])
        
        if self.is_iterative:
            self.lambdas = np.zeros(len(y))
            indices = np.arange(len(y))
            for _ in range(self.max_iter):
                np.random.shuffle(indices)
                for i_fake in range(len(y)):
                    i = indices[i_fake]
                    j = indices[self._get_random_j(i_fake, len(y))]

                    E_i = np.dot(self.lambdas * y, self.kernel_matrix[i]) - y[i]
                    E_j = np.dot(self.lambdas * y, self.kernel_matrix[j]) - y[j]

                    prev_a_i = self.lambdas[i]
                    prev_a_j = self.lambdas[j]
                    U, V = self._calc_U_V(i, j, y)
                    if V - U < 1e-9:
                        continue
                    eta = 2 * self.kernel_matrix[i][j] - (self.kernel_matrix[i][i] + self.kernel_matrix[j][j])
                    if eta > -1e-9:
                        continue
                    possible_new_a_j = prev_a_j + y[j] * (E_j - E_i) / eta
                    new_a_j = min(max(U, possible_new_a_j), V)
                    if abs(new_a_j - prev_a_j) < 1e-9:
                        continue
                    self.lambdas[j] = new_a_j
                    self.lambdas[i] += y[i] * y[j] * (prev_a_j - new_a_j)
                    
            self.fit_iterative(self)
        else:
            self.lambdas = solve_qp(
                # -\sum lambda_i + 1/2 * \sum\sum lambda_i * lambda_j * y_i * y_j * <x_i, x_j> -> min
                self.kernel_matrix, -np.ones(len(y)),
                # \sum lambda_i * y_i = 0
                A = y.astype('float'), b = np.zeros(1),
                # 0 <= lambda_i <= C
                lb = np.zeros(len(y)), ub = self.C * np.ones(len(y)),
                # some available solver
                solver = 'cvxopt',
            )
            # w = \sum_l lambda_i y_i x_i
            # w0 = <w, x_i> - y_i, where lambda_i > 0 and Mi = 1

        self.w = np.zeros(X.shape[1])
        for i in range(len(self.lambdas)):
            self.w += self.lambdas[i] * y[i] * X[i]

        S = (self.lambdas > 1e-9).flatten()
        self.w0 = np.mean(-y[S] + np.dot(X[S], self.w.reshape(-1,1)))
        
        return self
    
    def _get_random_j(self, i, ylen):
        res = np.random.randint(0, ylen - 1);
        return res if res < i else res + 1
    
    def _calc_U_V(self, i, j, y):
        a_i, a_j = self.lambdas[i], self.lambdas[j]
        if y[i] == y[j]:
            U = max(0, a_i + a_j - self.C)
            V = min(self.C, a_i + a_j)
        else:
            U = max(0, a_j - a_i)
            V = min(self.C, self.C + a_j - a_i)
        return U, V
    
    def _get_w0(self, i):
        return 1 / self.y[i] - np.dot(self.alphas * self.y, self.kernel[i])
    
    def predict(self, X):
        out = np.zeros(X.shape[0])
        for i in range(X.shape[0]):
            for j in range(len(self.lambdas)):
                out[i] += self.lambdas[j] * self.y[j] * self.kernel(X[i], self.X[j])
        return np.sign(out - self.w0)

class SVMIter(BaseEstimator, ClassifierMixin):
    def __init__(self, kernel_f, C=1.0, max_iter=1000, eps=1e-6):
        self.kernel_f = kernel_f
        self.C = C
        
        self.max_iter = max_iter
        self.eps = eps
        
    def predict(self, X):
        X = check_array(X)
        
        return np.array([self.predict_one(x) for x in X]) 
        
    def predict_one(self, x):
        kernel = self.calc_kernel_matrix(np.array([x]), self.X)
        res = int(np.sign(np.sum(self.alphas * self.y * kernel[0]) + self.b))
        return res if res != 0 else 1
    
    def calc_kernel_matrix(self, A, B):
        f = lambda i, j: self.kernel_f(A[i], B[j])
        return np.fromfunction(np.vectorize(f), (A.shape[0], B.shape[0]), dtype=int)
    
    def get_random_j(self, i):
        res = np.random.randint(0, self.N - 1);
        return res if res < i else res + 1
    
    def calc_U_V(self, i, j):
        a_i, a_j = self.alphas[i], self.alphas[j]
        if self.y[i] == self.y[j]:
            U = max(0, a_i + a_j - self.C)
            V = min(self.C, a_i + a_j)
        else:
            U = max(0, a_j - a_i)
            V = min(self.C, self.C + a_j - a_i)
        return U, V
    
    def calc_E(self, i):
        return np.dot(self.alphas * self.y, self.kernel[i]) - self.y[i]
    
    def get_b(self, i):
        return 1 / self.y[i] - np.dot(self.alphas * self.y, self.kernel[i])
    
    def calc_b(self):
        self.b = 0
        idx = None
        for i in range(self.N):
            if self.eps < self.alphas[i] and self.alphas[i] + self.eps < self.C:
                idx = i
                break
        if idx is None:
            cnt = 0
            for i in range(self.N):
                if self.eps < self.alphas[i]:
                    self.b += self.get_b(i)
                    cnt += 1
            if cnt != 0:
                self.b /= cnt
        else:
            self.b = self.get_b(idx)
            
    def fit(self, X, y):
        X, y = check_X_y(X, y)
        
        self.kernel = self.calc_kernel_matrix(X, X)
        self.X = X
        self.y = y
        self.N = len(y)
        self.alphas = np.zeros(self.N)
        self.b = 0
        
        indices = np.arange(self.N)
        for _ in range(self.max_iter):
            np.random.shuffle(indices)
            for i_fake in range(self.N):
                i = indices[i_fake]
                j = indices[self.get_random_j(i_fake)]
                E_i = self.calc_E(i)
                E_j = self.calc_E(j)
                prev_a_i = self.alphas[i]
                prev_a_j = self.alphas[j]
                U, V = self.calc_U_V(i, j)
                if V - U < self.eps:
                    continue
                eta = 2 * self.kernel[i][j] - (self.kernel[i][i] + self.kernel[j][j])
                if eta > -self.eps:
                    continue
                possible_new_a_j = prev_a_j + self.y[j] * (E_j - E_i) / eta
                new_a_j = min(max(U, possible_new_a_j), V)
                if abs(new_a_j - prev_a_j) < self.eps:
                    continue
                self.alphas[j] = new_a_j
                self.alphas[i] += self.y[i] * self.y[j] * (prev_a_j - new_a_j)
        self.calc_b()
        return self
