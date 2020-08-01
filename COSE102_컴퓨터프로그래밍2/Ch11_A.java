import java.util.ArrayList;
import java.util.Calendar;
import java.util.Scanner;

public class Ch11_A {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        ArrayList<Person> list = new ArrayList<>();
        int N = sc.nextInt();
        sc.nextLine();
        for (int n = 0; n < N; n++) {
            String[] items = sc.nextLine().split("\t");
            Person p = null;
            if (items[4].equals("Student")) {
                Student p1 = new Student();
                if (items[5].equals("FRESHMAN")) p1.status = Student.FRESHMAN;
                else if (items[5].equals("SOPHOMORE")) p1.status = Student.SOPHOMORE;
                else if (items[5].equals("JUNIOR")) p1.status = Student.JUNIOR;
                else if (items[5].equals("SENIOR")) p1.status = Student.SENIOR;
                p = p1;
            } else if (items[4].equals("Employee")) {
                Faculty p1 = new Faculty();
                if (items[5].equals("LECTURER")) p1.rank = Faculty.LECTURER;
                else if (items[5].equals("ASSISTANT_PROFESSOR")) p1.rank = Faculty.ASSISTANT_PROFESSOR;
                else if (items[5].equals("ASSOCIATE_PROFESSOR")) p1.rank = Faculty.ASSOCIATE_PROFESSOR;
                else if (items[5].equals("PROFESSOR")) p1.rank = Faculty.PROFESSOR;
                p = p1;
            } else if (items[4].equals("Staff")) {
                Staff p1 = new Staff();
                p1.title = items[5];
                p = p1;
            }
            p.name = items[0];
            p.address = items[1];
            p.phoneNumber = items[2];
            p.email = items[3];
            list.add(p);
        }
        for (Person p : list) System.out.println(p);
    }
}

class Person {
    String name;
    String address;
    String phoneNumber;
    String email;

    @Override
    public String toString() {
        return this.name + " is ";
    }
}

class Student extends Person {
    final static int FRESHMAN = 1, SOPHOMORE = 2, JUNIOR = 3, SENIOR = 4;
    int status;

    public String toString() {
        return super.toString() + "Student";
    }
}

class Employee extends Person {

    public String toString() {
        return super.toString();
    }
}

class Faculty extends Employee {
    final static int LECTURER = 1, ASSISTANT_PROFESSOR = 2, ASSOCIATE_PROFESSOR = 3, PROFESSOR = 4;
    int rank;

    public String toString() {
        return super.toString() + "Faculty";
    }
}

class Staff extends Employee {
    String title;

    public String toString() {
        return super.toString() + "Staff";
    }
}
