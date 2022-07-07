package homework.ch11_13.p4;

import java.util.ArrayList;
import java.util.List;

public class CompositeIterator extends Object implements Iterator {
    protected List<Iterator> iterators = new ArrayList<>();

    public CompositeIterator(Iterator iterator) {
        iterators.add(iterator);
    }

    @Override
    public boolean hasNext() {
        if (iterators.size() > 0) {
            Iterator it = iterators.get(0);
            if (!it.hasNext()) {
                iterators.remove(0);
                return hasNext();
            } else {
                return true;
            }
        } else {
            return false;
        }
    }

    @Override
    public Component next() {
        if (hasNext()) {
            Iterator it = iterators.get(0);
            Component c = it.next();
            iterators.add(c.iterator());
            return c;
        } else {
            return null;
        }
    }
}
