/*本类实现java同数据库的链接，有两个函数：
* getCon：链接，返回Connection对象
* getClose：Connection和Statement对象（此处是PrepareStatement）*/
package FinallExperiment.StudentInfoManageSystem;
import java.net.InetAddress;
import java.net.UnknownHostException;
import java.sql.*;

public class SqlCon {
    public static Connection getCon() throws ClassNotFoundException, SQLException, UnknownHostException {
        InetAddress ia = InetAddress.getLocalHost();
        String host = ia.getHostName();//获取计算机主机名
        String IP= ia.getHostAddress();//获取计算机IP
        System.out.println(host);
        System.out.println(IP);
        Connection conn = null;   //定义一个MYSQL链接对象
        Class.forName("com.mysql.cj.jdbc.Driver");  //MYSQL驱动
        conn = DriverManager.getConnection("jdbc:mysql://192.168.186.1:3306/database_java_sy?useUnicode=true&characterEncoding=UTF-8&serverTimezone=UTC", "root", "081008");
//        System.out.println("connecting succeed");
//        Statement stmt;
//        stmt = conn.createStatement();
        return conn;
    }
    public static void getClose(Connection conn, PreparedStatement stmt) throws SQLException {
        conn.close();
        stmt.close();
    }
}

