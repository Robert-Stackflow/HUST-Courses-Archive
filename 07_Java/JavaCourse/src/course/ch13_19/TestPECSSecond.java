package course.ch13_19;

import java.util.ArrayList;
import java.util.List;

public class TestPECSSecond {
    public static void m1(List<? extends A> list) {
    }

    public static void m2(List<A> list) {
    }

    public static void m3(List<? super A> list) {
    }

    public static void main(String[] args) {
        List<A> listA = new ArrayList<A>();
        List<B> listB = new ArrayList<B>();
        List<Object> listO = new ArrayList<Object>();

        m1(listA);
        m2(listA);
        m3(listA);
        m1(listB);
//        m2(listB);
//        m3(listB);
//        m1(listO);
//        m2(listO);
        m3(listO);
    }
}
