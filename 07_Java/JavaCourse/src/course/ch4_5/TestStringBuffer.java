package course.ch4_5;

/**
 * Test the functions of StringBuffer Class
 */
public class TestStringBuffer {
    /**
     * The entrance of program
     *
     * @param args: command line arguments
     */
    public static void main(String[] args) {
        StringBuffer s1 = new StringBuffer("Java");
        StringBuilder s2 = new StringBuilder("HTML");
        StringBuffer s = new StringBuffer("Welcome to JAVA");
        System.out.println(s.delete(0, s.length()));
        System.out.println(s1.append("  is fun"));
        System.out.println(s1.append(s2));
        System.out.println(s1.insert(2, "is fun"));
        System.out.println(s1.insert(1, s2));
        System.out.println(s1.charAt(2));
        System.out.println(s1.length());
        System.out.println(s1.deleteCharAt(3));
        System.out.println(s1.delete(1, 3));
        System.out.println(s1.reverse());
        System.out.println(s1.replace(1, 3, "Computer"));
        System.out.println(s1.substring(1, 3));
        System.out.println(s1);
        System.out.println(s1.substring(2));
        System.out.println(s1);
    }
}
