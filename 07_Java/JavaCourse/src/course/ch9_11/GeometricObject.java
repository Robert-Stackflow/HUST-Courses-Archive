package course.ch9_11;

import java.util.Date;

public class GeometricObject { //等价于public class GeometricObject extends Object
    private String color = "white";
    private boolean filled;
    private Date dateCreated; //java.util.Date是JDK定义的类，表示日期和时间
    public GeometricObject() { dateCreated = new Date();}

    public String getColor() { return color; }
    public void setColor(String color) { this.color = color;}
    public boolean isFilled() { return filled; }
    public void setFilled(boolean filled) { this.filled = filled;}
    public Date getDateCreated() {return dateCreated;}

    @Override //覆盖Object类的toString()方法
    public String toString( ) { //还应考虑equals，clone
        return "created on " + dateCreated + "\n\tcolor: " + color
                + " and filled: " + filled;
    }//toString方法应该返回一个描述当前对象的有意义的字符串
}

