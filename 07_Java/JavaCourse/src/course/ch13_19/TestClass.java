package course.ch13_19;

import java.util.ArrayList;

public class TestClass {
    public static void main(String[] args) {
        class GeometricObject {
        }
        class PolyGon extends GeometricObject {
        }
        class Rectangle extends PolyGon {
        }
        GeometricObject o = new Rectangle();
        Class clz1 = o.getClass();
        System.out.println(clz1.getSimpleName());
        Class<PolyGon> clz3 = null;
        clz3 = PolyGon.class;
//        clz3 = Rectangle.class;
        Class<? extends PolyGon> clz4 = null;
//        clz4 = GeometricObject.class;
        clz4 = PolyGon.class;
        clz4 = Rectangle.class;
        ArrayList<String> lists1 = new ArrayList<String>();
        ArrayList<? extends Object> lists = new ArrayList<String>();
        ArrayList<? super String> lists3 = new ArrayList<Object>();
        ArrayList<String> lists4 = new ArrayList();
        ArrayList lists5 = new ArrayList<String>();
    }
}
