import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.TreeMap;

public class PageRank {
    private static final double BETA = 0.85;
    private static final double ITERATOR_THRESHOLD = 0.0000001;
    static Matrix edges;
    static Matrix currentPr;
    static List<Integer> nodes;
    static int nodeCount, iterateTimes = 0;

    public static void main(String[] args) {
        PreProcesser.init();
        nodes = PreProcesser.getNodes();
        edges = PreProcesser.getMatrix();
        nodeCount = nodes.size();
        handler();
        printResult();
    }

    private static void handler() {
        edges = edges.normalization();
        Matrix nextPr;
        double errorRate = 300000;
        currentPr = new Matrix(nodeCount, 1, 1.0 / nodeCount);
        while (errorRate > ITERATOR_THRESHOLD) {
            //nextPr=βMcurrentPr+(1-β)1/N
            nextPr = edges.multiply(currentPr).multiply(BETA).plus(new Matrix(nodeCount, 1, (1.0 - BETA) / nodeCount)).normalization();
            //更新errorRate
            errorRate = nextPr.minus(currentPr).abs().sum();
            currentPr = nextPr;
            iterateTimes++;
//            System.out.printf("第%02d次迭代完成,误差率为%.20f\n", iterateTimes, errorRate);
        }
    }

    private static void printResult() {
        System.out.println("迭代次数:" + iterateTimes);
        Double[] pageRank = currentPr.getColumnArray(0);
        Map<Integer, Double> map = new TreeMap<>();
        for (int i = 0; i < nodeCount; i++)
            map.put(nodes.get(i), pageRank[i]);
        List<Map.Entry<Integer, Double>> list = new ArrayList<>(map.entrySet());
        list.sort((o1, o2) -> (int) ((o2.getValue() - o1.getValue()) * 10000));
        System.out.println("ID\tPageRank");
        for (Map.Entry<Integer, Double> entry : list)
            System.out.printf("%3d\t%.10f\n", entry.getKey(), entry.getValue());
    }

}
