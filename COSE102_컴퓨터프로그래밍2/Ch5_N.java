import java.util.Scanner;
import java.util.Vector;

public class Ch5_N {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int N = sc.nextInt(); sc.nextLine();

        Vector<String> substrings = new Vector<String>(100);
        String criteria = sc.nextLine();
        for(int i = 0; i < criteria.length(); i++) {
            for(int j = i; j <criteria.length(); j++) {
                substrings.add(criteria.substring(i, j+1));
            }
        }
        int k = 0;
        while(k < N - 1) {
            String s = sc.nextLine();
            for (int i = substrings.size() - 1; i >= 0; i--) {
                if(!s.contains(substrings.get(i))) { substrings.remove(i); }
            }
            k++;
        }

        int longest = 0;
        for(int i = 0; i < substrings.size(); i++) {
            if(substrings.get(i).length() > substrings.get(longest).length()) {
                longest = i;
            }
        }
        System.out.print(substrings.get(longest));
    }
}