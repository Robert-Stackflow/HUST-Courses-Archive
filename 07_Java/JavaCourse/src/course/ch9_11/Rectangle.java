package course.ch9_11;

public class Rectangle extends GeometricObject {
    private double width;
    private double height;

    public Rectangle() { }
    public Rectangle(double width, double height) {
        this.width = width;
        this.height = height;
    }

    public double getWidth() { return width; }
    public void setWidth (double width) { this.width = width;}
    public double getHeight() { return height;}
    public void setHeight (double height) { this.height = height;}
    public double getArea() { return width * height;}
    public double getPerimeter() {
        return 2 * (width + height);
    }
    //还应考虑equals，clone，toString等函数
}

