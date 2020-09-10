import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.StringTokenizer;

public class E {
    int g[][];
    int len[];
    int c[];
    int d[];
    int p[];
    int n, m;

    public static void main(String[] args) throws IOException {
        new E().run();
    }

    public void dfs(int v, int parent) {
        if (parent != -1) {
            d[v] = d[parent] + 1;
        }
        p[v] = parent;
        for (int i = 0; i < len[v]; i++) {
            if (g[v][i] != parent) {
                dfs(g[v][i], v);
            }
        }
    }

    public void setup() throws IOException {
        BufferedReader scan = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer str = new StringTokenizer(scan.readLine());
        n = Integer.parseInt(str.nextToken());
        m = Integer.parseInt(str.nextToken());
        g = new int[n][];
        d = new int[n];
        len = new int[n];
        p = new int[n];
        c = new int[m];
        for (int i = 0; i < n; i++) {
            g[i] = new int[1];
            len[i] = 0;
        }
        for (int i = 0; i < n - 1; i++) {
            str = new StringTokenizer(scan.readLine());
            int v = Integer.parseInt(str.nextToken()) - 1, u = Integer.parseInt(str.nextToken()) - 1;
            if (len[v] == g[v].length) {
                g[v] = Arrays.copyOf(g[v], 2 * g[v].length);
            }
            if (len[u] == g[u].length) {
                g[u] = Arrays.copyOf(g[u], 2 * g[u].length);
            }
            g[v][len[v]++] = u;
            g[u][len[u]++] = v;
        }
        str = new StringTokenizer(scan.readLine());
        for (int i = 0; i < m; i++) {
            c[i] = Integer.parseInt(str.nextToken()) - 1;
        }
        d[c[0]] = 0;
        dfs(c[0], -1);
    }

    int findMid() {
        int far = c[0];
        for (int i = 0; i < m; i++) {
            if (d[far] < d[c[i]]) {
                far = c[i];
            }
        }
        int dist = d[far];
        if (dist % 2 == 1) {
            return -1;
        }
        for (int i = 0; i < dist / 2; i++) {
            far = p[far];
        }
        return far;
    }

    public int run() throws IOException {
        setup();
        if (m == 1) {
            System.out.println("YES");
            System.out.println(c[0] + 1);
            return 0;
        }
        int root = findMid();
        if (root == -1) {
            System.out.println("NO");
            return 0;
        }
        d[root] = 0;
        dfs(root, -1);
        int dst = d[c[0]];
        for (int i = 0; i < m; i++) {
            if (d[c[i]] != dst) {
                System.out.println("NO");
                return 0;
            }
        }
        System.out.println("YES");
        System.out.println(root + 1);
        return 0;
    }
}
