import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class M {
    public static void main(String[] args) {
        new M().run();
    }

    public void run() {
        Scanner scan = new Scanner(System.in);
        int t = scan.nextInt();
        for (int i = 0; i < t; i++) {
            System.out.println(runTest(scan));
        }
    }

    public int runTest(Scanner scan) {
        int ans = 0;
        int n = scan.nextInt();
        int[] a = new int[n];
        for (int i = 0; i < n; i++) a[i] = scan.nextInt();
        Map<Integer, Integer> mp = new HashMap<Integer, Integer>();
        for (int j = 0; j < n; j++) {
            for (int k = j + 1; k < n; k++) {
                int l = 2 * a[j] - a[k];
                if (mp.containsKey(l)) ans += mp.get(l);
            }
            if (!mp.containsKey(a[j])) mp.put(a[j], 0);
            mp.replace(a[j], mp.get(a[j]) + 1);
        }
        return ans;
    }
}
