package RoutineWork.hw1_4;

public class BigLow {
    private static String mytoUpperCase(String st) {
        String string;
        char[] ast = st.toCharArray(); //char数组
        int i, temp;
        for (i = 0; i < ast.length; i++) {
            if ((int) ast[i] >= 97) {//如果是小写字母
                temp = (int) ast[i] - 32;
                ast[i] = (char) temp;
            }
        }
        string = String.copyValueOf(ast);
        return string;
    }
    private static String mytoLowerCase(String st) {
        String string;
        char[] ast = st.toCharArray(); //char数组
        int i, temp;
        for (i = 0; i < ast.length; i++) {
            if ((int) ast[i] < 97) {//如果是大写字母
                temp = (int) ast[i] + 32;
                ast[i] = (char) temp;
            }
        }
        string = String.copyValueOf(ast);
        return string;
    }
    public static void main(String[] args) {
        String A="abstract\n" ;
        String B=mytoUpperCase(A);
        String C=mytoLowerCase(A);
        System.out.printf("%s %s",A,B);
//        System.out.println(B);
//        System.out.println(C);

    }
}


