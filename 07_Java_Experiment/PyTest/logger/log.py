import logging
import os

class Logger:
    """
    日志类
    """
    def __init__(self, logger_name, logger_path):

        # 创建一个logger
        self.log_level = logging.DEBUG
        self.logger = logging.getLogger(logger_name)
        self.logger.setLevel(self.log_level)

        # 创建一个handler，用于写入日志文件
        if logger_path[-1] != '\\':
            logger_path += '\\'
        self.log_dir = logger_path
        self.log_file_path = self.log_dir + 'out.log'
        # print(self.log_file_path)
        file_handler = logging.FileHandler(self.log_file_path, encoding='utf-8', mode='w')  # 指定utf-8格式编码，避免输出的日志文本乱码
        file_handler.setLevel(self.log_level)

        # 创建一个handler，用于将日志输出到控制台
        console_handler = logging.StreamHandler()
        console_handler.setLevel(self.log_level)

        # 定义handler的输出格式
        self.log_formatter = logging.Formatter('%(asctime)s %(levelname)10s   %(message)s', '%Y-%m-%d-%H:%M:%S')
        file_handler.setFormatter(self.log_formatter)
        console_handler.setFormatter(self.log_formatter)

        # 给logger添加handler
        self.logger.addHandler(file_handler)
        self.logger.addHandler(console_handler)

    def get_logger(self):
        return self.logger




