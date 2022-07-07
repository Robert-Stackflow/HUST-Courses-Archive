# -*- coding:utf-8 -*-
# author: Ren_Heng
# datetime: 2020/9/23
# software: PyCharm
# author_email: 1621325877@qq.com

import tkinter as tk
import time
import random
import math


# TSP问题贪心算法版本

result_path = list()    # 节点列表
matrix = list()
# 保存所有节点
left_node = list()
# 画布对象
window = tk.Tk()
# 全局对象，当前走到哪一步
now_step = 0
# 节点坐标列表
node_list = list()
# 开始节点
start_node = 0
canvas = tk.Canvas(window, height=100000, width=100000)

# 以下部分最好用类封装
# canvas中不必要的线暂存
line_list = list()
# canvas中不必要的label暂存
label_list = list()
# 存放面板输入文本框对象
input_text = None
# 其余在重置的时候要清除的对象
other_label_list = list()
other_line_list = list()
# 全局最优路径
all_min_path = list()
# 全局最优路径存储
all_min_line = list()
all_min_label = list()
# greedy_line
greedy_line = list()


def next_step():
    global now_step, start_node, left_node

    if now_step == len(left_node):
        draw_curr_node(start_node, left_node[-1], matrix[left_node[-1]][start_node], 'SkyBlue')
        return

    if now_step == 0:
        # 开始节点
        # del left_node[now_step]
        draw_curr_node(start_node, start_node, str(now_step + 1))
        modify_one_row(start_node, left_node[1:])
    else:
        # 取消前面的颜色标记
        modify_one_row(left_node[now_step - 1], left_node[now_step:], 'white')

        # 标记选中的节点
        draw_curr_node(
            left_node[now_step],
            left_node[now_step - 1],
            matrix[left_node[now_step - 1]][left_node[now_step]],
            'SkyBlue'
        )

        # 标记当前节点为已读，从未读队列删除,由于每次都删除，因此index为0
        # print(left_node[now_step+1:], now_step)
        # del left_node[result_path[0]]

        draw_curr_node(result_path[now_step], result_path[now_step], str(now_step + 1))
        modify_one_row(result_path[now_step], left_node[now_step+1:])
    now_step += 1


def draw_matrix(matrix):
    """
    将矩阵在图形中画出
    :param matrix:
    :return:
    """
    # 第1步，实例化object，建立窗口window
    # 第2步，给窗口的可视化起名字
    window.title('TSP Matrix')
    # 第3步，设定窗口的大小(长 * 宽)
    window.geometry('500x300')  # 这里的乘是小x
    canvas = tk.Canvas(window, height=100 + 100 * len(matrix), width=100 + 100 * len(matrix))
    # 开始位置
    start_x, start_y = 50, 50

    rect_matrix = list()
    # 记录所有的方框对象
    for index_x in range(len(matrix)):
        row_rect = list()
        for index_y in range(len(matrix)):
            label = tk.Label(
                window,
                width=5,
                height=2,
                bg="white",
                text=str(matrix[index_x][index_y]),
                borderwidth=0,
                font=("Calibri", 15)
            )
            # 注意x，y的使用恰好相反
            label.place(x=50 + 100 * index_y, y=50 + 100 * index_x)
            row_rect.append(label)
        rect_matrix.append(row_rect)
    next_step_but = tk.Button(window, text="下一步", command=next_step).pack()
    canvas.pack()
    return window


def draw_curr_node(index_x, index_y, text, color='LightPink'):
    """
    修改一个节点颜色，主要用于当前节点
    :param index_x:
    :param index_y:
    :param text:
    :return:
    """
    label = tk.Label(
        window,
        width=5,
        height=2,
        bg=color,
        text=text,
        borderwidth=0,
        font=("Calibri", 30)
    )
    label.place(x=50 + 100 * index_x, y=50 + 100 * index_y)


