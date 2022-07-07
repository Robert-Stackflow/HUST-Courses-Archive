public class C {
    int x;
    String y;

    public C() {
        this("1");
        System.out.print("one ");
    }

    public C(String y) {
        this(1, "2");
        System.out.print("two ");
    }

    public C(int x, String y) {
        this.x = x;
        this.y = y;
        System.out.print("three ");
    }

    public static void main(String[] args) {
        C c = new C();
        System.out.println(c.x + " " + c.y);
    }
}

