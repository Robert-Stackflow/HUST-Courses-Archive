package course.ch4_5;

/**
 * Test the functions of String Class
 */
public class TestString {
    /**
     * The entrance of program
     *
     * @param args: command line arguments
     */
    public static void main(String[] args) {
        String s1 = "Welcome to Java";
        String s2 = s1;
        String s3 = new String("Welcome to Java");
        String s4 = s3.intern();
        String s5 = "Wel" + "come to Java";
        String s6 = "Wel";
        String s7 = "come to Java";
        String s8 = s6 + s7;
        String s9 = "Wel" + new String("come to Java");
        System.out.println(s4);
        System.out.println(s5);
        System.out.println(s8);
        System.out.println(s9);
        System.out.println(s1 == s2);
        System.out.println(s1 == s3);
        System.out.println(s1 == s4);
        System.out.println(s1 == s5);
        System.out.println(s1 == s8);
        System.out.println(s1 == s9);
        System.out.println(s1.equals(s2));
        System.out.println(s2.equals(s3));
        System.out.println(s1.equals(s4));
        System.out.println(s2.equals(s5));
        System.out.println(s1.equals(s8));
        System.out.println(s1.equals(s9));
        System.out.println(s1.compareTo(s2));
        System.out.println(s2.compareTo(s3));
        System.out.println(s1.charAt(0));
        System.out.println(s1.indexOf('j'));
        System.out.println(s1.indexOf("to"));
        System.out.println(s1.lastIndexOf("o", 15));
        System.out.println(s1.substring(3, 11));
        System.out.println(s1.endsWith("Java"));
        System.out.println(s1.startsWith("wel"));
        System.out.println("   We come  ".trim());
        System.out.println(s1.toUpperCase());
        System.out.println(s1.replace('o', 'T'));
    }
}
