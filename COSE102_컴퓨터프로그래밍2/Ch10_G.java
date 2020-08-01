import java.util.Scanner;
import java.math.*;

public class Ch10_G {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        BigInteger A = sc.nextBigInteger();
        while(true) {
            A = A.add(BigInteger.ONE);
            if((A.remainder(new BigInteger("100019"))).compareTo(BigInteger.ZERO) == 0) {
                break;
            }
        }
        System.out.print(A);
    }
}
