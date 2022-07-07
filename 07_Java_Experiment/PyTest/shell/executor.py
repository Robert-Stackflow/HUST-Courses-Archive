import subprocess
import shlex

class ShellExecutionResult:
    def __init__(self,  return_code, return_out, return_error):
        # __开头的属性为私有属性
        self.__return_code = return_code
        self.__return_out = return_out
        self.__return_error = return_error

    @property        # 属性装饰器
    def code(self):
        return self.__return_code

    @property        # 属性装饰器
    def out(self):
        return self.__return_out

    @property        # 属性装饰器
    def error(self):
        return self.__return_error


def execute(command):
    # print("Running " + command)
    # args = shlex.split(command)
    # obj = subprocess.Popen(args, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    _obj = subprocess.Popen(command, stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=True)

    # communicate方法会等待子进程结束，不要使用wait方法,否则容易导致死锁
    # communicate方法和子进程交互：发送数据到stdin，并从stdout和stderr读数据，直到收到EOF.此函数返回一个元组： (stdoutdata , stderrdata ) 。
    (_out, _err) = _obj.communicate()
    _out_lines = []
    _err_lines = []
    if _out:
        for _line in _out.splitlines():
            try:
                # _out_lines.append(_line.decode("utf-8"))
                _out_lines.append(_line.decode("gbk"))
            except Exception as e:  # decode可能会抛出异常
                continue

    if _err:
        for _line in _err.splitlines():
            try:
                # _err_lines.append(_line.decode("utf-8"))
                _err_lines.append(_line.decode("gbk"))
            except Exception as e:  # decode可能会抛出异常
                continue

    return ShellExecutionResult(_obj.returncode, _out_lines, _err_lines)
