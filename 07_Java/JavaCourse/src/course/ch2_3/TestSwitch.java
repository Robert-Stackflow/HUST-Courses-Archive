package course.ch2_3;

import java.util.Scanner;

/**
 * Test switch statement
 */
public class TestSwitch {
    /**
     * The entrance of program
     *
     * @param args: command line arguments
     */
    public static void main(String[] args) {
        System.out.print("Please input your choice[1,2]:");
        int i = new Scanner(System.in).nextInt();
        switch (i) {
            case 1:
                System.out.println("Your choice is 1");
                break;
            case 2:
                System.out.println("Your choice is 2");
                break;
            default:
                System.out.println("Wrong choice");
                break;
        }
    }
}
