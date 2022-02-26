import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.math.BigInteger;
import java.util.Scanner;

public class Q {
    private final boolean debug = false;

    public static void main(String[] args) throws IOException {
        new Q().run();
    }

    private int m, len, mod;
    private BigInteger n;
    private int[][] matrix;

    private boolean transAble(int a, int b) {
        for (int i = 0; i < m - 1; i++) {
            if ((a & (1 << i)) == (b & (1 << i)) && (a & (2 << i)) == (b & (2 << i)) && (a & (1 << i)) == (a & (2 << i)) / 2) {
                return false;
            }
        }
        return true;
    }

    private int[][] buildMatrix() {
        int[][] result = new int[len][len];
        for (int i = 0; i < len; i++) {
            for (int j = i; j < len; j++) {
                result[i][j] = (transAble(i, j)) ? 1 : 0;
                result[j][i] = result[i][j];
            }
        }
        return result;
    }

    private int[][] matrixMul(int[][] a, int[][] b) {
        int[][] retv = new int[len][len];
        for (int i = 0; i < len; i++) {
            for (int j = 0; j < len; j++) {
                retv[i][j] = 0;
                for (int k = 0; k < len; k++) {
                    retv[i][j] = (retv[i][j] + a[i][k] * b[k][j]) % mod;
                }
            }
        }
        return retv;
    }

    private int[][] binPow(BigInteger times) {
        if (times.equals(BigInteger.ZERO)) {
            int[][] ans = new int[len][len];
            for (int i = 0; i < len; i++) {
                for (int j = 0; j < len; j++) {
                    if (i == j) {
                        ans[i][j] = 1;
                    } else {
                        ans[i][j] = 0;
                    }
                }
            }
            return ans;
        } else {
            int[][] ans = binPow(times.divide(BigInteger.valueOf(2)));
            ans = matrixMul(ans, ans);
            if (times.mod(BigInteger.valueOf(2)).equals(BigInteger.ONE)) {
                ans = matrixMul(ans, matrix);
            }
            return ans;
        }
    }

    private void debugPrint() {
        if (debug) {
            for (int i = 0; i < len; i++) {
                for (int j = 0; j < len; j++) {
                    System.out.print(matrix[i][j] + " ");
                }
                System.out.println();
            }
        }
    }

    private void run() throws IOException {
        Scanner scan = (debug) ? new Scanner(System.in) : new Scanner(new File("nice3.in"));
        n = scan.nextBigInteger();
        m = scan.nextInt();
        mod = scan.nextInt();
        len = 1 << m;
        matrix = buildMatrix();
        debugPrint();
        int[][] result = binPow(n.subtract(BigInteger.ONE));
        debugPrint();
        int retv = 0;
        for (int i = 0; i < len; i++) {
            for (int j = 0; j < len; j++) {
                retv = (retv + result[i][j]) % mod;
            }
        }
        if (debug) {
            System.out.println(retv);
        } else {
            FileWriter out = new FileWriter(new File("nice3.out"));
            out.write(Integer.toString(retv));
            out.close();
        }
    }
}
