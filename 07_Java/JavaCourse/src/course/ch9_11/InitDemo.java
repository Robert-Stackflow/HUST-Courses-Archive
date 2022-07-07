package course.ch9_11;

public class InitDemo {
    InitDemo() {
        new M();
    }

    public static void main(String[] args) {
        System.out.println("(1) ");
        new InitDemo();
    }

    {
        System.out.println("(2) ");
    }

    static {
        System.out.println("(0) ");
    }
}

class N {
    N() {
        System.out.println("(6) ");
    }

    {
        System.out.println("(5) ");
    }

    static {
        System.out.println("(3) ");
    }
}

class M extends N {
    M() {
        System.out.println("(8) ");
    }

    {
        System.out.println("(7) ");
    }

    static {
        System.out.println("(4) ");
    }
}
