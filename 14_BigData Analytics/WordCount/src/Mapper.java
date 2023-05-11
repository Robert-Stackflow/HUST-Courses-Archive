import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class Mapper {
    static ExecutorService executorService = Executors.newCachedThreadPool();
    static Map<String, Map<String, Integer>> mapMap = new HashMap<>();

    private static void createThread(int index) {
        MapRunner mapRunner = new MapRunner(index);
        Thread thread = new Thread(mapRunner);
        executorService.execute(thread);
        mapMap.put(Config.getSourceFileName(index), mapRunner.getMap());
    }

    public static void Run() {
        System.out.println("Start Mapper...");
        for (int i = 0; i < Config.SOURCE_COUNT; i++)
            createThread(i + 1);
        executorService.shutdown();
    }

    public static boolean isFinished() {
        return executorService.isTerminated();
    }
}
