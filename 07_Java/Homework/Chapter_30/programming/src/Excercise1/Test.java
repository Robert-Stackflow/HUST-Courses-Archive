package Excercise1;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class Test {
    public static void testAdd() {
        Container<Integer> container = new Container<>();
        int addLoops = 10;  //addTask内的循环次数
        Runnable addTask = new Runnable() {
            @Override
            public synchronized void run() {
                for (int i = 0; i < addLoops; i++) {
                    container.add(i);
                }
            }
        };

        int addTaskCount = 100; //addTask线程个数
        ExecutorService es = Executors.newCachedThreadPool();
        for (int i = 0; i < addTaskCount; i++) {
            es.execute(addTask);
        }

        es.shutdown();
        while (!es.isTerminated()) {
        }
        System.out.println("Test add " + (addLoops * addTaskCount) +
                " elements to container");
        System.out.println("Container size = " + container.size() +
                ", correct size = " + (addLoops * addTaskCount));
    }

    public static void testRemove() {
        Container<Integer> container = new Container<>();
        int removeLoops = 10; //removeTask内的循环次数
        int removeTaskCount = 100; //removeTask线程个数

        //首先添加removeLoops * removeTask个元素到容器
        for (int i = 0; i < removeLoops * removeTaskCount; i++) {
            container.add(i);
        }

        Runnable removeTask = new Runnable() {
            @Override
            public synchronized void run() {
                for (int i = 0; i < removeLoops; i++) {
                    container.remove(0);
                }
            }
        };

        ExecutorService es = Executors.newCachedThreadPool();
        for (int i = 0; i < removeTaskCount; i++) {
            es.execute(removeTask);
        }

        es.shutdown();
        while (!es.isTerminated()) {
        }
        System.out.println("Test remove " + (removeLoops * removeTaskCount) +
                " elements from container");
        System.out.println("Container size = " + container.size() +
                ", correct size = 0");
    }

    public static void main(String[] args) {
        testAdd();
        testRemove();
    }
}