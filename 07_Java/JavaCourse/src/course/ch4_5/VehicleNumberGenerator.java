package course.ch4_5;

import java.util.ArrayList;
import java.util.List;

/**
 * Suppose a license plate number consists of three uppercase letters and four numbers after it.
 * Write a program. Randomly generated into 5 non-duplicate license plate numbers.
 */
public class VehicleNumberGenerator {
    private static final int UPPER_LETTER_LENGTH = 3;
    private static final int DIGIT_LENGTH = 4;

    /**
     * 产生指定数目的不重复车牌号码，车牌号码由三个大写字母和后面的四个数字组成
     *
     * @param n 车牌个数
     * @return 生成的车牌
     */
    public static String[] generate(int n) {
        if (n < 1)
            return null;

        List<Object> list = new ArrayList<>();
        while (list.size() < n) {
            //Generate  Uppercase Letter
            char[] letters = new char[UPPER_LETTER_LENGTH];
            for (int j = 0; j < UPPER_LETTER_LENGTH; j++) {
                letters[j] = RandomCharacter.getRandomUpperCaseLetter();
            }
            //Generate Digits
            char[] digits = new char[DIGIT_LENGTH];
            for (int j = 0; j < DIGIT_LENGTH; j++) {
                digits[j] = RandomCharacter.getRandomDigitCharacter();
            }
            String number = String.valueOf(letters) + String.valueOf(digits);

            if (!list.contains(number)) { //只有不重复，才加入list
                list.add(number);
            }

        }

        return (String[]) list.toArray(new Object[0]);
    }

    public static void print(String[] numbers) {
        for (String number : numbers) {
            System.out.println(number);
        }
    }

    public static void main(String[] args) {
        VehicleNumberGenerator.print(VehicleNumberGenerator.generate(5));
    }
}

class RandomCharacter {
    /**
     * Generate a random character between ch1 and ch2
     */
    public static char getRandomCharacter(char ch1, char ch2) {
        return (char) (ch1 + (int) (Math.random() * (ch2 - ch1 + 1)));
    }

    /**
     * Generate a random lowercase letter
     */
    public static char getRandomLowerCaseLetter() {
        return getRandomCharacter('a', 'z');
    }

    /**
     * Generate a random uppercase letter
     */
    public static char getRandomUpperCaseLetter() {
        return getRandomCharacter('A', 'Z');
    }

    /**
     * Generate a random digit character
     */
    public static char getRandomDigitCharacter() {
        return getRandomCharacter('0', '9');
    }

    /**
     * Generate a random character
     */
    public static char getRandomCharacter() {
        return getRandomCharacter('\u0000', '\uFFFF');
    }
}