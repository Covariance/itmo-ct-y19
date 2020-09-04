import java.util.Scanner;

public class Ilab {
    String[] res;
    int n, m;

    public static void main(String[] args) {
        new Ilab().run();
    }

    private void put(int ind, int a, int b, int c) {
        res[ind] = a + " " + b + " " + c;
    }

    private void generate1() {
        put(0, 1, 1, 2);
        for (int i = 1; i < res.length; i++) {
            put(i, 0, 2, 2);
        }
    }

    private void generate2() {
        for (int i = 0; i < 8; i++) {
            put(i, 1, 1, i + 2);
        }
        int boss = 10, crook = 1;
        for (int i = 8; i < res.length - 5; i++) {
            put(i++, 0, 2, 3);
            put(i++, 0, 4, 5);
            put(i++, 0, 6, 7);
            put(i++, 0, 8, 9);
            put(i, 1, boss, crook);
            crook = boss++;
        }
    }

    private void run() {
        Scanner scan = new Scanner(System.in);
        n = scan.nextInt();
        m = scan.nextInt();
        res = new String[100005];
        if (m < 128) {
            generate1();
        } else {
            generate2();
        }
        for (int i = 0; i < m; i++) {
            System.out.println(res[i]);
        }
        return;
    }
}
