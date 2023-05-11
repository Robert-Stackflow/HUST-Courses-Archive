package Kmeans;

import java.io.*;
import java.util.*;

public class Util {
    private final static int DIMENSION = 13;

    public static double getEuclideanDis(Point p1, Point p2) {
        double distance = 0;
        double[] p1Attrs = p1.getAttrs();
        double[] p2Attrs = p2.getAttrs();
        if (p1Attrs.length != p2Attrs.length)
            throw new IllegalArgumentException("样本长度必须一致");
        for (int i = 0; i < p1Attrs.length; i++)
            distance += Math.pow(p1Attrs[i] - p2Attrs[i], 2);
        return Math.sqrt(distance);
    }

    public static List<double[]> getRawData(String fileName) {
        List<double[]> list = new ArrayList<>();
        try {
            Scanner scanner = new Scanner(new File(fileName));
            while (scanner.hasNextLine()) {
                String[] words = scanner.nextLine().split(",");
                double[] item = new double[words.length - 1];
                for (int i = 1; i < words.length; i++)
                    item[i - 1] = Double.parseDouble(words[i]);
                list.add(item);
            }
        } catch (FileNotFoundException e) {
            System.out.println(fileName + " Not Found!");
        }
        return list;
    }

    public static Set<Cluster> getStandardCluster(String fileName) {
        Map<Integer, Cluster> clusterMap = new HashMap<>();
        Set<Cluster> clusterSet = new HashSet<>();
        try {
            Scanner scanner = new Scanner(new File(fileName));
            while (scanner.hasNextLine()) {
                String[] words = scanner.nextLine().split(",");
                double[] points = new double[words.length - 1];
                for (int i = 1; i < words.length; i++)
                    points[i - 1] = Double.parseDouble(words[i]);
                int clusterId = Integer.parseInt(words[0]);
                if (clusterMap.containsKey(clusterId))
                    clusterMap.get(clusterId).addPoint(new Point(points));
                else
                    clusterMap.put(clusterId, new Cluster(clusterId));
            }
        } catch (FileNotFoundException e) {
            System.out.println(fileName + " Not Found!");
        }
        clusterMap.forEach((k, v) -> {
            v.setCentroid(getCentroid(v));
            clusterSet.add(v);
        });
        return clusterSet;
    }

    public static Point getCentroid(List<Point> pointList) {
        double[] sum = new double[DIMENSION];
        for (int i = 0; i < DIMENSION; i++)
            for (Point point : pointList)
                sum[i] += point.getAttrs()[i];
        for (int i = 0; i < sum.length; i++)
            sum[i] = sum[i] / pointList.size();
        return new Point(sum);
    }

    public static Point getCentroid(Cluster cluster) {
        return getCentroid(cluster.getPoints());
    }

    public static void output(String fileName, Set<Cluster> clusterSet) {
        try {
            PrintWriter writer = new PrintWriter(new FileWriter(fileName, false));
            for (Cluster cluster : clusterSet) {
                for (Point point : cluster.getPoints()) {
                    writer.printf("%d,", cluster.getClusterId());
                    for (double d : point.getAttrs())
                        writer.printf("%.16f,", d);
                    writer.printf("\n");
                }
                writer.flush();
            }
            writer.close();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}
