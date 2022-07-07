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
    result_path = list()
    result_path.append(start_node)
    now_node = start_node   # 当前节点
    min_path = 0
    while len(result_path) < len(matrix):
        # 如果没有走过所有节点
        min_node_index = now_node   # 最小距离节点索引

        matrix[now_node][now_node] = 0xFFFFFF
        for col_index in range(len(matrix[now_node])):
            # 思考：当前节点为0要不要考虑呢？
            if matrix[now_node][col_index] < matrix[now_node][min_node_index] \
                    and col_index not in result_path:
                min_node_index = col_index
        matrix[now_node][now_node] = 0
        min_path += matrix[now_node][min_node_index]
        result_path.append(min_node_index)
        now_node = min_node_index

    result_path.append(start_node)
    for index in range(len(result_path)):
        result_path[index] = str(result_path[index])
    print('-'.join(result_path))

    # 添加最后节点返回开始节点距离
    return


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

    tsp_greedy_agr(matrix, start_node)


if __name__ == "__main__":
    build_data(10)

