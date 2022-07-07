package course.ch6_7;

public class A {
    public static void staticMethodOfA1() {
    }

    public void instancMethodOfA1() {
    }

    public void instancMethodOfA2() {
        //调用实例方法必须通过对象引用
        instancMethodOfA1();        //调用当前类的另一个实例方法，实际上和下面语句等价
        this.instancMethodOfA1();   //推荐用this.调用当前类的另一个实例方法，this就是指向当前对象的引用

        //调用静态方法

        A.staticMethodOfA1();   //推荐通过类名调用静态方法
        staticMethodOfA1();     //如果调用当前类的静态方法，类名可以省略
        B.staticMethodOfB();    //调用另外一个类的静态方法必须用类名

        //调用另外一个类的实例方法必须通过指向另外一个类的对象的引用
        new B().instancMethodOfB();
    }
}
