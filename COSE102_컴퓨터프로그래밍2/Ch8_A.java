import java.util.Scanner;

public class Ch8_A {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int N = sc.nextInt();
        int[] worktime = new int[N];
        String[] employee = new String[N];

        for (int i = 0; i < N; i++) {
            int sum = 0;
            employee[i] = sc.next();
            for (int j = 0; j < 7; j++) {
                sum += sc.nextInt();
            }
            worktime[i] = sum;
        }

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N - 1; j++) {
                if (worktime[j] < worktime[j + 1]) {
                    int temp = worktime[j];
                    worktime[j] = worktime[j + 1];
                    worktime[j + 1] = temp;

                    String temp2 = employee[j];
                    employee[j] = employee[j + 1];
                    employee[j + 1] = temp2;
                }
            }
        }

        for (int i = 0; i < N; i++) {
            System.out.println(employee[i] + " " + worktime[i]);
        }
    }
}