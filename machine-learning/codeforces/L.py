from typing import Tuple
import numpy as np
from scipy.stats import spearmanr

# function that calculates the rank of each element in the array with tied ranks
def find_rank(arr: np.ndarray) -> np.ndarray:
    order = arr.argsort()
    arrc = arr.copy()[order]

    ranks = np.zeros(arr.shape, dtype=np.float64)
    
    i = 0
    rank = 1
    while i < arr.shape[0]:
        cur = arrc[i]
        start = i
        
        while i < arr.shape[0] and arrc[i] == cur:
            i += 1

        new_rank = rank + (i - start)
        
        for j in range(start, i):
            ranks[j] = (rank + new_rank - 1) / 2
        
        rank = new_rank
        
    return ranks[order.argsort()]

def pearson(first_np: np.ndarray, second_np: np.ndarray) -> float:
    # I've already written pearson, so here goes the library implementation
    return np.corrcoef(first_np, second_np)[0, 1]

def spearman(first_np: np.ndarray, second_np: np.ndarray) -> float:
    n = first_np.shape[0]
    
    if n == 1:
        return 1.0
    
    f_rank, s_rank = find_rank(first_np), find_rank(second_np)
    
    return pearson(f_rank, s_rank)

# some stress testing here
def stress() -> None:
    def gen(size: int = 5, mx: int = 100) -> Tuple[np.ndarray, np.ndarray]:
        return np.random.randint(0, mx, size), np.random.randint(0, mx, size)
    
    for _ in range(1_000_000):
        first, second = gen()
        true, _ = spearmanr(first, second)
        pred = spearman(first, second)
        assert abs(true - pred) < 1e-6, f'{true} != {pred}\n\n{first}\n\n{second}'

if __name__ == '__main__':
    first, second = zip(*[list(map(int, input().split())) for _ in range(int(input()))])
    first_np, second_np = np.array(first), np.array(second)
    
    result = spearman(first_np, second_np)

    print(f'{result:.10f}')
