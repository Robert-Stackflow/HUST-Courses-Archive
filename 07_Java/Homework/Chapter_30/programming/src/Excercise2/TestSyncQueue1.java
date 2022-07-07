package Excercise2;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class TestSyncQueue1 {
    public static void main(String[] args) {
        System.out.println("The count of TEST is 3");
        SyncQueue1<Integer> syncQueue = new SyncQueue1<>();
        Runnable produceTask = () -> {
            int count = 3;
            while (count != 0) {
                try {
                    List<Integer> list = new ArrayList<>();
                    int elementsCount = (int) (Math.random() * 10) + 1;
                    for (int i = 0; i < elementsCount; i++) {
                        int r = (int) (Math.random() * 10) + 1;
                        list.add(r);
                    }
                    syncQueue.produce(list);
                    Thread.sleep((int) (Math.random() * 5) + 1);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                count--;
            }
        };

        Runnable consumeTask = () -> {
            int count = 3;
            while (count != 0) {
                try {
                    List<Integer> list = syncQueue.consume();
                    Thread.sleep((int) (Math.random() * 10) + 1);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                count--;
            }
        };

        ExecutorService es = Executors.newFixedThreadPool(2);
        es.execute(produceTask);
        es.execute(consumeTask);
        es.shutdown();
        while (!es.isTerminated()) {
        }
    }
}