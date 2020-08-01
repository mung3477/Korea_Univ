import java.util.Scanner;

public class Ch8_J {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int T = sc.nextInt();
        for(; T > 0; T--) {
            int[][] points = new int[4][2];

            //save points
            for(int i = 0; i < 4; i++) {
                for(int j = 0; j < 2; j++) {
                    points[i][j] = sc.nextInt();
                }
            }

            //check whether this is square or not
            if(is_square(points)) { System.out.println("square"); }
            else { System.out.println("not square"); }
        }
    }

    private static boolean is_square(int[][] points) {
           double[] G = new double[2];
           G[0] = (points[0][0] + points[1][0] + points[2][0] + points[3][0]) / 4.0;
           G[1] = (points[0][1] + points[1][1] + points[2][1] + points[3][1]) / 4.0;

           if(!same_distFromG(points, G)) return false;

           double d = (G[0] - points[0][0]) * (G[0] - points[0][0]) + (G[1] - points[0][1]) * (G[1] - points[0][1]);
           //System.out.println(d);
           int[] distances = new int[6];
           int k = 0;
           for(int i = 0; i < points.length - 1; i++) {
               for(int j = i + 1; j < points.length; j++) {
                   distances[k++] = (points[i][0] - points[j][0]) * (points[i][0] - points[j][0]) + (points[i][1] - points[j][1]) * (points[i][1] - points[j][1]);
                   //System.out.println(distances[k++]);
               }
           }

           if(!check_distances(distances, d)) return false;
           else return true;
    }

    private static boolean same_distFromG(int[][] points, double[] G) {
        double dist = 0.0;
        for(int i = 0; i < points.length; i++) {
            double d = (G[0] - points[i][0]) * (G[0] - points[i][0]) + (G[1] - points[i][1]) * (G[1] - points[i][1]);
            if(d == 0) return false;

            if(i == 0) dist = d;
            else {
                if (d != dist) return false;
            }
        }
        return true;
    }

    private static boolean check_distances(int[] distances, double d) {
        for(int i = 0; i < distances.length; i++) {
            if(distances[i] == 0) return false;

            if((double)(distances[i]) == 4 * d || (double)(distances[i]) == 2 * d)
                continue;
            else
                return false;
        }
        return true;
    }
}

