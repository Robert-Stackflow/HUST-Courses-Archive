public class Test_Hide_Override {
    public static void main(String... args){
        A5 o = new C5();
        o.m1();			//①
        o.m2();			//②
        ((B5)o).m1();		//③
        ((A5)(B5)o).m1();		//④
        ((A5)(B5)o).m2();		//⑤
    }
}

class A5{
    public static void m1(){  System.out.println("A's m1"); }
    public void m2(){ System.out.println("A's m2"); }
}

class B5 extends A5{
    public static void m1(){  System.out.println("B's m1"); }
    public void m2(){ System.out.println("B's m2"); }
}

class C5 extends B5{
    public static void m1(){  System.out.println("C's m1"); }
    public void m2(){ System.out.println("C's m2"); }
}
