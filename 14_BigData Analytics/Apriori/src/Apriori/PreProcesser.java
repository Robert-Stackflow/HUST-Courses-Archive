package Apriori;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.*;

public class PreProcesser {
    private static final String fileName = "Groceries.csv";
    private static List<List<String>> data;

    public static void init() {
        data = new ArrayList<>();
        try {
            Scanner scanner = new Scanner(new File(fileName));
            scanner.nextLine();
            while (scanner.hasNextLine()) {
                String[] words = scanner.nextLine().split("\"");
                String str = words[words.length - 1];
                String[] items = str.substring(1, str.length() - 1).split(",");
                data.add(List.of(items));
            }
        } catch (FileNotFoundException e) {
            System.out.println(fileName + " Not Found!");
        }
    }

    public static List<List<String>> getData() {
        return data;
    }
}
