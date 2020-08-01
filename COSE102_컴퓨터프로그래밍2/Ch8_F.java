import java.util.Scanner;

public class Ch8_F {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int N = sc.nextInt();
        double L = sc.nextDouble();

        int[] is_bankrupt = new int[N];
        double[] total_balance = new double[N];
        double[][] loan = new double[N][N];

        for(int i = 0; i < N; i++) {
            total_balance[i] = sc.nextDouble();
            int j = sc.nextInt();
            for(; j > 0; j--) {
                int loan_to = sc.nextInt();
                double amount = sc.nextDouble();
                total_balance[i] += amount;
                loan[i][loan_to] = amount;
            }
        }
        int bankrupted = 0;
        for(int i = 0; i < N; i++) {
            if(total_balance[i] < L && is_bankrupt[i] == 0) {
                is_bankrupt[i] = 1;
                bankrupted++;
                balanceUpdate(total_balance, loan, i);
                i = -1;
            }
        }
        int i;
        for(i = 0; i < N && bankrupted != 1; i++) {
            if(is_bankrupt[i] == 1) {
                System.out.print(i + " ");
                bankrupted--;
            }
        }
        for(; i < N; i++) {
            if(is_bankrupt[i] == 1) { System.out.print(i); }
        }
    }

    private static void balanceUpdate(double[] total_balance, double[][] loan, int i) {
        for(int j = 0; j < total_balance.length; j++) {
            total_balance[j] -= loan[j][i];
        }
    }
}
