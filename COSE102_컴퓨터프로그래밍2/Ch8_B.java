import java.util.Scanner;

public class Ch8_B {
    public static void main(String[] args) {
        int[][] array1 = new int[3][3];
        int[][] array2 = new int[3][3];
        int[][] array3 = new int[3][3];

        Scanner sc = new Scanner(System.in);

        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                array1[i][j] = sc.nextInt();
            }
        }

        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                array2[i][j] = sc.nextInt();
                array3[i][j] = 0;
            }
        }

        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                array3[i][j] = array1[i][0] * array2[0][j] + array1[i][1] * array2[1][j] + array1[i][2] * array2[2][j];
            }
        }

        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 2; j++) {
                System.out.print(array3[i][j] + " ");
            }
            System.out.println(array3[i][2]);
        }
    }
}
