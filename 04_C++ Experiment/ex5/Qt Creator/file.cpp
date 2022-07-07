#include"file.h"
#pragma warning(disable:6385)
#pragma warning(disable:6386)
#pragma warning(disable:6031)
#pragma warning(disable:4100)
STOP* GIS::st = nullptr;       //所有公交站点
LINE* GIS::ls = nullptr;       //所有公交线路
int  GIS::ns = 0, GIS::nl = 0,GIS::no=0; //公交站数ns，公交线路数nl
TMAP GIS::raw, GIS::tra;	//原始转乘矩阵， 闭包转乘矩阵
ORG* GIS::org=nullptr;
STOP::STOP(int n, int x, int y)
{
    number = n;
    STOP::x = x;
    STOP::y = y;
}
int& STOP::X()
{
    return x;
}
int& STOP::Y()
{
    return y;
}
int& STOP::N()
{
    return number;
}
LINE::LINE(int numb, int nofs, int* stop) :numb(numb), stop(new int[nofs]), nofs(nofs)
{
}
LINE::LINE(const LINE& r) : numb(r.numb), stop(new int[r.nofs]), nofs(r.nofs)
{
    for (int i = 0; i < nofs; i++)
        stop[i] = r.stop[i];
}
LINE::LINE(LINE&& r)noexcept :numb(r.numb), stop(new int[r.nofs]), nofs(r.nofs)
{
    if (stop)
        delete[] stop;
    *(const_cast<int**>(&stop)) = r.stop;
    *(const_cast<int**>(&r.stop)) = nullptr;
    *(const_cast<int*>(&r.numb)) = 0;
    *(const_cast<int*>(&r.nofs)) = 0;
}
LINE& LINE::operator=(const LINE& r)
{
    if (stop) delete[]stop;
    *(const_cast<int**>(&stop)) = new int[r.nofs];
    *(const_cast<int*>(&numb)) = r.numb;
    *(const_cast<int*>(&nofs)) = r.nofs;
    int** ptemp = const_cast<int**>(&stop);
    for (int i = 0; i < nofs; i++)
        *(*ptemp + i) = r.stop[i];
    return *this;
}
LINE& LINE::operator=(LINE&& r)noexcept
{
    if (stop)
        delete[] stop;
    *(const_cast<int**>(&stop)) = r.stop;
    *(const_cast<int*>(&numb)) = r.numb;
    *(const_cast<int*>(&nofs)) = r.nofs;
    *(const_cast<int**>(&r.stop)) = nullptr;
    *(const_cast<int*>(&r.numb)) = 0;
    *(const_cast<int*>(&r.nofs)) = 0;
    return *this;
}
int LINE::has(int s)const   //线路是否包含站点编号s,返回线路中的站次序号：-1表示没有
{
    for (int i = 0; i < nofs; i++)
        if (stop[i] == s)
            return i;
    return -1;
}
int LINE::cross(const LINE& b)const  //两条公交线路相交则返回1
{
    for (int i = 0; i < nofs; i++)
        for (int j = 0; j < b.nofs; j++)
            if (stop[i] == b.stop[j])
                return 1;
    return -1;
}
LINE::operator int()const  //取公交线路编号
{
    return numb;
}
int LINE::NOFS()const      //取公交线路的站点数量
{
    return nofs;
}
double LINE::dist(int d, int a)const //线路从站次d到站次e的距离
{
    int dis = 0;
    if (has(d) > has(a)) dis = has(d) - has(a);
    else dis = has(a) - has(d);
    return dis;
}
int& LINE::operator[](int x)//取线路某个站次的站点编号
{
    return stop[x];
}
LINE::~LINE()noexcept
{
    delete[] stop;
    *(const_cast<int*>(&nofs)) = 0;
}

TRAN::TRAN(int from, int to, int stop)
{
    TRAN::from = from;
    TRAN::to = to;
    TRAN::stop = stop;
}
int TRAN::operator==(const TRAN& t)const
{
    if (from == t.from && to == t.to && stop == t.stop)
        return 1;
    return 0;
}
int& TRAN::F()//现在乘坐的公交线路号
{
    return from;
}
int& TRAN::T()//需要转乘的公交线路号
{
    return to;
}
int& TRAN::S()//转乘点的站点编号
{
    return stop;
}

