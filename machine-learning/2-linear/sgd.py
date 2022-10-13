import numpy as np
from typing import Optional, Callable, List

# region loss
def mse_loss(y_true: np.ndarray, y_pred: np.ndarray) -> float:
    return ((y_true - y_pred) ** 2).sum()

def smape_loss(y_true: np.ndarray, y_pred: np.ndarray) -> float:
    return (np.abs(y_true - y_pred) / (np.abs(y_true) + np.abs(y_pred))).sum()

def mse_grad(X: np.ndarray, w: np.ndarray, y_true: np.ndarray, y_pred: np.ndarray) -> np.ndarray:
    return 2 * X.T.dot(y_true - y_pred)

def smape_grad(X: np.ndarray, w: np.ndarray, y_true: np.ndarray, y_pred: np.ndarray) -> np.ndarray:
    dif = y_true - y_pred
    sabs = np.abs(y_true) + np.abs(y_pred)
    
    fi = (-np.sign(y_pred) * np.abs(dif) - np.sign(dif) * sabs) / (sabs ** 2)
    
    result = np.zeros(w.shape[0])
    
    for i, row in enumerate(X):
        for j, item in enumerate(row * fi[i]):
            result[j] += item
            
    return result / y_true.shape[0]
# endregion

# region regularizations
def noreg(w: np.ndarray) -> np.ndarray:
    return np.zeros(w.shape)

def lasso(tau: float) -> Callable[[np.ndarray], np.ndarray]:
    def lasso_reg(w: np.ndarray) -> np.ndarray:
        return tau * np.sign(w)
    
    return lasso_reg

def ridge(tau: float) -> Callable[[np.ndarray], np.ndarray]:
    def ridge_reg(w: np.ndarray) -> np.ndarray:
        return tau * 2 * w
    
    return ridge_reg

def elastic_net(tau_lasso: float, tau_ridge: float) -> Callable[[np.ndarray], np.ndarray]:
    def elastic_net_reg(w: np.ndarray) -> np.ndarray:
        return tau_lasso * np.sign(w) + tau_ridge * 2 * w
    
    return elastic_net_reg
# endregion


class SGDRegressor:
    def __init__(self,
                 learning_rate: float = 0.001,   # Gradient multiplier
                 fading: float = 1,              # Fading of gradient
                 cond: Optional[float] = None,   # Terminal condition
                 fit_intercept: bool = True,     # Do we add bias
                 max_iter: int = 1000,           # Maximum number of iterations
                 loss: str = 'MSE',              # Loss that we use, can be 'MSE' or 'SMAPE'
                 reg: Optional[str] = None,      # Regularization, can be None, 'Lasso', 'Ridge' or 'ElasticNet'
                 lasso_tau: float = 0.,          # Regularization parameter for lasso
                 ridge_tau: float = 0.,          # Regularization parameter for ridge 
                 shuffle: bool = False,          # Do we shuffle data before each iter
                 batch_size: int = 50,           # Size of batch
                ):
        self.learning_rate_ = learning_rate
        self.fading_ = fading
        self.cond_ = cond
        self.fit_intercept_ = fit_intercept
        self.max_iter_ = max_iter
        self.loss_ = loss
        self.reg_ = reg
        self.lasso_tau_ = lasso_tau
        self.ridge_tau_ = ridge_tau
        self.shuffle_ = shuffle
        self.batch_size_ = batch_size
    

    @property
    def loss_function_(self) -> Callable[[np.ndarray, np.ndarray], float]:
        if self.loss_ == 'SMAPE':
            return smape_loss
        else: # Assuming MSE
            return mse_loss
    
    @property
    def grad_function_(self) -> Callable[[np.ndarray, np.ndarray, np.ndarray, np.ndarray], np.ndarray]:
        if self.loss_ == 'SMAPE':
            return smape_grad
        else: # Assuming MSE
            return mse_grad
    
    @property
    def reg_function_(self) -> Callable[[np.ndarray], np.ndarray]:
        if self.reg_ is None:
            return noreg
        elif self.reg_ == 'Lasso':
            return lasso(self.lasso_tau_)
        elif self.reg_ == 'ElasticNet':
            return elastic_net(self.lasso_tau_, self.ridge_tau_)
        else: # Assuming Ridge
            return ridge(self.ridge_tau_)
    
    def fit(self, X: np.ndarray, y: np.ndarray):
        learning_rate = self.learning_rate_
        
        if self.fit_intercept_:
            X = np.hstack((X, np.ones((X.shape[0], 1))))
        
        n = X.shape[0]
        w = np.random.uniform(low = -.5 / X.shape[1], high = .5 / X.shape[1], size=X.shape[1])
        
        self.epoch_loss_: List[float] = []
        
        for _ in range(self.max_iter_):
            # Shuffle data if needed
            if self.shuffle_:
                permutation = np.random.permutation(n)
                X, y = X[p], y[p]
            
            left_border = 0
            while left_border < n:
                # Take batch
                right_border = n if left_border + self.batch_size_ >= n else left_border + self.batch_size_
                X_batch = X[left_border:right_border]
                y_batch = y[left_border:right_border]
                
                # Calculate predictions
                y_pred = X_batch.dot(w)
                
                # Calculate gradient
                grad = self.grad_function_(X_batch, w, y_pred, y_batch)
                
                # Update weights
                w -= learning_rate * (grad + self.reg_function_(w))
                
                # Move batch
                left_border += self.batch_size_

            # Calculate epoch loss and break if needed
            loss = self.loss_function_(y, X.dot(w))
            if self.cond_ is not None and len(self.epoch_loss_) > 0 and np.abs(loss - self.epoch_loss_[-1]) < self.cond_:
                break
            self.epoch_loss_.append(loss)
            
            # Fade learning rate
            learning_rate *= self.fading_

        self.coef_ = w[:-1] if self.fit_intercept_ else w
        self.intercept_ = w[-1] if self.fit_intercept_ else 0.
        
        return self
    
    def predict(self, X: np.ndarray) -> np.ndarray:
        return X.dot(self.coef_) + self.intercept_
