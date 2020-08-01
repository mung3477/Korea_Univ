import java.util.*;

public class Ch12_C {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        StringBuilder input = new StringBuilder();

        while(sc.hasNextLine()) {
            String next = sc.nextLine();
            input.append(next + "\n");
        }
        input.deleteCharAt(input.length() - 1);

        String in = input.toString();
        String ans = in.replaceAll("\n\\s*[{]", " {");
        System.out.print(ans);
    }
}

