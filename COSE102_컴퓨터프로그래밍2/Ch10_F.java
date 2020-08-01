import java.util.Scanner;
public class Ch10_F {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int N = sc.nextInt();
        double[][] points = new double[N][2];
        for (int i = 0; i < N; i++) {
            points[i][0] = sc.nextDouble();
            points[i][1] = sc.nextDouble();
        }
        MyRectangle2D boundingRectangle = MyRectangle2D.getRectangle(points);
        System.out.printf("x, y: %.1f, %.1f\n", boundingRectangle.getX(), boundingRectangle.getY());
        System.out.printf("w, h: %.1f, %.1f\n", boundingRectangle.getWidth(), boundingRectangle.getHeight());
    }
}

class MyRectangle2D{
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

    double getX() {
        return this.x;
    }

    double getY() {
        return this.y;
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

    static  MyRectangle2D getRectangle(double[][] points) {
        double maxX = 0, minX = 100000, maxY = 0, minY = 100000;
        for(int i = 0; i < points.length; i++) {
            if(maxX < points[i][0]) { maxX = points[i][0]; }
            if(minX > points[i][0]) { minX = points[i][0]; }
            if(maxY < points[i][1]) { maxY = points[i][1]; }
            if(minY > points[i][1]) { minY = points[i][1]; }
        }
        double width2 = maxX - minX;
        double height2 = maxY - minY;
        double centerX = (maxX + minX) / 2;
        double centerY = (maxY + minY) / 2;
        MyRectangle2D bounding = new MyRectangle2D(centerX, centerY, width2, height2);

        return bounding;
    }
}
