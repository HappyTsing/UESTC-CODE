package RoutineWork.hw1_4;

public class TestString {
    public static void main(String[] args) {
        String s1="Hello";
        String s2=s1+"World";
        int a= 0b101;
        String s3=s1.toUpperCase();
        String s4=s1.toLowerCase();
        if("Hello".equals(s1)){
            System.out.println("相等");
        }
        System.out.println("s1:"+s1);
        System.out.println("s2:"+s2);
        System.out.println("s3:"+s3);
        System.out.println("s4:"+s4);
        System.out.println(a);
    }
}
