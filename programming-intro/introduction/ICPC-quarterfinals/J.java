import java.util.Scanner;

public class J {
    final int M = 1010, N = (int) (2e5 + 10);

    int n, a[][] = new int[M][M], b[][] = new int[M][M];

    public static void main(String[] args) {
        new J().run();
    }

    public void run() {
        Scanner scan = new Scanner(System.in);
        int n = scan.nextInt();
        scan.nextLine();
        for (int i = 0; i < n; i++) {
            Scanner tmpScan = new Scanner(scan.nextLine());
            tmpScan.useDelimiter("");
            for (int j = 0; j < n; j++) {
                a[i][j] = tmpScan.next().codePointAt(0) - 48;
            }
        }
        for (int i = n - 1; i >= 0; i--) {
            for (int j = i + 1; j < n; j++) {
                int s = 0;
                for (int k = i + 1; k < j; k++) {
                    s = (s + b[i][k] * a[k][j]) % 10;
                }
                b[i][j] = (s != a[i][j]) ? 1 : 0;
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                System.out.print(b[i][j]);
            }
            System.out.println();
        }

    }
}
