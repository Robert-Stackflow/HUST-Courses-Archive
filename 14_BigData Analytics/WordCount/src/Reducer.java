import java.io.*;
import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class Reducer {
    static ExecutorService executorService = Executors.newCachedThreadPool();
    static Map<String, Map<String, Integer>> mapMap = new HashMap<>();

    private static void createThread(int index) {
        ReduceRunner reduceRunner = new ReduceRunner(index);
        Thread thread = new Thread(reduceRunner);
        executorService.execute(thread);
        mapMap.put(Config.getReduceFileName(index), reduceRunner.getMap());
    }

    public static void Run() {
        System.out.println("Start Reducer...");
        for (int i = 0; i < Config.REDUCE_COUNT; i++)
            createThread(i + 1);
        executorService.shutdown();
    }

    public static boolean Merge() {
        String[] fileNames = new String[Config.REDUCE_COUNT];
        for (int i = 0; i < fileNames.length; i++)
            fileNames[i] = Config.getReduceFileName(i + 1);
        if (fileNames.length < 1)
            return false;
        if (fileNames.length == 1)
            return new File(fileNames[0]).renameTo(new File(Config.getResultFileName()));
        File[] files = new File[fileNames.length];
        for (int i = 0; i < fileNames.length; i++) {
            files[i] = new File(fileNames[i]);
            if (!files[i].exists() || !files[i].isFile()) {
                return false;
            }
        }
        File resultFile = new File(Config.getResultFileName());
        try {
            int bufSize = 1024;
            BufferedOutputStream outputStream = new BufferedOutputStream(new FileOutputStream(resultFile));
            byte[] buffer = new byte[bufSize];
            for (int i = 0; i < fileNames.length; i++) {
                BufferedInputStream inputStream = new BufferedInputStream(new FileInputStream(files[i]));
                int readcount;
                while ((readcount = inputStream.read(buffer)) > 0) {
                    outputStream.write(buffer, 0, readcount);
                }
                inputStream.close();
            }
            outputStream.close();
        } catch (IOException e) {
            e.printStackTrace();
            return false;
        }
        return true;
    }

    public static boolean isFinished() {
        return executorService.isTerminated();
    }
}
