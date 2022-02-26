import java.util.Scanner;

public class A {

    static public void main(String[] args) throws Exception {
        new A().run();
    }

    public void run() throws Exception {
        Scanner sc = new Scanner(System.in);

        int a = sc.nextInt();
        int b = sc.nextInt();
        int n = sc.nextInt();
        System.out.println(((n - b + (b - a - 1)) / (b - a)) * 2 + 1);
    }
}