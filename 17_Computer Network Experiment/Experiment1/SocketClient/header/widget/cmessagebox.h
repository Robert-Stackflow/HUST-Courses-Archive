#ifndef CMESSAGEBOX_H
#define CMESSAGEBOX_H

#include <QDialog>

namespace Ui {
class CMessageBox;
}

class CMessageBox : public QDialog
{
    Q_OBJECT
public:
    enum type{
        QUESTION,
        INFO,
        WARNING,
        CRITICAL,
        SEE,
        UNSEE
    };
    enum RETURNCODE{
        NONE,
        YES,
        NO
    };
    Q_ENUM(type)
    Q_ENUM(RETURNCODE)
private:
    RETURNCODE sResult=NONE;
    bool mousePressed;
    QPoint mousePoint;
    type messageBoxType;
    Ui::CMessageBox *ui;
public:
    explicit CMessageBox(CMessageBox::type messageBoxType, const QString &title, const QString &text,QWidget *parent = nullptr);
    ~CMessageBox();
    CMessageBox::RETURNCODE result();
    void setTitle(const QString &title);
    void setText(const QString &text);
    void setIcon(QIcon icon);
    void setType(type messageBoxType);
    QString toString();
public:
    static int information(QWidget *parent, const QString &title,const QString& text);
    static int question(QWidget *parent, const QString &title,const QString& text);
    static int warning(QWidget *parent, const QString &title,const QString& text);
    static int critical(QWidget *parent, const QString &title,const QString& text);
protected:
    void keyPressEvent( QKeyEvent* event);
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *);
    bool nativeEvent(const QByteArray &, void *message, long *);
private:
    void initWidget();
public slots:
    void onCopyClicked();
    void onCloseClicked();
    void onConfirmClicked();
    void onCancelClicked();
    void onMinimizeClicked();
    void onNcActived(bool active);
signals:
    void ncActive(bool);
};

#endif // CMESSAGEBOX_H
