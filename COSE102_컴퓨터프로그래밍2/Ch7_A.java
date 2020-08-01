import java.util.Scanner;

public class Ch7_A {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int N = sc.nextInt();
        int i = 0;
        double[] scores = new double[N];
        double max = 0;
        for(i = 0; i < N; i++) {
            scores[i] = sc.nextDouble();
            if(max < scores[i]) { max = scores[i]; }
        }

        for(double k : scores) {
            System.out.println(Grading(k, max));
        }
    }

    private static char Grading(double score, double max) {
        if (score >= max - 10) return 'A';
        else if (score >= max - 20) return 'B';
        else if (score >= max - 30) return 'C';
        else if (score >= max - 40) return 'D';
        else return 'F';
    }

}
