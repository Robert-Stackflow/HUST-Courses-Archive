package course.ch9_11;

public class Test3 {
    private double radius;
    public static int count = 0;

    public Test3(double r) {
        radius = r;
        count++;
    }

    public Test3() {
        this(1.0);
    }

    public static void main(String[] args) {
        Test3 c1 = new Test3();
        Test3 c2 = new Test3(15.0);
        c1.count++;
        c2.count++;
        Test3.count++;
        System.out.println("count =" + count);
    }
}
