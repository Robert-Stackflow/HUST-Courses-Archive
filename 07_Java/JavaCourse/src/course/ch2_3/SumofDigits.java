package course.ch2_3;

import java.util.Scanner;

/**
 * Calculate the sum of the digits of a number between 0 and 1000
 */
public class SumofDigits {
    /**
     * The entrance of program
     *
     * @param args: command line arguments
     */
    public static void main(String[] args) {
        int num, sum = 0;
        System.out.println("Enter a number between 0 and 1000:");
        num = new Scanner(System.in).nextInt();
        for (; num > 0; num /= 10)
            sum += num % 10;
        System.out.println("The sum of the digits is " + sum);
    }
}
