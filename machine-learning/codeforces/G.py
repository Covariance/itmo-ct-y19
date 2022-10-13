def bit_count(x: int):
    res = 0
    while x > 0:
        res += 1
        x = x & (x - 1)
        
    return res

if __name__ == '__main__':
    m = int(input())
    
    print(2)
    print(1 << m, 1)
    
    for mask in range(1 << m):
        for pos in range(m):
            if mask & (1 << pos) != 0:
                print('1.0', end=' ')
            else:
                print('-228228228.0', end=' ')
        
        print(.5 - bit_count(mask))
        
    for _ in range(1 << m):
        print(f'{input()}.0', end=' ')

    print('-0.5')
