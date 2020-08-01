import java.util.Scanner;

public class Ch6_E {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int T = sc.nextInt(), i = 0;
        while(i < T) {
            int M = sc.nextInt();
            System.out.println(PalindromicPrime(M));
            i++;
        }
    }

    private static int PalindromicPrime(int M) {
        int count = 0;
        for(int i = 2; i <= M; i++) {
            int t = i;
            int reversed_i = 0;
            while(t > 0) {
                reversed_i = reversed_i * 10 + t % 10;
                t /= 10;
            }

            if(reversed_i != i) { continue; }
            else {
                int j = 2;
                for(; (double)j <= Math.sqrt((double)i); j++) {
                    if(i % j == 0) { break; }
                }
                if((double)j > Math.sqrt((double)i)) { count++; }
            }
        }
        return count;
    }
}