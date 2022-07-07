package course.ch13_19;

import course.ch9_11.Rectangle;

public class ComparableRectangle extends Rectangle implements Comparable {
    /** Construct a ComparableRectangle with specified properties */
    public ComparableRectangle(double width, double height) {
        super(width,height);
    }
    /** Implement the compareTo method defined in Comparable */
    public int compareTo(Object o) {
        if (this.getArea( ) >((ComparableRectangle)o).getArea()) return 1;
        else if (this.getArea( ) <((ComparableRectangle)o).getArea()) return -1;
        else return 0;
    }
}
