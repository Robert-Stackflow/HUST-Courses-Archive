# encoding:GBK

import os
import autotest
import excelutil
import exception
import fileutil
import logger
import parse
import uncompressor  # import uncompressor包时，会自动执行import uncompressor包下面的__init__.py

# 学生提交文档的根目录 ，需要根据实际运行环境重新设置
# 该目录下包含学生提交的压缩文件，压缩文件必须遵循的命名规范
# submit_root_dir = r'E:\JavaExperimentTest\18'
submit_root_dir = r'D:\HUST-Courses\07_Java_Experiment\PyTestDIR'

if submit_root_dir[-1] != '\\':
    submit_root_dir += '\\'

# 解压的目标目录
uncompress_test_target = submit_root_dir + r'temp'
if not os.path.exists(uncompress_test_target):
    os.mkdir(uncompress_test_target)

# 运行测试的目录, 解压后的学生测试目录内容拷贝到这里，解决学生代码路径存在中文的问题
running_test_dir = submit_root_dir + r'run'
if not os.path.exists(running_test_dir):
    os.mkdir(running_test_dir)

# 日志目录
logger_path = submit_root_dir + r'logs'
if not os.path.exists(logger_path):
    os.mkdir(logger_path)

# 全局的logger
run_logger = logger.Logger('run logger', logger_path).get_logger()

# 是否需要将测试结果写入Excel,如果设置为False, 则下面二个全局变量original_score_excel_file和test_score_excel_file无效
# 如果是学生自己运行，请设为False
record_test_result_to_excel = False

# 原始成绩记载单
# original_score_excel_file = submit_root_dir + r'JAVA 语言程序设计(18级综合记载单最新).xlsx'
original_score_excel_file = submit_root_dir + r'JAVA 语言程序设计实验(20级实验课综合记载单).xlsx'

# 自动测试结果记载单，可以事先不存在
# test_score_excel_file = submit_root_dir + r'JAVA 语言程序设计(18级综合记载单最新)-实验测试结果.xlsx'
test_score_excel_file = submit_root_dir + r'JAVA 语言程序设计实验(20级实验课综合记载单)-实验测试结果.xlsx'

if record_test_result_to_excel:
    excel = excelutil.Excel(original_score_excel_file, test_score_excel_file)  # 加载Excel文件 original_score_excel_file


def find_all_submit_files(root_dir):
    """
    返回指定目录下所有学生提交的文档
    :param root_dir: 指定目录
    :return: 学生提交的文档列表
    """
    li = []
    submit_files = fileutil.find_files(submit_root_dir)
    for f in submit_files:
        f_suffix = fileutil.find_file_suffix(f)  # 得到f的后缀
        if f_suffix == '.zip' or f_suffix == '.rar':
            li.append(f)

    return li


