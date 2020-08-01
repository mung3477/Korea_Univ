import java.util.Arrays;
import java.util.Scanner;

public class Ch13_A {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int N = sc.nextInt();
        GeometricObject1[] aCircle1 = new Circle1[N];
        for (int i = 0; i < N; i++) {
            aCircle1[i] = new Circle1(sc.nextDouble(), sc.next(), sc.nextDouble());
        }
        Arrays.sort(aCircle1);
        for (GeometricObject1 c1 : aCircle1) {
            System.out.println(c1);
        }
    }
}

class GeometricObject1 { }

class Circle1 extends GeometricObject1 implements Comparable<Circle1>{
    double radius;
    String color;
    double weight;

    Circle1(double radius, String color, double weight) {
        this.radius = radius;
        this.color = color;
        this.weight = weight;
    }

    public int compareTo(Circle1 Circle) {
        if(this.radius > Circle.radius) return 1;
        else if (this.radius == Circle.radius) return 0;
        else return -1;
    }

    public String toString() {
        java.text.DecimalFormat df = new java.text.DecimalFormat("0.0");
        return "radius:" + df.format(this.radius) +", color:" + this.color + ", weight:" + df.format(this.weight);
    }
}
