class A3{
    public void draw() {
        System.out.print("Draw A.");
    }
    public void display() {
        draw();
        System.out.print("Display A.");
    }
}
class B3 extends A3{
    public void draw() {
        System.out.print("Draw B.");
    }
    public void display() {
        super.display();
        System.out.print("Display B.");
    }
}

public class TestOverride {
    public static void main(String[] args) {
        new B3().display();
    }
}
