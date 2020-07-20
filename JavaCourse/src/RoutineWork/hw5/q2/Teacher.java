package RoutineWork.hw5.q2;

public class Teacher extends Person {
    int tID;
    String department;
    public void setData(String s,char c,int i,int sID,String speciality){
        super.setData(s,c,i);
        this.tID=tID;
        this.department=department;
    }

    public String getData() {
        String s_sex = String.valueOf(sex);
        String s_age = String.valueOf(age);
        String s_sID = String.valueOf(tID);
        return "name" + name + "sex" + s_sex + "age" + s_age + "tID" + s_sID + "department" + department;
    }

}
