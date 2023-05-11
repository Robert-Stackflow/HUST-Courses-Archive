#include "clientwidget.h"
#include "QsLog.h"
#include "dialog/aboutdialog.h"
#include "qdebug.h"
#include "qdesktopwidget.h"
#include "qdir.h"
#include "qpropertyanimation.h"
#include "qtextcodec.h"
#include "ui_clientwidget.h"
#include "widget/cmessagebox.h"
#include "widget/floatbox.h"
#include "util/socketconfig.h"
#include "util/cvalidator.h"
#include "util/filehelper.h"
#include "util/loggerconfig.h"
#include <QFile>
#include <QDesktopServices>
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
ClientWidget::ClientWidget(QWidget *parent)
    : FramelessWidget(parent)
    , ui(new Ui::ClientWidget)
{
    ui->setupUi(this);
    initWidget();
    initSlots();
    initLogger();
    QLOG_INFO()<<"欢迎使用Socket Client应用程序";
}
void ClientWidget::initWidget()
{
#ifdef Q_OS_WIN
    setResizeableAreaWidth(8);
    addIgnoreWidget(ui->iconButton);
    addIgnoreWidget(ui->titleLabel);
    setTitleBar(ui->titleBarWidget);
    setBtnMin(ui->minimizeButton);
    setBtnMax(ui->maximizeButton);
    setBtnClose(ui->closeButton);
#endif
    QPropertyAnimation *anim = new QPropertyAnimation(this, "windowOpacity");
    anim->setDuration(300);
    anim->setStartValue(0);
    anim->setEndValue(1);
    anim->setEasingCurve(QEasingCurve::OutCurve);
    anim->start();
    this->setWindowTitle("Socket Client");
    ui->titleLabel->setText("Socket Client");
    loadQss(":custom/custom.qss");
    setGeometry(0,0,1200,800);
    move((QApplication::desktop()->width() - this->width())/2,(QApplication::desktop()->height() - this->height())/2);
    move((QApplication::desktop()->width() - this->width())/2,(QApplication::desktop()->height() - this->height())/2);
    if(SocketConfig::getPort()!=0)
        ui->portEdit->setText(QString::number(SocketConfig::getPort()));
    ui->portEdit->setValidator(CValidator::portValidator);
    ui->ipEdit->setValidator(CValidator::ipValidator);
    ui->connWidget->setVisible(false);
    ui->disconnButton->setEnabled(false);
    ui->ipEdit->setContextMenuPolicy(Qt::NoContextMenu);
    ui->logEdit->setContextMenuPolicy(Qt::NoContextMenu);
    ui->portEdit->setContextMenuPolicy(Qt::NoContextMenu);
    ui->logEdit->setVisible(true);
    ui->logEdit->setReadOnly(true);
    ui->logEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->logEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->responseTableWidget->verticalHeader()->setDefaultSectionSize(35);
    ui->responseTableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->responseTableWidget->verticalHeader()->hide();
    ui->responseTableWidget->setShowGrid(false);
    ui->responseTableWidget->setAlternatingRowColors(true);
    ui->responseTableWidget->setContextMenuPolicy(Qt::NoContextMenu);
    ui->responseTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->responseTableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->responseTableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->responseTableWidget->setContextMenuPolicy(Qt::NoContextMenu);
    ui->responseTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->responseTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->responseTableWidget->setFocusPolicy(Qt::NoFocus);
    ui->textEdit->setVisible(false);
    ui->textEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->textEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->pictureLabel->setVisible(true);
}
void ClientWidget::initLogger()
{
    QsLogging::Logger& logger = QsLogging::Logger::instance();
    logger.setLoggingLevel(QsLogging::TraceLevel);
    logger.setProgramName("Socket Client");
    QDir dir;
    if (!dir.exists(LoggerConfig::dataDir))
    {
        if (!dir.mkpath(QDir(LoggerConfig::dataDir).absolutePath())){
            CMessageBox::critical(this,"错误","无法创建数据文件夹!");
            return;
        }
    }
    if (!dir.exists(LoggerConfig::fileRecvDir))
    {
        if (!dir.mkpath(QDir(LoggerConfig::fileRecvDir).absolutePath())){
            CMessageBox::critical(this,"错误","无法创建数据文件夹!");
            return;
        }
    }
    QsLogging::DestinationPtr fileDestination(QsLogging::DestinationFactory::MakeFileDestination(
                                                  QCoreApplication::applicationDirPath()+LoggerConfig::logPath, LoggerConfig::rotationOption, LoggerConfig::maxSizeBytes,LoggerConfig::maxOldLogCount));
    QsLogging::DestinationPtr objectDestination(QsLogging::DestinationFactory::MakeFunctorDestination(this, SLOT(writeLog(QString,int))));
    logger.addDestination(fileDestination);
    logger.addDestination(objectDestination);
}
void ClientWidget::initSlots()
{
    connect(ui->closeButton,SIGNAL(clicked()),this,SLOT(onCloseClicked()));
    connect(ui->maximizeButton,SIGNAL(clicked()),this,SLOT(onMaximizeClicked()));
    connect(ui->minimizeButton,SIGNAL(clicked()),this,SLOT(onMinimizeClicked()));
    connect(ui->sendButton,SIGNAL(clicked()),this,SLOT(onSendButtonClicked()));
    connect(ui->logButton,SIGNAL(clicked()),this,SLOT(onLogButtonClicked()));
    connect(ui->helpButton,SIGNAL(clicked()),this,SLOT(onHelpButtonClicked()));
    connect(ui->connButton,SIGNAL(clicked()),this,SLOT(onConnButtonClicked()));
    connect(ui->disconnButton,SIGNAL(clicked()),this,SLOT(onDisConnButtonClicked()));
    connect(ui->requestButton,SIGNAL(clicked()),this,SLOT(onRequestButtonClicked()));
    connect(ui->clearLogButton,SIGNAL(clicked()),this,SLOT(onClearLogButtonClicked()));
    connect(ui->directoryButton,SIGNAL(clicked()),this,SLOT(onDirectoryButtonClicked()));
    connect(ui->responseTableWidget,SIGNAL(cellClicked(int,int)),this,SLOT(onResponseTableWidget(int,int)));
    connect(ui->responseTableWidget,SIGNAL(itemSelectionChanged()),this,SLOT(onSelectChanged()));
}
void ClientWidget::onSelectChanged()
{
    if(ui->responseTableWidget->selectedItems().size()==0)
    {
        ui->textEdit->setVisible(false);
        ui->pictureLabel->setVisible(true);
        ui->pictureLabel->setText("点击文件以预览");
    }
}
void ClientWidget::onResponseTableWidget(int row,int column)
{
    Response* response=SocketConfig::responseList.at(row);
    QString filename=response->getFileName();
    QString filepath=LoggerConfig::fileRecvDir+filename;
    QFileInfo fileInfo=QFileInfo(filepath);
    if(fileInfo.isFile())
    {
        if(FileHelper::isHtml(fileInfo.fileName())){
            ui->textEdit->setVisible(true);
            ui->pictureLabel->setVisible(false);
            QFile file(filepath);
            if(!file.exists())
                return;
            if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
                return;
            QTextCodec *codec = QTextCodec::codecForName("UTF-8");
            QTextStream filestream(&file);
            filestream.setCodec(codec);
            ui->textEdit->setHtml(filestream.readAll());
            file.close();
        }else if(FileHelper::isMarkdown(fileInfo.fileName())){
            ui->textEdit->setVisible(true);
            ui->pictureLabel->setVisible(false);
            QFile file(filepath);
            if(!file.exists())
                return;
            if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
                return;
            QTextCodec *codec = QTextCodec::codecForName("UTF-8");
            QTextStream filestream(&file);
            filestream.setCodec(codec);
            ui->textEdit->setMarkdown(filestream.readAll());
            file.close();
        }else if(FileHelper::isTextFile(fileInfo.fileName())){
            ui->textEdit->setVisible(true);
            ui->pictureLabel->setVisible(false);
            QFile file(filepath);
            if(!file.exists())
                return;
            if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
                return;
            QTextCodec *codec = QTextCodec::codecForName("UTF-8");
            QTextStream filestream(&file);
            filestream.setCodec(codec);
            ui->textEdit->setPlainText(filestream.readAll());
            file.close();
        }else if(FileHelper::isPictureFile(fileInfo.fileName())){
            ui->textEdit->setVisible(false);
            ui->pictureLabel->setVisible(true);
            QImage* img=new QImage;
            if(!(img->load(filepath))){
                delete img;
                return;
            }
            ui->pictureLabel->setPixmap(QPixmap::fromImage(*img).scaled(ui->pictureLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        }else if(FileHelper::isBinaryFile(fileInfo.fileName())){
            ui->textEdit->setVisible(false);
            ui->pictureLabel->setVisible(true);
            ui->pictureLabel->setText("无法预览二进制文件");
        }
    }else{
        ui->textEdit->setVisible(false);
        ui->pictureLabel->setVisible(true);
        ui->pictureLabel->setText("文件不存在");
    }
}
void ClientWidget::onConnButtonClicked()
{
    QString warning="";
    bool flag=true;
    if(!CValidator::checkIp(ui->ipEdit->text()))
        flag=false,warning+="IP地址不合法\n";
    if(!CValidator::checkPort(ui->portEdit->text().toInt()))
        flag=false,warning+="端口号不合法\n";
    if(!flag)
        CMessageBox::warning(this,"错误提示",warning);
    else{
        SocketConfig::setPort(ui->portEdit->text().toInt());
        SocketConfig::setIpAddressString(ui->ipEdit->text());
        QLOG_INFO()<<qUtf8Printable("开始连接服务器["+SocketConfig::getAddress()+"]");
        this->socketThread=new SocketThread();
        this->socketThread->start();
        connect(this->socketThread,SIGNAL(startFail()),this,SLOT(onStartFail()));
        connect(this->socketThread,SIGNAL(startSuccess()),this,SLOT(onStartSuccess()));
        connect(this,SIGNAL(sendFile(QString)),this->socketThread,SLOT(onSendFile(QString)));
        connect(this,SIGNAL(sendMessage(QString)),this->socketThread,SLOT(onSendMessage(QString)));
        connect(this->socketThread,SIGNAL(fileChanged()),this,SLOT(onFileChanged()));
    }
}
void ClientWidget::onFileChanged()
{
    for(int row=ui->responseTableWidget->rowCount()-1;row>=0;row--)
        ui->responseTableWidget->removeRow(row);
    QStringList header;
    header<<"编号"<<"文件路径"<<"字节数"<<"状态"<<"请求时间";
    ui->responseTableWidget->setColumnCount(header.size());
    ui->responseTableWidget->setHorizontalHeaderLabels(header);
    ui->responseTableWidget->setColumnWidth(0,50);
    ui->responseTableWidget->setColumnWidth(1,250);
    ui->responseTableWidget->setColumnWidth(4,200);
    for(int i=0;i<SocketConfig::responseList.size();i++)
    {
        Response* response=SocketConfig::responseList.at(i);
        ui->responseTableWidget->insertRow(ui->responseTableWidget->rowCount());
        ui->responseTableWidget->setItem(ui->responseTableWidget->rowCount()-1,0,new QTableWidgetItem(QString::number(response->getId())));
        ui->responseTableWidget->setItem(ui->responseTableWidget->rowCount()-1,1,new QTableWidgetItem(QString(response->getFilePath())));
        ui->responseTableWidget->setItem(ui->responseTableWidget->rowCount()-1,2,new QTableWidgetItem(QString::number(response->getBytes())));
        ui->responseTableWidget->setItem(ui->responseTableWidget->rowCount()-1,3,new QTableWidgetItem(qUtf8Printable(response->getStatusString())));
        ui->responseTableWidget->setItem(ui->responseTableWidget->rowCount()-1,4,new QTableWidgetItem(response->getRequestTime()));
    }
    for(int i=0;i<ui->responseTableWidget->rowCount();i++)
        for(int j=0;j<ui->responseTableWidget->columnCount();j++)
            ui->responseTableWidget->item(i,j)->setTextAlignment(Qt::AlignCenter);
    ui->responseTableWidget->selectRow(ui->responseTableWidget->rowCount()-1);
    onResponseTableWidget(ui->responseTableWidget->rowCount()-1,0);
}
void ClientWidget::onStartSuccess()
{
    QLOG_INFO()<<qUtf8Printable("与服务器["+SocketConfig::getAddress()+"]连接成功");
    FloatBox::Success("连接成功",this);
    ui->connWidget->setVisible(true);
    ui->connButton->setEnabled(false),ui->disconnButton->setEnabled(true);
}
void ClientWidget::onStartFail()
{
    QLOG_ERROR()<<qUtf8Printable("与服务器["+SocketConfig::getAddress()+"]连接失败");
    FloatBox::Fail("连接失败",this);
    ui->connWidget->setVisible(false);
    ui->connButton->setEnabled(true),ui->disconnButton->setEnabled(false);
}
void ClientWidget::onDisConnButtonClicked()
{
    if(CMessageBox::question(this,"是否断开连接","断开与服务器["+SocketConfig::getAddress()+"]的连接")==CMessageBox::YES){
        if(this->socketThread!=nullptr)
        {
            this->socketThread->finish();
            this->socketThread->quit();
            this->socketThread->exit();
            this->socketThread->terminate();
        }
        ui->connButton->setEnabled(true),ui->disconnButton->setEnabled(false);
        ui->connWidget->setVisible(false);
        FloatBox::Success("断开连接",this);
    }
}
void ClientWidget::onDirectoryButtonClicked()
{
    QDesktopServices::openUrl(QUrl("file:///"+QCoreApplication::applicationDirPath()+LoggerConfig::fileRecvDirWithoutDot));
}
void ClientWidget::onRequestButtonClicked()
{
    if(ui->filepathEdit->text()=="")
        FloatBox::Fail("文件路径不能为空",this);
    else
        emit sendFile(ui->filepathEdit->text());
}
void ClientWidget::onSendButtonClicked()
{
    if(ui->messageEdit->text()=="")
        FloatBox::Fail("消息不能为空",this);
    else
        emit sendMessage(ui->messageEdit->text());
}
void ClientWidget::onHelpButtonClicked()
{
    AboutDialog* aboutDialog=new AboutDialog(this);
    aboutDialog->show();
}
void ClientWidget::onLogButtonClicked()
{
    if(ui->logEdit->isVisible())
    {
        ui->logEdit->setVisible(false);
        FloatBox::Unsee("隐藏日志窗口",this);
    }else
    {
        ui->logEdit->setVisible(true);
        FloatBox::See("显示日志窗口",this);
    }
}
void ClientWidget::onClearLogButtonClicked()
{
    ui->logEdit->clear();
    FloatBox::Success("清除日志",this);
}
void ClientWidget::writeLog(const QString &message, int level)
{
    if(level==5)
        ui->logEdit->append(qUtf8Printable(QString("<p><font color=red>"+message+"</font></p>")));
    else if(level==4)
        ui->logEdit->append(qUtf8Printable(QString("<p><font color=red>"+message+"</font></p>")));
    else if(level==3)
        ui->logEdit->append(qUtf8Printable(QString("<p><font color=orange>"+message+"</font></p>")));
    else if(level==2)
        ui->logEdit->append(qUtf8Printable(QString("<p><font color=black>"+message+"</font></p>")));
    else if(level==1)
        ui->logEdit->append(qUtf8Printable(QString("<p><font color=blue>"+message+"</font></p>")));
    else if(level==0)
        ui->logEdit->append(qUtf8Printable(QString("<p><font color=gray>"+message+"</font></p>")));
}
void ClientWidget::loadQss(const QString& qssFilePath)
{
    QFile file(qssFilePath);
    file.open(QFile::ReadOnly);
    if (file.isOpen())
    {
        QString temp = this->styleSheet;
        temp += QLatin1String(file.readAll());
        this->styleSheet=temp;
        this->setStyleSheet(styleSheet);
        file.close();
    }
}
void ClientWidget::onMaximizeClicked()
{
    if (isMaximized())
        ui->maximizeButton->setIcon(QIcon(":custom/icons/maximize.png")),showNormal();
    else
        ui->maximizeButton->setIcon(QIcon(":custom/icons/restore.png")),showMaximized();
}
void ClientWidget::onMinimizeClicked()
{
    showMinimized();
}
void ClientWidget::onCloseClicked()
{
    close();
}
ClientWidget::~ClientWidget()
{
    delete ui;
}
