package RoutineWork.hw9;

import java.io.*;
import java.util.Scanner;


public class fileTest {
    public static void main(String[] args) throws IOException {
        Scanner sca=new Scanner(System.in);

        //写文件
        File file=new File("test.txt");//文件名        相对路径（项目名根目录下）
        FileOutputStream fos=new FileOutputStream(file,true);//true表示追加，如果文件存在 向里面继续添加内容
        System.out.println("请输入写入的内容:");
        String str=sca.next();
        byte bytes[]=str.getBytes();         //FileOutputStream 是基于字节流  把要写入的信息 保存到字节数组中
        fos.write(bytes,0,bytes.length);//将字节数组中全部内容写到文件中   从0—数组的长度
        fos.close();//关闭流
        System.out.println("文件写入成功！");

        //读文件
        FileInputStream fis=new FileInputStream(file);
        byte bt[]=new byte[1024];//1KB       每次最多读取的1KB  根据文件大小而定
        int temp=0;
        while((temp=fis.read(bt))!=-1){    //将数据保存到数组（缓冲区）中 并返回读取的字节数  -1表示读完了
            System.out.println(new String(bt,0,temp));//输出数组中保存内容 按照每次读取的字节数
        }
        fis.close();

        System.out.println("文件读出成功！");
    }
}