def modify_one_row(row_index, left_node, color='green'):
    """
    修改当前一行颜色，主要用于表示当前搜索最小的行
    left_node 表示可以标记为绿色的节点
    :param row_index:
    :param color:
    :return:
    """
    for col_index in range(len(matrix)):
        if col_index in left_node:
            label = tk.Label(
                window,
                width=5,
                height=2,
                bg=color,
                text=str(matrix[row_index][col_index]),
                borderwidth=0,
                font=("Calibri", 30)
            )
            label.place(x=50 + 100 * col_index, y=50 + 100 * row_index)


def read_graph_file(file_name=""):
    """
    读取文件，距离文件，文件格式为：
    第一行：所有地点名称，使用“,”分割
    其余行：每行均为地点A，地点B，距离，使用“,”分割
    :param file_name:
    :return: 距离矩阵matrix
    """
    with open(file_name, encoding="utf-8") as file:
        data = file.readlines()
        pos_name_list = list(data[0].split(','))
        dis_matr = []
        for index in range(len(pos_name_list)):
            # 所有初始距离均设为0x0FFFFFFF
            dis_matr.append([0x0FFFFFFF] * len(pos_name_list))
        # 距离处理
        for index in range(1, len(data)):
            start_node, end_node, distance = data[index].split(',')
            start_node, end_node, distance = pos_name_list.index(start_node), pos_name_list.index(end_node), eval(distance)
            dis_matr[start_node][end_node] = distance

        return dis_matr


def tsp_greedy_agr(matrix: list, start_node: int)-> int:
    """
    tsp贪心算法，可能结果会有误差
    :param matrix:  满秩矩阵
    :param start_node:  出发节点
    :return:    最短距离
    """
    # 0   3   6   7
    # 5   0   2   3
    # 6   4   0   2
    # 3   7   5   0
    # 将开始节点加入列表
    result_path.append(start_node)
    now_node = start_node   # 当前节点
    min_path = 0
    while len(result_path) < len(matrix):
        # 如果没有走过所有节点
        min_node_index = now_node   # 最小距离节点索引

        matrix[now_node][now_node] = 0xFFFFFFF
        for col_index in range(len(matrix[now_node])):
            # 思考：当前节点为0要不要考虑呢？
            if matrix[now_node][col_index] < matrix[now_node][min_node_index] \
                    and col_index not in result_path:
                min_node_index = col_index
        if matrix[now_node][min_node_index] >= 0xFFFFFF:
            print("当前输入无法找到合法路径！")
            return -1

        matrix[now_node][now_node] = 0
        min_path += matrix[now_node][min_node_index]
        result_path.append(min_node_index)
        now_node = min_node_index

    result_path.append(start_node)
    # 添加最后节点返回开始节点距离
    return min_path + matrix[result_path[-1]][result_path[0]]


def draw_():
    window = draw_matrix(matrix)
    window.mainloop()


def agr():
    global start_node, left_node, matrix, result_path
    print(tsp_greedy_agr(matrix, start_node))
    left_node = result_path


def find_all_path(now_dist, cur_node, left_nodes, path):
    """
    强行找到所有的路径
    :param now_dist: 当前已走距离
    :param left_nodes: 剩余没走的节点
    :param cur_node: 当前节点
    :return:
    """
    path_dict = dict()
    if not left_nodes:
        # 已经没有节点可走,返回回到开始节点的距离
        path.append(start_node)
        # 不能直接返回上面语句，执行结果不是path，是None
        return now_dist + matrix[cur_node][start_node], path
    for index in range(len(left_nodes)):
        new_path = path + [left_nodes[index]]
        one_dist, one_path = find_all_path(
            now_dist + matrix[cur_node][left_nodes[index]],
            left_nodes[index],
            list(left_nodes[0: index] + left_nodes[index + 1:]),
            new_path
        )
        path_dict[one_dist] = one_path
    min_path = None
    min_dist = 0xFFFFFF
    for key_dist, path_value in path_dict.items():
        if key_dist < min_dist:
            min_dist = key_dist
            min_path = path_dict[key_dist]
    return min_dist, min_path


