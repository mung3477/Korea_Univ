import java.util.*;

public class Ch11_C {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int T = sc.nextInt();
        for(; T > 0; T--) {
            int m = sc.nextInt();
            Integer[] m_factorize = factorization(m);
            Arrays.sort(m_factorize);

            int curNum = m_factorize[0];
            int curCount = 0;
            ArrayList<prime> factors = new ArrayList<prime>();

            for(int i = 1; i < m_factorize.length; i++) {
                curCount += 1;
                if(curNum != m_factorize[i]) {
                        factors.add(new prime(curNum, curCount));
                        curCount = 0;
                        curNum = m_factorize[i];
                }
            }
            factors.add(new prime(curNum, curCount + 1));

            int n = 1;
            for(int i = 0; i < factors.size(); i++) {
                if(factors.get(i).exponent % 2 != 0) {
                    n *= factors.get(i).base;
                }
            }

            System.out.println(m * n + " = " + m + " x " + n);
        }
    }

    static Integer[] factorization(int m) {
        ArrayList<Integer> result = new ArrayList<Integer>();

        for(int i = 2; m > 1; i++) {
            if(m % i == 0) {
                result.add(i);
                m = m / i;
                i--;
            }
        }

        Integer[] Res = result.toArray(new Integer[] { 0 });
        return Res;
    }
}

class prime {
    int base;
    int exponent;

    prime(int base, int exponent) {
        this.base = base;
        this.exponent = exponent;
    }
}

