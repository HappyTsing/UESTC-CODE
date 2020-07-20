package RoutineWork.hw7;


public class exceptionTest {
    public exceptionTest ()throws IndexOutOfBoundsException,NullPointerException {
        try {

            try {
                int[] a = new int[2];
                int zero = 0;
                int one = 1;
                int what;
                String str = null;
                System.out.println(str.toString());
                System.out.println(a[3]);
                what=one/zero;
                if(zero==0)
                    throw new ArithmeticException();

            } catch (IndexOutOfBoundsException e) {
                System.out.println("IndexOutOfBoundsException");
                System.out.println(e.toString());
            } finally {
                System.out.println("inner finish");
            }
        } catch (NullPointerException e) {
            System.out.println("NullPointerException");
            System.out.println(e.toString());
        } finally {
            System.out.println("outter finish");
        }
    }

    public static void main(String[] args) {
        new exceptionTest();
    }
}
