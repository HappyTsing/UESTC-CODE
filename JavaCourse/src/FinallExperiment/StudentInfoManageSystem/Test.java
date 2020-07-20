    package FinallExperiment.StudentInfoManageSystem;

    import java.sql.SQLException;
    //测试用类
    //待解决问题：
    // 1.重新运行后数据库会被清空：似乎不存在该问题，解决
    // 2.在命令行输出没有对齐：已解决
    // 3.connection succeed会显示，一些其他的奇怪输出之类的：已解决
    // 4.实现数据库的导入、导出、备份：默认导出即备份：已解决
    public class Test {
        public static void main(String[] args) throws SQLException, ClassNotFoundException {
            UserMenu s=new UserMenu();
            s.menu();
        }
    }
