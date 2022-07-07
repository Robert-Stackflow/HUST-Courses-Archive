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
	T* const e;		//ָ���������;���Ԫ�ص�ָ��
	const int r, c; //�������r����c��С
public:
	MAT(int r, int c); //������
	MAT(const MAT& a); //�������
	MAT(MAT&& a)
		noexcept; //�ƶ�����
	virtual ~MAT() noexcept;
	virtual T* const operator[](int r);			 //ȡ����r�еĵ�һ��Ԫ�ص�ַ��rԽ�����쳣
	virtual MAT operator+(const MAT& a) const;	 //����ӷ������ܼ����쳣
	virtual MAT operator-(const MAT& a) const;	 //������������ܼ����쳣
	virtual MAT operator*(const MAT& a) const;	 //����˷������ܳ����쳣
	virtual MAT operator~() const;				 //����ת��
	virtual MAT& operator=(const MAT& a);		 //�����ֵ����
	virtual MAT& operator=(MAT&& a) noexcept;	 //�ƶ���ֵ����
	virtual MAT& operator+=(const MAT& a);		 //��+=������
	virtual MAT& operator-=(const MAT& a);		 //��-=������
	virtual MAT& operator*=(const MAT& a);		 //��*=������
	virtual char* print(char* s) const noexcept; // print�����s������s�����ÿո���������ûس�����
};
template <typename T>
MAT<T>::MAT(int r, int c) : r(r), c(c), e(new T[r * c]) //������
{
}
template <typename T>
MAT<T>::MAT(const MAT& a) : e(new T[a.r * a.c]), r(a.r), c(a.c) //�������
{
	for (int i = 0; i < a.r * a.c; i++)
		e[i] = a.e[i];
}
template <typename T>
MAT<T>::MAT(MAT&& a) noexcept : r(a.r), c(a.c), e(a.e) //�ƶ�����
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
T* const MAT<T>::operator[](int r) //ȡ����r�еĵ�һ��Ԫ�ص�ַ��rԽ�����쳣
{
	if (r < this->r && r >= 0)
		return &e[r * c];
	else
		throw "Operator[] ERROR!";
}
template <typename T>
MAT<T> MAT<T>::operator+(const MAT& a) const //����ӷ������ܼ����쳣
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
MAT<T> MAT<T>::operator-(const MAT& a) const //������������ܼ����쳣
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
MAT<T> MAT<T>::operator*(const MAT& a) const //����˷������ܳ����쳣
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
MAT<T> MAT<T>::operator~() const //����ת��
{
	MAT A(c, r);
	for (int i = 0; i < r; i++)
		for (int j = 0; j < c; j++)
			A[j][i] = e[i * c + j];
	return A;
}
template <typename T>
MAT<T>& MAT<T>::operator=(const MAT& a) //�����ֵ����
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
MAT<T>& MAT<T>::operator=(MAT&& a) noexcept //�ƶ���ֵ����
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
MAT<T>& MAT<T>::operator+=(const MAT& a) //��+=������
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
MAT<T>& MAT<T>::operator-=(const MAT& a) //��-=������
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
MAT<T>& MAT<T>::operator*=(const MAT& a) //��*=������
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
char* MAT<T>::print(char* s) const noexcept // print�����s������s�����ÿո���������ûس�����
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