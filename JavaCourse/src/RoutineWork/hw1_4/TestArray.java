package RoutineWork.hw1_4;

        import java.util.Arrays;

public class TestArray {
    public static void main (String [] args){
        int [] sim={1,5,6,8,2,3,7};
        int i;
        Arrays.sort(sim);
        for(i=0;i<sim.length;i++)
            System.out.println(sim[i]);
    }
}
