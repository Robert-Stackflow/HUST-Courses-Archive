package Excercise3;

public class TestReusableThread {
    public static void main(String[] args) {
        test3();
    }
    public static void test3(){
        Runnable task1 = new Runnable() {
            @Override
            public void run() {
                System.out.println("Thread " + Thread.currentThread().getId() +
                        ": is running " + this);
                try { Thread.sleep(200); }
                catch (InterruptedException e) { e.printStackTrace(); }
            }
            @Override
            public String toString() {
                return "task1";
            }
        };

        Runnable task2 = new Runnable() {
            @Override
            public void run() {
                System.out.println("Thread " + Thread.currentThread().getId() +
                        " is running " + this);
                try { Thread.sleep(100); }
                catch (InterruptedException e) { e.printStackTrace(); }
            }
            @Override
            public String toString() {
                return "task2";
            }
        };

        ReusableThread t =new ReusableThread();
        t.start();  //主线程启动子线程
        for(int i = 0; i < 5; i++){
            t.submit(task1);
            t.submit(task2);
        }
    }
}
