package Kmeans;

import java.util.List;
import java.util.Set;

import static java.lang.Math.abs;

public class Kmeans {
    private static Set<Cluster> clusterSet;
    private static Set<Cluster> standardClusterSet;

    public static void main(String[] args) {
        List<double[]> rawData = Util.getRawData("归一化数据.csv");
        standardClusterSet = Util.getStandardCluster("归一化数据.csv");
        KmeansCore kmeansCore = new KmeansCore(rawData);
        clusterSet = kmeansCore.run();
        System.out.println("迭代总次数:" + kmeansCore.getIterateTimes());
        Util.output("result.csv", clusterSet);
        printResult();
    }

    private static void printResult() {
        int accurateTimes = 0, datasize = 0;
        double clusterSetDistanceSum = 0, standardClusterSetDistanceSum = 0;
        for (Cluster cluster : clusterSet)
            clusterSetDistanceSum += cluster.getDistanceSum();
        for (Cluster cluster : standardClusterSet)
            standardClusterSetDistanceSum += cluster.getDistanceSum();
        for (Cluster standardCluster : standardClusterSet) {
            datasize += standardCluster.getPoints().size();
            for (Cluster cluster : clusterSet) {
                if (abs(cluster.getCentroid().getAttrs()[0] - standardCluster.getCentroid().getAttrs()[0]) < 0.05) {
                    for (Point point : cluster.getPoints())
                        accurateTimes += standardCluster.has(point) ? 1 : 0;
                    break;
                }
            }
        }
        System.out.printf("标准距离和:%.14f\n", standardClusterSetDistanceSum);
        System.out.printf("实际距离和:%.14f\n", clusterSetDistanceSum);
        System.out.printf("算法准确率:%.15f\n", accurateTimes * 1.0 / datasize);
        System.out.println("各聚类的质心与距离和:");
        for (Cluster cluster : clusterSet) {
            clusterSetDistanceSum += cluster.getDistanceSum();
            System.out.println("Centroid:" + cluster.getCentroid() + "\nSSE:" + cluster.getDistanceSum());
        }
    }
}