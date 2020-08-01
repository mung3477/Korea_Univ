import java.util.*;

public class Ch9_C {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int T = sc.nextInt();

        for(; T > 0; T--) {
            Date date = new Date(sc.nextLong());
            System.out.println(date.toString());
        }
    }
}
