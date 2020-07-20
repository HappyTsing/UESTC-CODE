/*本类主要实现下述功能：
1.打印菜单界面，反复运行，直至用户输入8，即退出选项
2.switch菜单选择
3.具体实现菜单选择下的各个函数
   1.myAdd，该函数可反复调用直至选择退出（为了测数数据输入的方便，其余如删、改、查函数均只运行一次，需要在菜单重新进入）
      实现方法：从键盘接收所有学生属性，然后构造Student对象stu，构造ProcessSystem对象sys，将stu传入sys.add(stu)，完成在数据库中添加该学生数据
   2.myUpdate，该函数先从键盘接收要修改的学生的学号，然后显示该学生的其他信息，询问是否删除：
      修改实现：从键盘接收学生除了学号外所有的属性，然后构造Student对象stu，构造ProcessSystem对象sys，将stu传入sys.update(stu),实现更新修改
   3.myDelete，基本同myUpdate
   4.查询函数：接收相应内容，传入sys的函数，即可实现。
*/
package FinallExperiment.StudentInfoManageSystem;

import java.sql.SQLException;
import java.util.Scanner;

public class UserMenu {
    public void menu() throws SQLException, ClassNotFoundException {

        int choose;
        do {
            System.out.println("******************************");
            System.out.println("==== 欢迎进入学生信息管理系统====");
            System.out.println("*********1.新增学生************");
            System.out.println("*********2.修改学生************");
            System.out.println("*********3.删除学生************");
            System.out.println("*********4.显示总表************");
            System.out.println("*********5.查询姓名************");
            System.out.println("*********6.查询学号************");
            System.out.println("*********7.查询学院************");
            System.out.println("*********8.导出数据************");
            System.out.println("*********9.导入数据************");
            System.out.println("*********0.退出系统************");
            System.out.println("********请键入您的选择**********");
            Scanner scanner = new Scanner(System.in);
            choose = scanner.nextInt();

            switch (choose) {
                case 1:
                    myAdd(); //菜单选择1，是新增学生
                    break;
                case 2:
                    myUpdate();  //菜单选择2，是修改学生
                    break;
                case 3:
                    myDelete();  //菜单选择3，是删除学生
                    break;
                case 4:
                    myShowAll();  //菜单选择4，是显示总表
                    break;
                case 5:
                    myShowByName();  //菜单选择5，通过姓名查询学生
                    break;
                case 6:
                    myShowBySchoolNo();  //菜单选择6，通过学号查询学生
                    break;
                case 7:
                    myShowByCollege();  //菜单选择7，通过学院查询学生
                    break;
                case 8:
                    myExport_database();
                    break;
                case 9:
                    myImport_database();
                    break;
                case 0:     //菜单选择8，是退出该系统
                    System.out.println("您选择了退出系统，确定要退出吗？(y/n)");
                    Scanner scan = new Scanner(System.in);
                    String scanExit = scan.next();
                    if (scanExit.equals("y")) {
                        System.exit(-1);
                        System.out.println("您已成功退出系统，欢迎您再次使用！");
                    }
                    break;
                default:
                    System.out.println("请输入有效选择！");
                    break;
            }
        } while (choose != 0);
    }

    //增加
    public void myAdd() throws SQLException, ClassNotFoundException {

        String continute;
        do {
            Scanner s = new Scanner(System.in);
            String SchoolNo;  //学号
            String Name;      //姓名
            String Age;       //年龄
            String Gender;    //性别
            String Birthday;  //出生年月
            String Address;   //地址
            String Email;     //邮箱
            String College;   //学院

            System.out.println("====新增学生====");
            System.out.println("学号：");
            SchoolNo = s.next();
            System.out.println("姓名：");
            Name = s.next();
            System.out.println("年龄：");
            Age = s.next();
            System.out.println("性别：");
            Gender = s.next();
            System.out.println("生日：");
            Birthday = s.next();
            System.out.println("地址：");
            Address = s.next();
            System.out.println("邮箱：");
            Email = s.next();
            System.out.println("学院：");
            College = s.next();

            Student stu = new Student(SchoolNo, Name, Age, Gender, Birthday, Address, Email, College);
            ProcessSystem sys = new ProcessSystem();
            boolean succeed = sys.add(stu);
            if (succeed) {
                System.out.println("添加成功！");
            } else {
                System.out.println("添加失败！");
            }
            System.out.println("是否继续添加(y/n)：");
            Scanner scanner2 = new Scanner(System.in);
            continute = scanner2.next();
        } while (continute.equals("y"));
    }

    //删除
    public void myDelete() throws SQLException, ClassNotFoundException {
        Scanner s = new Scanner(System.in);
        String schoolno;
        System.out.println("====删除学生====");
        System.out.println("请输入要删除的学生学号：");
        schoolno = s.next();
        System.out.println("该学生的信息如下：");

        ProcessSystem sys = new ProcessSystem();
        sys.showBySchoolNo(schoolno);

        System.out.print("是否确认删除(y/n)：");
        Scanner scanner3 = new Scanner(System.in);
        String x = scanner3.next();
        if (x.equals("y")) {
            Student stu = new Student(schoolno);
            boolean ok = sys.delete(stu);
            if (ok) {
                System.out.println("删除成功！");
            } else {
                System.out.println("删除失败！");
            }
        }
    }

