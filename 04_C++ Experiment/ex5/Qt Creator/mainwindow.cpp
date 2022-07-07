#include "file.h"
GIS *gis;
ANS *ans=new ANS[1];//最终得到的推荐线路结果
FilePath *file=new FilePath;//文件读取路径和标记
CHOICE *choosef=new CHOICE[1];//起点选择信息
CHOICE *chooset=new CHOICE[1];//终点选择信息
CHOICE *chooseo=new CHOICE[1];//机构查询信息
MainWindow::MainWindow(QWidget *parent): QMainWindow(parent),ui(new Ui::MainWindow)
{
    //相关数据结构初始化
    ui->setupUi(this);
    searchdialog=nullptr;
    file->MapFlag=file->StopFlag=file->LineFlag=file->OrgFlag=choosef->flag=chooset->flag=chooseo->flag=ans->flag=file->LineFlagPaint=0;
    //相关样式初始化
    this->setWindowState(Qt::WindowMaximized);
    this->setWindowTitle("HUSTMAP-华中科技大学周边导航");
    combobox(ui->begin);
    combobox(ui->finish);
    ui->fx->setStyleSheet("QLabel{background-color:rgb(255,255,255);}");
    ui->fy->setStyleSheet("QLabel{background-color:rgb(255,255,255);}");
    ui->tx->setStyleSheet("QLabel{background-color:rgb(255,255,255);}");
    ui->ty->setStyleSheet("QLabel{background-color:rgb(255,255,255);}");
}

