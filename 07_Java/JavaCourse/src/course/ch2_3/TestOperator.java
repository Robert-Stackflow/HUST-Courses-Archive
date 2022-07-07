package course.ch2_3;

/**
 * Test the difference of two kinds of logical conjunction or logical disjunction
 */
public class TestOperator {
    /**
     * The entrance of program
     *
     * @param args: command line arguments
     */
    public static void main(String[] args) {
        int x = 0, y = 0;
        System.out.println(((x > 1) && (++x == 0)) + " " + x);
        System.out.println(((y < 1) | (y++ == 0)) + " " + y);
    }
}