package course.ch13_19;

import java.util.ArrayList;
import java.util.List;

public class TestGeneric {
    public static void main(String[] args) {
        //8
        class Shape {
        }
        class Circle extends Shape {
        }
        class Triangle extends Shape {
        }
        List<? extends Shape> list1 = new ArrayList<Triangle>();
        List<? extends Shape> list2 = new ArrayList<Circle>();

//                System.out.println(list1 instanceof List< Triangle>);
        System.out.println(list2 instanceof List);
        System.out.println(list1.getClass() == list2.getClass());
    }
//        class Holder<T> {
//            T value;
//
//            public Holder(T value) {
//                this.value = value;
//            }
//
//            public T getValue() {
//                return value;
//            }
//        }
//
//        class RawHolder {
//            Object value;
//
//            public RawHolder(Object value) {
//                this.value = value;
//            }
//
//            public Object getValue() {
//                return value;
//            }
//        }
//        /* 1 */
//        Holder<String> h1 = new Holder<>("aaa");
//        String s1 = h1.getValue();
//        System.out.println(s1);

//        //2
//        RawHolder h1 = new RawHolder("aaa");
//        String s1 = (String) h1.getValue();
//        System.out.println(s1);

//        //3
//        Holder<String> h1 =
//                new Holder<>(Integer.valueOf(111));
//        String s1 = h1.getValue();
//        System.out.println(s1);

//        //4
//        RawHolder h1 =
//                new RawHolder(Integer.valueOf(111));
//        String s1 = (String) h1.getValue();
//        System.out.println(s1);

//        //5
//        List<String> list = new ArrayList<String>();
//        list.add("test");
//        list.add("red");
//        list.add (100);
//        System.out.println(list. size ());

//        //6
//        List<Integer> ex_int= new ArrayList<Integer> ();
//        List<Number> ex_num = ex_int;
//        System.out.println(ex_num. size ());

//        //7
//        List<?> c1 = new ArrayList<String> (); c1.add (new Object ());
//        List<?> c2 = new ArrayList<String> (); c2.add (new String ("1"));
//        List<?> c3 = new ArrayList<String> (); c3.add ("1");
//        List<?> c4 = new ArrayList<String> (); c4.add(null);
}