    //修改
    public void myUpdate() throws SQLException, ClassNotFoundException {
        Scanner s = new Scanner(System.in);
        String schoolno;
        System.out.println("====修改学生====");
        System.out.println("请输入要修改的学生学号：");
        schoolno = s.next();
        System.out.println("该学生的信息如下：");
        ProcessSystem sys = new ProcessSystem();
        sys.showBySchoolNo(schoolno);

        System.out.println("请输入新的学生信息：");
//        String SchoolNo;  //学号,学号唯一指定，不允许更改
        String Name;      //姓名
        String Age;       //年龄
        String Gender;    //性别
        String Birthday;  //出生年月
        String Address;   //地址
        String Email;     //邮箱
        String College;   //学院

        System.out.println("姓名：");
        Name = s.next();
        System.out.println("年龄：");
        Age = s.next();
        System.out.println("性别：");
        Gender = s.next();
        System.out.println("生日：");
        Birthday = s.next();
        System.out.println("地址：");
        Address = s.next();
        System.out.println("邮箱：");
        Email = s.next();
        System.out.println("学院：");
        College = s.next();
        Student stu = new Student(schoolno, Name, Age, Gender, Birthday, Address, Email, College);
        boolean ok = sys.update(stu);
        if (ok) {
            System.out.println("修改成功！");
        } else {
            System.out.println("修改失败！");
        }
    }

    //显示全部
    public void myShowAll() throws SQLException, ClassNotFoundException {
        ProcessSystem sys = new ProcessSystem();
        System.out.println("====全部名单====");
        boolean ok = sys.showAll();
        if (ok) {
            System.out.println("显示成功！");
        } else {
            System.out.println("显示失败！");
        }
    }

    //通过姓名查询
    public void myShowByName() throws SQLException, ClassNotFoundException {
        Scanner s = new Scanner(System.in);
        String name;
        System.out.println("====姓名查询====");
        System.out.println("请输入要查询的学生姓名：");
        name = s.next();
        System.out.println("该学生的信息如下：");
        ProcessSystem sys = new ProcessSystem();
        boolean ok = sys.showByName(name);
        if (ok) {
            System.out.println("查询成功！");
        } else {
            System.out.println("查询失败！");
        }
    }

    //通过学号查询
    public void myShowBySchoolNo() throws SQLException, ClassNotFoundException {
        Scanner s = new Scanner(System.in);
        String schoolno;
        System.out.println("====学号查询====");
        System.out.println("请输入要查询的学生学号：");
        schoolno = s.next();
        System.out.println("该学生的信息如下：");
        ProcessSystem sys = new ProcessSystem();
        boolean ok = sys.showBySchoolNo(schoolno);
        if (ok) {
            System.out.println("查询成功！");
        } else {
            System.out.println("查询失败！");
        }
    }

    //通过学院查询
    public void myShowByCollege() throws SQLException, ClassNotFoundException {
        Scanner s = new Scanner(System.in);
        String college;
        System.out.println("====学院查询====");
        System.out.println("请输入要查询的学生学院：");
        college = s.next();
        System.out.println("该学生的信息如下：");
        ProcessSystem sys = new ProcessSystem();
        boolean ok = sys.showByCollege(college);
        if (ok) {
            System.out.println("查询成功！");
        } else {
            System.out.println("查询失败！");
        }
    }

    public void myExport_database() {
        String hostIP, port,userName, password, savePath, tableName, databaseName,fileName;
        Scanner s = new Scanner(System.in);
        System.out.println("输入IP地址（127.0.0.1或者localhost）：");
        hostIP = s.next();
        System.out.println("输入端口地址（3306）：");
        port = s.next();
        System.out.println("输入数据库用户名（root)：");
        userName = s.next();
        System.out.println("输入数据库密码（081008)：");
        password = s.next();
        System.out.println("输入备份/导出路径（C:\\Users\\59376\\Desktop\\大二\\JAVA\\sy\\)：");
        savePath = s.next();
        System.out.println("输入备份的数据库名称（database_java_sy)：");
        databaseName = s.next();
        System.out.println("输入备份的表名（table_java_sy)：");
        tableName = s.next();
        System.out.println("输入备份数据表的文件名(back_up_file)：");   //在export_database()函数实现中会自动为它添加.sql后缀
        fileName=s.next();
        if (ImportExport.export_database(hostIP, port,userName, password, savePath, databaseName, tableName,fileName)) {
            System.out.println("备份成功！");
        } else {
            System.out.println("备份失败！");
        }

//        String mysqldump_path="C:\\Users\\59376\\Desktop\\大二\\JAVA\\sy\\";
//        String trystmt = "mysqldump -uroot -h127.0.0.1 -p081008 -P3306 database_java_sy table_java_sy>d:/user.sql";
//        try {
//            //调用外部执行exe文件的javaAPI
//            Process process = Runtime.getRuntime().exec("cmd /c "+mysqldump_path+trystmt);
//            if (process.waitFor() == 0) {// 0 表示线程正常终止。
//            }
//        } catch (InterruptedException | IOException e) {
//            e.printStackTrace();
//        }
    }

    public void myImport_database() {
        String ip,port,userName,password,databaseName,sourcePath,fileName;
        Scanner s=new Scanner(System.in);
        System.out.println("输入IP地址(localhost)：");
        ip=s.next();
        System.out.println("输入端口地址(3306)");
        port=s.next();
        System.out.println("输入用户名(root)：");
        userName=s.next();
        System.out.println("输入密码(081008)：");
        password=s.next();
        System.out.println("输入数据库名称：");
        databaseName=s.next();
        System.out.println("输入导入文件路径（C:\\Users\\59376\\Desktop\\大二\\JAVA\\sy\\）");
        sourcePath=s.next();
        System.out.println("输入导入文件名（back_up_file）");  //不需要后缀，在import_database中自动添加
        fileName=s.next();
        ImportExport.import_database(ip,port,userName, password, databaseName,  sourcePath, fileName);
        System.out.println("导入成功！");
    }
}
