interface I1 {
}

interface I2 extends I1 {
}

public class Test {
    public static void main(String[] args) {
        class A implements I2 {
        }
        class B extends A {
        }
        A o1=new B();
        I1 o2= new B();
        I2 o3=new B();
        B o4=new B();
    }
}
