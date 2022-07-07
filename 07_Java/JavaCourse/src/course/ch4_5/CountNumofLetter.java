package course.ch4_5;

import javax.swing.*;

/**
 * Enter an English string from the console or dialog box
 * count the number of times each English letter in the string appears
 * and output it to the console (case-insensitive)
 */
public class CountNumofLetter {
    /**
     * The entrance of program
     *
     * @param args: command line arguments
     */
    public static void main(String[] args) {
        String temp = JOptionPane.showInputDialog(null, "Input an English String", "InputDialog", JOptionPane.PLAIN_MESSAGE);
        String lowerTemp = temp.toLowerCase();
        System.out.println("Your Input:" + lowerTemp);
        StringBuilder pend = new StringBuilder(lowerTemp);
        int[] count = new int[26];
        for (int i = 0; i < pend.length(); i++)
            count[pend.charAt(i) - 'a']++;
        for (int i = 0; i < 26; i++)
            System.out.printf("%c or %c : %d\n", 'a' + i, 'A' + i, count[i]);
    }
}
