import java.util.*;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Ch10_I {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int T = sc.nextInt();
        for (int t = 0; t < T; t++) {
            String str = sc.next();
            String delimiter = sc.next();

            String result = split(str, delimiter);
            System.out.println(result);
        }
    }

    public static String split(String s, String regex) {
        Pattern pattern = Pattern.compile(regex);
        StringBuilder result = new StringBuilder();
        Matcher m = pattern.matcher(s);
        int k, l = 0, i = 0;

        //i = previous start
        while(m.find()) {
            k = m.start();
            l = m.end();
            result.append(s.substring(i, k) + "," + s.substring(k, l) + ",");
            i = l;
        }
        result.append(s.substring(l));

        return result.toString();
    }
}
