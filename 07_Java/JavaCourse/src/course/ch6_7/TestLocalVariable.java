package course.ch6_7;

public class TestLocalVariable {
    public static void method1( ) {
        int x = 1; int y = 1;
        for (int i = 1; i < 10; i++) {
            x += i;
        }
        for (int i = 1; i < 10; i++) {//正确：两个循环未嵌套，二个for语句的i互不影响
            y += i;
        }
    }
    //错误，变量i在嵌套的语句块中声明：不能在嵌套块里声明同名的局部变量
    public static void method2( ) {
        int i = 1;
        int sum = 0;
//		for (int i = 1; i < 10; i++) {//
//			sum += i;
//		}
    }
}

