import java.util.Scanner;

public class Ch6_B {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int T = sc.nextInt(), n = 0;
        sc.nextLine();
        while(n < T) {
            printReverse(sc.nextLine());
            n++;
        }
    }

    private static void printReverse(String s) {
        int i = s.length() - 1;
        for(; i >= 0; i--) {
            System.out.print(s.charAt(i));
        }
        System.out.println();
    }
}
