import java.util.*;

public class Ch10_A {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int T = sc.nextInt();

        for(int i = T; i > 0; i--) {
            int n = sc.nextInt();
            int[] primes = new int[n];
            int count = 0;
            for(int j = 2; j <= n; j++) {
                if(n % j == 0) {
                    n /= j;
                    primes[count++] = j;
                    j--;
                }
            }
            for(int j = count - 1; j > 0; j--) {
                System.out.print(primes[j] + " ");
            }
            System.out.println(primes[0]);
        }
    }
}