void MainWindow::paintEvent(QPaintEvent *)
{
    //绘制地图
    QPixmap image;
    QPainter painter(this);
    bool flag=image.load(file->map);
    if(!flag)
        return;//地图读取错误则不绘图
    image=image.scaled(1525,1525,Qt::KeepAspectRatio,Qt::SmoothTransformation);
    painter.drawPixmap(5,60,image);
    //改换坐标系
    painter.save();
    file->newx=image.rect().bottomLeft().x()-85;
    file->newy=image.rect().bottomLeft().y()+10;
    painter.translate(file->newx,file->newy);
    painter.rotate(270);
    //绘制公交站点
    if(file->StopFlag)
    {
        painter.setPen(QPen(Qt::red,4));
        painter.setBrush(QBrush(Qt::red));
        for(int i=0;i<gis->ns;i++)
            painter.drawEllipse(gis->st[i].Y(),gis->st[i].X(),8,8);
    }
    //绘制公交线路
    if(file->LineFlagPaint)
    {
        painter.setPen(QPen(Qt::blue,4));
        painter.setBrush(QBrush(Qt::blue));
        for(int i=0;i<gis->nl;i++)
        {
            for(int j=0;j<gis->ls[i].NOFS()-1;j++)
            {
                QLineF line(gis->st[gis->ls[i][j]-1].Y()+3,gis->st[gis->ls[i][j]-1].X()+3,gis->st[gis->ls[i][j+1]-1].Y()+3,gis->st[gis->ls[i][j+1]-1].X()+3);
                painter.drawLine(line);
            }
        }
    }
    //绘制机构位置
    if(file->OrgFlag)
    {
        painter.setPen(QPen(Qt::yellow,4));
        painter.setBrush(QBrush(Qt::yellow));
        for(int i=0;i<gis->no;i++)
            painter.drawEllipse(gis->org[i].y,gis->org[i].x,8,8);
    }
    //绘制用户选择的起点和终点
    if(choosef->flag!=0)
    {
        painter.setPen(QPen(Qt::blue,4));
        painter.setBrush(QBrush(Qt::blue));
        painter.drawEllipse(choosef->y,choosef->x,4,4);
    }
    if(chooset->flag!=0)
    {
        painter.setPen(QPen(Qt::black,4));
        painter.setBrush(QBrush(Qt::black));
        painter.drawEllipse(chooset->y,chooset->x,4,4);
    }
    //绘制推荐路线
    if(ans->flag!=0)
    {
        //绘制起点和终点
        painter.setPen(QPen(Qt::blue,4));
        painter.setBrush(QBrush(Qt::blue));
        painter.drawEllipse(choosef->y,choosef->x,8,8);
        painter.drawEllipse(chooset->y,chooset->x,8,8);
        if(ans->n==0)
        {
            painter.setPen(QPen(Qt::blue,2));
            painter.setBrush(QBrush(Qt::blue));
            painter.drawLine(choosef->y+3,choosef->x+3,chooset->y+3,chooset->x+3);
            return;
        }
        painter.setPen(QPen(Qt::black,4));
        painter.setBrush(QBrush(Qt::black));
        painter.drawEllipse(gis->st[ans->f-1].Y(),gis->st[ans->f-1].X(),8,8);
        painter.drawEllipse(gis->st[ans->t-1].Y(),gis->st[ans->t-1].X(),8,8);
        //绘制中间转乘站点
        for(int i=0;i<ans->n;i++)
        {
            painter.setPen(QPen(Qt::black,4));
            painter.setBrush(QBrush(Qt::black));
            painter.drawEllipse(gis->st[ans->r[0][i].S()-1].Y(),gis->st[ans->r[0][i].S()-1].X(),8,8);
        }
        painter.setPen(QPen(Qt::blue,2));
        painter.setBrush(QBrush(Qt::blue));
        int flag,begin,finish,beginstop=ans->f,finishstop;
        //绘制起点到起点站点
        finish=gis->ls[ans->r[0][0].F()-1].has(beginstop);
        int tox=gis->st[gis->ls[ans->r[0][0].F()-1][finish]-1].X();
        int toy=gis->st[gis->ls[ans->r[0][0].F()-1][finish]-1].Y();
        painter.drawLine(choosef->y+3,choosef->x+3,toy+3,tox+3);
        //绘制中间线路
        for(int i=0;i<ans->n;i++)
        {
            finishstop=ans->r[0][i].S();
            begin=gis->ls[ans->r[0][i].F()-1].has(beginstop);
            finish=gis->ls[ans->r[0][i].F()-1].has(finishstop);
            if(begin<finish) //标记向前或向后
                flag=1;
            else
                flag=-1;
            finish=begin+flag;
            while(gis->ls[ans->r[0][i].F()-1][begin]!=finishstop)
            {
                int fromx=gis->st[gis->ls[ans->r[0][i].F()-1][begin]-1].X();
                int fromy=gis->st[gis->ls[ans->r[0][i].F()-1][begin]-1].Y();
                int tox=gis->st[gis->ls[ans->r[0][i].F()-1][finish]-1].X();
                int toy=gis->st[gis->ls[ans->r[0][i].F()-1][finish]-1].Y();
                painter.drawLine(fromy+3,fromx+3,toy+3,tox+3);
                begin+=flag;
                finish+=flag;
            }
            beginstop=finishstop;
        }
        finishstop=ans->t;
        begin=gis->ls[ans->r[0][ans->n-1].T()-1].has(beginstop);
        finish=gis->ls[ans->r[0][ans->n-1].T()-1].has(finishstop);
        if(begin<finish) //标记向前或向后
            flag=1;
        else
            flag=-1;
        finish=begin+flag;
        while(gis->ls[ans->r[0][ans->n-1].T()-1][begin]!=finishstop)
        {
            int fromx=gis->st[gis->ls[ans->r[0][ans->n-1].T()-1][begin]-1].X();
            int fromy=gis->st[gis->ls[ans->r[0][ans->n-1].T()-1][begin]-1].Y();
            int tox=gis->st[gis->ls[ans->r[0][ans->n-1].T()-1][finish]-1].X();
            int toy=gis->st[gis->ls[ans->r[0][ans->n-1].T()-1][finish]-1].Y();
            painter.drawLine(fromy+3,fromx+3,toy+3,tox+3);
            begin+=flag;
            finish+=flag;
        }
        int fromx=gis->st[gis->ls[ans->r[0][ans->n-1].T()-1][begin]-1].X();
        int fromy=gis->st[gis->ls[ans->r[0][ans->n-1].T()-1][begin]-1].Y();
        painter.drawLine(fromy+3,fromx+3,chooset->y+3,chooset->x+3);
        ans->flag=0;
    }
    //突出机构位置
    if(chooseo->flag!=0)
    {
        painter.setPen(QPen(Qt::blue,4));
        painter.setBrush(QBrush(Qt::blue));
        painter.drawEllipse(chooseo->y,chooseo->x,10,10);
    }
    painter.restore();
}
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(!(file->LineFlag&&file->MapFlag&&file->StopFlag&&file->OrgFlag))
        return;
    chooseo->flag=0;
    this->repaint();
    if (event->button() == Qt::LeftButton){
        ans->flag=0;
        choosef->stop=-1;
        if(choosef->flag==0) choosef->flag=1;
        //确定鼠标在当前坐标系下的实际坐标并存入choosef中
        int mx=this->mapFromGlobal(QCursor().pos()).x()-file->newx;
        int my=file->newy-this->mapFromGlobal(QCursor().pos()).y();
        choosef->x=mx;
        choosef->y=my;
        ui->fx->setText(QString::asprintf("%d",choosef->x));
        ui->fy->setText(QString::asprintf("%d",choosef->y));
//        ui->statusbar->showMessage(QString::asprintf("起点坐标:%d %d",choosef->x,choosef->y));
        this->repaint();
        for(int i=0;i<gis->ns;i++)
        {
            double dis=sqrt((mx-gis->st[i].X())*(mx-gis->st[i].X())+(my-gis->st[i].Y())*(my-gis->st[i].Y()));
            if(dis<8)
            {
                choosef->stop=i+1;
                //                qDebug()<<"已选择的临近出发站点"<<gis->st[i].N();
                break;
            }
        }
        for(int i=0;i<gis->no;i++)
        {
            double dis=sqrt((mx-gis->org[i].x)*(mx-gis->org[i].x)+(my-gis->org[i].y)*(my-gis->org[i].y));
            if(dis<8.0)
            {
                ui->begin->setCurrentIndex(i);
                break;
            }
        }
        if(choosef->flag&&chooset->flag)
        {
            gis->miniTran(choosef,chooset,ans);
            qDebug()<<"----------------------------------------------";
            qDebug()<<"上车站点"<<ans->f<<"\n下车站点"<<ans->t<<"\n转乘次数"<<ans->n;
            qDebug()<<"转乘方案(出发线路 转乘站点 换乘线路）如下:";
            ans->r[0].print();
            ans->flag=1;
            choosef->flag=chooset->flag=0;
            this->repaint();
        }
    }
    else if (event->button() == Qt::RightButton){
        ans->flag=0;
        chooset->stop=-1;
        if(chooset->flag==0) chooset->flag=1;
        //确定鼠标在当前坐标系下的实际坐标并存入chooset中
        int mx=this->mapFromGlobal(QCursor().pos()).x()-file->newx;
        int my=file->newy-this->mapFromGlobal(QCursor().pos()).y();
        chooset->x=mx;
        chooset->y=my;
        ui->tx->setText(QString::asprintf("%d",chooset->x));
        ui->ty->setText(QString::asprintf("%d",chooset->y));
//        ui->statusbar->showMessage(QString::asprintf("终点坐标:%d %d",chooset->x,chooset->y));
        this->repaint();
        for(int i=0;i<gis->ns;i++)
        {
            double dis=sqrt((mx-gis->st[i].X())*(mx-gis->st[i].X())+(my-gis->st[i].Y())*(my-gis->st[i].Y()));
            if(dis<8)
            {
                chooset->stop=i+1;
                //                qDebug()<<"已选择的临近到达站点"<<gis->st[i].N();
                break;
            }
        }
        for(int i=0;i<gis->no;i++)
        {
            double dis=sqrt((mx-gis->org[i].x)*(mx-gis->org[i].x)+(my-gis->org[i].y)*(my-gis->org[i].y));
            if(dis<8.0)
            {
                ui->finish->setCurrentIndex(i);
                break;
            }
        }
        if(choosef->flag&&chooset->flag)
        {
            gis->miniTran(choosef,chooset,ans);
            qDebug()<<"----------------------------------------------";
            qDebug()<<"上车站点"<<ans->f<<"\n下车站点"<<ans->t<<"\n转乘次数"<<ans->n;
            qDebug()<<"转乘方案(出发线路 转乘站点 换乘线路）如下:";
            ans->r[0].print();
            ans->flag=1;
            choosef->flag=chooset->flag=0;
            this->repaint();
        }
    }
}
MainWindow::~MainWindow()
{
    delete ui;
    delete searchdialog;
}

