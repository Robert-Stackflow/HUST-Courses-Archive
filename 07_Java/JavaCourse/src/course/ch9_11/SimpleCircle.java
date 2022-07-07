package course.ch9_11;

public class SimpleCircle {
    double radius = 1.0;

    SimpleCircle() {
        radius = 1.0;
    }

    SimpleCircle(double r) {
        this.radius = r;
    }

    double findArea() {
        return radius * radius * Math.PI;
    }

    public void setRadius(double newRadius){
        this.radius = newRadius;
    }
}

