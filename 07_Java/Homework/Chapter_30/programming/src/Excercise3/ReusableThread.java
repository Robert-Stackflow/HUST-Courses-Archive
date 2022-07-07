package Excercise3;

import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class ReusableThread extends Thread {
    private Runnable runTask = null;

    //TODO 加入需要的数据成员
    private static Lock lock = new ReentrantLock();
    private static Condition condition1 = lock.newCondition();
    private static Condition condition2 = lock.newCondition();

    //只定义不带参数的构造函数
    public ReusableThread() {
        super();
    }

    /**
     * 覆盖Thread类的run方法
     */
    @Override
    public void run() {
        //这里必须是永远不结束的循环
        while (true) {
            lock.lock();
            while (runTask == null) {
                try {
                    condition1.await();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
            runTask.run();
            runTask = null;
            condition2.signalAll();
            lock.unlock();
        }
    }

    /**
     * 提交新的任务
     *
     * @param task 要提交的任务
     */
    public void submit(Runnable task) {
        lock.lock();
        if (runTask != null) {
            try {
                condition2.await();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        if (task == null) {
        } else {
            runTask = task;
            condition1.signalAll();
        }
        lock.unlock();
    }
}
