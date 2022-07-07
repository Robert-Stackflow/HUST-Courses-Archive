class StudentInfo:
    # 构造函数
    def __init__(self, s_id, s_class, s_name):
        # __开头的属性为私有属性
        self.s_id = s_id
        self.s_class = s_class
        self.s_name = s_name

    @property  # 属性装饰器
    def sid(self):
        return self.s_id

    @property  # 属性装饰器
    def sclass(self):
        return self.s_class

    @property  # 属性装饰器
    def sname(self):
        return self.s_name

    def __str__(self):
        return repr(self.__dict__)  # 得到对象的json串, self.__dict__为对象的字典表示（为字典对象),因此需要进一步用repr转字符串
