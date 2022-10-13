import numpy as np

def f1_score(prc: float, rec: float) -> float:
    if prc + rec < 1e-9:
        return 0
    return 2 * (prc * rec) / (prc + rec)


if __name__ == '__main__':
    k = int(input())
    cm = np.array([list(map(int, input().split())) for _ in range(k)])
    
    szs = np.array([cm[i].sum() for i in range(k)])
    total = szs.sum()
    
    tp = np.array([cm[i][i] for i in range(k)])
    fp = np.array([cm[:, i].sum() for i in range(k)]) - tp
    fn = np.array([cm[i].sum() for i in range(k)]) - tp
    
    # micro
    micro_tp = np.average(tp, weights=szs)
    micro_fp = np.average(fp, weights=szs)
    micro_fn = np.average(fn, weights=szs)
    
    micro_prc = micro_tp / (micro_tp + micro_fp) if micro_tp > 0 else 0
    micro_rec = micro_tp / (micro_tp + micro_fn) if micro_tp > 0 else 0
    
    micro_f1 = f1_score(micro_prc, micro_rec)
    
    
    prc = np.array([tp[i] / (tp[i] + fp[i]) if tp[i] > 0 else 0 for i in range(k)])
    rec = np.array([tp[i] / (tp[i] + fn[i]) if tp[i] > 0 else 0 for i in range(k)])
    
    
    # macro
    macro_prc = np.average(prc, weights=szs)
    macro_rec = np.average(rec, weights=szs)
    
    macro_f1 = f1_score(macro_prc, macro_rec)
    
    
    # usual
    f1s = np.array([f1_score(prc[i], rec[i]) for i in range(k)])
    
    usual_f1 = np.average(f1s, weights=szs)
    
    # output
    print(f'{micro_f1:.10f}')
    print(f'{macro_f1:.10f}')
    print(f'{usual_f1:.10f}')
