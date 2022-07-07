import numpy as np
import pandas as pd
import openpyxl
from pandas import DataFrame

# 以下的索引都是从0开始计算

sheet0_sid_excel_col_index = 1                                  # 学号的列索引, 相对于DataFrame,不是Excel
sheet0_sname_excel_col_index = sheet0_sid_excel_col_index + 1   # 姓名的列索引, 相对于DataFrame,不是Excel
sheet0_auto_test_excel_col_index = 17                           # 自动测试分数的列索引, 相对于DataFrame,不是Excel
sheet0_auto_test_detail_excel_col_index = 21                    # 自动测试详情的列索引, 相对于DataFrame,不是Excel
sheet0_exam_excel_col_index = 26                                # 考试卷面分数的列索引, 相对于DataFrame,不是Excel
sheet0_excel_skip_rows = 7                                      # Sheet0的前7行忽略
sheet0_excel_cols_range = 'B:AC'                                # Sheet0的A列忽略


class Excel:

    def __init__(self, excel_file_full_path, new_excel_file_full_path, header=None, keep_default_na=False):
        """
        构造函数\n
        :param \n
            excel_file_full_path:   Excel文件完全路径\n
            new_excel_file_full_path: 新Excel文件完全路径\n
            header: 指定数据表的表头, 为None表示没有表头\n
            keep_default_na: 默认为False，这时读取空单元格时为空字符串''而不是nan
        """
        self.excel_file_full_path = excel_file_full_path
        self.new_excel_file_path = new_excel_file_full_path
        self.reader = pd.ExcelFile(excel_file_full_path)
        self.sheet_names = self.reader.sheet_names  # 得到所有的sheet name
        # 得到所有的sheet的DataFrame
        self.data_frames = []  # 保存所有sheet的DataFrame,Sheet0的下标为0,Sheet1的下标为1...
        # 读取所有的sheet
        for i in range(len(self.sheet_names)):
            if i == 0:
                # 得到sheet0的DataFrame
                self.data_frames.append(pd.read_excel(excel_file_full_path, header=header, sheet_name=i, skiprows=sheet0_excel_skip_rows, usecols=sheet0_excel_cols_range, keep_default_na=keep_default_na))
            else:
                self.data_frames.append(pd.read_excel(excel_file_full_path, header=header, sheet_name=i,  keep_default_na=keep_default_na))




    def read_row(self, sheet_index, row_index):
        """
        读取指定sheet里的指定行\n
        :param sheet_index: 指定的sheet索引
        :param row_index: 行号索引, 序号从0开始，相对DataFrame，而不是Excel
        :return: 指定行的内容，类型为 ndarray
        """
        return self.data_frames[sheet_index].values[row_index]


    def read_cell_in_row(self, row_array, col_index):
        """
        读取一行的指定列
        :param row_array: 行内容
        :param col_index: 列下标,从0开始，相对DataFrame，而不是Excel
        :return:
        """
        return row_array[col_index]

    def read_cell_in_dataframe(self, sheet_index, row_index, col_index):
        """
        读取指定sheet里的dataframe的一个单元格内容
        :param sheet_index: 指定的sheet索引
        :param row_index: 行索引
        :param col_index: 列索引
        :return:
        """
        return self.data_frames[sheet_index].values[row_index][col_index]

    def write_cell_in_dataframe(self, sheet_index, row_index, col_index, value):
        """
        写指定sheet里的dataframe的一个单元格
        :param sheet_index: 指定的sheet索引
        :param row_index: 行索引
        :param col_index: 列索引
        :param value: 单元格内容
        :return:
        """
        self.data_frames[sheet_index].iloc[row_index, col_index] = value


    def row_count(self, sheet_index):
        """
        获取指定sheet里的dataframe的总行数
         :param sheet_index: 指定的sheet索引
        :return:
        """
        return len(self.data_frames[sheet_index])

    def save_to_new_excel(self, dataframe_index):
        """
        将指定的dataframe写入到Excel的新的excel
        :param dataframe_index: dataframe的索引
        :return:
        """
        self.data_frames[dataframe_index].to_excel(self.new_excel_file_path, header=None)

        None

    def find_student(self, sheet_index, student_info):
        """
        在指定sheet里找到指定学生所在行索引
        :param sheet_index: 指定sheet的索引
        :param student_info: 指定的学生信息, StudentInfo类型
        :return: 学生的行索引,相对于DataFrame;如果没找到返回-1
        """
        for i in range(self.row_count(sheet_index)):
            sid = self.read_cell_in_dataframe(sheet_index, i, sheet0_sid_excel_col_index)
            sname = self.read_cell_in_dataframe(sheet_index, i, sheet0_sname_excel_col_index)
            if sid == student_info.sid and sname == student_info.sname:
                return i
        return -1
