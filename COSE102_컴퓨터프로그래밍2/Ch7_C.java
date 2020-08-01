import java.util.Scanner;

public class Ch7_C {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int N = sc.nextInt();
        int M = sc.nextInt();
        sc.nextLine();
        int i = 0;
        int[] balls = new int[M];
        for(int j = 0; j < M; j++) { balls[j] = 0; }
        //공 떨어트리기
        //R이면 index + 1
        while(i < N) {
            int index = 0;
            String path = sc.nextLine();
            for(int j = 0; j < path.length(); j++) {
                if (path.charAt(j) == 'R') { index++; }
            }
            balls[index]++;
            i++;
        }
        for(int j = 0; j < M; j++) { System.out.println(balls[j]); }
    }
}
