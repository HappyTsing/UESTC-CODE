package RoutineWork.hw1_4;

public class Point{
    int x,y;
    public Point(){
        x=0;
        y=0;
    }
    public void setX(int x){
        this.x=x;
    }
    public void setY(int y){
        this.y=y;
    }
    public void getPoint(){
        System.out.printf("(%d,%d)",x,y);
    }
    public void movePoinyt(int newx,int newy){
        x=newx;
        y=newy;
    }
}
