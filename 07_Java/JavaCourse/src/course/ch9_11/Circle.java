package course.ch9_11;

public class Circle extends GeometricObject {
    private double radius; //新增属性
    public Circle() { }
    public Circle(double radius) { this.radius = radius; }
    public double getRadius() { return radius; }
    public void setRadius (double radius) { this.radius = radius; }

    public double getArea() {
        return radius * radius * Math.PI;
    }
    public double getDiameter() {
        return 2 * radius;
    }
    public double getPerimeter() {
        return 2 * radius * Math.PI;
    }
    //还应考虑equals，clone，toString等函数
}

