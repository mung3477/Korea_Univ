import java.util.Scanner;

public class Ch8_H {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        //1 : R, 2 : Y
        int[][] board = new int[6][7];
        int[] count = new int[7];

        //put my chessman
        for(int i = 1; i <= 42; i++) {
            int column = sc.nextInt();
            board[5 - count[column]][column] = (i % 2 != 0 ? 1 : 2);
            count[column]++;
            if(isEnd(board)) {
                printBoard(board);
                return;
            }
        }
    }

    // i : row, j : column
    // blank(0) : blank space, R(1) : R, Y(2) : Y
    // Change line per 7 print
    private static void printBoard(int[][] board) {
        for(int i = 0; i < 6; i++) {
            for(int j = 0; j < 7; j++) {
                int t = board[i][j];
                switch(t) {
                    case 0 :
                        System.out.print(" ");
                        break;
                    case 1 :
                        System.out.print("R");
                        break;
                    case 2 :
                        System.out.print("Y");
                        break;
                    default :
                        break;
                }
            }
            System.out.println();
        }
    }

    private static boolean isEnd(int[][] arr) {
        int count = 0;
        count += check_vertical(arr);
        count += check_horizontal(arr);
        count += check_diagonal_left(arr);
        count += check_diagonal_right(arr);

        if(count == 0) return false;
        else return true;
    }

    //세로 체크
    // i : column, j : row
    public static int check_vertical(int[][] arr) {
        int count = 0;
        for(int i = 0; i < arr[0].length; i++) {
            for (int j = 0; j <= arr.length - 4; j++) {
                int t = arr[j][i];
                if(t != 0 && arr[j + 1][i] == t && arr[j + 2][i] == t && arr[j + 3][i] == t) { count++; }
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
                if(t != 0 && arr[i][j + 1] == t && arr[i][j + 2] == t && arr[i][j + 3] == t) { count++; }
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
                if(t != 0 && arr[i + 1][j + 1] == t && arr[i + 2][j + 2] == t && arr[i + 3][j + 3] == t) { count++; }
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
                if(t != 0 && arr[i + 1][j - 1] == t && arr[i + 2][j - 2] == t && arr[i + 3][j - 3] == t) { count++; }
            }
        }
        return count;
    }
}
