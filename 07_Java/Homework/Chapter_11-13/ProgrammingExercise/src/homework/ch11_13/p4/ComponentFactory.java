package homework.ch11_13.p4;

public class ComponentFactory extends Object {
    public ComponentFactory() {
    }

    public static Component create() {
        int id = 0;
        //创建计算对象
        Component computer = new CompositeComponent(id++, "Think Pad", 0.0);

        //创建键盘对象
        Component keyboard = new AtomicComponent(id++, "Keyboard", 20.0);
        //创建鼠标对象
        Component mouse = new AtomicComponent(id++, "Mouse", 20.0);
        //创建显示器对象
        Component monitor = new AtomicComponent(id++, "Monitor", 1000.0);
        computer.add(keyboard);     //键盘加入computer
        computer.add(mouse);        //鼠标加入computer
        computer.add(monitor);      //显示器加入computer

        //创建主机对象
        Component mainFrame = new CompositeComponent(id++, "Main frame", 0.0);
        //创建硬盘对象
        Component hardDisk = new AtomicComponent(id++, "Hard disk", 1000);
        //创建电源对象
        Component powerSupplier = new AtomicComponent(id++, "Power supplier", 500);
        mainFrame.add(hardDisk);
        mainFrame.add(powerSupplier);

        //创建主板对象
        Component mainBoard = new CompositeComponent(id++, "Main board", 0.0);
        //创建CPU对象
        Component cpu = new AtomicComponent(id++, "CPU", 1500.0);
        //创建显卡对象
        Component videoCard = new AtomicComponent(id++, "Video card", 900);
        //创建网卡对象
        Component networkCard = new AtomicComponent(id++, "Network card", 100);
        mainBoard.add(cpu);         //cpu加入主板
        mainBoard.add(videoCard);   //videoCard加入主板
        mainBoard.add(networkCard); //networkCard加入主板

        mainFrame.add(mainBoard);   //mainBoard加入主机
//        System.out.println(mainFrame);
        computer.add(mainFrame);    //将主机加入computer
//        return computer;

        id = 0;
        String aName1 = "aaa1";
        String aName2 = "aaa2";
        String aName3 = "aaa3";
        String aName4 = "aaa4";
        double aPrice1 = 5.0D;
        double aPrice2 = 10.0D;
        double aPrice3 = 15.0D;
        double aPrice4 = 25.0D;
        int var26 = id + 1;
        Component a1 = new AtomicComponent(id, aName1, aPrice1);
        Component a2 = new AtomicComponent(var26++, aName2, aPrice2);
        Component a3 = new AtomicComponent(var26++, aName3, aPrice3);
        Component a4 = new AtomicComponent(var26++, aName4, aPrice4);
        String cName1 = "ccc1";
        String cName2 = "ccc2";
        String cName3 = "ccc3";
        Component c1 = new CompositeComponent(var26++, cName1, 10.0D);
        Component c2 = new CompositeComponent(var26++, cName2, 10.0D);
        String tName = "root";
        Component root = new CompositeComponent(var26++, tName, 100.0D);
        c1.add(a1);
        c1.add(a2);
        c1.add(c2);
        c2.add(a3);
        c2.add(a4);
        root.add(c1);
        return root.clone();
    }
}
