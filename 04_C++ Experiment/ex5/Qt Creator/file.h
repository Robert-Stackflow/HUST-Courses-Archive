#ifndef FILE_H
#define FILE_H
#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <QDir>
#include <QFileDialog>
#include <QTextCursor>
#include <QMessageBox>
#include <QCompleter>
#include <QPushButton>
#include <QPainter>
#include <QPixmap>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QKeyEvent>
#include "searchdialog.h"
#include "ui_searchdialog.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
using namespace std;
typedef struct filename{//存储有关文件路径等信息的结构体
    QString map;
    QString stops;
    QString lines;
    QString orgs;
    int newx,newy;
    int MapFlag,StopFlag,LineFlag,OrgFlag,LineFlagPaint;
}FilePath;
typedef struct org{//描述机构信息
    char *name;
    int x,y;
    int order;
}ORG;
typedef struct info{//存储点距离某order车站的距离dis
    double dis;
    int order;
}INFO;
typedef struct stop_line{//存储车站stop所在的线路信息line，共处于nofl条线路上
    int stop;
    int nofl;
    int* line;
}SL;
typedef struct choice{//存储用户选择的点的信息，包括点的坐标，点是否在车站处
    int x;
    int y;
    int flag;//标记是否已经选择过
    int stop;
}CHOICE;
class STOP {        //描述一个公交站点
    int number;     //所有公交站点编号
    int x, y;       //公交站点坐标
public:
    STOP(int n = 0, int x = 0, int y = 0);
    virtual int& X();
    virtual int& Y();
    virtual int& N();
};
class LINE {        //描述一条公交线路
    const int numb; //公交线路编号从1开始
    int* const stop; //公交线路上所有站点编号
    const int nofs; //公交线路上站点数量
public:
    LINE(int numb = 0, int nofs = 0, int* stop = nullptr);
    LINE(const LINE& r);
    LINE(LINE&& r) noexcept;
    LINE& operator=(const LINE& r);
    LINE& operator=(LINE&& r)noexcept;
    virtual int has(int s)const;   //线路是否包含站点编号s,返回线路中的站次序号：-1表示没有
    virtual int cross(const LINE& b)const;  //两条公交线路相交则返回1
    virtual operator int()const;   //取公交线路编号
    virtual int NOFS()const;       //取公交线路的站点数量
    virtual double dist(int d, int a)const; //线路从站次d到站次e的距离
    virtual int& operator[](int x);//取线路某个站次的站点编号
    virtual ~LINE()noexcept;
};


class TRAN {        //从线路from经站点编号stop转至线路to
    int from;       //现在乘坐的公交线路号
    int to;         //需要转乘的公交线路号
    int stop;       //由stops.txt定义的站点编号
public:
    TRAN(int from = 0, int to = 0, int stop = 0);
    int operator==(const TRAN& t)const;//判断两转乘是否相等
    virtual int& F();//现在乘坐的公交线路号
    virtual int& T();//需要转乘的公交线路号
    virtual int& S();//转乘点的站点编号
};

class ROUTE {        //一条转乘路径
    TRAN* const tran;//转乘路径上的所有转乘
    const int noft; //转乘路径上转乘次数
public:
    ROUTE(TRAN* tran = nullptr, int noft = 0);
    ROUTE(const TRAN& t);
    ROUTE(const ROUTE& r);
    ROUTE(ROUTE&& r) noexcept;
    virtual int print()const;
    virtual operator int()const;        //得到转乘次数
    virtual int operator==(const ROUTE& r)const;//判断两转乘路径是有相同
    virtual ROUTE operator *()const;    //去重复公交转乘
    virtual TRAN& operator[](int);      //返回某个转乘节点
    virtual ROUTE operator+(const ROUTE& r)const;
    virtual ROUTE& operator=(const ROUTE& r);
    virtual ROUTE& operator=(ROUTE&& r) noexcept;
    virtual ROUTE& operator+=(const ROUTE& r);
    virtual ~ROUTE() noexcept;
};

class NODE {        //闭包矩阵元素：记载的转乘次数和线路
    ROUTE* const p; //闭包矩阵r*c个元素记载的转乘路径方案
    int n;          //闭包矩阵r*c个元素记载的转乘路径方案数
public:
    NODE(ROUTE* p, int n);
    NODE(int n = 0);
    NODE(const NODE& n);
    NODE(NODE&& n)noexcept;
    virtual NODE  operator*()const; //矩阵元素约简：去掉转乘中的环
    virtual NODE  operator+(const ROUTE& n)const;
    virtual NODE  operator+(const NODE& n)const;
    virtual NODE  operator*(const NODE& n)const;
    virtual NODE& operator=(const NODE& n);
    virtual NODE& operator+=(const NODE& n);
    virtual NODE& operator+=(const ROUTE& n);
    virtual NODE& operator*=(const NODE& n);
    virtual NODE& operator=(NODE&& n)noexcept;
    virtual ROUTE& operator [](int x);
    virtual operator int& ();        //可转乘路径数n
    virtual ~NODE()noexcept;
    virtual void print()const;      //打印转乘矩阵的元素
};

class TMAP {        //所有公交转乘元素的闭包矩阵
    NODE* const p;  //指向闭包矩阵的r*c个元素
    const int r, c; //闭包矩阵的行数和列数
public:
    TMAP(int r = 0, int c = 0);
    TMAP(const TMAP& a);
    TMAP(TMAP&& a)noexcept;
    virtual ~TMAP();
    virtual int notZero()const;                 //若有不可达站点则返回0
    virtual ROUTE miniTran(int b, int e)const;   //起点站次b,终点站次e,返回最小转乘路径
    //int getNUM(int b, int e, ROUTE& r); //起点站次b,终点站次e,基于路径r的转乘次数
    virtual NODE* operator[](int r);            //得到存储多种路径的NODE类元素的某行首址
    virtual int& operator()(int r, int c);      //得到r到c可转乘路径数目
    virtual TMAP operator*(const TMAP& a)const; //闭包运算：乘法
    virtual TMAP operator+(const TMAP& a)const; //闭包运算：加法
    virtual TMAP& operator=(const TMAP& a);
    virtual TMAP& operator=(TMAP&& a)noexcept;
    virtual TMAP& operator+=(const TMAP& a);
    virtual TMAP& operator*=(const TMAP& a);
    virtual TMAP& operator()(int r, int c, const ROUTE& a);//将路径加入到r行c列元素中
    virtual void print()const;                  //打印转乘矩阵
};
typedef struct answer{//存储得到的最小转乘路径的结构体
    int f,t,n,flag;//f,t指出发和下车站点，n指转乘次数，flag标记是否已经得到结果
    ROUTE r[100];
}ANS;
struct GIS {                //描述地理信息系统的类
public:
    static STOP* st;       //所有公交站点
    static LINE* ls;       //所有公交线路
    static int  ns, nl,no; //公交站数ns，公交线路数nl
    static TMAP raw, tra;  //原始转乘矩阵， 闭包转乘矩阵
    static ORG *org;       //所有机构信息
    GIS();
    GIS(const char* flstop, const char* flline,const char*florg);//根据文件路径加载信息
    void print()const;
    int* nearstop(int x, int y);//寻找距离(x,y)最近的站点并存入int数组中返回
    void miniTran(CHOICE *from,CHOICE*to,ANS *ans);//根据出发点和终点坐标，以及是否在车站处寻找最小转乘路径
    ~GIS();
};
#endif // FILE_H
