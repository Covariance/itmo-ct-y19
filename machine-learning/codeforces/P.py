import math
from typing import Dict, Tuple

if __name__ == '__main__':
    kx, ky = list(map(int, input().split()))
    n = int(input())
    
    x, y = zip(*[list(map(int, input().split())) for _ in range(n)])

    xs: Dict[int, float] = {}
    xys: Dict[Tuple[int, int], float] = {}

    for i in range(n):
        xs[x[i]] = xs.get(x[i], 0) + 1 / n
        xys[(x[i], y[i])] = xys.get((x[i], y[i]), 0) + 1 / n
        
    def mapping(input):
        (x, y), val = input
        return -val * (math.log(val) - math.log(xs[x]))
    
    print(sum(map(mapping, xys.items())))
