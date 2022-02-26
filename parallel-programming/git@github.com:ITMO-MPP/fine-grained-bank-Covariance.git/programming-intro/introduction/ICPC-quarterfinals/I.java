import java.util.Scanner;

import static java.lang.Math.max;
import static java.lang.Math.min;

public class I {
    final int INF = 1_000_000_000;
    int x1, y1;
    int x2, y2;
    int n;
    int[] ox;
    int[] oy;
    int[] oh;

    public static void main(String[] args) {
        new I().run();
    }

    public boolean checkHeight(int h) {
        x1 = -INF;
        y1 = -INF;
        x2 = INF;
        y2 = INF;
        for (int i = 0; i < n; i++) {
            int dif = h - oh[i];
            x1 = max(x1, ox[i] - dif);
            y1 = max(y1, oy[i] - dif);
            x2 = min(x2, ox[i] + dif);
            y2 = min(y2, oy[i] + dif);
        }
        return (x1 <= x2) && (y1 <= y2);
    }

    public void read() {
        Scanner scan = new Scanner(System.in);
        n = scan.nextInt();
        ox = new int[n];
        oy = new int[n];
        oh = new int[n];
        for (int i = 0; i < n; i++) {
            ox[i] = scan.nextInt();
            oy[i] = scan.nextInt();
            oh[i] = scan.nextInt();
        }
    }

    public void run() {
        read();
        int l = 0, r = 2*INF;
        while (l < r) {
            int m = l + (r - l) / 2;
            if (!checkHeight(m)) {
                l = m + 1;
            } else {
                r = m;
            }
        }
        checkHeight(l);
        System.out.println(Integer.toString(x1) + " " + Integer.toString(y1) + " " + Integer.toString(l));
    }
}
