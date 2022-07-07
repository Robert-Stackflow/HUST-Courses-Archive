package Test3;

import javax.swing.*;

/**
 * Test3
 */
public class code {
    /**
     * The entrance of program
     *
     * @param args: command line arguments
     */
    public static void main(String[] args) {
        String temp = JOptionPane.showInputDialog(null, "Input the row", "InputDialog", JOptionPane.PLAIN_MESSAGE);
        printArray(createArray(Integer.parseInt(temp)));
    }

    /**
     * 创建一个不规则二维数组
     * 第一行row列
     * 第二行row - 1列
     * ...
     * 最后一行1列
     * 数组元素值都为默认值
     *
     * @param row 行数
     * @return 创建好的不规则数组
     */
    public static int[][] createArray(int row) {
        int[][] array = new int[row][];
        for (int i = 0; i < row; i++)
            array[i] = new int[row - i];
        return array;
    }

    /**
     * 逐行打印出二维数组，数组元素之间以空格分开
     *
     * @param a 二维数组
     */
    public static void printArray(int[][] a) {
        for (int[] ints : a) {
            for (int anInt : ints) {
                System.out.print(anInt);
                System.out.print(' ');
            }
            System.out.println();
        }
    }

}