//import javafx.geometry.*;
import java.awt.geom.Line2D;
import java.util.Scanner;

public class Ch10_E {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int T = sc.nextInt();
        for (int t = 0; t < T; t++) {
            double x1, y1, x2, y2, x3, y3, x4, y4, x5, y5, x6, y6, x7, y7;
            x1 = sc.nextDouble();
            y1 = sc.nextDouble();
            x2 = sc.nextDouble();
            y2 = sc.nextDouble();
            x3 = sc.nextDouble();
            y3 = sc.nextDouble();
            x4 = sc.nextDouble();
            y4 = sc.nextDouble();
            x5 = sc.nextDouble();
            y5 = sc.nextDouble();
            x6 = sc.nextDouble();
            y6 = sc.nextDouble();
            x7 = sc.nextDouble();
            y7 = sc.nextDouble();

            Triangle2D r1 = new Triangle2D(x1, y1, x2, y2, x3, y3);
            Triangle2D r2 = new Triangle2D(x4, y4, x5, y5, x6, y6);

            System.out.printf("Area is %.1f\n", r1.getArea());
            System.out.printf("Perimeter is %.1f\n", r1.getPerimeter());
            System.out.println(r1.contains(x7, y7));
            if (r1.contains(r2)) {
                System.out.println("contain");
            } else if (r1.overlaps(r2)) {
                System.out.println("overlaps");
            } else {
                System.out.println("no overlap");
            }
        }
    }
}

class Triangle2D {
    MyPoint p1 = new MyPoint();
    MyPoint p2 = new MyPoint();
    MyPoint p3 = new MyPoint();

    Triangle2D() {
        p1.x = 0;
        p1.y = 0;
        p2.x = 1;
        p2.y = 1;
        p3.x = 2;
        p3.y = 5;
    }

    Triangle2D(double x1, double y1, double x2, double y2, double x3, double y3) {
        this.p1.x = x1;
        this.p1.y = y1;
        this.p2.x = x2;
        this.p2.y = y2;
        this.p3.x = x3;
        this.p3.y = y3;
    }

    double getArea() {
        double side1 = Math.sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
        double side2 = Math.sqrt((p1.x - p3.x) * (p1.x - p3.x) + (p1.y - p3.y) * (p1.y - p3.y));
        double side3 = Math.sqrt((p3.x - p2.x) * (p3.x - p2.x) + (p3.y - p2.y) * (p3.y - p2.y));
        double s = (side1 + side2 + side3) / 2.0;
        double area = Math.sqrt(s * (s - side1) * (s - side2) * (s - side3));
        return area;
    }

    double getPerimeter() {
        double side1 = Math.sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
        double side2 = Math.sqrt((p1.x - p3.x) * (p1.x - p3.x) + (p1.y - p3.y) * (p1.y - p3.y));
        double side3 = Math.sqrt((p3.x - p2.x) * (p3.x - p2.x) + (p3.y - p2.y) * (p3.y - p2.y));
        return side1 + side2 + side3;
    }

    boolean contains(double x, double y) {
        MyPoint p = new MyPoint(x, y);
        if( ((whichSide(p1, p2, p) & whichSide(p2, p3, p)) != 0)  && ((whichSide(p2, p3, p) & whichSide(p3, p1, p)) != 0 ) && ((whichSide(p3, p1, p) & whichSide(p1, p2, p)) != 0) ) {
            return true;
        }
        else { return false; }
    }

    boolean contains(Triangle2D t) {
        if(this.contains(t.p1.x, t.p1.y) && this.contains(t.p2.x, t.p2.y) && this.contains(t.p3.x, t.p3.y)) {
            return true;
        }
        else { return false; }
    }

    boolean overlaps(Triangle2D t) {
        /*if(t.contains(this) ||this.contains(t.p1.x, t.p1.y) || this.contains(t.p2.x, t.p2.y) || this.contains(t.p3.x, t.p3.y)) {
            return true;
        }
        else { return false; }*/
        Line2D line[] = new Line2D[6];
        line[0] = new Line2D.Double(p2.x, p2.y, p3.x, p3.y);
        line[1] = new Line2D.Double(p1.x, p1.y, p2.x, p2.y);
        line[2] = new Line2D.Double(p1.x, p1.y, p3.x, p3.y);
        line[3] = new Line2D.Double(t.p1.x, t.p1.y, t.p2.x, t.p2.y);
        line[4] = new Line2D.Double(t.p1.x, t.p1.y, t.p3.x, t.p3.y);
        line[5] = new Line2D.Double(t.p3.x, t.p3.y, t.p2.x, t.p2.y);

        boolean chk = true;
        for(int i=0 ; i<3 ; i++) {
            for(int j=3 ; j<6 ; j++) {
                if(line[i].intersectsLine(line[j])){
                    chk = false;
                    break;
                }
            }
        }

        return !chk;
    }

    int whichSide(MyPoint from, MyPoint to, MyPoint p) {
        double a = to.y - from.y;
        double b = from.x - to.x;
        double c = from.x * to.y - from.y * to.x;
        double pos =  a * p.x + b * p.y - c;

        if(pos < 0) { return 0x01; }
        else if(pos > 0) { return 0x02; }
        else { return 0x03; }
    }

}

class MyPoint {
    double x;
    double y;

    double getX() {
        return this.x;
    }

    double getY() {
        return this.y;
    }

    MyPoint() {
        this.x = 0;
        this.y = 0;
    }

    MyPoint(double x, double y) {
        this.x = x;
        this.y = y;
    }

    double distance(double x, double y) {
        return Math.sqrt(Math.pow(this.x - x, 2) - Math.pow(this.y - y, 2));
    }

    double distance(MyPoint A) {
        return Math.sqrt(Math.pow(this.x - A.x, 2) - Math.pow(this.y - A.y, 2));
    }
}
