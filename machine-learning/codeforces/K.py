import numpy as np

if __name__ == '__main__':
    first, second = zip(*[list(map(int, input().split())) for _ in range(int(input()))])
    first_np, second_np = np.array(first), np.array(second)
    
    fd, sd = np.var(first_np), np.var(second_np)
    
    if np.abs(fd) < 1e-5 or np.abs(sd) < 1e-5:
        result = .0
    else:
        result = ((first_np - first_np.mean()) * (second_np - second_np.mean())).mean() / np.sqrt(fd * sd)
    
    print(f'{result:.10f}')
    