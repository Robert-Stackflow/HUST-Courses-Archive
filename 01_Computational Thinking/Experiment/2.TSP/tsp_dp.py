# -*- coding:utf-8 -*-
# author: Ren_Heng
# datetime: 2020/9/24
# software: PyCharm
# author_email: 1621325877@qq.com

import random
import math

path = list()
matrix = list()
dp_martix = dict()
node_list = list()
# {(current_index, (left_index_set)): distance}
# 0   1   2   3   4   5   6   7
# 1
# 2
# 3

int_list_2_str = lambda x: ','.join([str(x_i) for x_i in x])


def get_dis_dict(cur_node: int, node_left: list)->int:
    """
    求解当前节点下剩余未走节点得最短距离
    :param cur_node: 当前已走节点
    :param node_left: 剩余未走系欸但
    :return: 当前状态下得最短距离
    """
    tem_key = "%d#%s" % (cur_node, int_list_2_str(node_left))
    if tem_key not in dp_martix.keys():
        # 尝试求解每一个未走节点为下一次节点
        # 下一步最优节点索引
        dp_martix[tem_key] = 0x0FFFFFFF
        for node_index in range(len(node_left)):
            if node_left[node_index]:
                node_left[node_index] = 0
                next_dist = get_dis_dict(node_index, node_left) + matrix[cur_node][node_index]
                if next_dist < dp_martix[tem_key]:
                    dp_martix[tem_key] = next_dist
                node_left[node_index] = 1

    return dp_martix[tem_key]


def tsp_dp(matrix: list, begin_node: int)-> int:
    """
    tsp 动态算法解法
    :param matrix:  满秩矩阵，各个节点之间的距离
    :param begin_node:  开始节点编号
    :return:    最短距离
    """
    # 对于含有N个元素的集合，一共含有2^N个子集
    # 对于大多数的C++/java方法，需要使用二进制移位
    # 对于python来讲，可以减少很多的操作
    # 求解dp矩阵

    # 初始化每个节点到start_node距离-》已知
    for node_index in range(len(matrix)):
        dp_martix["%d#%s" % (node_index, ",".join(['0'] * len(matrix)))] = matrix[node_index][begin_node]
        # 开始节点，剩余节点
    # 记录剩余未走完的节点,相应索引为1表示没有被访问
    left_nodes = [1] * len(matrix)
    now_node = begin_node
    left_nodes[now_node] = 0

    # 还是要使用递归
    get_dis_dict(now_node, left_nodes)
    print(dp_martix)


def get_path(start_node: int, left_node: list)-> None:
    """
    反向获取最短路径
    :param start_node:
    :param left_node: [1,2,...]
    :return:
    """
    if not left_node:
        return
    key = str(start_node) + '#'


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
    import time
    time_begin = time.time()
    tsp_dp(matrix, 0)
    time_end = time.time()
    print("动态规划耗时", time_end - time_begin)


if __name__ == "__main__":
    # matrix = [
    #         [100, 3, 100, 8, 9],
    #         [3, 100, 3, 10, 5],
    #         [100, 3, 100, 4, 3],
    #         [8, 10, 4, 100, 20],
    #         [9, 5, 3, 20, 100]
    #     ]
    # tsp_dp(matrix, 0)
    build_data(11)
