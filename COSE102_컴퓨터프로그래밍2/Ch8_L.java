import java.util.Scanner;

public class Ch8_L {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int T = sc.nextInt();
        for(; T > 0; T--) {
            int[][] points = new int[4][2];

            for(int i = 0; i < 4; i++) {
                for(int j = 0; j < 2; j++) {
                    points[i][j] = sc.nextInt();
                }
            }

            arrangePoints(points);
            /*for(int i = 0; i < 4; i++) {
                    System.out.println(points[i][0] + " " + points[i][1]);
            }*/

            //find cross point
            double a = points[0][1] - points[3][1];
            double b = -1 * points[0][0] + points[3][0];
            double e = (points[0][1] - points[3][1]) * points[0][0] - (points[0][0] - points[3][0]) * points[0][1];
            double c = points[1][1] - points[2][1];
            double d = -1 * points[1][0] + points[2][0];
            double f = (points[1][1] - points[2][1]) * points[1][0] - (points[1][0] - points[2][0]) * points[1][1];

            double[] crossPoint = new double[2];
            crossPoint[0] = (e * d - b * f) / (a * d - b * c);
            crossPoint[1] = (a * f - e * c) / (a * d - b * c);

            double[] area = new double[4];
            area[0] = getArea(points[0], points[1], crossPoint);
            area[1] = getArea(points[0], points[2], crossPoint);
            area[2] = getArea(points[1], points[3], crossPoint);
            area[3] = getArea(points[2], points[3], crossPoint);

            java.util.Arrays.sort(area);
            for(int i = 0; i < 3; i++) {
                System.out.printf( "%.2f", area[i]);
                System.out.print(" ");
            }
            System.out.printf("%.2f", area[3]);
            System.out.println();
        }
    }

    private static double getArea(int[] point1, int[] point2, double[] point3) {
        double Area = Math.abs(point1[0] * point2[1] + point2[0] * point3[1] + point3[0] * point1[1]
            - point2[0] * point1[1] - point3[0] * point2[1] - point1[0] * point3[1]) / 2.0;
        return Area;
    }

    private static void arrangePoints(int[][] points) {
        //x 오름차순 정렬
        for(int i = 0; i < 4; i++) {
            for(int j = i; j < 3; j++) {
                if(points[j][0] > points[j + 1][0]) {
                    int[] t = new int[2];
                    t[0] = points[j][0]; t[1] = points[j][1];
                    points[j][0] = points[j + 1][0]; points[j][1] = points[j + 1][1];
                    points[j + 1][0] = t[0]; points[j + 1][1] = t[1];
                }
            }
        }

        //동일 x좌표 정렬
        if(points[0][0] == points[1][0]) {
            if(points[0][1] > points[1][1]) {
                int t = points[0][1];
                points[0][1] = points[1][1];
                points[1][1] = t;
            }
        }

        int extreme_index = find_extreme_point(points);
        //System.out.println(extreme_index);
        int[] t = new int[2];
        t[0] = points[extreme_index][0]; t[1] = points[extreme_index][1];
        points[extreme_index][0] = points[3][0]; points[extreme_index][1] = points[3][1];
        points[3][0] = t[0]; points[3][1] = t[1];
    }

    private static int find_extreme_point(int[][] points) {
        int[] arr = new int[2];
        // i : extreme point 후보
        for(int i = 1; i <= 3; i++) {
            int a = points[i][1] - points[0][1];
            int b = points[0][0] - points[i][0];
            int c = points[0][0] * points[i][1] - points[0][1] * points[i][0];
            int k = 0;
            // j : 넣을 점
            for(int j = 1; j <= 3; j++) {
                if(i == j) continue;
                arr[k++] = a * points[j][0] + b * points[j][1] - c;
            }
            //System.out.println("multiple : " + arr[0] * arr[1]);
            if (arr[0] * arr[1] < 0) {
                //System.out.println("A");
                return i;
            }
        }

        return 0;
    }
}
