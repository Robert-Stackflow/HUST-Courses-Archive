import re
import exception
import parse
import os

def parse_student_info(file_name):
    """
    从文件名解析学生信息
    :param file_name: 压缩文件名
    :return: StudentInfo
    """

    # 字符串r前缀表示raw string，不识别转义
    # 字符串u前缀表示unicode，以Unicode字符来存储字符串; 在Python3中，字符串的存储方式中，不管前缀带不带u，默认方式都是unicode编码的字符串
    # 字符串b前缀表示bytearray，生成字节序列对象。比如在网络通信中，需要按字节序列发送数据时有用
    # 字符串f前缀表示format，用来格式化字符串。比format具有更好的可读性
    pattern = r'[_|-|——|-]'  # 中英文的下划线和短横
    parts = re.split(pattern, file_name)  # 以pattern的值 分割字符串
    if len(parts) != 3:
        file_name_format_err = exception.FileNameFormatError('压缩文件名格式错误：没有包含三个部分')
        raise file_name_format_err

    student_class = parts[0]
    student_id = parts[1]
    student_name = parts[2]

    return parse.StudentInfo(student_id, student_class, student_name)

def is_test_dir(dir_full_path):
    """
    判断指定目录是否为自动测试目录
    :param dir_full_path:  指定目录完整路径
    :return:
    """
    test_dir_contents = ['betest', 'lib', 'test', 'test-output', 'test.bat', 'testng.xml']
    is_target = True
    content = os.listdir(dir_full_path)
    for i in range(len(test_dir_contents)):
        if test_dir_contents[i] not in content:
            is_target = False
            break

    return is_target

def find_test_dir(root_full_path):
    """
    找到指定目录下的自动测试目录
    :param root_full_path: 指定目录
    :return: 如果找到则返回自动测试目录的完全路径字符串；否则返回空字符串''
    """
    test_dir = ''
    test_dir_contents = ['betest', 'lib', 'test', 'test-output', 'test.bat', 'testng.xml']
    content = os.listdir(root_full_path)
    for item in content:
        item_full_path = os.path.join(root_full_path, item)  # item只是文件名或路径名，非完整路径
        if os.path.isdir(item_full_path):
            if is_test_dir(item_full_path):
                test_dir += item_full_path
            else:
                test_dir += find_test_dir(item_full_path)

        if test_dir != '':
            break

    return test_dir
