package Apriori;

import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.*;

public class Util {
    public static String[] merge(boolean isPlainStr, String... stringList) {
        Set<String> set = new TreeSet<>();
        for (String str : stringList)
            set.addAll(Arrays.asList(stringToArray(isPlainStr ? arrayToString(str) : str)));
        return set.toArray(new String[0]);
    }

    public static boolean contains(List<String> stringList, String[] strings) {
        for (String str : strings)
            if (!stringList.contains(str))
                return false;
        return true;
    }

    public static String[] stringToArray(String string) {
        return string.substring(1, string.length() - 1).split(",");
    }

    public static String arrayToString(String string) {
        return "[" + string + "]";
    }

    public static String arrayToString(String[] strings) {
        StringBuilder stringBuilder = new StringBuilder("[");
        for (int i = 0; i < strings.length; i++) {
            stringBuilder.append(strings[i]);
            if (i < strings.length - 1)
                stringBuilder.append(",");
        }
        stringBuilder.append("]");
        return stringBuilder.toString();
    }

    public static void output(String fileName, Map<String, Double> map) {
        try {
            PrintWriter writer = new PrintWriter(new FileWriter(fileName, false));
            writer.printf("\"Set\",\"Frequency Or Confidence\"\n");
            for (Map.Entry<String, Double> entry : map.entrySet()) {
                String mapKey = entry.getKey();
                Double mapValue = entry.getValue();
                writer.printf("\"%s\",\"%.18f\"\n", mapKey, mapValue);
                writer.flush();
            }
            writer.close();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

}
