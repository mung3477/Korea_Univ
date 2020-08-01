import java.util.Scanner;

public class Ch13_B {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int N = sc.nextInt();
        GeometricObject[] aObject = new GeometricObject[N];
        for (int i = 0; i < N; i++) {
            String shape = sc.next();
            if (shape.equals("Square")) {
                aObject[i] = new Square(sc.nextDouble());
            } else if (shape.equals("Rectangle")) {
                aObject[i] = new Rectangle(sc.nextDouble(), sc.nextDouble());
            }
        }
        for (int i = 0; i < aObject.length; i++) {
            if (aObject[i] instanceof Colorable)
                ((Colorable) aObject[i]).howToColor();
            System.out.println("area: " + aObject[i].getArea());
            System.out.println("perimeter: " + aObject[i].getPerimeter());
        }
    }
}

interface Colorable {
    void howToColor();
}

abstract class GeometricObject implements Colorable{
    abstract double getArea();
    abstract double getPerimeter();

    public void howToColor() {
        System.out.println("howToColor: xxx");
    }
}

class Rectangle extends GeometricObject implements Colorable{
    double upside;
    double leftside;

    Rectangle(double upside, double leftside) {
        this.upside = upside;
        this.leftside = leftside;
    }

    double getArea() {
        return upside * leftside;
    }

    double getPerimeter() {
        return 2 * (upside + leftside);
    }

    public void howToColor() {
        System.out.println("Rectangle");
        super.howToColor();
    }


}

class Square extends GeometricObject implements Colorable{
    double side;

    Square(double side) {
        this.side = side;
    }

    double getArea() {
        return side * side;
    }

    double getPerimeter() {
        return side * 4;
    }

    public void howToColor() {
        System.out.println("Square");
        super.howToColor();
    }
}

