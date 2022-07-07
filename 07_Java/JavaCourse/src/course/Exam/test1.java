package course.Exam;

import java.util.ArrayList;
import java.util.List;

class A {
    public static void s() {
        System.out.println("A_static");
    }

    public void m(int n) {
        System.out.println("A_Example");
    }
}

class B extends A {
    public static void s(int n) {
        System.out.println("B_static");
    }

    public void m(int n) {
        System.out.println("B_Example");
    }

    public void m(double n) {
        System.out.println("B_Example_Double");
    }
}

public class test1 {
    public static void main(String[] args) {
        A o1 = new B();
        B o2 = new B();
//        o1.s(1);
//        o1.m(1.0);
        o1.m(1);
        ((A) o1).m(1);
        o2.s(1);
        o1.s();
        o2.m(1);
        o2.m(1.0);
        List<A> list = new ArrayList<>();
        list.add(list.size(), new A());
        list.add(-1, new A());
    }
}
