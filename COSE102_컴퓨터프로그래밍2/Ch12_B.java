import java.util.Scanner;

public class Ch12_B {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int T = sc.nextInt();
        for (int t = 0; t < T; t++) {
            String hex = sc.next();
            int value;
            try {
                value = HexFormat.parseHex(hex);
            } catch (HexFormatException ex) {
                System.out.println(ex);
                continue;
            }
            System.out.println(value);
        }
    }
}

class HexFormat {
    static int parseHex(String hex) throws HexFormatException {
        int digit = 0;
        for(int i = 0; i < hex.length(); i++) {
            digit = digit * 16;
            char c = hex.charAt(i);
            if('0' <= c && c <= '9') {
                digit += (int)(c - '0');
            }
            else if('A' <= c && c <= 'F') {
                digit += (int)(c - 'A') + 10;
            }
            else {
                HexFormatException e = new HexFormatException(c);
                throw e;
            }
        }
        return digit;
    }
}

class HexFormatException extends Exception {
    char illegal_char;

    HexFormatException(char c) {
        this.illegal_char = c;
    }

    @Override
    public String toString() {
        return "HexFormatException: Illegal hex character: " + illegal_char;
    }
};
