package homework.ch11_13.p3;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.Objects;

public class Course extends Object implements Cloneable {
    private String courseName;
    private List<Person> students = new ArrayList<>();
    private Person teacher;

    public Course(String courseName, Person teacher) {
        this.courseName = courseName;
        this.teacher = teacher;
    }

    public String getCourseName() {
        return courseName;
    }

    public int getNumberOfStudent() {
        return students.size();
    }

    public List<Person> getStudents() {
        return students;
    }

    public void setStudents(List<Person> students) {
        this.students = students;
    }

    public Person getTeacher() {
        return teacher;
    }

    public void register(Person s) {
        boolean flag = true;
        for (Person p : students)
            if (p.equals(s))
                flag = false;
        if(flag)
        students.add(s);
    }

    public void unregister(Person s) {
        students.remove(s);
    }

    @Override
    public String toString() {
        StringBuilder studentsInfo = new StringBuilder();
        for (Person p : students) {
            studentsInfo.append("\t" + p.toString() + "\n");
        }
        return "Course Name: " + courseName +
                "\nTeacher Info: " + teacher.toString() +
                "\nStudent List: \n" + studentsInfo +
                "Totally: " + getNumberOfStudent() + " students\n";
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Course)) return false;
        Course course = (Course) o;
        boolean flag = Objects.equals(courseName, course.courseName) && Objects.equals(teacher, course.teacher) && Objects.equals(getNumberOfStudent(), course.getNumberOfStudent()) && students.containsAll(course.students);
        return flag;
    }

    @Override
    public Object clone() throws CloneNotSupportedException {
        Course c = (Course) super.clone();
        c.courseName = new String(courseName);
        c.teacher = (Person) (teacher.clone());
        List<Person> temp = new ArrayList<>();
        for (Iterator<Person> iterator = this.students.iterator(); iterator.hasNext(); ) {
            Person p = (Person) iterator.next().clone();
            temp.add(p);
        }
        c.students = temp;
        return c;
    }
}