def travel_all_path():
    """
    遍历所有路径
    :return:
    """
    left_nodes = list(range(len(node_list)))
    del left_nodes[start_node]
    min_dist, min_path = find_all_path(0, start_node, left_nodes, [start_node])
    global all_min_path
    all_min_path = min_path
    print(min_dist, min_path)


def show_minest_path():
    """显示或删除最小路径"""
    global all_min_line
    if not all_min_path:
        from tkinter import messagebox
        messagebox.showinfo("提示", "节点数量过多，没有计算全局最优")
        return

    if not all_min_line:
        # 没有显示最小路径
        for index in range(1, len(all_min_path)):
            line = canvas.create_line(
                10 * node_list[all_min_path[index - 1]][0], 5 * node_list[all_min_path[index - 1]][1],
                10 * node_list[all_min_path[index]][0], 5 * node_list[all_min_path[index]][1],
                fill='yellow', width=2,
            )

            # 增加距离标签
            label = tk.Label(
                window,
                bg="white",
                text="%.0f" % matrix[all_min_path[index - 1]][all_min_path[index]],
                borderwidth=1,
                font=("Calibri", 8)
            )
            # 取的是中间距离
            label.place(
                x=5 * (node_list[all_min_path[index - 1]][0] + node_list[all_min_path[index]][0]),
                y=2.5 * (node_list[all_min_path[index - 1]][1] + node_list[all_min_path[index]][1])
            )
            all_min_line.append(line)
            all_min_label.append(label)
    else:
        # 删除最小路径
        for line_item in all_min_line:
            canvas.delete(line_item)
        for label_item in all_min_label:
            label_item.destroy()
        all_min_line = list()


def auto_step():
    """自动进行步骤"""
    global now_step
    for index in range(len(left_node)):
        two_dim_pic()
        window.update()
        time.sleep(1)
    now_step = 0


def get_input_num():
    """获取输入的点个数"""

    global result_path, matrix, left_node, now_step, other_label_list, greedy_line
    global node_list, start_node, line_list, label_list, input_text, other_line_list

    input_num = input_text.get("1.0", tk.END)
    # input_num除了字符后面还有\r等转义符
    if not input_num or not input_num.strip().isdigit():
        from tkinter import messagebox
        messagebox.showinfo("错误", "请输入有效数字！")
        return
    input_num = eval(input_num)
    for item in other_label_list:
        item.destroy()
    for item_line in other_line_list:
        canvas.delete(item_line)

    for item_line in greedy_line:
        canvas.delete(item_line)

    # 删除可能运行过程中存储的线
    for label_item in label_list:
        label_item.destroy()
    for item_line in line_list:
        canvas.delete(item_line)
    # 清空存储
    other_label_list = list()
    other_line_list = list()
    label_list = list()
    line_list = list()
    greedy_line = list()

    # 清空存储对象
    result_path = list()  # 节点列表
    matrix = list()
    # 保存所有节点
    left_node = list()
    # 全局对象，当前走到哪一步
    now_step = 0
    # 节点坐标列表
    node_list = list()
    # 开始节点
    start_node = 0
    # canvas中不必要的线暂存
    line_list = list()
    # canvas中不必要的label暂存
    label_list = list()
    # 存放面板输入文本框对象
    input_text = None
    # 其余在重置的时候要清除的对象
    other_label_list = list()
    other_line_list = list()

    # 重新创建画布
    build_data(input_num)


