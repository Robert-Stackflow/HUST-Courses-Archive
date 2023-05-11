#include "qdesktopwidget.h"
#include "serverwidget.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ServerWidget serverWidget;
    serverWidget.show();
    return a.exec();
}