ROUTE::ROUTE(TRAN* tran, int noft) :tran(new TRAN[noft]), noft(noft)
{
}
ROUTE::ROUTE(const TRAN& t) : tran(new TRAN[1]), noft(1)
{
    tran[0] = t;
}
ROUTE::ROUTE(const ROUTE& r) : tran(new TRAN[r.noft]), noft(r.noft)
{
    for (int i = 0; i < r.noft; i++)
        tran[i] = r.tran[i];
}
ROUTE::ROUTE(ROUTE&& r) noexcept :tran(), noft(r.noft)
{
    *(const_cast<TRAN**>(&tran)) = r.tran;
    *(const_cast<int*>(&noft)) = r.noft;
    *(const_cast<TRAN**>(&r.tran)) = nullptr;
    *(const_cast<int*>(&r.noft)) = 0;
}
int ROUTE::print()const//打印转乘路径
{
    for (int i = 0; i < noft; i++)
        qDebug("%d--%d-->%d\t", tran[i].F(), tran[i].S(), tran[i].T());
    return 1;
}
ROUTE::operator int()const        //得到该路径转乘次数
{
    return noft;
}
int ROUTE::operator==(const ROUTE& r)const//判断两路径是否相同
{
    if (noft != r.noft)return 0;
    for (int i = 0; i < noft; i++)
        if (!(tran[i] == r.tran[i]))
            return 0;
    return 1;
}
ROUTE ROUTE::operator *()const   //去重复公交转乘
{
    //对于一个在前面的转乘点，从后面开始搜索
    //如果和前转乘点的始发路线相同则覆盖删除重复转乘
    for (int i = 0; i < noft; i++)
    {
        for (int j = noft - 1; j > i; j--)
        {
            if (tran[i].F() == tran[j].F())
            {
                for (int k = 0; (j + k) < noft; k++)
                {
                    tran[i + k] = tran[j + k];
                    *(const_cast<int*>(&noft)) = noft - 1;
                }
                break;
            }
        }
        *(const_cast<int*>(&noft)) = noft - 1;
    }
    return *this;
}
TRAN& ROUTE::operator[](int x)     //返回一条路径上的所有转乘
{
    return tran[x];
}
ROUTE ROUTE::operator+(const ROUTE& r)const//将两个转乘路径并入一个转乘路径中并返回
{
    int newn = noft + r.noft;
    ROUTE R(nullptr, newn);
    //if (tran[noft-1].T() != r.tran[0].F()) //若两路径尾部路线和头部路线不同无法合并
    //	return R;
    for (int i = 0; i < noft; i++)
        R.tran[i] = tran[i];
    for (int i = 0; i < r.noft; i++)
        R.tran[i + noft] = r.tran[i];
    //R.print();
    return R;
}
ROUTE& ROUTE::operator=(const ROUTE& r)//深拷贝复制
{
    if (tran)
        delete[] tran;
    *(const_cast<int*>(&noft)) = r.noft;
    *(const_cast<TRAN**>(&tran)) = new TRAN[noft];
    TRAN** ptemp = const_cast<TRAN**>(&tran);
    for (int i = 0; i < noft; i++)
        *(*ptemp + i) = r.tran[i];
    return *this;
}
ROUTE& ROUTE::operator=(ROUTE&& r) noexcept//移动赋值
{
    if (tran)
        delete[] tran;
    *(const_cast<TRAN**>(&tran)) = r.tran;
    *(const_cast<int*>(&noft)) = r.noft;
    *(const_cast<TRAN**>(&r.tran)) = nullptr;
    *(const_cast<int*>(&r.noft)) = 0;
    return *this;
}
ROUTE& ROUTE::operator+=(const ROUTE& r)//将参数路径加到当前路径上
{
    ROUTE temp = *this + r;
    *this = temp;
    return *this;
}
ROUTE::~ROUTE() noexcept
{
    //if(tran)
    //	delete[]tran;
    *(const_cast<int*>(&noft)) = 0;
}

