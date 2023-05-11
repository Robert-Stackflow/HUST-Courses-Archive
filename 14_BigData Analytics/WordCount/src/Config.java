public class Config {
    static int SOURCE_COUNT = 9;
    static int REDUCE_COUNT = 3;
    static String DATA_DIR = "./data";
    static String DATA_PREFIX = "source0";
    static String MAP_DIR = "./map";
    static String MAP_PREFIX = "map0";
    static String REDUCE_DIR = "./reduce";
    static String REDUCE_PREFIX = "reduce0";
    static String RESULT_DIR = "./";
    static String RESULT_NAME = "result.txt";
    static boolean MERGE = true;
    static boolean CACHE = false;

    static String getSourceFileName(int index) {
        return DATA_DIR + "/" + DATA_PREFIX + index;
    }

    static String getMapFileName(int index) {
        return MAP_DIR + "/" + MAP_PREFIX + index;
    }

    static String getReduceFileName(int index) {
        return REDUCE_DIR + "/" + REDUCE_PREFIX + index;
    }

    static String getResultFileName() {
        return RESULT_DIR + "/" + RESULT_NAME;
    }
}
