import java.math.*;
import java.util.Scanner;

public class Ch13_D {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int T = sc.nextInt();
        for (int t = 0; t < T; t++) {
            Rational r1 = Rational.getFraction(sc.next());
            Rational r2 = Rational.getFraction(sc.next());

            System.out.println(r1 + " + " + r2 + " = " + r1.add(r2));
            System.out.println(r1 + " - " + r2 + " = " + r1.subtract(r2));
            System.out.println(r1 + " * " + r2 + " = " + r1.multiply(r2));
            System.out.println(r1 + " / " + r2 + " = " + r1.divide(r2));
        }
    }
}

class Rational {
    BigInteger numerator;
    BigInteger denominator;

    Rational() { }

    Rational(BigInteger a, BigInteger b) {
        this.numerator = a;
        this.denominator = b;
    }

    public Rational add(Rational r2) {
        Rational r3 = new Rational((this.numerator.multiply(r2.denominator)).add(r2.numerator.multiply(this.denominator)), (r2.denominator).multiply(this.denominator));
        r3 = r3.fraction(r3.numerator, r3.denominator);
        return r3;
    }

    public Rational subtract(Rational r2) {
        Rational r3 = new Rational((this.numerator.multiply(r2.denominator)).subtract(r2.numerator.multiply(this.denominator)), (r2.denominator).multiply(this.denominator));
        r3 = r3.fraction(r3.numerator, r3.denominator);
        return r3;
    }

    public Rational multiply(Rational r2) {
        Rational r3 = new Rational(this.numerator.multiply(r2.numerator), this.denominator.multiply(r2.denominator));
        r3 = r3.fraction(r3.numerator, r3.denominator);
        return r3;
    }

    public Rational divide(Rational r2) {
        Rational r3 = new Rational(this.numerator.multiply(r2.denominator), this.denominator.multiply(r2.numerator));
        r3 = r3.fraction(r3.numerator, r3.denominator);
        return r3;
    }

    public static Rational fraction(BigInteger a, BigInteger b) {
        Rational r = new Rational();
        BigInteger gcd = a.gcd(b);
        r.numerator = a.divide(gcd);
        r.denominator = b.divide(gcd);

        return r;
    }

    public String toString() {
        Rational r = new Rational();
        r = this.fraction(this.numerator, this.denominator);

        if (r.numerator.compareTo(BigInteger.ZERO) < 0 && r.denominator.compareTo(BigInteger.ZERO) < 0) {
            r.numerator = r.numerator.abs();
            r.denominator = r.denominator.abs();
        }

        else if (r.numerator.compareTo(BigInteger.ZERO) > 0 && this.denominator.compareTo(BigInteger.ZERO) < 0) {
            r.numerator = r.numerator.multiply(new BigInteger("-1"));
            r.denominator = r.denominator.abs();
        }

        if((r.denominator.compareTo(BigInteger.ONE) == 0) || (r.numerator.compareTo(BigInteger.ZERO) == 0))  {
            return r.numerator.toString();
        }
        else {
            return r.numerator + "/" + r.denominator;
        }
    }

    public static Rational getFraction(String s) {
        Rational r = new Rational();
        int DecDec = 0;
        double d = Double.parseDouble(s);

        if(s.contains(".")) {
            DecDec = s.length() - s.indexOf(".") - 1;
        }

        BigInteger D = BigInteger.ONE;

        for(int i = 0; i < DecDec; i++) {
            d *= 10;
            D = D.multiply(BigInteger.TEN);
        }
        BigInteger B = new BigInteger(Long.toString(Math.round(d)));

        r = fraction(B, D);
        return r;
    }
}
