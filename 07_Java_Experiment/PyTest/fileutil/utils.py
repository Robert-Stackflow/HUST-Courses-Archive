import os
import shutil   # 目录拷贝需要这个包

def find_file_suffix(file_full_path):
    """
    获取文件后缀名
    :param file_full_path: 文件完全路径
    :return: 文件后缀名
    """
    path, suffix = os.path.splitext(file_full_path)
    return suffix

def find_file_name_without_suffix(file_full_path):
    """
    获取不含后缀的文件名
    :param file_full_path: 文件完全路径
    :return:
    """
    file_path, file_name = os.path.split(file_full_path)
    suffix_begin_index = file_name.rfind('.')  # 找到最后一个.出现的位置
    return file_name[0: suffix_begin_index]

def find_compressed_files(dir_full_path):
    """
       递归地找到指定目录下所有压缩文件
       :param dir_full_path: 指定目录
       :return: 压缩文件所在目录、压缩文件名、文件后缀名组成的三元组集合
       """
    compressed_file_list = []
    if dir_full_path == '':
        return compressed_file_list
    if dir_full_path[-1] != '\\':
        dir_full_path += '\\'
    content = os.listdir(dir_full_path)
    for item in content:
        item_full_path = dir_full_path + item  # item只是文件名或路径名，非完整路径
        if os.path.isdir(item_full_path):
            compressed_file_list += find_compressed_files(item_full_path)
        else:
            item_suffix = find_file_suffix(item_full_path)
            if item_suffix == '.zip' or item_suffix == '.rar':
                compressed_file_name = find_file_name_without_suffix(item_full_path)
                compressed_file_list.append((dir_full_path, compressed_file_name, item_suffix))

    return compressed_file_list


def remove_dir(dir_full_path):
    """
    递归删除指定目录下的所有内容，指定目录本身也删除
    :param dir_full_path: 指定目录的完全路径
    :return:
    """
    childs = os.listdir(dir_full_path)
    for child in childs:
        child_full_path = os.path.join(dir_full_path, child)
        if os.path.isdir(child_full_path):
            remove_dir(child_full_path)
        else:
            os.remove(child_full_path)

    os.rmdir(dir_full_path)

def remove_subdir(dir_full_path):
    """
    递归删除指定目录下的所有内容，指定目录本身不删除
    :param dir_full_path: 指定目录的完全路径
    :return:
    """
    childs = os.listdir(dir_full_path)
    for child in childs:
        child_full_path = os.path.join(dir_full_path, child)
        if os.path.isdir(child_full_path):
            remove_dir(child_full_path)
        else:
            os.remove(child_full_path)

def find_files(dir_full_path):
    """
    返回指定目录下的文件
    :param dir_full_path: 指定目录的完全路径
    :return: 目录里文件完全路径列表
    """
    file_list = []
    childs = os.listdir(dir_full_path)
    for child in childs:
        child_full_path = os.path.join(dir_full_path, child)
        if os.path.isfile(child_full_path):
            file_list.append(child_full_path)

    return file_list

def copy_dir(source_dir_full_path, dest_dir_full_path):
    """
    将指定源目录的内容拷贝到目标目录下
    :param source_dir_full_path: 源目录, 必须事先存在
    :param dest_dir_full_path:  目标目录, 必须事先存在并为空
    :return:
    """
    shutil.copytree(source_dir_full_path, dest_dir_full_path, dirs_exist_ok=True)
    None

def write_to_file(file_full_path, contents):
    """
    写文本文件
    :param file_full_path: 文件的完全路径
    :param contents: 写入的内容，字符串列表
    :return:
    """
    # mode='w': 打开一个文件只用于写入。如果该文件已存在则打开文件，并从开头开始编辑，即原有内容会被删除。如果该文件不存在，创建新文件。
    fd = open(file_full_path, mode='w', encoding='utf-8')
    for line in contents:
        fd.write(line + '\n')
    fd.close()
    None



