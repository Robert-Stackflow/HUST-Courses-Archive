# encoding:GBK

import zipfile
from unrar import rarfile
import fileutil
import os
import exception

def unzip(zipfile_name, dest_folder):
    """
        解压zip文件
        zipfile_name    ：   zip文件名
        dest_folder     ：   解压到的目录
    """
    # print('unzip ' + zipfile_name + ' to ' + dest_folder)
    zip_file = None
    try:
        zip_file = zipfile.ZipFile(zipfile_name)
        zip_list = zip_file.namelist()  # 得到压缩包里所有文件
        for f in zip_list:
            zip_file.extract(f, dest_folder)  # 循环解压文件到指定目录
    except Exception as e:
        # print(e)
        raise exception.UncompressError('解压错误:' + e.__str__())

    if zip_file is None:
        return
    else:
        zip_file.close()  # 关闭文件，必须有，释放内存


def unrar(rarfile_name, dest_folder):
    """
        解压rar文件
        rarfile_name    ：   rar文件名
        dest_folder     ：   解压到的目录
    """
    try:
        rf = rarfile.RarFile(rarfile_name, mode='r')  # mode的值只能为'r'
        rf_list = rf.namelist()  # 得到压缩包里所有的文件
        for f in rf_list:
            rf.extract(f, dest_folder)  # 循环解压，将文件解压到指定路径
    except Exception as e:
        raise exception.UncompressError('解压错误:' + e.__str__())

    # print('unrar ' + rarfile_name + ' to ' + dest_folder)


def decompression(file_full_path, dest_folder):
    """
    递归解压压缩文件到目标目录
    :param file_full_path:  压缩文件完全路径
    :param dest_folder: 目标目录
    :return:
    """
    file_suffix = fileutil.find_file_suffix(file_full_path)
    # print(file_suffix)
    if file_suffix == '.zip':
        unzip(file_full_path, dest_folder)
    elif file_suffix == '.rar':
        unrar(file_full_path, dest_folder)
    else:
        compress_format_error = exception.CompressFormatError('压缩格式不识别')
        raise compress_format_error  # 抛出异常

    # 递归找到目标目录下所有压缩文件
    file_list = fileutil.find_compressed_files(dest_folder)
    for f in file_list:
        file_tuple = tuple(f)
        parent_dir_full_path = file_tuple[0]
        f_name = file_tuple[1]
        f_suffix = file_tuple[2]
        f_full_path = os.path.join(parent_dir_full_path, f_name + f_suffix)  # 压缩文件的完全路径
        target_full_path = os.path.join(parent_dir_full_path, f_name)  # 压缩文件要解压到的目标目录
        if not os.path.exists(target_full_path):
            os.mkdir(target_full_path)
        decompression(f_full_path, target_full_path)
    # print('extract ' + file_full_path + ' to ' + dest_folder)
