package FinallExperiment.PreparatoryExperiment3.策略模式;

public class Mypolice {
    public static void main(String args[]){
        int x=(int)(Math.random()*3);
        if(x<1){
            TanTan Mypolice=new TanTan();
            Mypolice.display();
        }
        else if(x<2){
            GoodMood Mypolice2=new GoodMood();
            Mypolice2.display();
        }
        else{
            BadMood Mypolice3=new BadMood();
            Mypolice3.display();
        }

    }
}

