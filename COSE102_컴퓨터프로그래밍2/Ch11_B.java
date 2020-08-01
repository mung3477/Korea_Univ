import java.util.Scanner;

public class Ch11_B {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int T = sc.nextInt();

        point[] points = new point[T];

        for(int i = 0; i < T; i++) {
            int x = sc.nextInt();
            int y = sc.nextInt();
            points[i] = new point(x, y);
        }

        double area = shoelaces(points);
        System.out.printf("The total area is %.2f", area);
    }

    static double shoelaces(point[] points) {
        double area = 0;

        for(int i = 0; i < points.length; i++) {
            int a = i % points.length;
            int b = (i + 1) % points.length;

            area += points[a].x * points[b].y - points[b].x * points[a].y;
        }

        return Math.abs(area) / 2.0;
    }
}

class point {
    int x;
    int y;

    point(int x, int y) {
        this.x = x;
        this.y = y;
    }
}

