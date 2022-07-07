import shell
import os
import fileutil
import shell

java_home_dir = 'D:\\jdk-13.0.2-64bit'
java_cmd_path = java_home_dir + '\\bin'


class TestEnvironment:
    """
    测试环境
    """
    def __init__(self, auto_test_dir):
        """
        构造函数
        :param auto_test_dir: 自动测试目录
        """
        self.auto_test_dir = auto_test_dir
        self.env_vars = {
            'JAVA_HOME': java_home_dir,
            'TO_BE_TEST_CLASSPAH': auto_test_dir + '\\betest',  # 被测试的学生类目录
            'TEST_SUITE_CLASSPATH': auto_test_dir + '\\test',  # 测试用例目录
            'LIB_DIR': auto_test_dir + '\\lib',                 # 测试依赖库目录
        }
        # # 获取当前环境变量classpath
        # class_path = os.getenv('classpath')
        # if class_path is None:
        #     class_path = ''
        # # 设置新的环境变量classpath
        # class_path += ';' + self.env_vars['TO_BE_TEST_CLASSPAH'] + ';' + self.env_vars['TEST_SUITE_CLASSPATH']

        # 设置环境变量classpath, 如果按照上面的代码，会导致classpath的长度超过32767 characters，而抛出异常
        class_path = self.env_vars['TO_BE_TEST_CLASSPAH'] + ';' + self.env_vars['TEST_SUITE_CLASSPATH']
        lib_files = fileutil.find_files(self.env_vars['LIB_DIR'])
        for f in lib_files:
            class_path += ';' + f
        self.env_vars['CLASSPATH'] = class_path

        # 获取当前环境变量path
        path = os.getenv('path')
        if path is None:
            path = ''
        # 设置新的环境变量path
        path = java_cmd_path + ';' + path
        self.env_vars['PATH'] = path


    def get_env_vars(self):
        """
         获取测试环境的所有环境变量
        :return:
        """
        return self.env_vars

    def get_env_var(self, key):
        """
        获取指定的环境变量值
        :param key: 指定环境变量的key
        :return:
        """
        return self.env_vars[key]

    def get_keys(self):
        """
        返回所有环境变量的key集合
        :return:
        """
        return self.env_vars.keys()

    def get_auto_test_dir(self):
        """
        返回自动测试目录
        :return:
        """
        return self.auto_test_dir




class TestExecutor:
    """
    自动测试执行器
    """

    def __init__(self, auto_test_dir):
        """
        构造函数
        :param auto_test_dir: 自动测试目录
        """
        self.test_env = TestEnvironment(auto_test_dir)
        self.cmd = 'java  org.testng.TestNG ' + os.path.join(self.test_env.get_auto_test_dir(), 'testng.xml') + \
                   ' -d ' + os.path.join(self.test_env.get_auto_test_dir(), 'test-output')

        # 设置系统环境变量.此更改只对当前分配的进程有效，不会永久更改该值。子进程将自动继承父进程的环境
        os.environ['JAVA_HONE'] = self.test_env.get_env_var('JAVA_HOME')
        os.environ['CLASSPATH'] = self.test_env.get_env_var('CLASSPATH')
        os.environ['PATH'] = self.test_env.get_env_var('PATH')

    def run_test(self):
        """
        执行自动测试
        :return: ShellExecutionResult
        """
        result = shell.execute(self.cmd)
        return result
    None

    def parse_final_result(self, result):
        """
        解析运行结果，得到运行测试个数、失败个数、忽略的个数
        :param result: 运行得到的测试结果，ShellExecutionResult对象
        :return: tuple(运行测试个数, 失败个数, 忽略的个数), 如果解析失败，返回None
        """

        for s in result.out:
            if s.startswith('Total tests run'):
                parts = s.split(',')   # 根据,切分成子串列表parts
                # 得到运行测试个数
                num_begin_index = parts[0].rfind(':') + 1  # 找到子串parts[0]里数字的起始索引
                total_test_run = parts[0][num_begin_index:].strip()
                # 得到失败的个数
                num_begin_index = parts[1].rfind(':') + 1  # 找到子串parts[1]里数字的起始索引
                failures = parts[1][num_begin_index:].strip()
                # 得到忽略的个数
                num_begin_index = parts[2].rfind(':') + 1  # 找到子串parts[2]里数字的起始索引
                skips = parts[2][num_begin_index:].strip()
                return total_test_run, failures, skips

        # result.error不用解析

        return None
