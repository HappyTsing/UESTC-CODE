package RoutineWork.hw1_4;

public class TestPoint {
    public static void main(String[] args) {
        Point test=new Point();
        //此时为原点值（0，0）
        test.getPoint();
        test.setX(0);
        test.setY(0);
        //设置x,y为0
        test.getPoint();
        test.movePoinyt(10,20);
        //移动到（10，20）
        test.getPoint();
        //输出
    }
}
