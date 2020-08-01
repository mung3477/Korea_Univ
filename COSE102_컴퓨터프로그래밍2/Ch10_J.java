import java.util.*;

public class Ch10_J {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int T = sc.nextInt();
        sc.nextLine();
        for(int i = 0; i < T; i++) {
            String s = sc.nextLine();
            Scanner scanner = new Scanner(s);
            int[] nums = new int[100];
            int count = 0;
            while(scanner.hasNextInt()) {
                nums[count++] = scanner.nextInt();
            }

            int[] ans = new int[count];
            System.arraycopy(nums, 0, ans, 0, count);
            Arrays.sort(ans);
            for(int j = ans.length - 1; j >= 0; j--) {
                System.out.print(ans[j]);
            }
            System.out.println();
            scanner.close();
        }
    }
}
