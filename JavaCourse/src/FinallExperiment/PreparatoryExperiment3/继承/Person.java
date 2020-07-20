package FinallExperiment.PreparatoryExperiment3.继承;

public class Person {
    String name;
    char sex;
    int age;
    public Person(String name,char sex,int age){
        this.name=name;
        this.sex=sex;
        this.age=age;
    }
    public Person(){};
    public void setData(String name,char sex,int age){
        this.name=name;
        this.sex=sex;
        this.age=age;
    }
    public String getData(){
        String s_sex=String.valueOf(sex);
        String s_age=String.valueOf(age);
        return "name"+name+"sex"+s_sex+"age"+s_age;
    }
}

