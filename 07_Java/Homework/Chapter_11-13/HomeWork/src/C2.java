interface I {
}

class A2 implements I {
}

class B2 extends A2 {
}

public class C2 extends B2 {
    public static void main(String[] args) {
        B2 b = new B2();
        C2 c = (C2) b;
        B2 d = (B2) (A2) b;
        I i = b;
        A2 a = b;
    }
}
