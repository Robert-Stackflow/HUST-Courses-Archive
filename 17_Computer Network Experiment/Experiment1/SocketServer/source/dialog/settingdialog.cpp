#include "dialog/settingdialog.h"
#include "qdesktopwidget.h"
#include "widget/cmessagebox.h"
#include "widget/floatbox.h"
#include "qdebug.h"
#include "qevent.h"
#include "QsLog.h"
#include "qgraphicseffect.h"
#include "ui_settingdialog.h"
#include "util/socketconfig.h"
#include "util/sockethelper.h"
#include "util/cvalidator.h"
#include <Windows.h>
#include <WinUser.h>
#include <QDir>
#include <QDesktopServices>
#include <QFileDialog>
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
SettingDialog::SettingDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingDialog)
{
    ui->setupUi(this);
    initWidget();
    if(parent!=nullptr){
        QPoint globalPos = parent->mapToGlobal(QPoint(0,0));
        int x = globalPos.x() + (parent->width() - this->width())/2;
        int y = globalPos.y() + (parent->height() - this->height())/2;
        this->move(x,y);
    }
    move((QApplication::desktop()->width() - this->width())/2,(QApplication::desktop()->height() - this->height())/2);
    move((QApplication::desktop()->width() - this->width())/2,(QApplication::desktop()->height() - this->height())/2);
}
void SettingDialog::initWidget()
{
    setWindowCustomTitle("设置");
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::FramelessWindowHint|Qt::Dialog);
    setWindowModality(Qt::WindowModal);
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(0,0);
    shadow->setBlurRadius(20);
    shadow->setColor(QColor(167,166,170));
    setGraphicsEffect(shadow);
    ui->dialogGridLayout->setMargin(20);
    QFile file(":custom/custom.qss");
    file.open(QFile::ReadOnly);
    if (file.isOpen())
    {
        QString temp = this->styleSheet;
        temp += QLatin1String(file.readAll());
        this->styleSheet=temp;
        this->setStyleSheet(styleSheet);
        file.close();
    }
    {
        ui->ipEdit->setVisible(false);
        ui->portEdit->setText(QString::number(SocketConfig::getPort()));
        if(SocketConfig::getIpAddress()==nullptr)
            ui->ipEdit->setText("");
        else
            ui->ipEdit->setText(SocketConfig::getIpAddressString());
        ui->directoryEdit->setText(SocketConfig::getDirectory());
        ui->ipEdit->setValidator(CValidator::ipValidator);
        ui->portEdit->setValidator(CValidator::portValidator);
        ui->portEdit->setContextMenuPolicy(Qt::NoContextMenu);
        ui->ipEdit->setContextMenuPolicy(Qt::NoContextMenu);
        ui->directoryEdit->setContextMenuPolicy(Qt::NoContextMenu);
    }
    ui->ipComboBox->addItems(SocketHelper::getIpList());
    connect(ui->closeButton,SIGNAL(clicked()),this,SLOT(onCloseClicked()));
    connect(ui->minimizeButton,SIGNAL(clicked()),this,SLOT(onMinimizeClicked()));
    connect(this,SIGNAL(ncActive(bool)),this,SLOT(onNcActived(bool)));
    connect(ui->dirButton,SIGNAL(clicked()),this,SLOT(onDirButtonClicked()));
    connect(ui->portEdit,SIGNAL(textChanged(QString)),this,SLOT(onPortEdited(QString)));
    connect(ui->directoryEdit,SIGNAL(textChanged(QString)),this,SLOT(onDirectoryEdited(QString)));
    connect(ui->portEdit,SIGNAL(textChanged(QString)),this,SLOT(onPortEdited(QString)));
    connect(ui->directoryEdit,SIGNAL(textChanged(QString)),this,SLOT(onDirectoryEdited(QString)));
    connect(ui->confirmButton,SIGNAL(clicked()),this,SLOT(onOperationButtonsClicked()));
    connect(ui->cancelButton,SIGNAL(clicked()),this,SLOT(onOperationButtonsClicked()));
    connect(ui->ipComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(onIpComboBoxChanged(int)));
    //    connect(ui->ipEdit,SIGNAL(textChanged(QString)),this,SLOT(onIpEdited(QString)));
}
void SettingDialog::onPortEdited(const QString & newPort)
{
    if(newPort!=QString::number(SocketConfig::getPort()))
        isPortChanged=true;
    else
        isPortChanged=false;
    if(!CValidator::checkPort(newPort))
        FloatBox::Fail("端口号不合法",this),ui->portEdit->setStyleSheet(ui->portEdit->styleSheet()+"color:red;");
    else
        ui->portEdit->setStyleSheet(ui->portEdit->styleSheet()+"color:black;");
}
void SettingDialog::onIpComboBoxChanged(int)
{
    if(ui->ipComboBox->currentText()!=SocketConfig::getIpAddressString())
        isIpChanged=true;
    else
        isIpChanged=false;
}
void SettingDialog::onIpEdited(const QString & newIp)
{
    if(newIp!=SocketConfig::getIpAddressString())
        isIpChanged=true;
    else
        isIpChanged=false;
    if(!CValidator::checkIp(newIp))
        FloatBox::Fail("IP地址不合法",this),ui->ipEdit->setStyleSheet(ui->ipEdit->styleSheet()+"color:red;");
    else
        ui->ipEdit->setStyleSheet(ui->ipEdit->styleSheet()+"color:black;");
}
void SettingDialog::onDirectoryEdited(const QString & newDirectory)
{
    if(newDirectory!=SocketConfig::getDirectory())
        isDirChanged=true;
    else
        isDirChanged=false;
    QString result=CValidator::getInfo(CValidator::checkDir(newDirectory));
    if(result!="")
        FloatBox::Fail(result,this),ui->directoryEdit->setStyleSheet(ui->directoryEdit->styleSheet()+"color:red;");
    else
        ui->directoryEdit->setStyleSheet(ui->directoryEdit->styleSheet()+"color:black;");
}
void SettingDialog::onOperationButtonsClicked()
{
    QToolButton* button=(QToolButton*)sender();
    if(button==ui->confirmButton){
        if(saveSettings())
            close();
    }else if(button==ui->cancelButton){
        close();
    }
}
void SettingDialog::onDirButtonClicked()
{
    QString dirPath = QFileDialog::getExistingDirectory(this,"选择主目录",SocketConfig::getDirectory(),QFileDialog::ShowDirsOnly|QFileDialog::DontResolveSymlinks);
    if(dirPath==nullptr||dirPath=="")
        return;
    QString result=CValidator::getInfo(CValidator::checkDir(dirPath));
    if(result!="")
        FloatBox::Fail(result,this);
    else
        ui->directoryEdit->setText(dirPath),onDirectoryEdited(dirPath);
}
bool SettingDialog::saveSettings()
{
    QString warningText="";
    bool flag=true;
    if(!CValidator::checkPort(ui->portEdit->text()))
        flag=false,warningText+="端口号应在1~65535内\n";
    if(CValidator::getInfo(CValidator::checkDir(ui->directoryEdit->text()))!="")
        flag=false,warningText+=CValidator::getInfo(CValidator::checkDir(ui->directoryEdit->text()));
    if(flag){
        if(!(!isPortChanged&&!isIpChanged&&!isDirChanged))
        {
            QLOG_INFO()<<qUtf8Printable(QString::asprintf("配置已修改"));
            SocketConfig::setDirectory(ui->directoryEdit->text());
            SocketConfig::setIpAddressString(ui->ipComboBox->currentText());
            SocketConfig::setPort(ui->portEdit->text().toInt());
            emit settingChanged();
            FloatBox::Success("应用配置成功",this);
        }
    }else
        CMessageBox::warning(this,"错误提示",warningText);
    return flag;
}
SettingDialog::~SettingDialog()
{
    delete ui;
}
void SettingDialog::onMinimizeClicked()
{
    this->showMinimized();
}
void SettingDialog::onCloseClicked()
{
    close();
}
void SettingDialog::mouseMoveEvent(QMouseEvent *e)
{
    if (mousePressed && (e->buttons())) {
        this->move(e->globalPos()-mousePoint);
        e->accept();
    }
}
void SettingDialog::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        mousePressed = true;
        mousePoint = e->globalPos()-this->pos();
        e->accept();
    }
}
void SettingDialog::mouseReleaseEvent(QMouseEvent*)
{
    mousePressed = false;
}
bool SettingDialog::nativeEvent(const QByteArray &, void *message, long *)
{
    MSG *msg = static_cast< MSG * >(message);
    if(msg->message == WM_NCACTIVATE)
    {
        bool active = (bool)(msg->wParam);
        emit ncActive(active);
    }
    return false;
}
void SettingDialog::onNcActived(bool active)
{
    if(active)
        ui->titleBarWidget->setStyleSheet("QWidget#titleBarWidget{background:white;}");
    else
        ui->titleBarWidget->setStyleSheet("QWidget#titleBarWidget{background:#f5f5f5;}");
}
void SettingDialog::setWindowCustomTitle(const QString& newWindowTitle)
{
    setWindowTitle(newWindowTitle);
    ui->programNameLabel->setText(newWindowTitle);
}
