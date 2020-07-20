    /*本函数对学生进行了封装，具有属性如下：
    * 利用重载定义了两个构造函数，其一参数包含学生所有属性，其二参数仅包含学号
    * 因在删除和更新时所传入的Student对象只需要知道学号，其他属性无用，故构造学生对象时，只需要提供学号属性即可*/
    package FinallExperiment.StudentInfoManageSystem;

    public class Student {
        private String SchoolNo;  //学号
        private String Name;      //姓名
        private String Age;       //年龄
        private String Gender;    //性别
        private String Birthday;  //出生年月
        private String Address;   //地址
        private String Email;     //邮箱
        private String College;   //学院
        public Student(String SchoolNo ,String Name,String Age,String Gender,String Birthday,String Address,String Email,String College){
            this.SchoolNo=SchoolNo;
            this.Name=Name;
            this.Age=Age;
            this.Gender=Gender;
            this.Birthday=Birthday;
            this.Address=Address;
            this.Email=Email;
            this.College=College;
        }

        public Student(String SchoolNo){
            this.SchoolNo=SchoolNo;
        }

        public String getAge() {
            return Age;
        }

        public String getBirthday() {
            return Birthday;
        }

        public String getCollege() {
            return College;
        }

        public String getEmail() {
            return Email;
        }

        public String getGender() {
            return Gender;
        }

        public String getSchoolNo() {
            return SchoolNo;
        }

        public String getAddress() {
            return Address;
        }

        public String getName(){
            return Name;
        }

    //    public void setAddress(String address) {
    //        Address = address;
    //    }
    //
    //    public void setAge(String age) {
    //        Age = age;
    //    }
    //
    //    public void setBirthday(String birthday) {
    //        Birthday = birthday;
    //    }
    //
    //    public void setCollege(String college) {
    //        College = college;
    //    }
    //
    //    public void setEmail(String email) {
    //        Email = email;
    //    }
    //
    //    public void setGender(String gender) {
    //        Gender = gender;
    //    }
    //
    //    public void setName(String name) {
    //        Name = name;
    //    }
    //
    //    public void setSchoolNo(String Schoolno) {
    //        SchoolNo = Schoolno;
    //    }

    }

