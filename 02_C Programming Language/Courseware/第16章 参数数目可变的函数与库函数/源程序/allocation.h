/**
 * 文件: allocation.h
 * --------------
 * 动态存储分配函数库.
 */
#ifndef _ALLOCATION_H_
#define _ALLOCATION_H_

#include <stdio.h>
#include <unistd.h>
/**
 * 函数名: malloc
 * 功  能: 向系统申请size个字节的存储空间, 所分配存储区未被初始化
 * 参  数: 无符号整型size, 输入
 * 返回值: void *, 非空指针表示申请成功, 返回新分配存储区的首地址
 *                 NULL表示申请失败
 */
void *malloc(size_t size);

/**
 * 函数名: calloc
 * 功  能: 向系统申请n个大小为size字节的存储空间, 所分配存储区初始化为0
 * 参  数: 无符号整型n, 输入
 *         无符号整型size, 输入
 * 返回值: void *, 非空指针表示申请成功, 返回新分配存储区的首地址
 *                 NULL表示申请失败
 */
void *calloc(size_t n, size_t size);

/**
 * 函数名: realloc
 * 功  能: 向系统申请将p_block所指向的已分配动态存储区大小修改为size个字节, 
 *         若size小于原存储区大小, 缩小后的原存储区内容保留; 若size大于原存储
 *         区大小，则新增存储区未被初始化。
 * 参  数: 无类型指针p_block, 输入
 *         无符号整型size, 输入
 * 返回值: void *, 非空指针表示申请成功, 返回新分配存储区的首地址
 *                 NULL表示申请失败
 */
void *realloc(void *p_block, size_t size);

/**
 * 函数名: free
 * 功  能: 释放由指针p_block所指向的动态存储区
 * 参  数: 无类型指针p_block, 输入
 * 返回值: 无
 */
void free(void *p_block);

#endif