void MainWindow::on_action_1_triggered()
{
    file->MapFlag=0;
    QString OpenFile, OpenFilePath;
    OpenFile = QFileDialog::getOpenFileName(this,tr("请选择地图文件（华中科技大学周边地图.bmp)"),"",tr("Image Files(*.jpg *.png *.bmp *.pgm *.pbm);;All(*.*)"));
    if (OpenFile != "")
    {
        QFileInfo OpenFileInfo;
        OpenFileInfo = QFileInfo(OpenFile);
        OpenFilePath = OpenFileInfo.filePath();
        file->map=OpenFilePath;
        file->MapFlag=1;
        this->repaint();
    }
}

void MainWindow::on_action_2_triggered()
{
    //判断规则限制
    if(!file->MapFlag)
    {
        QMessageBox error(QMessageBox::Critical, "错误提示", "尚未加载地图文件,请加载地图文件后重试");
        error.exec();
        return;
    }
    //读取文件路径
    file->StopFlag=0;
    QString OpenFile,OpenFilePath;
    OpenFile = QFileDialog::getOpenFileName(this,"请选择站点文件（stops.txt)","","Txt Files(*.txt);");
    if (OpenFile != "")
    {
        QFileInfo OpenFileInfo;
        OpenFileInfo = QFileInfo(OpenFile);
        OpenFilePath = OpenFileInfo.filePath();
        file->stops=OpenFilePath;
        file->StopFlag=1;
    }
    //创建GIS
    if(file->MapFlag&&file->StopFlag&&file->LineFlag&&file->OrgFlag)
    {
        const char* sfile;
        QByteArray stemp=file->stops.toLocal8Bit();
        sfile=stemp.data();
        const char* lfile;
        QByteArray ltemp=file->lines.toLocal8Bit();
        lfile=ltemp.data();
        const char* ofile;
        QByteArray otemp=file->orgs.toLocal8Bit();
        ofile=otemp.data();
        gis=new GIS(sfile,lfile,ofile);
        this->repaint();
    }
}
void MainWindow::on_action_3_triggered()
{
    //判断规则限制
    if(!file->MapFlag||!file->StopFlag)
    {
        QMessageBox error(QMessageBox::Critical, "错误提示", "尚未加载地图或站点文件,请加载地图或站点文件后重试");
        error.exec();
        return;
    }
    file->LineFlag=0;
    QString OpenFile,OpenFilePath;
    OpenFile = QFileDialog::getOpenFileName(this,"请选择路线文件（lines.txt)","","Txt Files(*.txt);");
    if (OpenFile != "")
    {
        QFileInfo OpenFileInfo;
        OpenFileInfo = QFileInfo(OpenFile);
        OpenFilePath = OpenFileInfo.filePath();
        file->lines=OpenFilePath;
        file->LineFlag=1;
    }
    //创建GIS
    if(file->MapFlag&&file->StopFlag&&file->LineFlag&&file->OrgFlag)
    {
        const char* sfile;
        QByteArray stemp=file->stops.toLocal8Bit();
        sfile=stemp.data();
        const char* lfile;
        QByteArray ltemp=file->lines.toLocal8Bit();
        lfile=ltemp.data();
        const char* ofile;
        QByteArray otemp=file->orgs.toLocal8Bit();
        ofile=otemp.data();
        gis=new GIS(sfile,lfile,ofile);
        this->repaint();
    }
}

