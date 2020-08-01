import java.util.Scanner;

public class Ch7_D {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int[] hor = new int[8];
        int[] ver = new int[8];
        int[] diag = new int[2 * 8 - 1];

        for(int i = 0; i < hor.length; i++) { hor[i] = 0; }
        for(int i = 0; i < ver.length; i++) { ver[i] = 0; }
        for(int i = 0; i < diag.length; i++) { diag[i] = 0; }

        for(int i = 0; i < hor.length; i++) {
            String Queens = sc.nextLine();

            for(int j = 0; j < ver.length; j++) {
                if (Queens.charAt(j) == 'Q') {
                    if (hor[i] != 1) { hor[i] = 1; }
                    else {
                        System.out.println("Invalid");
                        return;
                    }

                    if (ver[j] != 1) { ver[j] = 1; }
                    else {
                        System.out.println("Invalid");
                        return;
                    }

                    if(diag[8 + j - i] != 1) { diag[8+j-i] = 1; }
                    else {
                        System.out.println("Invalid");
                        return;
                    }
                }
            }
        }
        System.out.println("Valid");
    }
}
