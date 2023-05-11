#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QWidget>

namespace Ui {
class AboutDialog;
}

class AboutDialog : public QWidget
{
    Q_OBJECT

public:
    explicit AboutDialog(QWidget *parent = nullptr);
    void setWindowCustomTitle(const QString& newWindowTitle);
    ~AboutDialog();
protected:
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *);
    bool nativeEvent(const QByteArray &, void *message, long *);
private:
    void initWidget();
    Ui::AboutDialog *ui;
    bool mousePressed;
    QPoint mousePoint;
    QString styleSheet;
private slots:
    void onCloseClicked();
    void onMinimizeClicked();
    void onNcActived(bool active);
signals:
    void ncActive(bool);
    void settingsChanged();
};

#endif // ABOUTDIALOG_H
