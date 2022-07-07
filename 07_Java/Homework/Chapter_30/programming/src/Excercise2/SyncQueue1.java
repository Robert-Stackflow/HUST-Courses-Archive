package Excercise2;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class SyncQueue1<T> {
    /**
     * 保存队列元素
     */
    private ArrayList<T> list = new ArrayList<>();
    private static Lock lock = new ReentrantLock();
    private static Condition condition1 = lock.newCondition();
    private static Condition condition2 = lock.newCondition();

    /**
     * 生产数据
     *
     * @param elements 生产出的元素列表，需要将该列表元素放入队列
     */
    public void produce(List<T> elements) {
        lock.lock();
        while (!list.isEmpty()) {
            try {
                condition1.await();
            } catch (InterruptedException e1) {
                e1.printStackTrace();
            }
        }
        list.addAll(elements);
        condition2.signalAll();
        System.out.print("Produce elements: ");
        for (T e : elements) {
            System.out.print(e + " ");
        }
        System.out.println();
        lock.unlock();
    }

    /**
     * 消费数据
     *
     * @return 从队列中取出的数据
     */
    public List<T> consume() {
        lock.lock();
        while (list.isEmpty()) {
            try {
                condition2.await();
            } catch (InterruptedException e1) {
                e1.printStackTrace();
            }
        }
        System.out.print("Consume elements: ");
        for (T e : list) {
            System.out.print(e + " ");
        }
        System.out.println();
        List<T> l = list;
        list.removeAll(list);
        condition1.signalAll();
        lock.unlock();
        return l;
    }
}