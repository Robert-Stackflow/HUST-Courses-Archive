package course.ch13_19;
import java.lang.reflect.Array;

/**
 * 容器类，内部用T[]保存元素
 */
class Container<T> {
    private Object[] elements;
    private int elementsCount = 0;
    private int size = 0;

    public Container(int size){
        elements = new Object[size];
        this.size = size;
    }

    public boolean add(T e){
        if(elementsCount < size){
            elements[elementsCount ++] = e;
            return true;
        }
        else{
            return  false;
        }
    }

    /**
     * 返回容器的迭代器
     * @return new ArrayIterator<T>((T[])elements)
     */
    public Iterator<T> iterator(){
        return new ArrayIterator<T>((T[])elements);
    }
}