void MainWindow::on_action_4_triggered()
{
    //判断规则限制
    if(!file->MapFlag)
    {
        QMessageBox error(QMessageBox::Critical, "错误提示", "尚未加载地图文件,请加载地图文件后重试");
        error.exec();
        return;
    }
    //预处理相关信息框
    if(!searchdialog)
        searchdialog = new SearchDialog(this);
    combobox(searchdialog->ui->comboBox);
    ui->begin->clear();
    ui->finish->clear();
    searchdialog->ui->comboBox->clear();
    searchdialog->setWindowTitle("查询机构");
    //读取文件路径
    file->OrgFlag=0;
    QString OpenFile,OpenFilePath;
    OpenFile = QFileDialog::getOpenFileName(this,"请选择机构文件（organization.txt)","","Txt Files(*.txt);");
    if (OpenFile != "")
    {
        QFileInfo OpenFileInfo;
        OpenFileInfo = QFileInfo(OpenFile);
        OpenFilePath = OpenFileInfo.filePath();
        file->orgs=OpenFilePath;
        file->OrgFlag=1;
    }
    //创建GIS
    if(file->MapFlag&&file->StopFlag&&file->LineFlag&&file->OrgFlag)
    {
        const char* sfile;
        QByteArray stemp=file->stops.toLocal8Bit();
        sfile=stemp.data();
        const char* lfile;
        QByteArray ltemp=file->lines.toLocal8Bit();
        lfile=ltemp.data();
        const char* ofile;
        QByteArray otemp=file->orgs.toLocal8Bit();
        ofile=otemp.data();
        gis=new GIS(sfile,lfile,ofile);
        this->repaint();
    }
    //读取机构文件并进行模糊查找处理
    for(int i=0;i<gis->no;i++)
    {
        ui->begin->addItem(QString::asprintf("%s",gis->org[i].name));
        ui->finish->addItem(QString::asprintf("%s",gis->org[i].name));
        searchdialog->ui->comboBox->addItem(QString::asprintf("%s",gis->org[i].name));
    }
    QCompleter *pcomp = new QCompleter(ui->begin->model(),this);
    ui->begin->setCompleter(pcomp);
    ui->begin->setCurrentIndex(-1);
    QCompleter *qcomp = new QCompleter(ui->finish->model(),this);
    ui->finish->setCompleter(qcomp);
    ui->finish->setCurrentIndex(-1);
    QCompleter *rcomp = new QCompleter(searchdialog->ui->comboBox->model(),this);
    searchdialog->ui->comboBox->setCompleter(rcomp);
    searchdialog->ui->comboBox->setCurrentIndex(-1);
    connect(ui->begin, SIGNAL(currentIndexChanged(int)), this, SLOT(choosebegin(int)));
    connect(ui->finish, SIGNAL(currentIndexChanged(int)), this, SLOT(choosefinish(int)));
    connect(searchdialog->ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(focusorg(int)));
}

