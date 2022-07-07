package Excercise1;

import java.util.ArrayList;
import java.util.List;

class Container<T> {
    private List<T> elements = new ArrayList<>();

    public synchronized void add(T e) {
        elements.add(e);
    }

    public synchronized T remove(int index) {
        return elements.remove(index);
    }

    public int size() {
        return elements.size();
    }

    public T get(int index) {
        return elements.get(index);
    }
}