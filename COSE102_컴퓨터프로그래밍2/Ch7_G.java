import java.util.Scanner;

public class Ch7_G {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int T = sc.nextInt();

        for(int i = 0; i < T; i++) {
            //input : the number of students, the number of locker to check

            int students = sc.nextInt();
            int check = sc.nextInt();
            int open = 0;

            for(int j = 1; j <= students; j++) {
                if (check >= j && check % j == 0) {
                    if (open == 0) { open = 1; }
                    else { open = 0; }
                }
            }

            if (open == 1) { System.out.println("open"); }
            else { System.out.println("close"); }
        }
    }
}
