package course.ch6_7;

/**
 * Test the functions of StringBuffer Class
 */
public class TestArray {
    /**
     * The entrance of program
     *
     * @param args: command line arguments
     */
    public static void main(String[] args) {
        int[] array = new int[10];
        increase(array);
        System.out.print(array[0]);
    }
    /**
     * The function increase
     *
     * @param args: 要进行操作的int数组array
     */
    public static void increase(int[] array) {
        for (int i = 0; i < array.length; i++) {
            array[i]++;
        }
    }
}