void MainWindow::choosebegin(int index)
{
    choosef->flag=1;
    choosef->stop=-1;
    choosef->x=gis->org[index].x;
    choosef->y=gis->org[index].y;
    ui->fx->setText(QString::asprintf("%d",choosef->x));
    ui->fy->setText(QString::asprintf("%d",choosef->y));
    this->repaint();
}

void MainWindow::choosefinish(int index)
{
    chooset->flag=1;
    chooset->stop=-1;
    chooset->x=gis->org[index].x;
    chooset->y=gis->org[index].y;
    ui->tx->setText(QString::asprintf("%d",chooset->x));
    ui->ty->setText(QString::asprintf("%d",chooset->y));
    this->repaint();
    if(choosef->flag&&chooset->flag)
    {
        gis->miniTran(choosef,chooset,ans);
        qDebug()<<"----------------------------------------------";
        qDebug()<<"上车站点"<<ans->f<<"\n下车站点"<<ans->t<<"\n转乘次数"<<ans->n;
        qDebug()<<"转乘方案(出发线路 转乘站点 换乘线路）如下:";
        ans->r[0].print();
        ans->flag=1;
        choosef->flag=chooset->flag=0;
        ui->begin->clearEditText();
        ui->finish->clearEditText();
        this->repaint();
    }
}
void MainWindow::focusorg(int index)
{
    chooseo->flag=1;
    chooseo->x=gis->org[index].x;
    chooseo->y=gis->org[index].y;
    //    qDebug()<<gis->org[index].name<<index;
    this->repaint();
}

