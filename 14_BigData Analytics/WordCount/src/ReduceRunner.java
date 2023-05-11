import java.io.*;
import java.util.Map;
import java.util.Scanner;
import java.util.TreeMap;

public class ReduceRunner implements Runnable {
    private final String fileName;
    private final int index;
    private final Map<String, Integer> map;

    public ReduceRunner(int index) {
        this.index = index;
        this.fileName = Config.getReduceFileName(index);
        map = new TreeMap<>();
    }

    public Map<String, Integer> getMap() {
        return map;
    }

    private void output() throws IOException {
        if (!new File(Config.REDUCE_DIR).exists())
            new File(Config.REDUCE_DIR).mkdirs();
        PrintWriter writer = new PrintWriter(new FileWriter(fileName, false));
        for (Map.Entry<String, Integer> entry : map.entrySet()) {
            String mapKey = entry.getKey();
            Integer mapValue = entry.getValue();
            writer.println(mapKey + ":" + mapValue);
            writer.flush();
        }
        writer.close();
    }

    @Override
    public void run() {
        long startTime = System.currentTimeMillis();
        for (int i = 1; i < 10; i++) {
            String filePath = Config.getMapFileName(i) + ".part" + index;
            try {
                Scanner scanner = new Scanner(new File(filePath));
                while (scanner.hasNextLine()) {
                    String[] words = scanner.nextLine().split(",");
                    for (String word : words) {
                        word = word.trim();
                        String key = word.split(":")[0];
                        int value = Integer.parseInt(word.split(":")[1]);
                        if (map.containsKey(key)) {
                            map.put(key, map.get(key) + value);
                        } else
                            map.put(key, value);
                    }
                }
                scanner.close();
            } catch (FileNotFoundException e) {
                System.out.println(filePath + "Not Found!");
            }
        }
        try {
            output();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        long endTime = System.currentTimeMillis();
        long usedTime = endTime - startTime;
        System.out.println("Finished Reducer:" + fileName + ",Used Time:" + usedTime + "ms");
    }
}