package homework.ch11_13.p2;

public class TestTaskExecute {
    public static void main(String[] args) {
        WechatTask w = new WechatTask();
        ChromeTask c = new ChromeTask();
        GeekTask g = new GeekTask();
        TaskServiceImpl t = new TaskServiceImpl();
        t.addTask(w);
        t.addTask(c);
        t.addTask(g);
        t.executeTasks();
    }
}
