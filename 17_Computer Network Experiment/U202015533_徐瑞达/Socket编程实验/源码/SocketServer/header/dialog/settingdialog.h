#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H
#include <QMap>
#include "qtoolbutton.h"
#include <QWidget>
namespace Ui {
class SettingDialog;
}

class SettingDialog : public QWidget
{
    Q_OBJECT

public:
    explicit SettingDialog(QWidget *parent = nullptr);
    ~SettingDialog();
    void setWindowCustomTitle(const QString& newWindowTitle);
protected:
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *);
    bool nativeEvent(const QByteArray &, void *message, long *);
private:
    void initWidget();
    bool isPortChanged=false;
    bool isIpChanged=false;
    bool isDirChanged=false;
    Ui::SettingDialog *ui;
    bool mousePressed;
    QPoint mousePoint;
    QString styleSheet;
    QMap<QToolButton*,int> buttonToIconMap;
    QList<QToolButton*> buttons;
public slots:
    bool saveSettings();
    void onCloseClicked();
    void onMinimizeClicked();
    void onOperationButtonsClicked();
    void onDirButtonClicked();
    void onNcActived(bool active);
    void onPortEdited(const QString & newPort);
    void onIpEdited(const QString & newIp);
    void onIpComboBoxChanged(int);
    void onDirectoryEdited(const QString & newDirectory);
signals:
    void ncActive(bool);
    void settingChanged();
};

#endif // SETTINGDIALOG_H
