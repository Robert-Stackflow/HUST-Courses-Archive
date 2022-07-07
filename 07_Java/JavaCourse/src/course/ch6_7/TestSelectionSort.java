package course.ch6_7;

public class TestSelectionSort {
    public static void main(String[] args) {
        double[] list = {1.1, 0.3, 2.2, 0.5, 3.3};
        selectionSort(list);
        for (double num : list) {
            System.out.println(num);
        }
    }

    static void selectionSort(double[] list) {
        for (int i = list.length - 1; i >= 0; i--) {
            // Find the maximum in the list[0..i]
            double currentMax = list[0];
            int currentMaxIndex = 0;

            for (int j = 0; j <= i; j++) {
                if (currentMax < list[j]) {
                    currentMax = list[j];
                    currentMaxIndex = j;
                }
            }

            // Swap list[i] with list[currentMaxIndex] if necessary;
            if (currentMaxIndex != i) {
                list[currentMaxIndex] = list[i];
                list[i] = currentMax;
            }
        }
    }


}
