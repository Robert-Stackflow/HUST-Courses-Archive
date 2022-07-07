#ifndef _MAT_H
#define _MAT_H
#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstring>
#include <exception>
#include <iomanip>
#include <iostream>
#include <typeinfo>
using namespace std;
template <typename T>
class MAT
{
	T* const e;		//指向所有整型矩阵元素的指针
	const int r, c; //矩阵的行r和列c大小
public:
	MAT(int r, int c); //矩阵定义
	MAT(const MAT& a); //深拷贝构造
	MAT(MAT&& a)
		noexcept; //移动构造
	virtual ~MAT() noexcept;
	virtual T* const operator[](int r);			 //取矩阵r行的第一个元素地址，r越界抛异常
	virtual MAT operator+(const MAT& a) const;	 //矩阵加法，不能加抛异常
	virtual MAT operator-(const MAT& a) const;	 //矩阵减法，不能减抛异常
	virtual MAT operator*(const MAT& a) const;	 //矩阵乘法，不能乘抛异常
	virtual MAT operator~() const;				 //矩阵转置
	virtual MAT& operator=(const MAT& a);		 //深拷贝赋值运算
	virtual MAT& operator=(MAT&& a) noexcept;	 //移动赋值运算
	virtual MAT& operator+=(const MAT& a);		 //“+=”运算
	virtual MAT& operator-=(const MAT& a);		 //“-=”运算
	virtual MAT& operator*=(const MAT& a);		 //“*=”运算
	virtual char* print(char* s) const noexcept; // print输出至s并返回s：列用空格隔开，行用回车结束
};
template <typename T>
MAT<T>::MAT(int r, int c) : r(r), c(c), e(new T[r * c]) //矩阵定义
{
}
template <typename T>
MAT<T>::MAT(const MAT& a) : e(new T[a.r * a.c]), r(a.r), c(a.c) //深拷贝构造
{
	for (int i = 0; i < a.r * a.c; i++)
		e[i] = a.e[i];
}
template <typename T>
MAT<T>::MAT(MAT&& a) noexcept : r(a.r), c(a.c), e(a.e) //移动构造
{
	*(const_cast<int*>(&a.r)) = 0;
	*(const_cast<int*>(&a.c)) = 0;
	*(const_cast<T**>(&a.e)) = nullptr;
}
template <typename T>
MAT<T>::~MAT() noexcept
{
	if (e != nullptr)
		delete[] e;
	*(const_cast<int*>(&r)) = 0;
	*(const_cast<int*>(&c)) = 0;
	*(const_cast<T**>(&e)) = nullptr;
}
template <typename T>
T* const MAT<T>::operator[](int r) //取矩阵r行的第一个元素地址，r越界抛异常
{
	if (r < this->r && r >= 0)
		return &e[r * c];
	else
		throw "Operator[] ERROR!";
}
template <typename T>
MAT<T> MAT<T>::operator+(const MAT& a) const //矩阵加法，不能加抛异常
{
	if (r == a.r && c == a.c)
	{
		MAT A(r, c);
		for (int i = 0; i < r * c; i++)
		{
			A.e[i] = e[i] + a.e[i];
		}
		return A;
	}
	else
		throw("Operator+ ERROR!");
}
template <typename T>
MAT<T> MAT<T>::operator-(const MAT& a) const //矩阵减法，不能减抛异常
{
	if (r == a.r && c == a.c)
	{
		MAT A(r, c);
		for (int i = 0; i < r * c; i++)
		{
			A.e[i] = e[i] - a.e[i];
		}
		return A;
	}
	else
		throw("Operator- ERROR!");
}
template <typename T>
MAT<T> MAT<T>::operator*(const MAT& a) const //矩阵乘法，不能乘抛异常
{
	if (c == a.r)
	{
		MAT A(r, a.c);
		for (int i = 0; i < r; i++)
		{
			for (int j = 0; j < a.c; j++)
			{
				T temp = 0;
				for (int k = 0; k < c; k++)
					temp += e[i * c + k] * a.e[k * c + j];
				A[i][j] = temp;
			}
		}
		return A;
	}
	else
		throw("Operator* ERROR!");
}
template <typename T>
MAT<T> MAT<T>::operator~() const //矩阵转置
{
	MAT A(c, r);
	for (int i = 0; i < r; i++)
		for (int j = 0; j < c; j++)
			A[j][i] = e[i * c + j];
	return A;
}
template <typename T>
MAT<T>& MAT<T>::operator=(const MAT& a) //深拷贝赋值运算
{
	if (this != &a)
	{
		if (e != nullptr)
			delete[] e;
		*(const_cast<int*>(&r)) = a.r;
		*(const_cast<int*>(&c)) = a.c;
		*(const_cast<T**>(&e)) = new T[r * c];
		for (int i = 0; i < a.r; i++)
			for (int j = 0; j < a.c; j++)
				e[i * a.c + j] = a.e[i * a.c + j];
	}
	return *this;
}
template <typename T>
MAT<T>& MAT<T>::operator=(MAT&& a) noexcept //移动赋值运算
{
	if (this != &a)
	{
		if (e != nullptr)
			delete[] e;
		*(const_cast<int*>(&r)) = a.r;
		*(const_cast<int*>(&c)) = a.c;
		*(const_cast<T**>(&e)) = a.e;
		*(const_cast<int*>(&a.r)) = 0;
		*(const_cast<int*>(&a.c)) = 0;
		*(const_cast<T**>(&a.e)) = nullptr;
	}
	return *this;
}
template <typename T>
MAT<T>& MAT<T>::operator+=(const MAT& a) //“+=”运算
{
	if (r == a.r && c == a.c)
	{
		for (int i = 0; i < r * c; i++)
		{
			e[i] += a.e[i];
		}
	}
	else
		throw("Operator+ ERROR!");
	return *this;
}
template <typename T>
MAT<T>& MAT<T>::operator-=(const MAT& a) //“-=”运算
{
	if (r == a.r && c == a.c)
	{
		for (int i = 0; i < r * c; i++)
		{
			e[i] -= a.e[i];
		}
	}
	else
		throw("Operator- ERROR!");
	return *this;
}
template <typename T>
MAT<T>& MAT<T>::operator*=(const MAT& a) //“*=”运算
{
	if (c == a.r)
	{
		MAT A(r, a.c);
		for (int i = 0; i < r; i++)
		{
			for (int j = 0; j < a.c; j++)
			{
				T temp = 0;
				for (int k = 0; k < c; k++)
					temp += e[i * c + k] * a.e[k * c + j];
				A[i][j] = temp;
			}
		}
		delete[] e;
		*(const_cast<T**>(&e)) = new T[r * a.c];
		for (int i = 0; i < r; i++)
			for (int j = 0; j < a.c; j++)
				e[i * a.c + j] = A[i][j];
	}
	else
		throw("Operator* ERROR!");
	return *this;
}
template <typename T>
char* MAT<T>::print(char* s) const noexcept // print输出至s并返回s：列用空格隔开，行用回车结束
{
	s[0] = '\0';
	if (typeid(e[0]) == typeid(int))
	{
		for (int i = 0; i < r; i++)
		{
			for (int j = 0; j < c; j++)
			{
				if (j != 0)
				{
					char* temp = s + strlen(s);
					sprintf(temp, "%c", ' ');
				}
				char* temp = s + strlen(s);
				sprintf(temp, "%6ld", (int)e[i * c + j]);
				if (j == c - 1)
				{
					char* temp = s + strlen(s);
					sprintf(temp, "%c", '\n');
				}
			}
		}
	}
	else if (typeid(e[0]) == typeid(long long))
	{
		for (int i = 0; i < r; i++)
		{
			for (int j = 0; j < c; j++)
			{
				if (j != 0)
				{
					char* temp = s + strlen(s);
					sprintf(temp, "%c", ' ');
				}
				char* temp = s + strlen(s);
				sprintf(temp, "%6lld", (long long)e[i * c + j]);
				if (j == c - 1)
				{
					char* temp = s + strlen(s);
					sprintf(temp, "%c", '\n');
				}
			}
		}
	}
	else if (typeid(e[0]) == typeid(float))
	{
		for (int i = 0; i < r; i++)
		{
			for (int j = 0; j < c; j++)
			{
				if (j != 0)
				{
					char* temp = s + strlen(s);
					sprintf(temp, "%c", ' ');
				}
				char* temp = s + strlen(s);
				sprintf(temp, "%8f", (float)e[i * c + j]);
				if (j == c - 1)
				{
					char* temp = s + strlen(s);
					sprintf(temp, "%c", '\n');
				}
			}
		}
	}
	else if (typeid(e[0]) == typeid(double))
	{
		for (int i = 0; i < r; i++)
		{
			for (int j = 0; j < c; j++)
			{
				if (j != 0)
				{
					char* temp = s + strlen(s);
					sprintf(temp, "%c", ' ');
				}
				char* temp = s + strlen(s);
				sprintf(temp, "%8lf", (double)e[i * c + j]);
				if (j == c - 1)
				{
					char* temp = s + strlen(s);
					sprintf(temp, "%c", '\n');
				}
			}
		}
	}
	return s;
}

#endif