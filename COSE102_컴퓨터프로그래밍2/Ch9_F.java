import java.util.*;

public class Ch9_F {
    public static void main(String args[]) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();

        Fan1 fan1 = new Fan1();
        for (int i = 0; i < n; i++) {
            String op = sc.next();
            String val = sc.next();
            if (op.compareTo("speed") == 0) {
                if (val.compareTo("SLOW") == 0) fan1.setSpeed(Fan1.SLOW);
                else if (val.compareTo("FAST") == 0) fan1.setSpeed(Fan1.FAST);
                else fan1.setSpeed(Fan1.MEDIUM);
            } else if (op.compareTo("radius") == 0) {
                fan1.setRadius(Double.parseDouble(val));
            } else if (op.compareTo("color") == 0) {
                fan1.setColor(val);
            } else if (op.compareTo("on") == 0) {
                if (val.compareTo("true") == 0) fan1.setOn(true);
                else fan1.setOn(false);
            }
        }
        System.out.println(fan1.toString());
    }
}

class Fan1 {
    final static int SLOW = 1, MEDIUM = 2, FAST = 3;
    int speed;
    boolean on;
    double radius;
    String color;

    Fan1() {
        this.speed = 1;
        this.on = false;
        this.radius = 5.00;
        this.color = "blue";
    }

    void setSpeed(int speed) {
        this.speed = speed;
    }

    void setRadius(double radius) {
        this.radius = radius;
    }

    void setColor(String color) {
        this.color = color;
    }

    void setOn(boolean onoff) {
        this.on = onoff;
    }

    public String toString() {
        if(this.on) {
            String newStr = String.format("speed %d\ncolor %s\nradius %.2f", this.speed, this.color, this.radius);
            return newStr;
        }
        else {
            String newStr = String.format("color %s\nradius %.2f\nfan is off", this.color, this.radius);
            return newStr;
        }
    }
}

