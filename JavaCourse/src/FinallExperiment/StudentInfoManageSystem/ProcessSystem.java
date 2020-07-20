/*本函数类实现与数据库链接的增删查改，初步实现了增删查改的各种函数，其中：
1.add函数需要接受Student对象，来完成在数据库的添加
2.delete、update同add，但是删除是根据学号来定位的（学号唯一），即sql="XXX WHERE SchoolNo=？"
3.查询函数有四个：
  1.显示全部，即select all，无需输入，可直接调用
  2.通过学号查询，需要输入String类型的学号
  3.通过姓名查询，需要姓名
  4.通过学院查询，需要学院
具体的输入在UserMenu类中进行*/
package FinallExperiment.StudentInfoManageSystem;

import java.net.UnknownHostException;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class ProcessSystem {
    private Connection con;
    private PreparedStatement pstmt;
    private ResultSet selectRes;
    public ProcessSystem() throws SQLException, ClassNotFoundException {
    }
    //增
    public boolean add(Student stu) throws SQLException {
        String add_sql="INSERT INTO table_java_sy(SchoolNo,Name,Age,Gender,Birthday,Address,Email,College)VALUES (?,?,?,?,?,?,?,?)";
        try{
            con=SqlCon.getCon();
            pstmt=con.prepareStatement(add_sql);
            pstmt.setString(1,stu.getSchoolNo());
            pstmt.setString(2,stu.getName());
            pstmt.setString(3,stu.getAge());
            pstmt.setString(4,stu.getGender());
            pstmt.setString(5,stu.getBirthday());
            pstmt.setString(6,stu.getAddress());
            pstmt.setString(7,stu.getEmail());
            pstmt.setString(8,stu.getCollege());
            pstmt.executeUpdate();
        } catch (SQLException | ClassNotFoundException | UnknownHostException e) {
            e.printStackTrace();
        } finally {
            SqlCon.getClose(con,pstmt);
        }
        return true;
    }
    //删（学号）
    public boolean delete(Student stu) throws SQLException {
        String delete_sql="DELETE FROM table_java_sy WHERE SchoolNo=?";
        try{
            con = SqlCon.getCon();
            pstmt=con.prepareStatement(delete_sql);
            pstmt.setString(1,stu.getSchoolNo());
            pstmt.executeUpdate();

        } catch (SQLException | ClassNotFoundException | UnknownHostException e) {
            e.printStackTrace();
        } finally {
            SqlCon.getClose(con,pstmt);
        }
        return true;
    }
    //改（学号）
    public boolean update(Student stu) throws SQLException {
        String update_sql="UPDATE table_java_sy SET Name=?,Age=?,Gender=?,Birthday=?,Address=?,Email=?,College=? WHERE SchoolNo=?";
        try{
            con = SqlCon.getCon();
            pstmt=con.prepareStatement(update_sql);
            pstmt.setString(8,stu.getSchoolNo());
            pstmt.setString(1,stu.getName());
            pstmt.setString(2,stu.getAge());
            pstmt.setString(3,stu.getGender());
            pstmt.setString(4,stu.getBirthday());
            pstmt.setString(5,stu.getAddress());
            pstmt.setString(6,stu.getEmail());
            pstmt.setString(7,stu.getCollege());
            pstmt.executeUpdate();
        } catch (SQLException | ClassNotFoundException | UnknownHostException e) {
            e.printStackTrace();
        } finally {
            SqlCon.getClose(con,pstmt);
        }
        return true;
    }
    //查:by Name
    public boolean showByName(String name) throws SQLException {
        String show_name_sql="SELECT *FROM table_java_sy WHERE Name=? ORDER BY SchoolNo ASC";
        try {
            con = SqlCon.getCon();
            pstmt=con.prepareStatement(show_name_sql);
            pstmt.setString(1,name);
            selectRes=pstmt.executeQuery();
            while(selectRes.next()){
                System.out.printf("%10s  %10s  %10s  %10s  %10s  %10s  %10s  %10s",selectRes.getString("SchoolNo"),selectRes.getString("Name"),selectRes.getString("Age"),selectRes.getString("Gender"),selectRes.getString("Birthday"),selectRes.getString("Address"),selectRes.getString("Email"),selectRes.getString("College"));
                System.out.println();//换行
            }
        } catch (SQLException | ClassNotFoundException | UnknownHostException e) {
            e.printStackTrace();
        } finally {
            SqlCon.getClose(con,pstmt);
        }
        return true;
    }
    //查BY SchoolNo
    public boolean showBySchoolNo(String schoolno) throws SQLException {
        String show_schoolno_sql="SELECT *FROM table_java_sy WHERE SchoolNo=? ORDER BY SchoolNo ASC";
        try {
            con = SqlCon.getCon();
            pstmt=con.prepareStatement(show_schoolno_sql);
            pstmt.setString(1,schoolno);
            selectRes=pstmt.executeQuery();
            while(selectRes.next()){
                System.out.printf("%10s  %10s  %10s  %10s  %10s  %10s  %10s  %10s",selectRes.getString("SchoolNo"),selectRes.getString("Name"),selectRes.getString("Age"),selectRes.getString("Gender"),selectRes.getString("Birthday"),selectRes.getString("Address"),selectRes.getString("Email"),selectRes.getString("College"));
                System.out.println();//换行
            }
        } catch (SQLException | ClassNotFoundException | UnknownHostException e) {
            e.printStackTrace();
        } finally {
            SqlCon.getClose(con,pstmt);
        }
        return true;
    }
//    查BY College
    public boolean showByCollege(String college) throws SQLException {
        String show_college_sql="SELECT *FROM table_java_sy WHERE College=? ORDER BY SchoolNo ASC";
        try {
            con = SqlCon.getCon();
            pstmt=con.prepareStatement(show_college_sql);
            pstmt.setString(1,college);
            selectRes=pstmt.executeQuery();
            while(selectRes.next()){
                System.out.printf("%10s  %10s  %10s  %10s  %10s  %10s  %10s  %10s",selectRes.getString("SchoolNo"),selectRes.getString("Name"),selectRes.getString("Age"),selectRes.getString("Gender"),selectRes.getString("Birthday"),selectRes.getString("Address"),selectRes.getString("Email"),selectRes.getString("College"));
                System.out.println();//换行
            }
        } catch (SQLException | ClassNotFoundException | UnknownHostException e) {
            e.printStackTrace();
        } finally {
            SqlCon.getClose(con,pstmt);
        }
        return true;
    }
    //浏览（显示全部）
    public boolean showAll() throws SQLException {
        String all_sql="SELECT * FROM table_java_sy ORDER BY SchoolNo ASC";  //ASC升序
        try{
            con = SqlCon.getCon();
            pstmt=con.prepareStatement(all_sql);
            selectRes=pstmt.executeQuery();
//            System.out.println("SchoolNo        Name        Age     Gender      Birthday        Address     Email       College：");
            while(selectRes.next()){
                System.out.printf("%10s  %10s  %10s  %10s  %10s  %10s  %10s  %10s",selectRes.getString("SchoolNo"),selectRes.getString("Name"),selectRes.getString("Age"),selectRes.getString("Gender"),selectRes.getString("Birthday"),selectRes.getString("Address"),selectRes.getString("Email"),selectRes.getString("College"));
                System.out.println();//换行
            }
        } catch (SQLException | ClassNotFoundException | UnknownHostException e) {
            e.printStackTrace();
        } finally {
            SqlCon.getClose(con,pstmt);
        }
        return true;
    }
}
