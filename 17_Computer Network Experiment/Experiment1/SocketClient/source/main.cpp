#include "qdesktopwidget.h"
#include "clientwidget.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ClientWidget clientWidget;
    clientWidget.show();
    return a.exec();
}
