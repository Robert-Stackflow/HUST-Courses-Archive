set JAVA_HOME=C:\Users\ruida\.jdks\openjdk-17.0.2
set PROJECT_HOME=.
set path=%path%;%JAVA_HOME%\bin
set classpath=%classpath%;%PROJECT_HOME%\bin\production\Test3
cls
java -classpath %classpath% Test3.code
pause