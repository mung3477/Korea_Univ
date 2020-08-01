import java.util.Scanner;

public class Ch6_C {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int T = sc.nextInt(), n = 0;
        sc.nextLine();
        while(n < T) {
            CheckPassword(sc.nextLine());
            n++;
        }
    }

    private static void CheckPassword(String s) {
        if(s.length() < 8) {
            System.out.println("Invalid");
            return;
        }
        else{
            int numbers = 0;
            for(int i = 0; i < s.length(); i++) {
                char c = s.charAt(i);
                if(('0' <= c && c <= '9') || ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z')) {
                    if('0' <= c && c <= '9') { numbers++; }
                }
                else {
                    System.out.println("Invalid");
                    return;
                }
            }
            if(numbers < 2) {
                System.out.println("Invalid");
                return;
            }
            else { System.out.println("Valid"); }
        }
    }
}
