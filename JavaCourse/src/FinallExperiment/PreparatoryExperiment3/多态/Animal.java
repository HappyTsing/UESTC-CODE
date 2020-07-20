package FinallExperiment.PreparatoryExperiment3.多态;

public class Animal {

    public static void main(String args[]){

        Rodent[] MyRodent =new Rodent[4];
        MyRodent[0]=new Rodent();
        MyRodent[1]=new Mouse();
        MyRodent[2]=new Gerbil();
        MyRodent[3]=new Hamster();
        System.out.print("Rodent:");
        MyRodent[0].eat();
        System.out.print("Mouse:");
        MyRodent[1].eat();
        System.out.print("Gerbil:");
        MyRodent[2].eat();
        System.out.print("Hamster:");
        MyRodent[3].eat();
    }
}
