package Kmeans;

import java.util.*;

import static Kmeans.Util.getEuclideanDis;

public class KmeansCore {
    private static final List<Point> points = new ArrayList<>();
    private static final int K_NUM = 3;
    private final List<double[]> rawData;
    private int iterateTimes = 0;

    public KmeansCore(List<double[]> rawData) {
        this.rawData = rawData;
        for (int i = 0, j = rawData.size(); i < j; i++)
            points.add(new Point(i, rawData.get(i)));
    }

    private Set<Cluster> randomCentroid() {
        Random random = new Random();
        Set<Cluster> clusterSet = new TreeSet<>();
        for (int id = 1; id < K_NUM + 1; ) {
            Point randomPoint = points.get(random.nextInt(points.size()));
            boolean flag = true;
            for (Cluster cluster : clusterSet)
                if (cluster.getCentroid().equals(randomPoint))
                    flag = false;
            if (flag)
                clusterSet.add(new Cluster(id++, randomPoint));
        }
        return clusterSet;
    }

    public void cluster(Set<Cluster> clusterSet) {
        for (Point point : points) {
            double minDistance = Integer.MAX_VALUE;
            for (Cluster cluster : clusterSet) {
                double temp = Math.min(getEuclideanDis(point, cluster.getCentroid()), minDistance);
                if (temp != minDistance) {
                    minDistance = temp;
                    point.setDistToCentroid(minDistance);
                    point.setClusterId(cluster.getClusterId());
                }
            }
        }
        for (Cluster cluster : clusterSet) {
            cluster.getPoints().clear();
            for (Point point : points)
                if (point.getClusterid() == cluster.getClusterId())
                    cluster.addPoint(point);
        }
    }

    public boolean iterate(Set<Cluster> clusterSet) {
        boolean isNeedIterate = false;
        for (Cluster cluster : clusterSet) {
            Point centroid = Util.getCentroid(cluster);
            if (getEuclideanDis(cluster.getCentroid(), centroid) > 0.0)
                isNeedIterate = true;
            cluster.setCentroid(centroid);
        }
        return isNeedIterate;
    }

    public Set<Cluster> run() {
        Set<Cluster> clusterSet = randomCentroid();
        boolean isNeedIterate = true;
        while (isNeedIterate) {
            cluster(clusterSet);
            isNeedIterate = iterate(clusterSet);
            iterateTimes++;
        }
        return clusterSet;
    }

    public int getIterateTimes() {
        return iterateTimes;
    }
}