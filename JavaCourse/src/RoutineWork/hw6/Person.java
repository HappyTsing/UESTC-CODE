package RoutineWork.hw6;

public interface Person {
    void setDate(String name,String sex,String birthday);
    String getDate();
}

class Student implements Person {
    private String name;
    private String sex;
    private String birthday;
    private String sID;
    private String speciality;


    @Override
    public void setDate(String name, String sex, String birthday) {
        this.name = name;
        this.sex = sex;
        this.birthday = birthday;
    }
    public void my_setDate(String name, String sex, String birthday,String sID,String speciality) {
        this.setDate(name,sex,birthday);
        this.sID=sID;
        this.speciality=speciality;
    }

    @Override
    public String getDate() {
        return "名字" + name + "性別" + sex + "生日" + birthday + "ID" + sID + "专业" + speciality;
    }

    public static void main(String[] args) {
        Student stu=new Student();
        stu.my_setDate("name","girl","2.30","007","java");
        System.out.println(stu.getDate());
    }
}
