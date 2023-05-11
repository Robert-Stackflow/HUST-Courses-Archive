package Kmeans;

public class Point {
    private final double[] attrs;
    private final int id;
    private int clusterId;
    private double distToCentroid;

    public Point(int id, double[] attrs) {
        this.id = id;
        this.attrs = attrs;
    }

    public Point(double[] attrs) {
        this.id = -1;
        this.attrs = attrs;
    }

    public double[] getAttrs() {
        return attrs;
    }

    public int getId() {
        return id;
    }

    public void setClusterId(int clusterId) {
        this.clusterId = clusterId;
    }

    public int getClusterid() {
        return clusterId;
    }

    public double getDistToCentroid() {
        return distToCentroid;
    }

    public void setDistToCentroid(double distToCentroid) {
        this.distToCentroid = distToCentroid;
    }

    @Override
    public String toString() {
        StringBuilder result = new StringBuilder();
        result.append("[");
//        result.append("PointId=").append(id).append("  [");
        for (double v : attrs)
            result.append(v).append(" ");
        return result.toString().trim() + "]";
    }

    @Override
    public boolean equals(Object obj) {
        if (obj == null || getClass() != obj.getClass())
            return false;

        Point point = (Point) obj;
        if (point.attrs.length != attrs.length)
            return false;

        for (int i = 0; i < attrs.length; i++) {
            if (Double.compare(point.attrs[i], attrs[i]) != 0) {
                return false;
            }
        }
        return true;
    }

    @Override
    public int hashCode() {
        double x = attrs[0];
        double y = attrs[attrs.length - 1];
        long temp = x != 0.0d ? Double.doubleToLongBits(x) : 0L;
        int result = (int) (temp ^ (temp >>> 32));
        temp = y != 0.0d ? Double.doubleToLongBits(y) : 0L;
        result = 31 * result + (int) (temp ^ (temp >>> 32));
        return result;
    }

    public double sum() {
        double sum = 0;
        for (double attr : attrs)
            sum += attr;
        return sum;
    }
}