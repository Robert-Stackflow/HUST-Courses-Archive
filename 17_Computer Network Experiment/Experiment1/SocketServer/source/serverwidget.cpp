#include "serverwidget.h"
#include "qclipboard.h"
#include "qdebug.h"
#include "qdesktopwidget.h"
#include "qdir.h"
#include "qpropertyanimation.h"
#include "ui_serverwidget.h"
#include "widget/cmessagebox.h"
#include "util/socketconfig.h"
#include "util/sockethelper.h"
#include "util/loggerconfig.h"
#include "widget/floatbox.h"
#include "QsLog.h"
#include <QFile>
#include <QDesktopServices>
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
ServerWidget::ServerWidget(QWidget *parent)
    :FramelessWidget(parent)
    ,ui(new Ui::ServerWidget)
{
    ui->setupUi(this);
    initWidget();
    initSlots();
    initLogger();
    refreshSetting();
    initTableWidget();
    this->show();
    QLOG_INFO()<<"欢迎使用Socket Server应用程序";
    QLOG_INFO()<<"本机IP地址列表:"<<SocketHelper::getIpList();
    SocketConfig::setIpAddressString(SocketHelper::getIpList().at(0));
    refreshSetting();
}
void ServerWidget::initWidget()
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
    setGeometry(0,0,1200,800);
    move((QApplication::desktop()->width() - this->width())/2,(QApplication::desktop()->height() - this->height())/2);
    move((QApplication::desktop()->width() - this->width())/2,(QApplication::desktop()->height() - this->height())/2);
    QPropertyAnimation *anim = new QPropertyAnimation(this, "windowOpacity");
    anim->setDuration(300);
    anim->setStartValue(0);
    anim->setEndValue(1);
    anim->setEasingCurve(QEasingCurve::OutCurve);
    anim->start();
    loadQss(":custom/custom.qss");
    this->setWindowTitle("Socket Server");
    ui->titleLabel->setText("Socket Server");
    ui->portEdit->installEventFilter(this);
    ui->ipEdit->installEventFilter(this);
    ui->dirEdit->installEventFilter(this);
    ui->ipEdit->setReadOnly(true);
    ui->portEdit->setReadOnly(true);
    ui->dirEdit->setReadOnly(true);
    ui->portEdit->setContextMenuPolicy(Qt::NoContextMenu);
    ui->ipEdit->setContextMenuPolicy(Qt::NoContextMenu);
    ui->dirEdit->setContextMenuPolicy(Qt::NoContextMenu);
    ui->logEdit->setVisible(true);
    ui->logEdit->setReadOnly(true);
    ui->logEdit->setContextMenuPolicy(Qt::NoContextMenu);
    ui->logEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->logEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->endButton->setEnabled(false);
    aboutDialog =new AboutDialog(this);
    settingDialog =new SettingDialog(this);
}
void ServerWidget::initLogger()
{
    QsLogging::Logger& logger = QsLogging::Logger::instance();
    logger.setLoggingLevel(QsLogging::DebugLevel);
    logger.setProgramName("Socket Server");
    QDir dir;
    if (!dir.exists(LoggerConfig::dataDir))
    {
        if (!dir.mkpath(QDir(LoggerConfig::dataDir).absolutePath())){
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
void ServerWidget::initTableWidget()
{
    ui->requestTableWidget->verticalHeader()->setDefaultSectionSize(35);
    ui->requestTableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->requestTableWidget->verticalHeader()->hide();
    ui->requestTableWidget->setShowGrid(false);
    ui->requestTableWidget->setAlternatingRowColors(true);
    ui->requestTableWidget->setContextMenuPolicy(Qt::NoContextMenu);
    ui->requestTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->requestTableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->requestTableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->requestTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->requestTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->requestTableWidget->setFocusPolicy(Qt::NoFocus);
}
void ServerWidget::initSlots()
{
    connect(ui->closeButton,SIGNAL(clicked()),this,SLOT(onCloseClicked()));
    connect(ui->maximizeButton,SIGNAL(clicked()),this,SLOT(onMaximizeClicked()));
    connect(ui->minimizeButton,SIGNAL(clicked()),this,SLOT(onMinimizeClicked()));
    connect(ui->directoryButton,SIGNAL(clicked()),this,SLOT(onDirectoryButtonClicked()));
    connect(ui->startButton,SIGNAL(clicked()),this,SLOT(onStartButtonClicked()));
    connect(ui->endButton,SIGNAL(clicked()),this,SLOT(onEndButtonClicked()));
    connect(ui->logButton,SIGNAL(clicked()),this,SLOT(onLogButtonClicked()));
    connect(ui->helpButton,SIGNAL(clicked()),this,SLOT(onHelpButtonClicked()));
    connect(ui->settingButton,SIGNAL(clicked()),this,SLOT(onSettingButtonClicked()));
    connect(ui->clearLogButton,SIGNAL(clicked()),this,SLOT(onClearLogButtonClicked()));
    connect(ui->indexButton,SIGNAL(clicked()),this,SLOT(onIndexButtonClicked()));
    connect(settingDialog,SIGNAL(settingChanged()),this,SLOT(refreshSetting()));
}
void ServerWidget::refreshSetting()
{
    ui->dirEdit->setText(SocketConfig::getDirectory());
    ui->portEdit->setText(QString::number(SocketConfig::getPort()));
    if(SocketConfig::getIpAddress()==nullptr)
        ui->ipEdit->setText("默认地址");
    else
        ui->ipEdit->setText(SocketConfig::getIpAddressString());
}
void ServerWidget::onIndexButtonClicked()
{
    QLOG_DEBUG()<<"http://"+SocketConfig::getIpAddressString()+":"+QString::number(SocketConfig::getPort());
    QDesktopServices::openUrl(QUrl("http://"+SocketConfig::getIpAddressString()+":"+QString::number(SocketConfig::getPort())));
}
void ServerWidget::onDirectoryButtonClicked()
{
    QDesktopServices::openUrl(QUrl("file:///"+SocketConfig::getDirectory()+"/"));
}
void ServerWidget::onStartButtonClicked()
{
    this->socketThread=new SocketThread();
    this->socketThread->start();
    connect(this->socketThread,SIGNAL(startFail()),this,SLOT(onStartFail()));
    connect(this->socketThread,SIGNAL(startSuccess()),this,SLOT(onStartSuccess()));
    connect(this->socketThread,SIGNAL(requestChanged()),this,SLOT(onRequestUpdated()));
}
void ServerWidget::onStartSuccess()
{
    QLOG_INFO()<<"服务器运行成功";
    FloatBox::Success("运行成功",this);
    ui->settingButton->setEnabled(false);
    ui->startButton->setEnabled(false),ui->endButton->setEnabled(true);
}
void ServerWidget::onStartFail()
{
    QLOG_ERROR()<<"服务器运行失败";
    FloatBox::Fail("运行失败",this);
    ui->settingButton->setEnabled(true);
    ui->startButton->setEnabled(true),ui->endButton->setEnabled(false);
}
void ServerWidget::onEndButtonClicked()
{
    if(CMessageBox::question(this,"是否结束","是否终止服务器运行")==CMessageBox::YES){
        if(this->socketThread!=nullptr)
        {
            this->socketThread->finish();
            this->socketThread->quit();
            this->socketThread->exit();
            this->socketThread->terminate();
        }
        FloatBox::Success("结束运行",this);
        ui->settingButton->setEnabled(true);
        ui->startButton->setEnabled(true),ui->endButton->setEnabled(false);
    }
}
void ServerWidget::onRequestUpdated()
{
    for(int row=ui->requestTableWidget->rowCount()-1;row>=0;row--)
        ui->requestTableWidget->removeRow(row);
    QStringList header;
    header<<"编号"<<"IP地址"<<"端口号"<<"文件路径"<<"状态"<<"连接时间"<<"报文";
    ui->requestTableWidget->setColumnCount(header.size());
    ui->requestTableWidget->setHorizontalHeaderLabels(header);
    ui->requestTableWidget->setColumnWidth(3,200);
    ui->requestTableWidget->setColumnWidth(4,100);
    ui->requestTableWidget->setColumnWidth(5,200);
    ui->requestTableWidget->setColumnWidth(6,400);
    for(int i=0;i<SocketConfig::getRequestList().size();i++)
    {
        Request* request=SocketConfig::getRequestList().at(i);
        ui->requestTableWidget->insertRow(ui->requestTableWidget->rowCount());
        ui->requestTableWidget->setItem(ui->requestTableWidget->rowCount()-1,0,new QTableWidgetItem(QString::number(request->getId())));
        ui->requestTableWidget->setItem(ui->requestTableWidget->rowCount()-1,1,new QTableWidgetItem(QString(request->getIp())));
        ui->requestTableWidget->setItem(ui->requestTableWidget->rowCount()-1,2,new QTableWidgetItem(QString::number(request->getPort())));
        ui->requestTableWidget->setItem(ui->requestTableWidget->rowCount()-1,3,new QTableWidgetItem(qUtf8Printable(QString(request->getFilePath()).replace(SocketConfig::getDirectory(),""))));
        ui->requestTableWidget->setItem(ui->requestTableWidget->rowCount()-1,4,new QTableWidgetItem(qUtf8Printable(request->getStatusString())));
        ui->requestTableWidget->setItem(ui->requestTableWidget->rowCount()-1,5,new QTableWidgetItem(request->getConnTime()));
        ui->requestTableWidget->setItem(ui->requestTableWidget->rowCount()-1,6,new QTableWidgetItem(request->getPacket()));
    }
    for(int i=0;i<ui->requestTableWidget->rowCount();i++)
        for(int j=0;j<ui->requestTableWidget->columnCount();j++)
            ui->requestTableWidget->item(i,j)->setTextAlignment(Qt::AlignCenter);
}
void ServerWidget::onHelpButtonClicked()
{
    aboutDialog->show();
}
void ServerWidget::onSettingButtonClicked()
{
    settingDialog->show();
}
void ServerWidget::onLogButtonClicked()
{
    if(ui->logEdit->isVisible()){
        ui->logEdit->setVisible(false);
        FloatBox::Unsee("隐藏日志窗口",this);
    }else{
        ui->logEdit->setVisible(true);
        FloatBox::See("显示日志窗口",this);
    }
}
void ServerWidget::onClearLogButtonClicked()
{
    ui->logEdit->clear();
    FloatBox::Success("清除日志",this);
}
void ServerWidget::writeLog(const QString &message, int level)
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
bool ServerWidget::eventFilter(QObject *obj, QEvent *event)
{
    if(event->type() == QEvent::MouseButtonDblClick) {
        if(obj==ui->portEdit||obj==ui->ipEdit||obj==ui->dirEdit){
            QClipboard* clip=QApplication::clipboard();
            clip->setText(((QLineEdit*)obj)->text());
            FloatBox::Success("复制成功",this);
            return false;
        }
    }
    return false;
}
void ServerWidget::loadQss(const QString& qssFilePath)
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
void ServerWidget::onMaximizeClicked()
{
    if (isMaximized())
        ui->maximizeButton->setIcon(QIcon(":custom/icons/maximize.png")),showNormal();
    else
        ui->maximizeButton->setIcon(QIcon(":custom/icons/restore.png")),showMaximized();
}
void ServerWidget::onMinimizeClicked()
{
    showMinimized();
}
void ServerWidget::onCloseClicked()
{
    close();
}
ServerWidget::~ServerWidget()
{
    delete ui;
}
