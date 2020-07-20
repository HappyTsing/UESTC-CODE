package RoutineWork.hw5.q2;

public abstract class Person {
    String name;
    char sex;
    int age;
    public void setData(String s,char c,int i){
        name=s;
        sex=c;
        age=i;
    }
    public abstract String getData();
}
