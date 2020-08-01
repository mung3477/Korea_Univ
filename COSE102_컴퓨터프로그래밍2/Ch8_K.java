import java.util.Scanner;

public class CH8_K {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int N = sc.nextInt();
        int[][] mat = new int[N][N];

        //save matrix
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < N; j++) {
                mat[i][j] = sc.nextInt();
            }
        }

        //find max submat
        for(int i = N; i >= 1; i--) {
            for(int j = 0; j <= N - i; j++) {
                for(int k = 0; k <= N - i; k++) {
                    if(check_submat(mat, j, k , i)) {
                        System.out.print(j + " " + k + " " + i);
                        return;
                    }
                }
            }
        }
        System.out.println('a');
    }

    //j : start row, k : start column, i : one side element number
    private static boolean check_submat(int[][] mat, int j, int k, int i) {

        if(mat[j][k] == 0) return false;

        for(int p = j; p <= j + i - 1; p++) {
            for(int q = k; q <= k + i - 1; q++) {
                if(mat[p][q] == 0) return false;
            }
        }
        return true;
    }

}
