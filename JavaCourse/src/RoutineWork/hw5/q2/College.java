package RoutineWork.hw5.q2;

public class College extends Student {
    String dir;
    //方向
    public void setData(String s,char c,int i,int sID,String speciality,String dir){
        super.setData(s,c,i,sID,speciality);
        this.dir=dir;
    }

    public String getData() {
        String stu=super.getData();
        return stu+"dir:"+dir;
    }
}
