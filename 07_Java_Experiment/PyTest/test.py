# encoding:GBK

import uncompressor  # import uncompressor包时，会自动执行import uncompressor包下面的__init__.py
import fileutil
import parse
import exception
import logger
import excelutil
import shell
import autotest
import os


def test_uncompressor():
    # uncompressor.unzip('E:\\Java实验提交\\18_10人\\CS1801-U201814506_郭科甫.zip', 'E:\\Java实验提交\\18_10人\\temp')
    # uncompressor.unrar('E:\\Java实验提交\\18_10人\\CS1801_U201814527_李明月.rar', 'E:\\Java实验提交\\18_10人\\temp')
    # uncompressor.decompression('E:\\Java实验提交\\18_10人\\CS1801-U201814506_郭科甫.zip', 'E:\\Java实验提交\\18_10人\\temp')
    # uncompressor.decompression('E:\\Java实验提交\\18_10人\\CS1801_U201814527_李明月.rar', 'E:\\Java实验提交\\18_10人\\temp')

    try:
        uncompressor.decompression(r'E:\JavaExperimentTest\18\CS1803-U201814792-宋家垚.zip',
                                   r'E:\JavaExperimentTest\18\temp')
    except Exception as e:
        print(e)


def test_fileutil():
    # file_list = fileutil.find_compressed_files('E:\\Java实验提交\\18_10人\\temp')
    # print(file_list)
    #

    # fileutil.remove_subdir(r'E:\JavaExperimentTest\18\temp')

    # file_list = fileutil.find_files('E:\\Java实验提交\\18_10人\\temp\\auto_test\\Experiment1Test\\lib')
    # print(file_list)

    fileutil.copy_dir(r'E:\JavaExperimentTest\18\temp\CS1807_U201814701_罗雅露', r'E:\JavaExperimentTest\18\run')

    None


def test_parse():
    try:
        sinfo = parse.parse_student_info('CS1801-U201814506_郭科甫')
        print(sinfo)
    except exception.FileNameFormatError as e:
        print(e)

    test_dir = parse.find_test_dir('E:\\Java实验提交\\18_10人\\temp')
    print(test_dir)


def test_logger():
    run_logger = logger.Logger('run logger', 'E:\\JavaExperimentTest\\18\\logs').get_logger()
    run_logger.debug('debug message')
    run_logger.info('info message')
    run_logger.warning('warning message')
    run_logger.error('error message')
    run_logger.critical('critical message')


def test_excel():
    excel = excelutil.Excel('E:\\Java实验提交\\18_10人\\JAVA 语言程序设计(18级综合记载单最新).xlsx',
                            'E:\\Java实验提交\\18_10人\\JAVA 语言程序设计(18级综合记载单最新)-实验测试结果.xlsx')
    0

    # for i in range(excel.row_count(sheet_index)):
    #     excel_row = excel.read_row(sheet_index, i)
    #     sid = excel.read_cell_in_row(excel_row, excelutil.sheet0_sid_excel_col_index)
    #     sname = excel.read_cell_in_row(excel_row, excelutil.sheet0_sname_excel_col_index)
    #     auto_test_score = excel.read_cell_in_row(excel_row, excelutil.sheet0_auto_test_excel_col_index)
    #     # if auto_test_score != auto_test_score:  # 这是在Python里判断NaN的一个办法
    #     #     auto_test_score = 0
    #     if auto_test_score == '':
    #         auto_test_score = 0
    #     print(str(i + 1) + '   ' + sid + ' ' + sname + '    ' + str(auto_test_score))

    # for i in range(excel.row_count(sheet_index)):
    #     sid = excel.read_cell_in_dataframe(sheet_index, i, excelutil.sheet0_sid_excel_col_index)
    #     sname = excel.read_cell_in_dataframe(sheet_index, i, excelutil.sheet0_sname_excel_col_index)
    #     auto_test_score = excel.read_cell_in_dataframe(sheet_index, i, excelutil.sheet0_auto_test_excel_col_index)
    #     if auto_test_score == '':
    #         auto_test_score = 0
    #         excel.write_cell_in_dataframe(sheet_index, i, excelutil.sheet0_auto_test_excel_col_index, auto_test_score)
    #     print(str(i + 1) + '   ' + sid + ' ' + sname + '    ' + str(auto_test_score))
    #
    # excel.save_to_new_excel(0)

    # sinfo = parse.parse_student_info('CS1801-U201814506_郭科甫')
    sinfo = parse.parse_student_info('CS1801_U201814527_李明月')
    index = excel.find_student(0, sinfo)
    print(index)

    None


def test_shell():
    cmds = [
        'dir C:\\',
        'dir D:\\'
    ]
    for c in cmds:
        result = shell.execute(c)
        print(result.code)
        for s in result.out:
            print(s)
        for s in result.error:
            print(s)

    None


def test_environment():
    test_dir = parse.find_test_dir('E:\\Java实验提交\\18_10人\\temp')
    test_env = autotest.TestEnvironment(test_dir)
    env_var_keys = test_env.get_keys()
    for key in env_var_keys:
        print(key + ':  ' + test_env.get_env_var(key))
    None


def test_test_executor():
    # test_dir = parse.find_test_dir('E:\\Java实验提交\\18_10人\\temp')
    # test_executor = autotest.TestExecutor(test_dir)

    # 测试路径出现中文的情况
    test_executor = autotest.TestExecutor(r'E:\JavaExperimentTest\18\temp\提交版本\Experiment1Test')

    # 测试环境变量是否生效
    java_home = os.getenv('JAVA_HONE')
    print('JAVA_HONE:   ' + java_home)
    class_path = os.getenv('CLASSPATH')
    print('CLASSPATH:   ' + class_path)
    path = os.getenv('PATH')
    print('PATH:   ' + path)

    result = test_executor.run_test()
    for s in result.out:
        print(s)
    for s in result.error:  # 例如运行测试程序中出现的警告都在result.error里
        print(s)

    final_result = test_executor.parse_final_result(result)
    if final_result is None:
        print('测试不能正常运行')
    else:
        print(str(final_result[0]) + '   ' + str(final_result[1]) + '   ' + str(final_result[2]))
    print('rtn code:' + str(result.code))

    None


def test():
    # test_uncompressor()

    # test_fileutil()

    # test_parse()

    # test_logger()

    # test_excel()

    # test_shell()

    # test_environment()

    test_test_executor()

    None


if __name__ == "__main__":
    test()
