import java.util.Scanner;

public class Ch6_F {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int T = sc.nextInt(), i = 0;
        while (i < T) {
            System.out.println(Twin_Primes(sc.nextInt()));
            i++;
        }
    }

    private static int Twin_Primes(int M) {
        int i = 2, j = 2, count = 0;
        for(; i <= M - 2; i++) {
            if(isPrime(i)) {
                if(isPrime(i + 2)) {
                    count++;
                }
            }
        }
        return count;
    }

    private static boolean isPrime(int N) {
        for (int j = 2; (double) j <= Math.sqrt((double)N); j++) {
            if (N % j == 0) {
                return false;
            }
        }
        return true;
    }
}