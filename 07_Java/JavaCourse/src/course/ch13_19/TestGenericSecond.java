package course.ch13_19;

import java.util.ArrayList;
import java.util.List;

public class TestGenericSecond {
    public static void main(String[] args) {
        List<? extends Comparable<Double>> x8 = new ArrayList<Double>();
//        List<? extends Number> x9 = new ArrayList<int> ();
    }
}
