import java.util.*;

public class Ch9_D {
    public static void main(String args[]) {
        Scanner sc = new Scanner(System.in);

        int t = sc.nextInt();
        for(int i = 0 ; i < t ; i++) {
            int y =sc.nextInt();
            int m = sc.nextInt();
            int da = sc.nextInt();
            int h = sc.nextInt();
            int min = sc.nextInt();
            int sec = sc.nextInt();

            Date d = new Date(y - 1900, m-1, da + 1000, h, min, sec - 1000);

            System.out.printf("%d.%02d.%02d %02d:%02d:%02d\n", d.getYear()+1900,d.getMonth()+1,d.getDate(),d.getHours(),d.getMinutes(),d.getSeconds());

        }
    }
}
