package RoutineWork.hw1_4;

public class Student {
    String name;
    String  sex;
    int number;
    int age;
    public Student(String name,String sex,int number,int age ){
        this.name=name;
        this.sex=sex;
        this.number=number;
        this.age=age;
    }
    public void getNumber(){
        System.out.printf("学号：%d",number);
    }
    public void getName(){
        System.out.printf("名字：%s",name);
    }
    public void getSex(){
        System.out.printf("性别：%s",sex);
    }
    public void getAge(){
        System.out.printf("年龄：%d",age);
    }
    public void changeAge(int age){
        this.age=age;
    }
}
