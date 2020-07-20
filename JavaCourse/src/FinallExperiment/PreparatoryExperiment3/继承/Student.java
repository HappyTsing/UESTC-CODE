package FinallExperiment.PreparatoryExperiment3.继承;

import java.util.Scanner;

public class Student extends Person {
    int sID;
    int classNO;

    public Student(String name, char sex, int age) {
        super(name, sex, age);
    }
    public Student(){};

    public void setData(String name, char sex, int age,int sID,int classNO) {
        super.setData(name, sex, age);
        this.sID=sID;
        this.classNO=classNO;
    }
    public String getDate(){
        String s_sex=String.valueOf(sex);
        String s_age=String.valueOf(age);
        String s_sID=String.valueOf(sID);
        String s_classNO=String.valueOf(classNO);
        return "name"+name+"sex"+s_sex+"age"+s_age+"sID"+s_sID+"classNO"+s_classNO;
    }

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        Student MyStu=new Student();
        System.out.print("Please input the name of the student:");
        String name=in.next();
        System.out.print("Please input the sex of the student:");
        String temp=in.next();
        char sex=temp.charAt(0);
        System.out.print("Please input the age of the student:");
        int age=in.nextInt();
        System.out.print("Please input the ID of the student:");
        int sID=in.nextInt();
        System.out.print("Please input the class number of the student:");
        int classNo=in.nextInt();
        MyStu.setData(name,sex,age,sID,classNo);
        System.out.println(MyStu.getDate());
    }
}
