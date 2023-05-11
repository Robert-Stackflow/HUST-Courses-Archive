#include "widget/floatbox.h"
#include "qdebug.h"
#include "qpropertyanimation.h"
#include "qtimer.h"
#include "ui_floatbox.h"
#include <QGraphicsDropShadowEffect>
FloatBox::FloatBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FloatBox)
{
    ui->setupUi(this);
    initWidget();
    if(parent!=nullptr){
        QPoint globalPos = parent->mapToGlobal(QPoint(0,0));
        int x = globalPos.x() + (parent->width() - this->width())/2;
        int y = globalPos.y() + (parent->height() - this->height())/2;
        this->move(mapFromGlobal(QPoint(x,y)));
    }
}
FloatBox::FloatBox(const QString& text,QImage& image,QWidget *parent):
    QWidget(parent),
    ui(new Ui::FloatBox)
{
    ui->setupUi(this);
    initWidget();
    setImage(image);
    setText(text);
    if(parent!=nullptr){
        QPoint globalPos = parent->mapToGlobal(QPoint(0,0));
        int x = globalPos.x() + (parent->width() - this->width())/2;
        int y = globalPos.y() + (parent->height() - this->height())/2;
        this->move(mapFromGlobal(QPoint(x,y)));
    }
}
FloatBox::FloatBox(const QString& text,const QString& imagePath,QWidget *parent):
    QWidget(parent),
    ui(new Ui::FloatBox)
{
    ui->setupUi(this);
    initWidget();
    setImage(imagePath);
    setText(text);
    if(parent!=nullptr){
        QPoint globalPos = parent->mapToGlobal(QPoint(0,0));
        int x = globalPos.x() + (parent->width() - this->width())/2;
        int y = globalPos.y() + (parent->height() - this->height())/2;
        this->move(mapFromGlobal(QPoint(x,y)));
    }
}
void FloatBox::initWidget()
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setWindowOpacity(0.5);
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(0,0);
    shadow->setBlurRadius(10);
    shadow->setColor(QColor(167,166,170));
    setGraphicsEffect(shadow);
    ui->widgetGridLayout->setMargin(5);
    ui->widget->setStyleSheet("QWidget{border-radius:5px;border:1px solid white;}");
    QTimer* timer = new QTimer(this);
    timer->start(1500);
    timer->setSingleShot(true);
    connect(timer, &QTimer::timeout, [=]{
        emit timeout();
        delete this;
    });
}
void FloatBox::Fail(const QString& text,QWidget *parent)
{
    FloatBox* box=new FloatBox(parent);
    box->setText(text);
    box->setImage(":custom/icons/fail.png");
    box->show();
}
void FloatBox::See(const QString& text,QWidget *parent)
{
    FloatBox* box=new FloatBox(parent);
    box->setText(text);
    box->setImage(":custom/icons/see.png");
    box->show();
}
void FloatBox::Help(const QString& text,QWidget *parent)
{
    FloatBox* box=new FloatBox(parent);
    box->setText(text);
    box->setImage(":custom/icons/help_white.png");
    box->show();
}
void FloatBox::Unsee(const QString& text,QWidget *parent)
{
    FloatBox* box=new FloatBox(parent);
    box->setText(text);
    box->setImage(":custom/icons/unsee.png");
    box->show();
}
void FloatBox::Success(const QString& text,QWidget *parent)
{
    FloatBox* box=new FloatBox(parent);
    box->setText(text);
    box->setImage(":custom/icons/success.png");
    box->show();
}
void FloatBox::TextOnly(const QString& text,QWidget *parent)
{
    FloatBox* box=new FloatBox(parent);
    box->setText(text);
    box->setImageLabelEnabled(false);
    box->show();
}
void FloatBox::TextImage(const QString& text,QImage& image,QWidget *parent)
{
    FloatBox* box=new FloatBox(text,image,parent);
    box->show();
}
void FloatBox::TextImage(const QString& text,const QString& imagePath,QWidget *parent)
{
    FloatBox* box=new FloatBox(text,imagePath,parent);
    box->show();
}
FloatBox::~FloatBox()
{
    delete ui;
}
void FloatBox::setImage(QImage& image)
{
    ui->imageLabel->setPixmap(QPixmap::fromImage(image));
}
void FloatBox::setImage(const QString& imagePath)
{
    ui->imageLabel->setPixmap(imagePath);
}
void FloatBox::setText(const QString& text)
{
    ui->textLabel->setText(text);
}
void FloatBox::setImageLabelEnabled(bool enabled)
{
    ui->imageLabel->setVisible(enabled);
}
