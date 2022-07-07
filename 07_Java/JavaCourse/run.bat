set JAVA_HOME=C:\Users\ruida\.jdks\openjdk-17.0.2
set PROJECT_HOME=D:\HUST-Courses\10_Java\Projects\JavaCourse
set path=%path%;%JAVA_HOME%\bin
set classpath=%classpath%;%PROJECT_HOME%\bin\production\JavaCourse

java -classpath %classpath% course.ch1.HelloWorld
pause