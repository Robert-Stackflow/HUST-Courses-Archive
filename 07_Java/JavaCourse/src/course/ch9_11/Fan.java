package course.ch9_11;

public class Fan {
    public final static int SLOW = 1;
    public final static int MEDIUM = 2;
    public final static int FAST = 3;
    private int speed = SLOW;
    private boolean on = false;
    private double radius = 5;
    private StringBuilder color = new StringBuilder("blue");

    public int getSpeed() {
        return speed;
    }

    public boolean getOn() {
        return on;
    }

    public double getRadius() {
        return radius;
    }

    public String getColor() {
        return color.toString();
    }

    public void setSpeed(int newSpeed) {
        speed = newSpeed;
    }

    public void setOn(boolean newOn) {
        on = newOn;
    }

    public void setRadius(double newRadius) {
        radius = newRadius;
    }

    public void setColor(String newColor) {
        color = new StringBuilder(newColor);
    }

    public void Fan() {
    }

    public String toString() {
        StringBuilder speedString = new StringBuilder();
        if (speed == 1)
            speedString = new StringBuilder("SLOW");
        else if (speed == 2)
            speedString = new StringBuilder("MEDIUM");
        else if (speed == 3)
            speedString = new StringBuilder("FAST");
        if (on) {
            return "Speed:" + speedString + ",Radius:" + radius + ",Color:" + color.toString();
        } else {
            return "fan is off,Radius:" + radius + ",Color:" + color.toString();
        }
    }
}