NODE::NODE(ROUTE* p, int n) :p(p), n(n)
{
}
NODE::NODE(int n) : p(new ROUTE[n]), n(n)
{
}
NODE::NODE(const NODE& n) : p(new ROUTE[n.n]), n(n.n)
{
    if (p)
        delete[] p;
    for (int i = 0; i < NODE::n; i++)
        p[i] = n.p[i];
}
NODE::NODE(NODE&& n)noexcept : p(), n(n.n)
{
    if (p)
        delete[] p;
    *(const_cast<ROUTE**>(&p)) = n.p;
    *(const_cast<ROUTE**>(&n.p)) = nullptr;
    *(const_cast<int*>(&n.n)) = 0;
}
NODE  NODE::operator*()const //去掉每个方案中的重复转乘
{
    for (int i = 0; i < n; i++)
        *p[i];
    return *this;
}
NODE  NODE::operator+(const ROUTE& n)const //将参数路径和当前结点的路径并入到一个结点中返回
{
    NODE R(NODE::n + 1);
    for (int i = 0; i < NODE::n; i++)
        R.p[i] = p[i];
    if ((int)n)
        R.p[NODE::n] = n;
    return R;
}
NODE  NODE::operator+(const NODE& n)const	//加法将两个结点的路径加入到一个结点中
{
    NODE R(NODE::n + n.n);
    for (int i = 0; i < NODE::n; i++)
        R.p[i] = p[i];
    for (int i = 0; i < n.n; i++)
        R.p[i + NODE::n] = n.p[i];
    return R;
}
NODE  NODE::operator*(const NODE& n)const	//乘法将两个结点的路径按组合数相缀
{
    int newn = NODE::n * n.n, flag = 0;
    NODE R(newn);
    if (newn > 0)
    {
        for (int i = 0; i < NODE::n; i++)
            for (int j = 0; j < n.n; j++)
                R.p[flag++] = p[i] + n.p[j];
    }
    return R;
}
NODE& NODE::operator=(const NODE& n)	//深拷贝赋值
{
    if (p)
        delete[] p;
    NODE::n = n.n;
    *(const_cast<ROUTE**>(&p)) = new ROUTE[NODE::n];
    for (int i = 0; i < NODE::n; i++)
        p[i] = n.p[i];
    return *this;
}
NODE& NODE::operator+=(const NODE& n)//将参数结点加到当前结点中
{
    *this = *this + n;
    return *this;
}
NODE& NODE::operator+=(const ROUTE& n)//将参数路径加入到当前结点中
{
    *this = *this + n;
    return *this;
}
NODE& NODE::operator*=(const NODE& n)//将参数结点乘到当前结点中
{
    *this = *this * n;
    *(*this);//去环
    this->print();
    return *this;
}
NODE& NODE::operator=(NODE&& n)noexcept//移动赋值
{
    if (p)
        delete[] p;
    NODE::n = n.n;
    *(const_cast<ROUTE**>(&p)) = n.p;
    *(const_cast<ROUTE**>(&n.p)) = nullptr;
    *(const_cast<int*>(&n.n)) = 0;
    return *this;
}
ROUTE& NODE::operator [](int x)//取下标为x的路径的引用
{
    return p[x];
}
NODE::operator int& ()       //返回可转乘路径数n
{
    return n;
}
NODE::~NODE()noexcept
{
    n = 0;
}
void NODE::print()const      //打印结点存储的路径方案
{
    qDebug("Path Scheme Number:%d", n);
    for (int i = 0; i < n; i++)
        p[i].print();
}

