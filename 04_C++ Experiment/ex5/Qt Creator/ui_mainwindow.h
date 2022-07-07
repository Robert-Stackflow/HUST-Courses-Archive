/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_2;
    QAction *action_3;
    QAction *action_4;
    QAction *action_1;
    QAction *action_5;
    QAction *action_6;
    QAction *action_7;
    QAction *action_HUSTMAP;
    QWidget *centralwidget;
    QLabel *label_3;
    QComboBox *begin;
    QLabel *label_4;
    QComboBox *finish;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_4;
    QHBoxLayout *horizontalLayout_5;
    QLabel *info_tx;
    QLabel *tx;
    QHBoxLayout *horizontalLayout_6;
    QLabel *info_ty;
    QLabel *ty;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_3;
    QHBoxLayout *horizontalLayout;
    QLabel *info_fx;
    QLabel *fx;
    QHBoxLayout *horizontalLayout_2;
    QLabel *info_fy;
    QLabel *fy;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QMenuBar *menubar;
    QMenu *menu;
    QMenu *menu_2;
    QMenu *menu_3;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1546, 847);
        action_2 = new QAction(MainWindow);
        action_2->setObjectName(QString::fromUtf8("action_2"));
        action_2->setCheckable(false);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/images/open.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_2->setIcon(icon);
        action_3 = new QAction(MainWindow);
        action_3->setObjectName(QString::fromUtf8("action_3"));
        action_3->setIcon(icon);
        action_4 = new QAction(MainWindow);
        action_4->setObjectName(QString::fromUtf8("action_4"));
        action_4->setIcon(icon);
        action_1 = new QAction(MainWindow);
        action_1->setObjectName(QString::fromUtf8("action_1"));
        action_1->setIcon(icon);
        action_5 = new QAction(MainWindow);
        action_5->setObjectName(QString::fromUtf8("action_5"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/images/search.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_5->setIcon(icon1);
        action_6 = new QAction(MainWindow);
        action_6->setObjectName(QString::fromUtf8("action_6"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/images/images/help.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_6->setIcon(icon2);
        action_7 = new QAction(MainWindow);
        action_7->setObjectName(QString::fromUtf8("action_7"));
        action_7->setIcon(icon2);
        action_HUSTMAP = new QAction(MainWindow);
        action_HUSTMAP->setObjectName(QString::fromUtf8("action_HUSTMAP"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/images/images/copyright.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_HUSTMAP->setIcon(icon3);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 10, 30, 16));
        begin = new QComboBox(centralwidget);
        begin->setObjectName(QString::fromUtf8("begin"));
        begin->setGeometry(QRect(60, 10, 201, 21));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(310, 10, 30, 16));
        finish = new QComboBox(centralwidget);
        finish->setObjectName(QString::fromUtf8("finish"));
        finish->setGeometry(QRect(350, 10, 201, 21));
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(930, 10, 271, 24));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        info_tx = new QLabel(layoutWidget);
        info_tx->setObjectName(QString::fromUtf8("info_tx"));

        horizontalLayout_5->addWidget(info_tx);

        tx = new QLabel(layoutWidget);
        tx->setObjectName(QString::fromUtf8("tx"));
        tx->setAlignment(Qt::AlignCenter);

        horizontalLayout_5->addWidget(tx);


        horizontalLayout_4->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        info_ty = new QLabel(layoutWidget);
        info_ty->setObjectName(QString::fromUtf8("info_ty"));

        horizontalLayout_6->addWidget(info_ty);

        ty = new QLabel(layoutWidget);
        ty->setObjectName(QString::fromUtf8("ty"));
        ty->setAlignment(Qt::AlignCenter);

        horizontalLayout_6->addWidget(ty);


        horizontalLayout_4->addLayout(horizontalLayout_6);

        layoutWidget1 = new QWidget(centralwidget);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(620, 10, 271, 24));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        info_fx = new QLabel(layoutWidget1);
        info_fx->setObjectName(QString::fromUtf8("info_fx"));

        horizontalLayout->addWidget(info_fx);

        fx = new QLabel(layoutWidget1);
        fx->setObjectName(QString::fromUtf8("fx"));
        fx->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(fx);


        horizontalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        info_fy = new QLabel(layoutWidget1);
        info_fy->setObjectName(QString::fromUtf8("info_fy"));

        horizontalLayout_2->addWidget(info_fy);

        fy = new QLabel(layoutWidget1);
        fy->setObjectName(QString::fromUtf8("fy"));
        fy->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(fy);


        horizontalLayout_3->addLayout(horizontalLayout_2);

        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(1220, 10, 81, 21));
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(1320, 10, 81, 21));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1546, 26));
        menu = new QMenu(menubar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menu_2 = new QMenu(menubar);
        menu_2->setObjectName(QString::fromUtf8("menu_2"));
        menu_3 = new QMenu(menubar);
        menu_3->setObjectName(QString::fromUtf8("menu_3"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        statusbar->setSizeGripEnabled(true);
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menu->menuAction());
        menubar->addAction(menu_2->menuAction());
        menubar->addAction(menu_3->menuAction());
        menu->addAction(action_1);
        menu->addAction(action_2);
        menu->addAction(action_3);
        menu->addAction(action_4);
        menu_2->addAction(action_5);
        menu_3->addAction(action_6);
        menu_3->addAction(action_7);
        menu_3->addAction(action_HUSTMAP);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        action_2->setText(QCoreApplication::translate("MainWindow", "\345\212\240\350\275\275\347\253\231\347\202\271\346\226\207\344\273\266", nullptr));
#if QT_CONFIG(shortcut)
        action_2->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+S", nullptr));
#endif // QT_CONFIG(shortcut)
        action_3->setText(QCoreApplication::translate("MainWindow", "\345\212\240\350\275\275\350\267\257\347\272\277\346\226\207\344\273\266", nullptr));
#if QT_CONFIG(shortcut)
        action_3->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+L", nullptr));
#endif // QT_CONFIG(shortcut)
        action_4->setText(QCoreApplication::translate("MainWindow", "\345\212\240\350\275\275\346\234\272\346\236\204\346\226\207\344\273\266", nullptr));
#if QT_CONFIG(shortcut)
        action_4->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+O", nullptr));
#endif // QT_CONFIG(shortcut)
        action_1->setText(QCoreApplication::translate("MainWindow", "\345\212\240\350\275\275\345\234\260\345\233\276\346\226\207\344\273\266", nullptr));
#if QT_CONFIG(shortcut)
        action_1->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+M", nullptr));
#endif // QT_CONFIG(shortcut)
        action_5->setText(QCoreApplication::translate("MainWindow", "\346\237\245\350\257\242\345\234\260\347\202\271", nullptr));
#if QT_CONFIG(shortcut)
        action_5->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+F", nullptr));
#endif // QT_CONFIG(shortcut)
        action_6->setText(QCoreApplication::translate("MainWindow", "\344\275\277\347\224\250\346\214\207\345\215\227", nullptr));
#if QT_CONFIG(shortcut)
        action_6->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+H", nullptr));
#endif // QT_CONFIG(shortcut)
        action_7->setText(QCoreApplication::translate("MainWindow", "\345\277\253\346\215\267\351\224\256\346\214\207\345\215\227", nullptr));
#if QT_CONFIG(shortcut)
        action_7->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Q", nullptr));
#endif // QT_CONFIG(shortcut)
        action_HUSTMAP->setText(QCoreApplication::translate("MainWindow", "\345\205\263\344\272\216HUSTMAP", nullptr));
#if QT_CONFIG(shortcut)
        action_HUSTMAP->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+N", nullptr));
#endif // QT_CONFIG(shortcut)
        label_3->setText(QCoreApplication::translate("MainWindow", "\350\265\267\347\202\271", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\347\273\210\347\202\271", nullptr));
        info_tx->setText(QCoreApplication::translate("MainWindow", "\347\273\210\347\202\271x\345\235\220\346\240\207", nullptr));
        tx->setText(QString());
        info_ty->setText(QCoreApplication::translate("MainWindow", "\347\273\210\347\202\271y\345\235\220\346\240\207", nullptr));
        ty->setText(QString());
        info_fx->setText(QCoreApplication::translate("MainWindow", "\350\265\267\347\202\271x\345\235\220\346\240\207", nullptr));
        fx->setText(QString());
        info_fy->setText(QCoreApplication::translate("MainWindow", "\347\273\210\347\202\271y\345\235\220\346\240\207", nullptr));
        fy->setText(QString());
        pushButton->setText(QCoreApplication::translate("MainWindow", "\346\270\205\351\231\244\351\200\211\346\213\251", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "\345\205\254\344\272\244\347\272\277\350\267\257", nullptr));
        menu->setTitle(QCoreApplication::translate("MainWindow", "\346\226\207\344\273\266", nullptr));
        menu_2->setTitle(QCoreApplication::translate("MainWindow", "\346\237\245\350\257\242", nullptr));
        menu_3->setTitle(QCoreApplication::translate("MainWindow", "\345\270\256\345\212\251", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
