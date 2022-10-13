from typing import Tuple, Callable, Union
 
import numpy as np
 
 
def read_data(reader: Callable[[], str] = input, add_bias: bool = False) -> Tuple[np.ndarray, np.ndarray]:
    n, m = list(map(int, reader().rstrip().split()))
    
    features = []
    labels = []
    
    for _ in range(n):
        lst = list(map(float, reader().rstrip().split()))
        
        labels.append(lst[-1])
        features.append(lst[:-1] if not add_bias else lst[:-1] + [1])
        
    return np.array(features), np.array(labels)
 
 
def read_xs(reader: Callable[[], str] = input) -> Tuple[np.ndarray]:
    return np.array(list(map(float, reader().rstrip().split())))
 
 
def smape_grad_f(pred: Union[np.ndarray, float], true: Union[np.ndarray, float]):
    dif = true - pred
    sabs = np.abs(true) + np.abs(pred)
    return (-np.sign(pred) * np.abs(dif) - np.sign(dif) * sabs) / (sabs ** 2)
 
 
if __name__ == '__main__':
    ft, lb = read_data(add_bias = True)
    
    cf = read_xs()
    
    fi = smape_grad_f(ft.dot(cf), lb)
    
    for i, row in enumerate(ft):
        for item in (row * fi[i]):
            print(item, end=' ')
        print()
