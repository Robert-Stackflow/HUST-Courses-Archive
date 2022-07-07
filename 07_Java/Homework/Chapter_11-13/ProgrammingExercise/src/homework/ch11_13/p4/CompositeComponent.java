package homework.ch11_13.p4;

public class CompositeComponent extends Component {
    protected ComponentList childs = new ComponentList();

    public CompositeComponent() {
    }

    public CompositeComponent(int id, String name, double price) {
        super(id, name, price);
    }

    @Override
    public void add(Component component) throws UnsupportedOperationException {
        childs.add(component);
    }

    @Override
    public void remove(Component component) throws UnsupportedOperationException {
        childs.remove(component);
        price -= component.calcPrice();
    }

    @Override
    public double calcPrice() {
        double price = 0.0;
        for (Component c : childs)
            price += c.calcPrice();
        return price;
    }

    @Override
    public Iterator iterator() {
        return new CompositeIterator(childs);
    }

    @Override
    public String toString() {
        StringBuilder str = new StringBuilder(super.toString() + "sub-components of " + getName() + ":\n");
        for (Iterator iterator = iterator(); iterator.hasNext(); ) {
            Component temp = iterator.next();
            if (temp != null)
                str.append(temp);
        }
        return str.toString().trim();
    }

    public CompositeComponent clone() {
        CompositeComponent componentCopy = new CompositeComponent();
        componentCopy.setId(getId());
        componentCopy.setName(getName());
        componentCopy.setPrice(getPrice());
        for (Component child : childs) {
            componentCopy.add(child.clone());
        }
        return componentCopy;
    }
}
