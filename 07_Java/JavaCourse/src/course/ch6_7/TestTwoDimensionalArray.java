package course.ch6_7;

/**
 * Test two-dimensional array
 */
public class TestTwoDimensionalArray {
    /**
     * The entrance of program
     *
     * @param args: command line arguments
     */
    public static void main(String[] args) {
        String[][] a = {
                {"Beijing", "Wuhan"},
                {"Shanghai", "Guangzhou", "Xian"},
                {"Chongqing", "Chengdu"}
        };
        System.out.println(a[a.length - 1].length);
        System.out.println(a[a.length - 1][a[a.length - 1].length - 1].length());
        String[] s = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
        System.out.println(s.length);
        System.out.println(s[1].length());
    }
}
