package course.ch6_7;

import java.util.Arrays;

/**
 * Test2
 */
public class Test2 {
    /**
     * The entrance of program
     *
     * @param args: command line arguments
     */
    public static void main(String[] args) {
        int[] a = {1};
        String[] s = {"Hello"};
        int i = a[0];
        m(s, a, i);
        for (String v : s) {
            System.out.println(v);
        }
        for (int v : a) {
            System.out.println(v);
        }
        System.out.println(i);
    }
    public static void m(String[] a1, int[] a2, int i) {
        Arrays.fill(a1, "Java");
        for (int j = 0; j < a2.length; j++) {
            a2[j]++;
        }
        i++;
    }
}
