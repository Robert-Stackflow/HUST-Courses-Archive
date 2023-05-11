package Kmeans;

import java.util.ArrayList;
import java.util.List;

import static Kmeans.Util.getEuclideanDis;

public class Cluster implements Comparable {
    private final int clusterId;
    private Point centroid;
    private List<Point> points = new ArrayList<>();

    public Cluster(int clusterId) {
        this.clusterId = clusterId;
    }

    public Cluster(int clusterId, Point centroid) {
        this.clusterId = clusterId;
        this.centroid = centroid;
    }

    public Cluster(int clusterId, Point centroid, List<Point> points) {
        this.clusterId = clusterId;
        this.centroid = centroid;
        this.points = points;
    }

    public void addPoint(Point newPoint) {
        if (!points.contains(newPoint))
            points.add(newPoint);
        else
            System.out.println("样本数据点 {" + newPoint.toString() + "} 已经存在！");
    }

    public boolean has(Point point){
        for(Point p:points)
            if(p.equals(point))
                return true;
        return false;
    }

    public int getClusterId() {
        return clusterId;
    }

    public Point getCentroid() {
        return centroid;
    }

    public void setCentroid(Point centroid) {
        this.centroid = centroid;
    }

    public List<Point> getPoints() {
        return points;
    }

    public double getDistanceSum() {
        calDistance();
        double sum = 0;
        for (Point point : points)
            sum += Math.pow(point.getDistToCentroid(), 2);
        return sum;
    }

    public void calDistance() {
        for (Point point : points)
            point.setDistToCentroid(getEuclideanDis(point, getCentroid()));
    }

    @Override
    public String toString() {
        StringBuilder toString = new StringBuilder();
        toString.append("-----------ClusterId=").append(this.clusterId).append("-----------\n");
        toString.append("DistanceSum=").append(getDistanceSum()).append("\n");
        toString.append("Centroid=").append(this.centroid.getId()).append("\n");
        toString.append(centroid.toString()).append("\n");
//        for (Point point : points)
//            toString.append(point.toString()).append("\n");
        return toString + "\n";
    }

    @Override
    public int compareTo(Object o) {
        return this.clusterId - ((Cluster) o).clusterId;
    }
}
