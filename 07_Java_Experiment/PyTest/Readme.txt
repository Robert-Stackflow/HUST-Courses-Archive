1：从目前测试结果看，如果测试过程中抛出异常，则返回码为不为0

例如，如果路径出现中文，会抛出异常如下：

java.io.FileNotFoundException: E:\JavaExperimentTest\18\temp\CS1801_U201814527_%e6%9d%8e%e6%98%8e%e6%9c%88\Experiment1Test\Experiment1Test\test\config\..\json\hit_index_search_sort_death_rate_intersection.json (系统找不到指定的路径。)
	at java.base/java.io.FileInputStream.open0(Native Method)
	at java.base/java.io.FileInputStream.open(FileInputStream.java:213)
	at java.base/java.io.FileInputStream.<init>(FileInputStream.java:155)
	at hust.cs.javacourse.search.deser.JsonReader.read(JsonReader.java:64)
	at hust.cs.javacourse.search.index.IndexTestCase.buildFromJsonFile(IndexTestCase.java:29)
	at hust.cs.javacourse.search.query.IndexSearcherTestDataProvider.testIndexSearcher(IndexSearcherTestDataProvider.java:69)
	at java.base/jdk.internal.reflect.NativeMethodAccessorImpl.invoke0(Native Method)
	at java.base/jdk.internal.reflect.NativeMethodAccessorImpl.invoke(NativeMethodAccessorImpl.java:62)
	at java.base/jdk.internal.reflect.DelegatingMethodAccessorImpl.invoke(DelegatingMethodAccessorImpl.java:43)
	at java.base/java.lang.reflect.Method.invoke(Method.java:567)
	at org.testng.internal.MethodInvocationHelper.invokeMethod(MethodInvocationHelper.java:124)
	at org.testng.internal.MethodInvocationHelper.invokeMethod(MethodInvocationHelper.java:74)
	at org.testng.internal.MethodInvocationHelper.invokeMethodNoCheckedException(MethodInvocationHelper.java:45)
	at org.testng.internal.MethodInvocationHelper.invokeDataProvider(MethodInvocationHelper.java:131)
	at org.testng.internal.Parameters.handleParameters(Parameters.java:706)
	at org.testng.internal.ParameterHandler.handleParameters(ParameterHandler.java:49)
	at org.testng.internal.ParameterHandler.createParameters(ParameterHandler.java:37)
	at org.testng.internal.Invoker.invokeTestMethods(Invoker.java:924)
	at org.testng.internal.TestMethodWorker.invokeTestMethods(TestMethodWorker.java:125)
	at org.testng.internal.TestMethodWorker.run(TestMethodWorker.java:109)
	at org.testng.TestRunner.privateRun(TestRunner.java:648)
	at org.testng.TestRunner.run(TestRunner.java:505)
	at org.testng.SuiteRunner.runTest(SuiteRunner.java:455)
	at org.testng.SuiteRunner.runSequentially(SuiteRunner.java:450)
	at org.testng.SuiteRunner.privateRun(SuiteRunner.java:415)
	at org.testng.SuiteRunner.run(SuiteRunner.java:364)
	at org.testng.SuiteRunnerWorker.runSuite(SuiteRunnerWorker.java:52)
	at org.testng.SuiteRunnerWorker.run(SuiteRunnerWorker.java:84)
	at org.testng.TestNG.runSuitesSequentially(TestNG.java:1208)
	at org.testng.TestNG.runSuitesLocally(TestNG.java:1137)
	at org.testng.TestNG.runSuites(TestNG.java:1049)
	at org.testng.TestNG.run(TestNG.java:1017)
	at org.testng.TestNG.privateMain(TestNG.java:1354)
	at org.testng.TestNG.main(TestNG.java:1323)
88   9   19
rtn code:3

可以看到从result.out可以解析出：88   9   19
result.code = 3

同时通过debug可以看到Java抛出的异常都在result.error里