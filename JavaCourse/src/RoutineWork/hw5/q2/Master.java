package RoutineWork.hw5.q2;

public class Master extends College {
    String dis;
    //研究方向
    public void setData(String s,char c,int i,int sID,String speciality,String dir,String dis){
        super.setData(s,c,i,sID,speciality,dir);
        this.dis=dis;
    }

    public String getData() {
        String col=super.getData();
        return col+"dis:"+dis;
    }

    public static void main(String[] args) {
        Master a=new Master();
        a.setData("a",'b',2,2,"a","b","c");
        String b=a.getData();
        System.out.println(b);
    }
}

