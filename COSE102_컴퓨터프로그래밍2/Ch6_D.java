import java.util.Scanner;

public class Ch6_D {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int T = sc.nextInt(), n = 0;
        sc.nextLine();
        while(n < T) {
            Convert(sc.nextLine());
            n++;
        }
    }

    private static void Convert(String s) {
        for(int i = 0; i < s.length(); i++) {
            char c = s.charAt(i);
            if(('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z')) {
                c = Character.toLowerCase(c);
                switch(c) {
                    case 'a':
                    case 'b':
                    case 'c':
                        System.out.print(2);
                        break;
                    case 'd':
                    case 'e':
                    case 'f':
                        System.out.print(3);
                        break;
                    case 'g':
                    case 'h':
                    case 'i':
                        System.out.print(4);
                        break;
                    case 'j':
                    case 'k':
                    case 'l':
                        System.out.print(5);
                        break;
                    case 'm':
                    case 'n':
                    case 'o':
                        System.out.print(6);
                        break;
                    case 'p':
                    case 'q':
                    case 'r':
                    case 's':
                        System.out.print(7);
                        break;
                    case 't':
                    case 'u':
                    case 'v':
                        System.out.print(8);
                        break;
                    case 'w':
                    case 'x':
                    case 'y':
                    case 'z':
                        System.out.print(9);
                        break;
                }
            }
            else { System.out.print(c); }
        }
        System.out.println();
    }
}