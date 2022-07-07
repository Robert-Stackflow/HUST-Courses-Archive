package course.ch13_19;
/**
 * 迭代器接口，用于遍历组件树里的每一个组件. 注意这不是java.util.Iterator接口
 */
interface Iterator<T> {
    /**
     * 是否还有元素
     *
     * @return 如果元素还没有迭代完，返回true;否则返回false
     */
    boolean hasNext();

    /**
     * 获取下一个元素
     *
     * @return 下一个元素
     */
    T next();
}

/**
 * 数组迭代器
 */
class ArrayIterator<T> implements Iterator<T> {
    private int pos = 0;
    private T[] a = null;

    public ArrayIterator(T[] array) {
        a = array;
    }

    @Override
    public boolean hasNext() {
        return !(pos >= a.length);
    }

    @Override
    public T next() {
        if (hasNext()) {
            T c = a[pos];
            pos++;
            return c;
        } else
            return null;
    }
}
