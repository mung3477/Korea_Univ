import java.util.Scanner;

public class Ch8_G {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int N = sc.nextInt();
        int M = sc.nextInt();
        int[][] arr = new int[N][M];
        int count = 0;

        //making array
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < M; j++) {
                arr[i][j] = sc.nextInt();
            }
        }

        count += check_vertical(arr);
        count += check_horizontal(arr);
        count += check_diagonal_left(arr);
        count += check_diagonal_right(arr);

        System.out.print(count);
    }

    //세로 체크
    // i : column, j : row
    public static int check_vertical(int[][] arr) {
        int count = 0;
        for(int i = 0; i < arr[0].length; i++) {
            for (int j = 0; j <= arr.length - 4; j++) {
                int t = arr[j][i];
                if(arr[j + 1][i] == t && arr[j + 2][i] == t && arr[j + 3][i] == t) { count++; }
            }
        }
        return count;
    }

    //가로 체크
    // i : row, j : column
    public static int check_horizontal(int[][] arr) {
        int count = 0;
        for (int i = 0; i < arr.length; i++) {
            for (int j = 0; j <= arr[0].length - 4; j++) {
                int t = arr[i][j];
                if(arr[i][j + 1] == t && arr[i][j + 2] == t && arr[i][j + 3] == t) { count++; }
            }
        }
        return count;
    }

    //대각선 우하단 체크
    // i : row, j : column
    public static int check_diagonal_right(int[][] arr) {
        int count = 0;
        for(int i = 0; i <= arr.length - 4; i++) {
            for(int j = 0; j <= arr[0].length - 4; j++) {
                int t = arr[i][j];
                if(arr[i + 1][j + 1] == t && arr[i + 2][j + 2] == t && arr[i + 3][j + 3] == t) { count++; }
            }
        }
        return count;
    }

    //대각선 좌하단 체크
    // i : row, j : coloumn
    public static int check_diagonal_left(int[][] arr){
        int count = 0;
        for(int i = 0; i <= arr.length - 4; i++) {
            for(int j = 3; j < arr[0].length; j++) {
                int t = arr[i][j];
                if(arr[i + 1][j - 1] == t && arr[i + 2][j - 2] == t && arr[i + 3][j - 3] == t) { count++; }
            }
        }
        return count;
    }

}
