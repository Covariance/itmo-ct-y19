import java.util.*;

import static java.lang.Math.max;

public class H {
    public static void main(String[] args) {
        new H().run();
    }

    public void run() {
        int n, m;
        Scanner scan = new Scanner(System.in);
        n = scan.nextInt();
        int p[] = new int[n];
        int mx = 0;
        for (int i = 0; i < n; i++) {
            p[i] = scan.nextInt();
            mx = max(mx, p[i]);
            if (i > 0) p[i] += p[i - 1];
        }
        Map<Integer, Integer> mem = new LinkedHashMap<Integer, Integer>();
        m = scan.nextInt();
        for (int i = 0; i < m; i++) {
            int t = scan.nextInt();
            if (t < mx) {
                System.out.println("Impossible");
                continue;
            }
            if (mem.containsKey(t)) {
                System.out.println(mem.get(t));
                continue;
            }
            int cur_ans = 0;
            for (int pos = 0; pos < n; cur_ans++) {
                int l = pos, r = n;
                int p_sum = (pos > 0 ? p[pos - 1] : 0);
                while (l < r) {
                    int mid = l + (r - l) / 2;
                    if (p[mid] - p_sum <= t) {
                        l = mid + 1;
                    } else {
                        r = mid;
                    }
                }
                pos = l;
            }
            mem.put(t, cur_ans);
            System.out.println(cur_ans);
        }
    }


}
