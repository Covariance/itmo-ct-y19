import java.util.Scanner;

public class B {
    public static void main(String[] args) {
        new B().run();
    }

    public void run() {
        Scanner sc = new Scanner(System.in);
        int stPoint = -710 * 25000, n = sc.nextInt();
        for (int i = 0; i < n; i++) {
            System.out.println(stPoint);
            stPoint += 710;
        }
    }
}
