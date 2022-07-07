package course.ch6_7;

public class TestAmbiguousOverloading {
    public static void main(String[] args) {
//        System.out.println(max(1, 2));  //该调用产生歧义
        //以下任一函数的参数都相容（都能自动转换），编译无法确定用哪个函数
    }

    public static double max(int num1, double num2) {
        return (num1 > num2) ? num1 : num2;
    }

    public static double max(double num1, int num2) {
        return (num1 > num2) ? num1 : num2;
    }
}
