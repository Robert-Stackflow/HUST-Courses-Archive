package course.ch13_19;

import java.util.ArrayList;
import java.util.List;

class A {
}

class B extends A {
}

class C extends B {
}

class D extends C {
}

public class TestPECS {
    public static <T> void m(List<? super T> list1, List<? extends T> list2) {
    }

    public static void main(String[] args) {

        //    A.
        List<B> l1 = new ArrayList<>();
        List<B> l2 = new ArrayList<>();
        m(l1, l2);
        //    B.
        List<B> l3 = new ArrayList<>();
        List<D> l4 = new ArrayList<>();
        m(l3, l4);
        //    C.
        List<B> l5 = new ArrayList<>();
        List<A> l6 = new ArrayList<>();
//        m(l5, l6);
        //    D.
        List<C> l7 = new ArrayList<>();
        List<D> l8 = new ArrayList<>();
        m(l7, l8);
        //    E.
//        <B>m(l7, l8);
        //    F.
        List<D> l9 = new ArrayList<>();
        List<C> l10 = new ArrayList<>();
//        m(l9, l10);
    }
}