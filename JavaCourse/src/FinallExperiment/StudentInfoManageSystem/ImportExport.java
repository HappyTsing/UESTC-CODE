/**
 * 本函数实现.sql文件的导入导出
 */

package FinallExperiment.StudentInfoManageSystem;

import java.io.File;
import java.io.IOException;

/**
 *  hostIP ip地址，可以是本机也可以是远程
 *  port 端口号
 *  userName 数据库的用户名
 *  password 数据库的密码
 *  savePath 备份的路径
 *  tableName 备份的表名
 *  databaseName 需要备份的数据库的名称
 *  fileName 备份文件的名称
 *  mysqldump_path mysqldump.exe的路径
 */
public class ImportExport {
    public static boolean export_database(String hostIP, String port,String userName, String password, String savePath, String databaseName, String tableName,String fileName) {
        fileName+=".sql";
        File saveFile=new File(savePath);
        if (!saveFile.exists()) {// 如果目录不存在
            saveFile.mkdirs();// 创建文件夹
        }
        if (!savePath.endsWith(File.separator)) {
            savePath = savePath + File.separator;
        }
        //拼接命令行的命令
//        String trystmt = "mysqldump -uroot -h127.0.0.1 -p081008 -P3306 database_java_sy table_java_sy>d:/user.sql";
        StringBuilder stringBuilder = new StringBuilder();
        stringBuilder.append("mysqldump").append(" -u").append(userName);
        stringBuilder.append(" -h").append(hostIP).append(" -p").append(password);
        stringBuilder.append(" -P").append(port).append(" ").append(databaseName).append(" ").append(tableName);
        stringBuilder.append(">").append(savePath).append(fileName);
//        System.out.println(stringBuilder.toString());
        try {
            //调用外部执行exe文件的javaAPI

            String mysqldump_path="C:\\Users\\59376\\Desktop\\大二\\JAVA\\sy\\";  //此处存放着mysqldump.exe，由于一开始该exe路径存在空格，因此备份文件始终大小为0!
            Process process = Runtime.getRuntime().exec("cmd /c "+mysqldump_path+stringBuilder.toString());
            if (process.waitFor() == 0) {// 0 表示线程正常终止。
                return true;
            }
        } catch (InterruptedException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
        return false;
    }
    /**
     *  ip IP地址
     *  port 端口
     *  databaseName 数据库名称
     *  userName 用户名
     *  password 密码
     *  sourcePath 源文件的路径（即你要导入的文件的路径）
     *  fileName 导入的文件名
     *  mysql_path mysql.exe的文件位置
     */
    public static boolean import_database(String ip,String port,String userName,String password,String databaseName, String sourcePath,String fileName ) {
        StringBuilder stringBuilder=new StringBuilder();
        fileName=fileName+".sql";
//        String trystmt="mysql -h127.0.0.1 -uroot -p081008 -P3306 lalala<C:\\Users\\59376\\Desktop\\大二\\JAVA\\sy\\back_up_file.sql";
        stringBuilder.append("mysql").append(" -u").append(userName).append(" -p").append(password);
        stringBuilder.append(" -h").append(ip).append(" -P").append(port).append(" ").append(databaseName);
        stringBuilder.append("<").append(sourcePath).append(fileName);
//        System.out.println(stringBuilder.toString());

        try {
            Runtime runtime = Runtime.getRuntime();
            String mysqld_path="C:\\Users\\59376\\Desktop\\大二\\JAVA\\sy\\";
           Process process =  Runtime.getRuntime().exec("cmd /c "+mysqld_path+stringBuilder.toString());
            //cmd /k在执行命令后不关掉命令行窗口  cmd /c在执行完命令行后关掉命令行窗口
//            Process process = runtime.exec("cmd /c "+mysqld_path+trystmt);
            if (process.waitFor() == 0) {// 0 表示线程正常终止。
                return true;
            }
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
            return false;
        }
        return false;
    }
}
