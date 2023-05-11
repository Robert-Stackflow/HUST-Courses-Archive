#include "widget/cmessagebox.h"
#include <QMouseEvent>
#include <Windows.h>
#include <WinUser.h>
#include <QClipboard>
#include <QMetaEnum>
#include "qdebug.h"
#include "ui_cmessagebox.h"
#include <QGraphicsDropShadowEffect>
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
CMessageBox::CMessageBox(CMessageBox::type messageBoxType,const QString &title, const QString &text,QWidget *parent):
    QDialog(parent),
    sResult(NONE),
    ui(new Ui::CMessageBox)
{
    ui->setupUi(this);
    initWidget();
    setTitle(title);
    setText(text);
    setType(messageBoxType);
    if(messageBoxType==INFO){
        ui->cancelButton->hide();
        setIcon(QIcon(":custom/icons/info.png"));
    }else if(messageBoxType==QUESTION){
        setIcon(QIcon(":custom/icons/question.png"));
    }else if(messageBoxType==WARNING){
        ui->cancelButton->hide();
        setIcon(QIcon(":custom/icons/warning.png"));
    }else if(messageBoxType==CRITICAL){
        ui->cancelButton->hide();
        ui->confirmButton->setText("退出");
        setIcon(QIcon(":custom/icons/critical.png"));
    }
    if(parent!=nullptr){
        QPoint globalPos = parent->mapToGlobal(QPoint(0,0));
        int x = globalPos.x() + (parent->width() - this->width())/2;
        int y = globalPos.y() + (parent->height() - this->height())/2;
        this->move(mapFromGlobal(QPoint(x,y)));
    }
    QApplication::beep();
}
void CMessageBox::initWidget()
{
    setFocusPolicy(Qt::StrongFocus);
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::FramelessWindowHint|Qt::Dialog);
    setWindowModality(Qt::WindowModal);
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(0,0);
    shadow->setBlurRadius(10);
    shadow->setColor(QColor(167,166,170));
    setGraphicsEffect(shadow);
    ui->widgetGridLayout->setMargin(20);
    ui->copyButton->setVisible(false);
    connect(this,SIGNAL(ncActive(bool)),this,SLOT(onNcActived(bool)));
    connect(ui->copyButton,SIGNAL(clicked()),this,SLOT(onCopyClicked()));
    connect(ui->closeButton,SIGNAL(clicked()),this,SLOT(onCloseClicked()));
    connect(ui->confirmButton,SIGNAL(clicked()),this,SLOT(onConfirmClicked()));
    connect(ui->cancelButton,SIGNAL(clicked()),this,SLOT(onCancelClicked()));
    connect(ui->minimizeButton,SIGNAL(clicked()),this,SLOT(onMinimizeClicked()));
}

void CMessageBox::keyPressEvent( QKeyEvent* event)
{
    if(event->matches(QKeySequence::Copy))
        onCopyClicked();
}
void CMessageBox::mouseMoveEvent(QMouseEvent *e)
{
    if (mousePressed && (e->buttons())) {
        this->move(e->globalPos()-mousePoint);
        e->accept();
    }
}
void CMessageBox::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        mousePressed = true;
        mousePoint = e->globalPos()-this->pos();
        e->accept();
    }
}
void CMessageBox::mouseReleaseEvent(QMouseEvent*)
{
    mousePressed = false;
}
CMessageBox::RETURNCODE CMessageBox::result()
{
    return sResult;
}
void CMessageBox::onMinimizeClicked()
{
    this->showMinimized();
}
void CMessageBox::onConfirmClicked()
{
    sResult=YES;
    this->close();
}
void CMessageBox::onCancelClicked()
{
    sResult=NO;
    this->close();
}
void CMessageBox::onCopyClicked()
{
    QClipboard* clip=QApplication::clipboard();
    clip->setText(toString());
}
QString CMessageBox::toString()
{
    QString str;
    QMetaEnum typeMeta = QMetaEnum::fromType<CMessageBox::type>();
    str.append("type:").append(typeMeta.valueToKey(messageBoxType)).append("\n");
    str.append("title:").append(ui->titleLabel->text()).append("\n");
    str.append("message:").append(ui->infoLabel->text());
    return str;
}
void CMessageBox::onCloseClicked()
{
    sResult=NONE;
    this->close();
}
void CMessageBox::setTitle(const QString &title)
{
    setWindowTitle(title);
    ui->titleLabel->setText(title);
}
void CMessageBox::setText(const QString &text)
{
    ui->infoLabel->setText(text);
}
void CMessageBox::setIcon(QIcon icon)
{
    ui->iconLabel->setPixmap(icon.pixmap(20,20));
}
void CMessageBox::setType(type messageBoxType)
{
    this->messageBoxType=messageBoxType;
}
CMessageBox::~CMessageBox()
{
    delete ui;
}
bool CMessageBox::nativeEvent(const QByteArray &, void *message, long *)
{
    MSG *msg = static_cast< MSG * >(message);
    if(msg->message == WM_NCACTIVATE)
    {
        bool active = (bool)(msg->wParam);
        emit ncActive(active);
    }
    return false;
}
void CMessageBox::onNcActived(bool active)
{
    if(active)
        ui->titleBarWidget->setStyleSheet("QWidget#titleBarWidget{background:white;}");
    else
        ui->titleBarWidget->setStyleSheet("QWidget#titleBarWidget{background:#f5f5f5;}");
}
int CMessageBox::information(QWidget *parent, const QString &title,const QString& text)
{
    CMessageBox* msgBox=new CMessageBox(CMessageBox::INFO,title,text,parent);
    msgBox->exec();
    return msgBox->result();
}
int CMessageBox::question(QWidget *parent, const QString &title,const QString& text)
{
    CMessageBox* msgBox=new CMessageBox(CMessageBox::QUESTION,title,text,parent);
    msgBox->exec();
    return msgBox->result();
}
int CMessageBox::warning(QWidget *parent, const QString &title,const QString& text)
{
    CMessageBox* msgBox=new CMessageBox(CMessageBox::WARNING,title,text,parent);
    msgBox->exec();
    return msgBox->result();
}
int CMessageBox::critical(QWidget *parent, const QString &title,const QString& text)
{
    CMessageBox* msgBox=new CMessageBox(CMessageBox::CRITICAL,title,text,parent);
    msgBox->exec();
    return msgBox->result();
}
