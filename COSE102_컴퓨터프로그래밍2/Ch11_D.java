//import java.text.DecimalFormat;
//import java.util.Scanner;
//
//public class Ch11_D {
//    public static void main(String[] args) {
//        Scanner sc = new Scanner(System.in);
//
//        int T = sc.nextInt();
//        for (int t = 0; t < T; t++) {
//            double side1 = sc.nextDouble();
//            double side2 = sc.nextDouble();
//            double side3 = sc.nextDouble();
//
//            GeometricObject triangle = new Triangle(side1, side2, side3);
//            String color = sc.next();
//            triangle.setColor(color);
//
//            boolean filled = sc.nextBoolean();
//            triangle.setFilled(filled);
//            DecimalFormat df = new DecimalFormat("##.00");
//            System.out.println("The area is " + df.format(triangle.getArea()));
//            System.out.println("The perimeter is " + df.format(triangle.getPerimeter()));
//            System.out.println(triangle);
//        }
//    }
//}
//
//abstract class GeometricObject {
//    private String color = "white";
//    private boolean filled;
//
//    /**
//     * Default construct
//     */
//    protected GeometricObject() {
//    }
//
//    /**
//     * Construct a geometric object
//     */
//    protected GeometricObject(String color, boolean filled) {
//        this.color = color;
//        this.filled = filled;
//    }
//
//    /**
//     * Getter method for color
//     */
//    public String getColor() {
//        return color;
//    }
//
//    /**
//     * Setter method for color
//     */
//    public void setColor(String color) {
//        this.color = color;
//    }
//
//    /**
//     * Getter method for filled. Since filled is boolean,
//     * so, the get method name is isFilled
//     */
//    public boolean isFilled() {
//        return filled;
//    }
//
//    /**
//     * Setter method for filled
//     */
//    public void setFilled(boolean filled) {
//        this.filled = filled;
//    }
//
//    /**
//     * Abstract method findArea
//     */
//    public abstract double getArea();
//
//    /**
//     * Abstract method getPerimeter
//     */
//    public abstract double getPerimeter();
//}
//
//class Triangle extends GeometricObject {
//    double side1;
//    double side2;
//    double side3;
//
//    Triangle(double side1, double side2, double side3) {
//        this.side1 = side1;
//        this.side2 = side2;
//        this.side3 = side3;
//    }
//
//    @Override
//    public double getArea() {
//        double s = (side1 + side2 + side3) / 2.0;
//        double area = Math.sqrt(s * (s - side1) * (s - side2) * (s - side3));
//        return area;
//    }
//
//    @Override
//    public double getPerimeter() {
//        double perimeter = side1 + side2 + side3;
//        return perimeter;
//    }
//
//    @Override
//    public String toString() {
//        DecimalFormat df = new DecimalFormat("##.00");
//        return "Triangle: side1 = " + df.format(side1) + " side2 = " + df.format(side2) + " side3 = " + df.format(side3);
//    }
//}