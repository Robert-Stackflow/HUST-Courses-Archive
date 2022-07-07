package homework.ch11_13.p3;

import java.util.ArrayList;

public class CourseTest {
    public static void main(String[] args) throws CloneNotSupportedException {
        Faculty teacherA = new Faculty("A", 35, 100, "Professor", "A@hust.edu.cn");
        Faculty teacherB = new Faculty("B", 30, 101, "Associate Professor", "B@hust.edu.cn");
        Faculty teacherC = new Faculty("C", 25, 102, "Lecturer", "C@hust.edu.cn");
        Faculty teacherD = new Faculty("D", 24, 103, "Lecturer", "D@hust.edu.cn");
        Course courceJava = new Course("Java", teacherA);
        Course courceC = new Course("C", teacherB);
        Course courceCPP = new Course("C++", teacherC);
        Course courceEnglish = new Course("English", teacherD);
        Student zhangsan = new Student("zhangsan", 18, 201, "CS", "2001");
        Student lisi = new Student("lisi", 19, 202, "CS", "2002");
        Student wangwu = new Student("wangwu", 20, 203, "PIC", "2003");
        Student zhaoliu = new Student("zhaoliu", 21, 204, "CIP", "2004");
        courceJava.register(zhangsan);
        courceJava.register(lisi);
        courceJava.register(wangwu);
        courceJava.register(zhaoliu);
        courceC.register(zhangsan);
        courceC.register(lisi);
        courceC.register(wangwu);
        courceCPP.register(lisi);
        courceCPP.register(wangwu);
        courceCPP.register(zhaoliu);
        courceEnglish.register(zhangsan);
        courceEnglish.register(lisi);
        courceEnglish.register(zhaoliu);
        ArrayList<Course> courses = new ArrayList<>();
        courses.add(courceJava);
        courses.add(courceC);
        courses.add(courceCPP);
        courses.add(courceEnglish);
        for (Course c : courses)
            System.out.println(c.toString());

        //Test Clone
        System.out.println("-----Test Faculty-----");
        Faculty teacherClone = (Faculty) teacherA.clone();
        System.out.println(teacherClone.equals(teacherA));
        System.out.println(teacherClone.getName() != teacherA.getName());
        System.out.println(teacherClone.getEmail() != teacherA.getEmail());
        System.out.println(teacherClone.getTitle() != teacherA.getTitle());
        System.out.println("-----Test Student-----");
        Student studentClone = (Student) zhangsan.clone();
        System.out.println(studentClone.equals(zhangsan));
        System.out.println(teacherClone.getName() != teacherA.getName());
        System.out.println(studentClone.getClassNo() != zhangsan.getClassNo());
        System.out.println(studentClone.getDepartment() != zhangsan.getDepartment());
        System.out.println("-----Test Course-----");
        Course courseClone = (Course) courceJava.clone();
        System.out.println(courseClone.equals(courceJava));
        System.out.println(courseClone.getCourseName() != courceJava.getCourseName());
        System.out.println(courseClone.getTeacher() != courceJava.getTeacher());
        System.out.println(courseClone.getStudents() != courceJava.getStudents());
    }
}