void MainWindow::on_action_6_triggered()
{
    QMessageBox guide(QMessageBox::Information, "使用指南",
                      "1.首先需要在“文件”菜单选项中依次载入文件;\n"
                      "2.载入地图文件后将会立即显示在窗口中;\n"
                      "3.载入其余三个文件后相关站点、线路和机构才会显示;\n"
                      "4.公交站点将会以突出标记的红色点显示;\n"
                      "5.加载的机构地点以黄色点显示;\n"
                      "6.左键选择起点，右键选择终点，选择成功后将自动规划路线;\n"
                      "7.选择的起点为蓝色小圆点，终点为黑色小圆点;\n"
                      "8.规划路线中，用户选择的点为黑色圆点，规划的起点终点为蓝色，路线为蓝色;\n"
                      "9.地图上方将显示选择的机构信息和具体位置;\n"
                      "10.可通过查询菜单查找机构以进行导航。");
    guide.exec();
}


void MainWindow::on_action_7_triggered()
{
    QMessageBox quick(QMessageBox::Information, "快捷键指南",
                      "注意事项:快捷键需ctrl组合触发;\n"
                      "ctrl+M\t\t加载地图文件;\n"
                      "ctrl+S\t\t加载站点文件;\n"
                      "ctrl+L\t\t加载路线文件;\n"
                      "ctrl+O\t\t加载机构文件;\n"
                      "ctrl+F\t\t打开查询功能;\n"
                      "ctrl+H\t\t查看使用帮助;\n"
                      "ctrl+Q\t\t查看快捷键帮助;\n"
                      "ctrl+N\t\t查看版权信息");
    quick.exec();
}


void MainWindow::on_action_HUSTMAP_triggered()
{
    QMessageBox copyright(QMessageBox::NoIcon, "关于HUSTMAP", "Copyright © 2021 by Ruida Xu. All rights reserved.\n");
    copyright.exec();
}


void MainWindow::on_action_5_triggered()
{
    if(!searchdialog)
    {
        QMessageBox error(QMessageBox::Critical, "错误提示", "尚未加载机构坐标文件,请加载后再次尝试查询");
        error.exec();
    }
    else
    {
        searchdialog->setModal(true);
        searchdialog->exec();
        searchdialog->ui->comboBox->clearEditText();
    }
}
void MainWindow::combobox(QComboBox* box)//设定下拉菜单框样式
{
    box->setEditable(true);
    box->setStyleSheet(
                "QComboBox{"
                "combobox-popup: 0;"
                "border-style:none;"
                "padding-left:10px;"
                "width:48px; "
                "height:24px; "
                "line-height:24px;"
                "}"
                "QComboBox:drop-down {"
                "width:40px;"
                "height:50px; "
                "border: none;  "
                "subcontrol-position: right center; "
                "subcontrol-origin: padding;"
                "}"
                "QComboBox:down-arrow {"
                "border: none; "
                "background: transparent; "
                "}"
                "QComboBox QAbstractScrollArea QScrollBar:vertical{"
                "width: 6px;"
                "height: 100px;"
                "background-color: transparent;"
                "}"
                "QComboBox QAbstractScrollArea QScrollBar::handle:vertical{"
                "border-radius: 3px;"
                "background: rgba(0,0,0,0.1);"
                "}"
                "QComboBox QAbstractScrollArea QScrollBar::handle:vertical:hover{"
                "background: rgb(90, 91, 93);"
                "}"
                "QComboBox QScrollBar::add-line::vertical{"
                "border:none;"
                "}"
                "QComboBox QScrollBar::sub-line::vertical{"
                "border:none;"
                "}"
                );
}

void MainWindow::on_pushButton_clicked()
{
    choosef->flag=0;
    chooset->flag=0;
    chooseo->flag=0;
    ui->begin->clearEditText();
    ui->finish->clearEditText();
    ui->fx->clear();
    ui->fy->clear();
    ui->tx->clear();
    ui->ty->clear();
    ans->flag=0;
    this->repaint();
}

void MainWindow::on_pushButton_2_clicked()
{
    if(file->LineFlagPaint==1)
        file->LineFlagPaint=0;
    else
        file->LineFlagPaint=1;
    this->repaint();
}