def draw_all_path_greedy():
    # 保留路径
    for index in range(1, len(left_node)):
        # 上一条路径
        line = canvas.create_line(
            10 * node_list[left_node[index - 1]][0], 5 * node_list[left_node[index - 1]][1],
            10 * node_list[left_node[index]][0], 5 * node_list[left_node[index]][1],
            fill='SkyBlue', width=2,
        )

        # 增加距离标签
        label = tk.Label(
            window,
            bg="white",
            text="%.0f" % matrix[left_node[index - 1]][left_node[index]],
            borderwidth=1,
            font=("Calibri", 8)
        )
        # 取的是中间距离
        label.place(
            x=5 * (node_list[left_node[index - 1]][0] + node_list[left_node[index]][0]),
            y=2.5 * (node_list[left_node[index - 1]][1] + node_list[left_node[index]][1])
        )
        other_line_list.append(line)
        other_label_list.append(label)


def two_dim_pic():
    """每次单击后下一步的处理,
        横坐标*10，纵坐标*5
    """

    global now_step, left_node, line_list, label_list, \
        other_label_list, other_line_list, greedy_line

    # 对于后面得操作
    if now_step >= len(left_node):
        now_step = 0
        for line in greedy_line:
            canvas.delete(line)
        greedy_line = list()
        # draw_all_path_greedy()

    # 将前面的线删除
    for line in line_list:
        canvas.delete(line)
    # 清空line_list
    line_list = list()
    # 将前面的label删除
    for label in label_list:
        label.destroy()
    # 清空label_list
    label_list = list()

    # 将选择的路径标记
    if now_step != 0:
        line = canvas.create_line(
            10 * node_list[left_node[now_step]][0], 5 * node_list[left_node[now_step]][1],
            10 * node_list[left_node[now_step - 1]][0], 5 * node_list[left_node[now_step - 1]][1],
            fill='green', width=2,
        )
        greedy_line.append(line)

    # 标记当前节点颜色
    # 将当要访问的节点标记为蓝色
    label = tk.Label(
        window,
        width=2,
        height=2,
        bg="SkyBlue",
        text=str(left_node[now_step]),
        borderwidth=1,
        font=("Calibri", 20)
    )
    label.place(x=10 * node_list[left_node[now_step]][0], y=5 * node_list[left_node[now_step]][1])
    other_label_list.append(label)
    # 画出后面的线
    for index in range(now_step + 1, len(left_node)):

        if matrix[left_node[now_step]][left_node[index]] > 0xFFFFFF:
            continue;

        line = canvas.create_line(
            10 * node_list[left_node[now_step]][0], 5 * node_list[left_node[now_step]][1],
            10 * node_list[left_node[index]][0], 5 * node_list[left_node[index]][1],
            fill='green', width=2,
        )

        # 增加距离标签
        label = tk.Label(
            window,
            bg="white",
            text="%.0f" % matrix[left_node[now_step]][left_node[index]],
            borderwidth=1,
            font=("Calibri", 8)
        )
        # 取的是中间距离
        label.place(
            x=5 * (node_list[left_node[now_step]][0] + node_list[left_node[index]][0]),
            y=2.5 * (node_list[left_node[now_step]][1] + node_list[left_node[index]][1])
        )

        line_list.append(line)
        label_list.append(label)

    now_step += 1


def drwa_all_path():
    """画出所有的路径"""
    for index_x in range(len(matrix)):
        for index_y in range(index_x + 1, len(matrix)):
            if matrix[index_x][index_y] < 0xFFFFFF:
                line = canvas.create_line(
                    10 * node_list[index_x][0], 5 * node_list[index_x][1],
                    10 * node_list[index_y][0], 5 * node_list[index_y][1],
                    fill='Silver', width=2,
                )
                other_line_list.append(line)


