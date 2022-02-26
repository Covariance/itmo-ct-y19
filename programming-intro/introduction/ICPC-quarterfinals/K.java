import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.StringTokenizer;

public class K {
    public static void main(String[] args) throws IOException {
        new K().run();
    }

    final int M = 1010;
    int n, m, x, y, s[][] = new int[M][M];
    char c[][] = new char[M][M];

    public int sum(int x1, int y1, int x2, int y2) {
        return (s[x2][y2] - s[x1 - 1][y2] - s[x2][y1 - 1]) + s[x1 - 1][y1 - 1];
    }

    public void fill(int x1, int y1, int x2, int y2) {
        StringBuilder s = new StringBuilder("");
        boolean f = false;
        for (int i = x1; i <= x2; i++) {
            char t = '.';
            for (int j = y1; j <= y2; j++) {
                if (c[i][j] != '.') {
                    t = c[i][j];
                    break;
                }
            }
            if (t == '.') {
                if (f) {
                    for (int j = y1; j <= y2; j++) {
                        c[i][j] = s.charAt(j - y1);
                    }
                }
            } else {
                s = new StringBuilder("");
                for (int j = y1; j <= y2; j++) {
                    if (c[i][j] == '.') {
                        c[i][j] = (char) ((int) t - (int) 'A' + (int)'a');
                    } else {
                        t = c[i][j];
                    }
                    if (c[i][j] >= 'A' && c[i][j] <= 'Z') {
                        s.append((char)((int)c[i][j] - (int)'A' + (int)'a'));
                    } else {
                        s.append(c[i][j]);
                    }
                }
                if (!f) {
                    for (int k = x1; k < i; k++) {
                        for (int j = y1; j <= y2; j++) {
                            c[k][j] = s.charAt(j - y1);
                        }
                    }
                    f = true;
                }
            }
        }
    }

    public void run() throws IOException {
        BufferedReader scan = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer str = new StringTokenizer(scan.readLine());
        int n = Integer.parseInt(str.nextToken()), m = Integer.parseInt(str.nextToken());
        for (int i = 1; i <= n; i++) {
            String ss = scan.readLine();
            for (int j = 1; j <= m; j++) {
                c[i][j] = ss.charAt(j - 1);
                if (c[i][j] == 'A') {
                    x = i;
                    y = j;
                }
                s[i][j] = s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1] + ((c[i][j] != '.') ? 1 : 0);
            }
        }
        int lx = x, rx = x, ly = y, ry = y;
        for (int li = 1; li <= x; li++) {
            for (int ri = x; ri <= n; ri++) {
                if (sum(li, y, ri, y) != 1) {
                    break;
                }
                int l = 0, r = y;
                while (l + 1 < r) {
                    int mm = (l + r) / 2;
                    if (sum(li, mm, ri, y) == 1) {
                        r = mm;
                    } else {
                        l = mm;
                    }
                }
                int lj = r;
                l = y;
                r = m + 1;
                while (l + 1 < r) {
                    int mm = (l + r) / 2;
                    if (sum(li, y, ri, mm) == 1) {
                        l = mm;
                    } else {
                        r = mm;
                    }
                }
                int rj = l;
                if ((ri - li + 1) * (rj - lj + 1) > (rx - lx + 1) * (ry - ly + 1)) {
                    lx = li;
                    rx = ri;
                    ly = lj;
                    ry = rj;
                }
            }
        }
        for (int i = lx; i <= rx; i++) {
            for (int j = ly; j <= ry; j++) {
                if (c[i][j] == '.') {
                    c[i][j] = 'a';
                }
            }
        }
        fill(1, 1, lx - 1, m);
        fill(lx, 1, rx, ly - 1);
        fill(lx, ry + 1, rx, m);
        fill(rx + 1, 1, n, m);
        PrintWriter out = new PrintWriter(System.out);
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                out.print(c[i][j]);
            }
            out.println();;
        }
        out.close();
    }

}
