#ifndef CLIENTWIDGET_H
#define CLIENTWIDGET_H

#include "socket/thread.h"
#include "widget/framelesswidget.h"
QT_BEGIN_NAMESPACE
namespace Ui { class ClientWidget; }
QT_END_NAMESPACE

class ClientWidget : public FramelessWidget
{
    Q_OBJECT

public:
    ClientWidget(QWidget *parent = nullptr);
    ~ClientWidget();
private:
    void initWidget();
    void initSlots();
    void initLogger();
    void loadQss(const QString &qssFilePath);
private:
    SocketThread * socketThread;
    QString styleSheet;
    Ui::ClientWidget *ui;
public slots:
    void writeLog(const QString &message, int level);
    void onConnButtonClicked();
    void onDisConnButtonClicked();
    void onClearLogButtonClicked();
    void onRequestButtonClicked();
    void onDirectoryButtonClicked();
    void onSendButtonClicked();
    void onLogButtonClicked();
    void onHelpButtonClicked();
    void onMinimizeClicked();
    void onMaximizeClicked();
    void onCloseClicked();
    void onStartFail();
    void onStartSuccess();
    void onFileChanged();
    void onSelectChanged();
    void onResponseTableWidget(int row,int column);
signals:
    void sendMessage(QString message);
    void sendFile(QString filepath);
};
#endif // CLIENTWIDGET_H
