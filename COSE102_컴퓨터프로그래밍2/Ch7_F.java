import java.util.Scanner;

public class Ch7_F {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int T = sc.nextInt();

        for(int i = 0; i < T; i++) {
            int check = sc.nextInt();
            int open = 0;

            for(int j = 1; j <= 100; j++) {
                if (check % j == 0) {
                    if (open == 0) { open = 1; }
                    else { open = 0; }
                }
            }

            if (open == 1) { System.out.println("open"); }
            else { System.out.println("close"); }
        }
    }
}
