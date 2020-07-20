package RoutineWork.hw8;

public class testThread {
    public testThread(){
        FirstThread first=new FirstThread();
        SecondThread second=new SecondThread();
        thirdThread third= new thirdThread();
        lastThread last= new lastThread();

        Thread thread1=new Thread(first);
        Thread thread2=new Thread(second);
        Thread thread3=new Thread(third);
        Thread thread4=new Thread(last);
        thread1.start();
        thread2.start();
        thread3.start();
        thread4.start();
    }

    public static void main(String[] args) {
        new testThread();
    }
}
