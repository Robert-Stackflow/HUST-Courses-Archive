class FileNameFormatError(Exception):
    """
    压缩文件名格式错误异常
    """
    def __init__(self, message):
        """
        构造函数
        :param message: 异常信息描述字符串
        """
        self.message = message

    # __str__相当于Java的toString函数，把对象转成字符串
    def __str__(self):
        return repr(self.message)


class CompressFormatError(Exception):
    """
    压缩格式错误异常
    """
    def __init__(self, message):
        """
        构造函数
        :param message: 异常信息描述字符串
        """
        self.message = message

    # __str__相当于Java的toString函数，把对象转成字符串
    def __str__(self):
        return repr(self.message)

class AutoTestDirError(Exception):
    """
    自动测试目录异常
    """

    def __init__(self, message):
        """
        构造函数
        :param message: 异常信息描述字符串
        """
        self.message = message

        # __str__相当于Java的toString函数，把对象转成字符串

    def __str__(self):
        return repr(self.message)

class UncompressError(Exception):
    """
    解压异常
    """
    def __init__(self, message):
        """
        构造函数
        :param message: 异常信息描述字符串
        """
        self.message = message

        # __str__相当于Java的toString函数，把对象转成字符串

    def __str__(self):
        return repr(self.message)
    None
