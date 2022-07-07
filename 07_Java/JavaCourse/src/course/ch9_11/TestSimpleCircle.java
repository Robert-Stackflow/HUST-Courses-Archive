package course.ch9_11;

public class TestSimpleCircle {
    public static void main(String[] args){
        SimpleCircle c1 = new SimpleCircle();
        System.out.println("Area = " + c1.findArea() +
                ", radius = " + c1.radius);

        SimpleCircle c2 = new SimpleCircle(10.0);
        System.out.println("Area = " + c2.findArea() +
                ", radius = " + c2.radius);

        //modify radius
        c2.setRadius(20.0);
        System.out.println("Area = " + c2.findArea() +
                ", radius = " + c2.radius);
    }
}

