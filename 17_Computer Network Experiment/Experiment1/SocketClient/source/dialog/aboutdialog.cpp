#include "dialog/aboutdialog.h"
#include "qevent.h"
#include "qgraphicseffect.h"
#include "ui_aboutdialog.h"
#include <Windows.h>
#include <WinUser.h>
#include <QDesktopServices>
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
AboutDialog::AboutDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
    initWidget();
    if(parent!=nullptr){
        QPoint globalPos = parent->mapToGlobal(QPoint(0,0));
        int x = globalPos.x() + (parent->width() - this->width())/2;
        int y = globalPos.y() + (parent->height() - this->height())/2;
        this->move(x,y);
    }
}
void AboutDialog::initWidget()
{
    setWindowCustomTitle("关于 - Socket Client");
    ui->programName->setText("Socket Client");
    setFocusPolicy(Qt::StrongFocus);
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::FramelessWindowHint|Qt::Dialog);
    setWindowModality(Qt::WindowModal);
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(0,0);
    shadow->setBlurRadius(20);
    shadow->setColor(QColor(167,166,170));
    setGraphicsEffect(shadow);
    ui->dialogGridLayout->setMargin(20);
    connect(this,SIGNAL(ncActive(bool)),this,SLOT(onNcActived(bool)));
    connect(ui->closeButton,SIGNAL(clicked()),this,SLOT(onCloseClicked()));
    connect(ui->minimizeButton,SIGNAL(clicked()),this,SLOT(onMinimizeClicked()));
}
AboutDialog::~AboutDialog()
{
    delete ui;
}
void AboutDialog::onMinimizeClicked()
{
    this->showMinimized();
}
void AboutDialog::onCloseClicked()
{
    close();
}
void AboutDialog::mouseMoveEvent(QMouseEvent *e)
{
    if (mousePressed && (e->buttons())) {
        this->move(e->globalPos()-mousePoint);
        e->accept();
    }
}
void AboutDialog::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        mousePressed = true;
        mousePoint = e->globalPos()-this->pos();
        e->accept();
    }
}
void AboutDialog::mouseReleaseEvent(QMouseEvent*)
{
    mousePressed = false;
}
bool AboutDialog::nativeEvent(const QByteArray &, void *message, long *)
{
    MSG *msg = static_cast< MSG * >(message);
    if(msg->message == WM_NCACTIVATE)
    {
        bool active = (bool)(msg->wParam);
        emit ncActive(active);
    }
    return false;
}
void AboutDialog::onNcActived(bool active)
{
    if(active)
        ui->titleBarWidget->setStyleSheet("QWidget#titleBarWidget{background:white;}");
    else
        ui->titleBarWidget->setStyleSheet("QWidget#titleBarWidget{background:#f5f5f5;}");
}
void AboutDialog::setWindowCustomTitle(const QString& newWindowTitle)
{
    setWindowTitle(newWindowTitle);
    ui->programNameLabel->setText(newWindowTitle);
}
