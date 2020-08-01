import java.util.Scanner;

public class Ch7_B {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int N = sc.nextInt();
        int[] num = new int[N + 1];

        for(int i = 0; i < N; i++) {
            num[i] = sc.nextInt();
        }
        num[N] = 101;
        java.util.Arrays.sort(num);
        int count = 1;
        for(int i = 0; i < N; i++) {
            if(num[i + 1] != num[i]) {
                System.out.println(num[i] + " " + count);
                count = 1;
            }
            else {
                count++;
            }
        }
    }
}
