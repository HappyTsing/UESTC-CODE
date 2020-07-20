package RoutineWork.hw5.q2;

public class Student extends Person {
    int sID;
    String speciality;
    public void setData(String s,char c,int i,int sID,String speciality){
        super.setData(s,c,i);
        this.sID=sID;
        this.speciality=speciality;
    }

    public String getData() {
        String s_sex = String.valueOf(sex);
        String s_age = String.valueOf(age);
        String s_sID = String.valueOf(sID);
        return "name:" + name + "sex:" + s_sex + "age:" + s_age + "sID:" + s_sID + "speciality:" + speciality;
    }

}