TMAP::TMAP(int r, int c) :p(new NODE[r * c]), r(r), c(c)
{
}
TMAP::TMAP(const TMAP& a) : p(new NODE[a.r * a.c]), r(a.r), c(a.c)
{
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            p[i * c + j] = a.p[i * c + j];
}
TMAP::TMAP(TMAP&& a)noexcept :p(), r(a.r), c(a.c)
{
    *(const_cast<NODE**>(&p)) = a.p;
    *(const_cast<NODE**>(&a.p)) = nullptr;
    *(const_cast<int*>(&a.r)) = 0;
    *(const_cast<int*>(&a.c)) = 0;
}
TMAP::~TMAP()
{
    delete[]p;
}
int TMAP::notZero()const                 //若有不可达站点则返回0
{
    for (int i = 0; i < r * c; i++)
        if (i % r != i / r && (int)p[i] == 0)
            return 0;
    return 1;
}
ROUTE TMAP::miniTran(int b, int e)const   //起点站次b,终点站次e,返回最小转乘路径
{
    int min = 10000, flag = 0;
    for (int i = 0; i < (int)p[(b - 1) * TMAP::r + e - 1]; i++)
    {
        if (min > (int)(p[(b - 1) * TMAP::r + e - 1][i]))
        {
            min = (int)(p[(b - 1) * TMAP::r + e - 1][i]);
            flag = i;
        }
    }
    return p[(b - 1) * TMAP::r + e - 1][flag];
}
NODE* TMAP::operator[](int r)            //得到存储多种路径的NODE类元素的某行首址
{
    return &p[r * c];
}
int& TMAP::operator()(int r, int c)      //得到r到c可转乘路径数目（从0开始）
{
    return p[(r - 1) * TMAP::r + c - 1];
}
TMAP TMAP::operator*(const TMAP& a)const //进行两个TMAP的乘法运算
{
    if (c == a.r)
    {
        TMAP A(r, a.c);
        for (int i = 0; i < r; i++)
        {
            for (int j = 0; j < a.c; j++)
            {
                NODE temp;
                for (int k = 0; k < c; k++)
                    temp += p[i * c + k] * a.p[k * c + j];
                A[i][j] = temp;
            }
        }
        NODE temp(nullptr, 0);
        for (int i = 0; i < r; i++)
            A[i][i] = temp;
        return A;
    }
    else
        throw("Operator* ERROR!");
}
TMAP TMAP::operator+(const TMAP& a)const //进行两个TMAP的加法运算
{
    if (r == a.r && c == a.c)
    {
        TMAP A(r, c);
        for (int i = 0; i < r * c; i++)
        {
            A.p[i] = p[i] + a.p[i];
        }
        return A;
    }
    else
        throw("Operator+ ERROR!");
}
TMAP& TMAP::operator=(const TMAP& a) //深拷贝复制
{
    if (this != &a)
    {
        if (p != nullptr)
            delete[] p;
        *(const_cast<int*>(&r)) = a.r;
        *(const_cast<int*>(&c)) = a.c;
        *(const_cast<NODE**>(&p)) = new NODE[r * c];
        for (int i = 0; i < a.r; i++)
            for (int j = 0; j < a.c; j++)
                p[i * a.c + j] = a.p[i * a.c + j];
    }
    return *this;
}
TMAP& TMAP::operator=(TMAP&& a)noexcept//移动赋值
{
    if (this != &a)
    {
        if (p != nullptr)
            delete[] p;
        *(const_cast<int*>(&r)) = a.r;
        *(const_cast<int*>(&c)) = a.c;
        *(const_cast<NODE**>(&p)) = a.p;
        *(const_cast<int*>(&a.r)) = 0;
        *(const_cast<int*>(&a.c)) = 0;
        *(const_cast<NODE**>(&a.p)) = nullptr;
    }
    return *this;
}
TMAP& TMAP::operator+=(const TMAP& a)//将参数闭包矩阵加到当前闭包矩阵上
{
    if (r == a.r && c == a.c)
    {
        for (int i = 0; i < r * c; i++)
        {
            p[i] += a.p[i];
        }
    }
    else
        throw("Operator+ ERROR!");
    return *this;
}
TMAP& TMAP::operator*=(const TMAP& a)//将参数闭包矩阵乘到当前闭包矩阵上
{
    if (c == a.r)
    {
        TMAP A(r, a.c);
        for (int i = 0; i < r; i++)
        {
            for (int j = 0; j < a.c; j++)
            {
                NODE* temp = new NODE;
                for (int k = 0; k < c; k++)
                    *temp += p[i * c + k] * a.p[k * c + j];
                A[i][j] = *temp;
            }
        }
        delete[] p;
        *(const_cast<NODE**>(&p)) = new NODE[r * a.c];
        for (int i = 0; i < r; i++)
            for (int j = 0; j < a.c; j++)
                p[i * a.c + j] = A[i][j];
    }
    else
        throw("Operator* ERROR!");
    return *this;
}
TMAP& TMAP::operator()(int r, int c, const ROUTE& a)//将路径加入到r行c列元素中（从0开始）
{
    int location = r * TMAP::r + c;
    p[location] += a;
    return *this;
}
void TMAP::print()const              //打印转乘矩阵
{
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
            qDebug("%d ", (int)p[i * r + j]);
        //p[i * r + j].print();

    }
}
GIS::GIS()
{
}
GIS::GIS(const char* flstop, const char* flline,const char*florg)
{
    //读取站点文件存入到st中
    FILE* fpstop = fopen(flstop, "r");
    if (!fpstop) exit(-1);
    fscanf(fpstop, "%d", &ns);
    st = new STOP[ns];
    for (int i = 0; i < GIS::ns; i++)
    {
        GIS::st[i].N() = i+1;
        fscanf(fpstop, "%d%d", &GIS::st[i].X(), &GIS::st[i].Y());
    }
    //读取路线文件存入到ls中
    FILE* fpline = fopen(flline, "r");
    if (!fpline) exit(-1);
    fscanf(fpline, "%d", &nl);
    ls = new LINE[nl];
    int* ntemp = new int[nl];
    for (int i = 0; i < nl; i++)
        fscanf(fpline, "%d", &ntemp[i]);
    for (int i = 0; i < GIS::nl; i++)
    {
        LINE temp(i + 1, ntemp[i]);
        for (int j = 0; j < temp.NOFS(); j++)
            fscanf(fpline, "%d", &temp[j]);
        ls[i] = temp;
    }
    delete[]ntemp;
    fclose(fpstop);
    fclose(fpline);
    //初始化原始闭包raw
    raw = *(new TMAP(nl, nl));
    for (int i = 0; i < nl; i++)
    {
        for (int j = 0; j < nl; j++)
        {
            if (i == j || (ls[i].cross(ls[j])) == -1)
                continue;//如果是自身路线或者两路线不相交则进行下一次循环
            int longer = (ls[i].NOFS() > ls[j].NOFS() ? i : j);
            int shorter = (ls[i].NOFS() > ls[j].NOFS() ? j : i);
            for (int k = 0; k < ls[shorter].NOFS(); k++)
            {
                if (ls[longer].has(ls[shorter][k]) != -1)
                {
                    TRAN temp(i + 1, j + 1, ls[shorter][k]);//构造转乘结点
                    ROUTE add = temp;//以转乘结点构造转乘路径
                    raw(i, j, add);//加入当前路径
                }
            }
        }
    }
    //进行闭包运算
    tra = raw;
    for (int i = 0; i < nl - 1; i++)
    {
        TMAP temp = raw * tra;//闭包乘法并存入中间数组
        int flag = 0;//标记是否往下闭包运算，0为不需要
        for (int i = 0; i < nl; i++)
            for (int j = 0; j < nl; j++)
                if (i != j && temp[i][j] == 0) flag = 1;
        tra += temp;//闭包加法，加到闭包运算矩阵上
        if (flag == 0) break;
    }
    //读取机构文件并进行模糊查找处理
    org=new ORG[10];
    FILE *fp=fopen(florg,"r");
    if(!fp)exit(0);
    while(1)
    {
        char ch;
        char orgname[100];
        int orgx=0,orgy=0;
        fscanf(fp,"%s%d%c%d",orgname,&orgx,&ch,&orgy);
        org[no].name=(char*)malloc(sizeof(char)*strlen(orgname));
        strcpy(org[no].name,orgname);
        org[no].order=no;
        org[no].x=orgx;
        org[no++].y=orgy;
        fgetc(fp);
        if(feof(fp)) break;
    }
    fclose(fp);
}
int comp(const void* a, const void* b)
{
    return (*(INFO*)a).dis > (*(INFO*)b).dis ? 1 : -1;
}
int* GIS::nearstop(int x, int y)
{
    INFO* ds = new INFO[ns];
    for (int i = 0; i < ns; i++)
    {
        ds[i].dis = sqrt((x - st[i].X()) * (x - st[i].X()) + (y - st[i].Y()) * (y - st[i].Y()));
        ds[i].order = i + 1;
    }
    qsort(ds, ns, sizeof(ds[0]), comp);
    int* temp = new int[ns], num = 1;
    temp[0] = ds[0].order;
    for (int i = 0; i < ns; i++)
    {
        if (ds[i].dis == temp[0])
            temp[num++] = ds[i].order;
        else break;
    }
    int* s = new int[num];
    s[0] = num;
    for (int i = 0; i < num; i++)
        s[i + 1] = temp[i];
    delete[] temp;
    return s;
}
int comp1(const void* a, const void* b)
{
    return ((int)(*(ROUTE*)a) > (int)(*(ROUTE*)b) ? 1 : -1);
}
void GIS::miniTran(CHOICE *from,CHOICE*to,ANS *ans)
{
    //搜索距离起点和终点的最近站点，如果已经提供临近站点则无需搜索
    int *sfrom=nullptr,*sto=nullptr,i=0,j=0;
    if(from->stop!=-1)
    {
        sfrom=new int[2];
        sfrom[0]=1;
        sfrom[1]=from->stop;
    }
    else
        sfrom = nearstop(from->x, from->y);
    if(to->stop!=-1)
    {
        sto=new int[2];
        sto[0]=1;
        sto[1]=to->stop;
    }
    else
        sto = nearstop(to->x, to->y);
    //搜索各得到的站点所在线路
    SL *slfrom = new SL[sfrom[0]], *slto = new SL[sto[0]];
    for (i = 0; i < sfrom[0]; i++)
    {
        slfrom[i].stop = sfrom[i + 1];//复制stop信息
        int* temp = new int[nl], num = 0;
        for (int j = 0; j < nl; j++)//得到所在线路，存入temp数组
        {
            if (ls[j].has(slfrom[i].stop) != -1)
                temp[num++] = j + 1;
        }
        //将得到的线路信息存入slfrom中
        slfrom[i].nofl = num;
        slfrom[i].line = new int[num];
        for (int k = 0; k < num; k++)
            slfrom[i].line[k] = temp[i];
        delete[] temp;
    }
    for (i = 0; i < sto[0]; i++)
    {
        slto[i].stop = sto[i + 1];
        int* temp = new int[nl], num = 0;
        for (int j = 0; j < nl; j++)
        {
            if (ls[j].has(slto[i].stop) != -1)
                temp[num++] = j + 1;
        }
        slto[i].nofl = num;
        slto[i].line = new int[num];
        for (int k = 0; k < num; k++)
            slto[i].line[k] = temp[i];
        delete[] temp;
    }
    //按照组合数依次比较各线路之间转乘时的转乘次数
    int nofr = 0;//最终得到的路径总数
    for (i = 0; i < sfrom[0]; i++)
    {
        for (j = 0; j < sto[0]; j++)
        {//对于每两个起始站点和下车站点均需进行比较操作
            if(sfrom[i+1]==sto[j+1])
            {
                ans->f=ans->t=sfrom[i+1];
                ans->n=0;
                for(int i=0;i<sfrom[0];i++)
                {
                    delete [] slfrom[i].line;
                }
                delete[]slfrom;
                for(int i=0;i<sto[0];i++)
                {
                    delete [] slto[i].line;
                }
                delete[]slto;
                if(from->stop!=-1)
                    delete[]sfrom;
                if(from->stop!=-1)
                    delete[]sto;
                sfrom=sto=nullptr;
                return ;
            }
            for (int il = 0; il < slfrom[i].nofl; il++)
            {
                for (int jl = 0; jl < slto[j].nofl; jl++)
                {//对于这两个站点所在线路进行组合比较得到NODE转乘方案中的最少转乘路径
                    ans->r[nofr++]=tra.miniTran(slfrom[i].line[il], slto[j].line[jl]);
                }
            }
        }
    }
    //释放slfrom和slto
    for(int i=0;i<sfrom[0];i++)
    {
        delete [] slfrom[i].line;
    }
    delete[]slfrom;
    for(int i=0;i<sto[0];i++)
    {
        delete [] slto[i].line;
    }
    delete[]slto;
    //按照转乘次数进行升序排序
    qsort(ans->r, nofr, sizeof(ans->r[0]), comp1);
    //回溯查找上车站点
    if(from->stop!=-1)
        ans->f=from->stop;
    else
        for(i=0;i<sfrom[0];i++)
            if(ls[ans->r[0][0].F()-1].has(sfrom[i+1])!=-1) ans->f=sfrom[i+1];
    //回溯查找下车站点
    ans->n=(int)ans->r[0];
    if(to->stop!=-1)
        ans->t=to->stop;
    else
        for(i=0;i<sto[0];i++)
            if(ls[ans->r[0][ans->n-1].T()-1].has(sto[i+1])!=-1) ans->t=sto[i+1];
    if(from->stop!=-1)
        delete[]sfrom;
    if(to->stop!=-1)
        delete[]sto;
    sfrom=sto=nullptr;
}
void GIS::print()const
{
    qDebug("---------------STOPS-----------------");
    qDebug("number of stops:%d", ns);
    for (int i = 0; i < ns; i++)
        qDebug("%d %d", st[i].X(), st[i].Y());
    qDebug("---------------LINES-----------------");
    qDebug("number of lines:%d", nl);
    for (int i = 0; i < nl; i++)
        qDebug("%d ", ls[i].NOFS());
    for (int i = 0; i < nl; i++)
    {
        for (int j = 0; j < ls[i].NOFS(); j++)
            qDebug("%d ", ls[i][j]);
    }
    qDebug("---------------RAW-----------------");
    raw.print();
    //(raw[0] + 1)->print();
    qDebug("---------------TRA-----------------");
    tra.print();
    qDebug("---------------ORG-----------------");
    for(int i=0;i<no;i++)
        qDebug()<<org->name<<org[i].x<<org[i].y;
}
GIS::~GIS()
{
}
