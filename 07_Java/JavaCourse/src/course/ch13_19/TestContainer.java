package course.ch13_19;
public class TestContainer {

    public static void main(String[] args) {
        testInteger();
        testString();
    }

    public static void testInteger() {
        System.out.println("-----Test Integer-----");
        Container<Integer> container = new Container<>(6);
        container.add(1);
        container.add(1);
        container.add(3);
        container.add(4);
        container.add(5);
        container.add(10);
        Iterator<Integer> it = container.iterator();
        while (it.hasNext()) {
            System.out.println(it.next());
        }
    }

    public static void testString() {
        System.out.println("-----Test String-----");
        Container<Object> container = new Container<>(6);
        container.add("12");
        container.add("34");
        container.add("56");
        container.add("78");
        container.add(10);
        Iterator<Object> it = container.iterator();
        while (it.hasNext()) {
            String s = (String) it.next();
            if (s != null)
                System.out.println(s);
        }
    }
}
