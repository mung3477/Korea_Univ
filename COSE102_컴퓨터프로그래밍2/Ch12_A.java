import java.util.*;

public class Ch12_A {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int T = sc.nextInt();
        sc.nextLine();
        for(; T > 0; T--) {
            boolean was_op1 = true;
            String[] tokens = sc.nextLine().split(" ");
            try {
                int op1 = Integer.parseInt(tokens[0]);
                was_op1 = false;
                int op2 = Integer.parseInt(tokens[2]);
                int ans = 0;
                switch(tokens[1]) {
                    case "+":
                        ans = op1 + op2;
                        break;
                    case "-" :
                        ans = op1 - op2;
                        break;
                    case "*":
                        ans = op1 * op2;
                        break;
                    case "/":
                        ans = op1 / op2;
                        break;
                    case "%":
                        ans = op1 % op2;
                        break;
                }
                System.out.println(op1 + " " + tokens[1] + " " + op2 + " = " + ans);
            }
            catch (Exception e) {
                System.out.print("Wrong Input: ");
                if(was_op1) {
                    System.out.println(tokens[0]);
                }
                else {
                    System.out.println(tokens[2]);
                }
            }
        }
    }
}
