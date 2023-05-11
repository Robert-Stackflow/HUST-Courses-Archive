import java.io.*;
import java.util.Map;
import java.util.Scanner;
import java.util.TreeMap;

public class MapRunner implements Runnable {
    private final int index;
    private final String fileName;
    private final Map<String, Integer> map;

    public MapRunner(int index) {
        this.index = index;
        this.fileName = Config.getSourceFileName(index);
        map = new TreeMap<>();
    }

    public Map<String, Integer> getMap() {
        return map;
    }

    private int shuffle(String key) {
        if (key.charAt(0) >= 'd' && key.charAt(0) <= 'o')
            return 2;
        else if (key.charAt(0) >= 'p' && key.charAt(0) <= 'z')
            return 3;
        else
            return 1;
    }

    private void output() throws IOException {
        if (!new File(Config.MAP_DIR).exists())
            new File(Config.MAP_DIR).mkdirs();
        PrintWriter writer1 = new PrintWriter(new FileWriter(Config.getMapFileName(index) + ".part1", false));
        PrintWriter writer2 = new PrintWriter(new FileWriter(Config.getMapFileName(index) + ".part2", false));
        PrintWriter writer3 = new PrintWriter(new FileWriter(Config.getMapFileName(index) + ".part3", false));
        for (Map.Entry<String, Integer> entry : map.entrySet()) {
            String mapKey = entry.getKey();
            Integer mapValue = entry.getValue();
            switch (shuffle(mapKey)) {
                case 1 -> writer1.println(mapKey + ":" + mapValue);
                case 2 -> writer2.println(mapKey + ":" + mapValue);
                case 3 -> writer3.println(mapKey + ":" + mapValue);
            }
        }
        writer1.flush();
        writer1.close();
        writer2.flush();
        writer2.close();
        writer3.flush();
        writer3.close();
    }

    @Override
    public void run() {
        long startTime = System.currentTimeMillis();
        try {
            Scanner scanner = new Scanner(new File(fileName));
            while (scanner.hasNextLine()) {
                String[] words = scanner.nextLine().split(",");
                for (String word : words) {
                    word = word.trim();
                    if (map.containsKey(word)) {
                        map.put(word, map.get(word) + 1);
                    } else
                        map.put(word, 1);
                }
            }
            scanner.close();
        } catch (FileNotFoundException e) {
            System.out.println(fileName + "Not Found!");
        }
        try {
            output();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        long endTime = System.currentTimeMillis();
        long usedTime = endTime - startTime;
        System.out.println("Finished Mapper:source0" + index + ",Used Time:" + usedTime+"ms");
    }
}