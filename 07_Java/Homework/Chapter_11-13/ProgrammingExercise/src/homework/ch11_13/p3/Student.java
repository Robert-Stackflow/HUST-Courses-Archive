package homework.ch11_13.p3;

import java.util.Objects;

public class Student extends Person {
    private String classNo;
    private String department;
    private int studentId;

    public Student() {
    }

    public Student(String name, int age, int studentId, String department, String classNo) {
        super(name, age);
        this.classNo = classNo;
        this.department = department;
        this.studentId = studentId;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Student)) return false;
        if (!super.equals(o)) return false;
        Student student = (Student) o;
        return studentId == student.studentId && Objects.equals(classNo, student.classNo) && Objects.equals(department, student.department);
    }

    @Override
    public Object clone() throws CloneNotSupportedException {
        Student s = (Student) super.clone();
        s.studentId = studentId;
        s.classNo = new String(classNo);
        s.department = new String(department);
        return s;
    }

    @Override
    public String toString() {
        return super.toString() +
                ", classNo : " + classNo +
                ", department : " + department +
                ", studentId : " + studentId;
    }

    public String getClassNo() {
        return classNo;
    }

    public void setClassNo(String classNo) {
        this.classNo = classNo;
    }

    public String getDepartment() {
        return department;
    }

    public void setDepartment(String department) {
        this.department = department;
    }

    public int getStudentId() {
        return studentId;
    }

    public void setStudentId(int studentId) {
        this.studentId = studentId;
    }
}
