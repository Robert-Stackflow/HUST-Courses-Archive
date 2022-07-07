package homework.ch11_13.p4;

public class AtomicComponent extends Component {
    public AtomicComponent() {
    }

    public AtomicComponent(int id, String name, double price) {
        super(id, name, price);
    }

    @Override
    public void add(Component component) throws UnsupportedOperationException {
        throw new UnsupportedOperationException();
    }

    @Override
    public void remove(Component component) throws UnsupportedOperationException {
        throw new UnsupportedOperationException();
    }

    @Override
    public double calcPrice() {
        return price;
    }

    @Override
    public Iterator iterator() {
        return new NullIterator();
    }

    @Override
    public AtomicComponent clone() {
        AtomicComponent componentCopy = new AtomicComponent();
        componentCopy.setId(getId());
        componentCopy.setName(getName());
        componentCopy.setPrice(getPrice());
        return componentCopy;
    }
}
