package course.ch9_11;

public class B extends A {
    public void m() {
        new A().j = 10;
        this.j = 10;
    }
}
