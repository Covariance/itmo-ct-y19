import java.util.Scanner;

import static java.lang.Math.sqrt;

public class D {
    final int mod = 998_244_353;
    public long[] d;
    public long[] pw;
    int k;

    public static void main(String[] args) {
        new D().run();
    }

    public int r(int n) {
        return (int)((n % 2 == 0 ? (long) (n / 2) * pw[n / 2] * (k + 1) : (long) n * pw[(n + 1) / 2]) % mod);
    }

    public void setup(int n) {
        d = new long[n];
        pw = new long[n];
        pw[0] = 1;
        pw[1] = k;
        d[1] = k;

        for (int i = 2; i < n; i++) {
            pw[i] = (pw[i - 1] * k) % mod;
            d[i] = r(i);
            d[i] -= d[1] * i;
            if (i % sqrt(i) == 0) {
                d[i] -= d[(int)sqrt(i)] * sqrt(i);
            }
            d[i] %= mod;
            for (int j = 2; j < sqrt(i); j++) {
                if (i % j == 0) {
                    d[i] = (d[i] - (i/j) * d[j] - (j) * d[i/j]) % mod;
                    if (d[i] < 0) {
                        d[i] -= mod*(d[i]/mod);
                        d[i] += mod;
                    }
                }
            }
        }
    }

    public void run() {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        k = sc.nextInt();
        setup(n + 1);
        long ans = 0;
        for (int i = 1; i <= n; i++) {
            if (i % sqrt(i) == 0) {
                ans = (ans + d[(int) sqrt(i)]);
            }
            for (int j = 1; j < sqrt(i); j++) {
                if (i % j == 0) {
                    ans = (ans + d[j] + d[i / j]);
                }
            }
            ans %= mod;
        }
        System.out.println(ans);
    }
}
