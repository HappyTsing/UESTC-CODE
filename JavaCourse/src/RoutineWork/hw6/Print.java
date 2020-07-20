package RoutineWork.hw6;

public interface Print {
    public void print();
}

class Print_number implements Print{

    @Override
    public void print() {
        System.out.println("number");
    }
}
class Print_string implements Print{

    @Override
    public void print() {
        System.out.println("string");
    }

}
class test{

    public static void main(String[] args) {
        Print_string str=new Print_string();
        str.print();
        Print_number num=new Print_number();
        num.print();
    }
}