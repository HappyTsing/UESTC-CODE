package RoutineWork.hw1_4;

public class StudentTest {
    public static void main(String[] args) {
        Student s1 = new Student("one", "boy", 01, 19);
        Student s2 = new Student("two", "girl", 02, 20);
        Student s3 = new Student("three", "boy", 03, 13);
        s1.getAge();
        s1.getName();
        s1.getNumber();
        s1.getSex();
        s1.changeAge(18);
        s1.getAge();
        System.out.printf("\n");

        s2.getAge();
        s2.getName();
        s2.getNumber();
        s2.getSex();
        s2.changeAge(36);
        s2.getAge();
        System.out.printf("\n");

        s3.getAge();
        s3.getName();
        s3.getNumber();
        s3.getSex();
        s3.changeAge(26);
        s3.getAge();
        System.out.printf("\n");
    }
}