def handle_per_compressed_file(compressed_file):
    """
    处理每个学生提交的压缩文件
    :param compressed_file: 学生提交的压缩文件的完全路径
    :return:
    """
    run_logger.info('---->测试' + compressed_file + '下的学生代码')

    # 得到不带后缀的压缩文件名
    file_name_without_suffix = fileutil.find_file_name_without_suffix(compressed_file)
    # 从压缩文件名解析学生信息
    try:
        sinfo = parse.parse_student_info(file_name_without_suffix)
    except exception.FileNameFormatError as e:
        run_logger.error('-------->' + e)
        return  # 如果学生信息解析错误, 直接返回，不做下一步处理

    if record_test_result_to_excel:
        student_index_excel = excel.find_student(0, sinfo)  # 查找该学生是否在Excel里
        if student_index_excel == -1:
            run_logger.warning(
                '-------->学生信息:学号=' + sinfo.s_id + ',班级=' + sinfo.s_class + ',姓名=' + sinfo.s_name + '的学生不在花名册里')
            return  # 如果该学生不在Excel里直接返回不处理

    run_logger.info('-------->学生信息:学号=' + sinfo.s_id + ',班级=' + sinfo.s_class + ',姓名=' + sinfo.s_name)

    # 解压学生文件
    fileutil.remove_subdir(uncompress_test_target)  # 首先清空解压的目标目录
    try:
        uncompressor.decompression(compressed_file, uncompress_test_target)
        run_logger.info('-------->解压' + compressed_file + '到目标文件夹' + uncompress_test_target)
    except Exception as e:
        run_logger.error('-------->' + e.__str__())
        return  # 如果解压错误, 直接返回，不做下一步处理

    # 找到解压后学生代码的自动测试目录
    run_logger.info('---------------->开始测试学号=' + sinfo.s_id + ',班级=' + sinfo.s_class + ',姓名=' + sinfo.s_name + '的代码')
    test_dir = parse.find_test_dir(uncompress_test_target)  # 找到解压后学生代码的自动测试目录
    if test_dir == '':
        run_logger.error(
            '---------------->学号=' + sinfo.s_id + ',班级=' + sinfo.s_class + ',姓名=' + sinfo.s_name + '的自动测试目录不存在或者存在问题')
        if record_test_result_to_excel:
            # 在Excel里记录该生的测试详情
            excel.write_cell_in_dataframe(0, student_index_excel, excelutil.sheet0_auto_test_detail_excel_col_index,
                                          '自动测试目录不存在或者存在问题')
        return  # 如果找不到测试目录，则直接返回，不做下一步处理

    # 拷贝自动测试目录test_dir的内容到运行测试的目录running_test_dir
    fileutil.remove_subdir(running_test_dir)  # 先清空运行测试的目录running_test_dir
    fileutil.copy_dir(test_dir, running_test_dir)

    # 开始测试running_test_dir里面的代码
    # test_executor = autotest.TestExecutor(test_dir)
    test_executor = autotest.TestExecutor(running_test_dir)
    result = test_executor.run_test()
    if result.code != 0:
        # 将测试过程中的错误写入该学生的日志文件
        student_error_log_file = sinfo.s_id + '_' + sinfo.s_class + '_' + sinfo.s_name + '_error.log'
        student_error_log_file_full_path = os.path.join(logger_path, student_error_log_file)
        fileutil.write_to_file(student_error_log_file_full_path, result.error)

        student_out_log_file = sinfo.s_id + '_' + sinfo.s_class + '_' + sinfo.s_name + '_out.log'
        student_out_log_file_full_path = os.path.join(logger_path, student_out_log_file)
        fileutil.write_to_file(student_out_log_file_full_path, result.out)

        run_logger.error(
            '---------------->学号=' + sinfo.s_id + ',班级=' + sinfo.s_class + ',姓名=' + sinfo.s_name + '的自动测试存在问题,请查看文件' +
            student_error_log_file_full_path + '和' + student_out_log_file_full_path)

    final_result = test_executor.parse_final_result(result)
    if final_result is None:
        run_logger.error(
            '---------------->学号=' + sinfo.s_id + ',班级=' + sinfo.s_class + ',姓名=' + sinfo.s_name + '的代码测试没有得到最终测试结果')
        if record_test_result_to_excel:
            # 在Excel里记录该生的测试详情
            excel.write_cell_in_dataframe(0, student_index_excel, excelutil.sheet0_auto_test_detail_excel_col_index,
                                          '代码测试没有得到最终测试结果')
    else:
        run_logger.info('---------------->学号=' + sinfo.s_id + ',班级=' + sinfo.s_class + ',姓名=' + sinfo.s_name +
                        '的代码测试结果为：测试总数=' + str(final_result[0]) + ',失败个数=' + str(final_result[1]) + ',忽略个数=' + str(final_result[2]))
        if record_test_result_to_excel:
            # 在Excel里记录该生的测试详情
            record_info = str(final_result[0]) + '-' + str(final_result[1]) + '-' + str(final_result[2])
            excel.write_cell_in_dataframe(0, student_index_excel, excelutil.sheet0_auto_test_detail_excel_col_index,
                                          record_info)


def run_auto_test():
    run_logger.info('开始自动测试' + submit_root_dir + '下的所有学生代码')

    # 返回所有学生提交的压缩文档列表
    compressed_file_list = find_all_submit_files(submit_root_dir)
    # print(compressed_file_list)

    # 处理每个学生的压缩文档
    for file in compressed_file_list:
        handle_per_compressed_file(file)

    run_logger.info('测试完毕')
    if record_test_result_to_excel:
        excel.save_to_new_excel(0)


if __name__ == "__main__":
    run_auto_test()
