package util;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.*;

public class FileUtil {
    private static final String movieSetFileName = "./datasets/movies.csv";
    private static final String testSetFileName = "./datasets/test_set.csv";
    private static final String trainSetFileName = "./datasets/train_set.csv";

    public static List<Record> getTrainSet() {
        List<Record> records = new ArrayList<>();
        try {
            Scanner scanner = new Scanner(new File(trainSetFileName));
            scanner.nextLine();
            while (scanner.hasNextLine()) {
                String[] nums = scanner.nextLine().split(",");
                records.add(new Record(Integer.parseInt(nums[0]), Integer.parseInt(nums[1]), Double.parseDouble(nums[2]), Long.parseLong(nums[3])));
            }
        } catch (FileNotFoundException e) {
            System.out.println(trainSetFileName + " Not Found!");
        }
        return records;
    }

    public static List<Record> getTestSet() {
        List<Record> records = new ArrayList<>();
        try {
            Scanner scanner = new Scanner(new File(testSetFileName));
            scanner.nextLine();
            while (scanner.hasNextLine()) {
                String[] nums = scanner.nextLine().split(",");
                records.add(new Record(Integer.parseInt(nums[0]), Integer.parseInt(nums[1]), Double.parseDouble(nums[2]), Long.parseLong(nums[3])));
            }
        } catch (FileNotFoundException e) {
            System.out.println(testSetFileName + " Not Found!");
        }
        return records;
    }

    public static Map<Integer, Movie> getMovieSet() {
        Map<Integer, Movie> records = new TreeMap<>();
        try {
            Scanner scanner = new Scanner(new File(movieSetFileName));
            scanner.nextLine();
            while (scanner.hasNextLine()) {
                String[] strings = scanner.nextLine().split(",");
                StringBuilder title = new StringBuilder();
                for (int i = 1; i < strings.length - 1; i++)
                    title.append(strings[i]);
                records.put(Integer.parseInt(strings[0]), new Movie(Integer.parseInt(strings[0]), title.toString(), strings[strings.length - 1]));
            }
        } catch (FileNotFoundException e) {
            System.out.println(movieSetFileName + " Not Found!");
        }
        return records;
    }
}