def build_ori_pic():
    """
    创建原始画布
    :return:
    """
    window.title('TSP greedy')
    # 第3步，设定窗口的大小(长 * 宽)
    window.geometry('500x300')  # 这里的乘是小x

    for index in range(len(matrix)):
        label = tk.Label(
            window,
            width=2,
            height=2,
            bg="LightPink",
            text=str(index),
            borderwidth=1,
            font=("Calibri", 15)
        )
        # 注意x，y的使用恰好相反
        label.place(x=10 * node_list[index][0], y=5 * node_list[index][1])
        other_label_list.append(label)

    global input_text
    next_step_but = tk.Button(window, text="下 一 步", command=two_dim_pic, height=2, width=10)
    auto_step_but = tk.Button(window, text="自动执行", command=auto_step, height=2, width=10)
    input_text = tk.Text(window, height=2, width=11)
    get_input_but = tk.Button(window, text="重置输入", command=get_input_num, height=2, width=10)
    show_min_but = tk.Button(window, text="最小路径", command=show_minest_path, height=2, width=10)
    other_label_list.append(next_step_but)
    other_label_list.append(auto_step_but)
    other_label_list.append(input_text)
    other_label_list.append(get_input_but)
    other_label_list.append(show_min_but)
    # 需要根据屏幕大小调整这些参数，不然可能显示在屏幕外
    # 本机约为1500,800
    next_step_but.place(x=1400, y=500)
    auto_step_but.place(x=1400, y=550)
    input_text.place(x=1400, y=600)
    get_input_but.place(x=1400, y=650)
    show_min_but.place(x=1400, y=700)
    # next_step_but.pack()
    # auto_step_but.pack()
    canvas.pack()

    # 将greedy路径画出
    drwa_all_path()
    # draw_all_path_greedy()
    window.mainloop()


def run_many_agr(n):
    # 计算耗时
    time_start = None
    time_end = None

    if n <= 13:
        # 时间复杂度原因，限制全局搜索时n的个数
        print("全局最优")
        time_start = time.time()
        travel_all_path()
        time_end = time.time()
        print("全局搜索时间", time_end - time_start)
    print("贪心算法")
    time_start = time.time()
    print(tsp_greedy_agr(matrix, start_node))
    print(result_path)
    time_end = time.time()
    print("贪心算法用时", time_end - time_start)

    print("dp算法")
    time_start = time.time()
    tsp_dp.matrix = matrix
    tsp_dp.tsp_dp(matrix, start_node)
    time_end = time.time()
    print("dp算法用时", time_end - time_start)
    print("=====================================")
    global left_node
    left_node = result_path
    # left_node.append(start_node)

    build_ori_pic()


def build_data(n: int)->list:
    """
    根据输入节点个数生成数据
    :param n:
    :return:
    """
    # 生成一个由（x，y）组成的list
    # 坐标范围为x：x10，y:x5
    sample_size = 130
    # 随机数样本空间，不能过大
    index_x_list = random.sample(range(1, sample_size), n)
    index_y_list = random.sample(range(1, sample_size), n)
    for index in range(n):
        node_list.append([index_x_list[index], index_y_list[index]])

    # 生成距离矩阵
    # 此处可以用上三角矩阵，稀疏矩阵
    for index_x in range(n):
        one_row_list = list()
        for index_y in range(n):
            one_dist = 0.0
            one_dist = math.sqrt(
                # 平方和
                pow(node_list[index_x][0] - node_list[index_y][0], 2) +
                pow(node_list[index_x][1] - node_list[index_y][1], 2)
            )
            one_row_list.append(one_dist)
        # 增加一行数据
        matrix.append(one_row_list)

    global all_min_path
    all_min_path = list()

    for index in range(n-1):
        x_y = random.sample(range(0, n), 2)
        if x_y[0] != x_y[1]:
            matrix[x_y[0]][x_y[1]] = 0xFFFFFFF
            matrix[x_y[1]][x_y[0]] = 0xFFFFFFF

    # print("距离矩阵")
    # for index_x in range(len(matrix)):
    #     for index_y in range(len(matrix)):
    #         print(matrix[index_x][index_y], end='\t')
    #     print()
    # print("----------------")
    run_many_agr(n)


if __name__ == "__main__":

    build_data(5)

