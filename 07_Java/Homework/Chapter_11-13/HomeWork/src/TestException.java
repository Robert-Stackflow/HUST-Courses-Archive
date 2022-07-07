import java.io.IOException;

public class TestException {
    //    public static void main(String[] args) {
//        try {
//            System.out.print(10 + 10 / 0);
//        } catch (NullPointerException e1) {
//            System.out.print("a");
//        } catch (RuntimeException e2) {
//            System.out.print("b");
//        } finally {
//            System.out.print("c");
//        }
//    }
//    public static void main(String args[]) {
//        try {
//            System.out.print("Hello Java.");
//        } finally {
//            System.out.print("Finally Java.");
//        }
//        int[] m = new int[5];
//        m[5] = 10;
//    }
    public static void main(String args[]) {
        try {
            System.out.print("try.");
            return;
        } catch (Exception e) {
            System.out.print("catch.");
        } finally {
            System.out.print("finally.");
        }
    }
    public void m1() throws IOException {
        try {
            throw new IOException();
        } catch (IOException e) {

        }
    }

    public void m2() throws IOException{
        m1();
//        try {
//            m1();
//        } catch (IOException e) {
//
//        }
    }
    public void m3() throws RuntimeException{
        throw new RuntimeException();
    }
    public void m4(){
        m3();
    }
}
