#ifndef FLOATBOX_H
#define FLOATBOX_H

#include <QWidget>

namespace Ui {
class FloatBox;
}

class FloatBox : public QWidget
{
    Q_OBJECT

public:
    explicit FloatBox(QWidget *parent = nullptr);
    explicit FloatBox(const QString& text,QImage& image,QWidget *parent = nullptr);
    explicit FloatBox(const QString& text,const QString& imagePath,QWidget *parent = nullptr);
    ~FloatBox();
    void setImage(QImage& image);
    void setImage(const QString& imagePath);
    void setText(const QString& text);
    void setImageLabelEnabled(bool enabled);
    static void Fail(const QString& text,QWidget *parent = nullptr);
    static void Success(const QString& text,QWidget *parent = nullptr);
    static void Help(const QString& text,QWidget *parent = nullptr);
    static void See(const QString& text,QWidget *parent = nullptr);
    static void Unsee(const QString& text,QWidget *parent = nullptr);
    static void TextOnly(const QString& text,QWidget *parent = nullptr);
    static void TextImage(const QString& text,QImage& image,QWidget *parent = nullptr);
    static void TextImage(const QString& text,const QString& imagePath,QWidget *parent = nullptr);
private:
    Ui::FloatBox *ui;
    void initWidget();
signals:
    void timeout();
};

#endif // FLOATBOX_H
