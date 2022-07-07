public class Test5 {
    public static void main(String... args) {
        C4 o1 = new D4();
        o1.m(1, 1);            //①
        o1.m(1.0, 1.0);            //②
        o1.m(1.0f, 1.0f);        //③

        D4 o2 = new D4();
        o2.m(1, 1);            //④
        o2.m(1.0, 1.0);            //⑤
        o2.m(1.0f, 1.0f);        //⑥
    }
}

class C4 {
    public void m(int x, int y) {
        System.out.println("C's m(int,int)");
    }

    public void m(double x, double y) {
        System.out.println("C' m(double,double)");
    }
}

class D4 extends C4 {
    public void m(float x, float y) {
        System.out.println("D's m(float,float)");
    }

    public void m(int x, int y) {
        System.out.println("D's m(int,int)");
    }
}
