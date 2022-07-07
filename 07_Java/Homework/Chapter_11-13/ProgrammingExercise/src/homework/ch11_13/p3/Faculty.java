package homework.ch11_13.p3;

import java.util.Objects;

public class Faculty extends Person {
    private String email;
    private String title;
    private int facultyId;

    public Faculty() {
    }

    public Faculty(String name, int age, int facultyId, String title, String email) {
        super(name, age);
        this.email = email;
        this.title = title;
        this.facultyId = facultyId;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public String getTitle() {
        return title;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public int getFacultyId() {
        return facultyId;
    }

    public void setFacultyId(int facultyId) {
        this.facultyId = facultyId;
    }

    @Override
    public String toString() {
        return  super.toString() +
                ", email : " + email +
                ", title : " + title +
                ", facultyId : " + facultyId;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Faculty)) return false;
        if (!super.equals(o)) return false;
        Faculty faculty = (Faculty) o;
        return facultyId == faculty.facultyId && Objects.equals(email, faculty.email) && Objects.equals(title, faculty.title);
    }

    @Override
    public Object clone() throws CloneNotSupportedException {
        Faculty s = (Faculty) super.clone();
        s.facultyId = facultyId;
        s.email = new String(email);
        s.title = new String(title);
        return s;
    }
}
