#ifndef SERVERWIDGET_H
#define SERVERWIDGET_H

#include "dialog/aboutdialog.h"
#include "dialog/settingdialog.h"
#include "socket/thread.h"
#include "widget/framelesswidget.h"
QT_BEGIN_NAMESPACE
namespace Ui { class ServerWidget; }
QT_END_NAMESPACE

class ServerWidget : public FramelessWidget
{
    Q_OBJECT
protected:
    virtual bool eventFilter(QObject *obj, QEvent *event)Q_DECL_OVERRIDE;
public:
    ServerWidget(QWidget *parent = nullptr);
    ~ServerWidget();
private:
    void initWidget();
    void initSlots();
    void initLogger();
    void initTableWidget();
    void loadQss(const QString &qssFilePath);
private:
    QString styleSheet;
    Ui::ServerWidget *ui;
    SocketThread* socketThread;
    SettingDialog * settingDialog=nullptr;
    AboutDialog * aboutDialog=nullptr;
public slots:
    void refreshSetting();
    void writeLog(const QString &message, int level);
    void onDirectoryButtonClicked();
    void onStartButtonClicked();
    void onEndButtonClicked();
    void onLogButtonClicked();
    void onClearLogButtonClicked();
    void onHelpButtonClicked();
    void onSettingButtonClicked();
    void onMinimizeClicked();
    void onMaximizeClicked();
    void onCloseClicked();
    void onStartFail();
    void onIndexButtonClicked();
    void onStartSuccess();
    void onRequestUpdated();
};
#endif // SERVERWIDGET_H
