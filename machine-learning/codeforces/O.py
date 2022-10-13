from typing import Dict, Tuple
from itertools import product

if __name__ == '__main__':
    k1, k2 = list(map(int, input().split()))
    n = int(input())
    
    objects: Dict[Tuple[int, int], int] = {}
    c1, c2 = [0] * k1, [0] * k2
    
    for _ in range(n):
        x1, x2 = list(map(int, input().split()))
        x1, x2 = x1 - 1, x2 - 1
        objects[(x1, x2)] = objects.get((x1, x2), 0) + 1
        c1[x1] += 1
        c2[x2] += 1
        
    total = .0
    diff = .0
    
    for (i, j), count in objects.items():
        clc = c1[i] * c2[j] / n
        total += (count - clc) ** 2 / clc
        diff += clc
    
    total += n - diff   
    
    print(total)
    