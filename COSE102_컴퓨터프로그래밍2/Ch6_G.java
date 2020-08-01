import java.util.Scanner;

public class Ch6_G {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int T = sc.nextInt(), i = 0;
        while(i < T) {
            long N = sc.nextLong();
            if(LuhnCheck(N)) { System.out.println("Valid"); }
            else { System.out.println("Invalid"); }
            i++;
        }
    }

    private static boolean LuhnCheck(long N) {
        String to = Long.toString(N);
        if(13 <= to.length() && to.length() <= 16) {
            char start = to.charAt(0);
            if (start == '4' || start == '5' || start == '6' || "37".equals(to.substring(0, 2))) {
                int i = 1, OddSum = 0, EvenSum = 0;
                //step 1 ~ 3
                while (N > 0) {
                    if (i % 2 == 1) {
                        OddSum += N % 10;
                    } else {
                        int t = (int) (N % 10) * 2;
                        if (t >= 10) {
                            EvenSum += t % 10 + 1;
                        } else {
                            EvenSum += t;
                        }
                    }
                    N /= 10;
                    i++;
                }
                //step 4
                int sum = OddSum + EvenSum;

                //step 5
                if (sum % 10 == 0) {
                    return true;
                } else {
                    return false;
                }
            }
            else { return false; }
        }
        else { return false; }
    }
}
