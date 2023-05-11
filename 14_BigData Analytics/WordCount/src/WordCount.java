import java.io.File;
import java.io.IOException;

import static org.apache.commons.io.FileUtils.deleteDirectory;

public class WordCount {
    public static void main(String[] args) throws IOException {
        Mapper.Run();
        while (true) {
            if (Mapper.isFinished()) {
                Reducer.Run();
                break;
            }
        }
        while (true) {
            if (Reducer.isFinished()) {
                if (Config.MERGE)
                    System.out.println("Merge Reduce:" + (Reducer.Merge() ? "Successful" : "Fail"));
                break;
            }
        }
        if(Config.CACHE){
            System.out.println("Clear Cache...");
            deleteDirectory(new File(Config.REDUCE_DIR));
            deleteDirectory(new File(Config.MAP_DIR));
        }
    }
}
