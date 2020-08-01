import java.util.*;

public class Ch10_H {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int T = sc.nextInt();
        for (int t = 0; t < T; t++) {
            char ch = sc.next().charAt(0);
            MyCharacter c = new MyCharacter(ch);
            System.out.println(c.charValue());
            System.out.println(c.compareTo(new MyCharacter('i')));
            System.out.println(c.equals(new MyCharacter('i')));
            System.out.println(c.isDigit());
            System.out.println(c.isDigit(ch));
            System.out.println(MyCharacter.isDigit(ch));
            System.out.println(MyCharacter.isLetter(ch));
            System.out.println(MyCharacter.isLetterOrDigit(ch));
            System.out.println(MyCharacter.isLowerCase(ch));
            System.out.println(MyCharacter.isUpperCase(ch));
            System.out.println(MyCharacter.toUpperCase(ch));
            System.out.println(MyCharacter.toLowerCase(ch));
        }
    }
}

class MyCharacter {
    char c;

    MyCharacter(char ch) { this.c = ch; }

    char charValue() { return c; }

    int compareTo(MyCharacter P) { return (int)this.c - (int)P.c; }

    boolean equals(MyCharacter P) { return (P.c == this.c); }

    boolean isDigit() { return ('0' <= this.c && this.c <= '9'); }

    static boolean isDigit(char c) { return ('0' <= c && c <= '9'); }

    static boolean isLetter(char c) { return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z'); }

    static boolean isLetterOrDigit(char c) { return isLetter(c) || isDigit(c); }

    static boolean isLowerCase(char c) {
        if(isLetter(c)) {
            return ('a' <= c && c <= 'z');
        }
        else return false;
    }

    static boolean isUpperCase(char c) {
        if(isLetter(c)) {
            return ('A' <= c && c <= 'Z');
        }
        else return false;
    }

    static char toUpperCase(char c) {
        if(isLetter(c)) {
            if(isUpperCase(c)) { return c; }
            else { return (char)('A' - 'a' + (int)c); }
        }
        else return c;
    }

    static char toLowerCase(char c) {
        if(isLetter(c)) {
            if(isLowerCase(c)) { return c; }
            else { return (char)((int)c - 'A' + 'a'); }
        }
        else return c;
    }
}