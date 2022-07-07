package Exercise2;

import java.util.Objects;

public class TwoTuple<T1 extends Comparable<T1>, T2 extends Comparable<T2>> implements Comparable<TwoTuple<T1, T2>> {
    private T1 first;
    private T2 second;

    public TwoTuple(T1 first, T2 second) {
        this.first = first;
        this.second = second;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        TwoTuple<T1, T2> T= (TwoTuple<T1, T2>) o;
        return Objects.equals(first, T.first) && Objects.equals(second, T.second);
    }

    public T2 getSecond() {
        return second;
    }

    public void setSecond(T2 second) {
        this.second = second;
    }

    public T1 getFirst() {
        return first;
    }

    public void setFirst(T1 first) {
        this.first = first;
    }

    @Override
    public String toString() {
        return "(" + first + "," + second + ")";
    }

    @Override
    public int compareTo(TwoTuple<T1, T2> o) {
        if (first.equals(o.first))
            return second.compareTo(o.second);
        else
            return first.compareTo(o.first);
    }
}
