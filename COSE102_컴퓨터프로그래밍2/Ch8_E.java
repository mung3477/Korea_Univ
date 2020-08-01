import java.util.Scanner;

public class Ch8_E {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int N = sc.nextInt();
        int [][] arr = new int[N][2];
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < 2; j++) {
                arr[i][j] = sc.nextInt();
            }
        }

        for(int i = 0; i < N; i++) {
            for(int j = 0; j < N - 1; j++) {
                if(arr[j][0] > arr[j + 1][0]) {
                    int[] temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
                else if (arr[j][0] == arr[j + 1][0]) {
                    if(arr[j][1] > arr[j + 1][1]) {
                        int temp = arr[j][1];
                        arr[j][1] = arr[j + 1][1];
                        arr[j + 1][1] = temp;
                    }
                }
            }
            /*for(int k = 0; k < N; k++) {
                System.out.println(arr[k][0] + " " +arr[k][1]);
            }
            System.out.println();*/
        }

        //System.out.println();
        for(int i = 0; i < N; i++) {
                System.out.println(arr[i][0] + " " +arr[i][1]);
        }
    }
}
