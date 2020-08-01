import java.util.Scanner;

public class Ch10_C {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int T = sc.nextInt();
        for (int t = 0; t < T; t++) {
            double x1, y1, w1, h1, x2, y2, w2, h2, x3, y3;
            x1 = sc.nextDouble();
            y1 = sc.nextDouble();
            w1 = sc.nextDouble();
            h1 = sc.nextDouble();
            x2 = sc.nextDouble();
            y2 = sc.nextDouble();
            w2 = sc.nextDouble();
            h2 = sc.nextDouble();
            x3 = sc.nextDouble();
            y3 = sc.nextDouble();

            MyRectangle2D r1 = new MyRectangle2D(x1, y1, w1, h1);
            MyRectangle2D r2 = new MyRectangle2D(x2, y2, w2, h2);

            System.out.printf("Area is %.1f\n", r1.getArea());
            System.out.printf("Perimeter is %.1f\n", r1.getPerimeter());
            System.out.println(r1.contains(x3, y3));
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
/*
class MyRectangle2D {
    double x;
    double y;
    double width;
    double height;

    MyRectangle2D() {
        this.x = 0;
        this.y = 0;
        this.width = 1;
        this.height = 1;
    }

    MyRectangle2D(double x, double y, double w, double h) {
        this.x = x;
        this.y = y;
        this.width = w;
        this.height = h;
    }

    double getWidth() {
        return this.width;
    }

    double getHeight() {
        return this.height;
    }

    void setWidth(double width) {
        this.width = width;
    }

    void setHeight(double height) {
        this.height = height;
    }

    double getArea() {
        return width * height;
    }

    double getPerimeter() { return 2 * width + 2 * height;}

    boolean contains(double x, double y) {
        if (Math.abs(x - this.x) <= width / 2 && Math.abs(y - this.y) <= height / 2) { return true; }
        else return false;
    }

    boolean contains(MyRectangle2D r) {
        if( (this.x + this.width / 2 >= r.x + r.width/2) && (this.x - this.width / 2 <= r.x - r.width / 2) && (this.y + this.height / 2 >= r.y + r.height / 2) && (this.y - this.height / 2 <= r.y - r.height / 2))
            return true;
        else return false;
    }

    boolean overlaps(MyRectangle2D r) {
        if(!this.contains(r)) {
            if( !((this.y + this.height / 2 < r.y - r.height / 2) || (this.y - this.height / 2 > r.y + r.height / 2) || (this.x + this.width / 2 < r.x - r.width / 2) || (this.x - this.width / 2 > r.x + r.width / 2))) {
                return true;
            }
            else return false;
        }
        else return false;
    }

}
 */

