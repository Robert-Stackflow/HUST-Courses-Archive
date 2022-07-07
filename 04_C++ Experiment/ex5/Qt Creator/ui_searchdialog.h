/********************************************************************************
** Form generated from reading UI file 'searchdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEARCHDIALOG_H
#define UI_SEARCHDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SearchDialog
{
public:
    QPushButton *pushButton;
    QLabel *label;
    QComboBox *comboBox;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;

    void setupUi(QDialog *SearchDialog)
    {
        if (SearchDialog->objectName().isEmpty())
            SearchDialog->setObjectName(QString::fromUtf8("SearchDialog"));
        SearchDialog->resize(391, 250);
        pushButton = new QPushButton(SearchDialog);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(280, 200, 93, 28));
        label = new QLabel(SearchDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(110, 10, 171, 31));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setCursor(QCursor(Qt::ArrowCursor));
        label->setAlignment(Qt::AlignCenter);
        comboBox = new QComboBox(SearchDialog);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(60, 40, 271, 31));
        widget = new QWidget(SearchDialog);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(60, 90, 291, 71));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout->addWidget(label_2);

        label_3 = new QLabel(widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout->addWidget(label_3);

        label_4 = new QLabel(widget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        verticalLayout->addWidget(label_4);


        retranslateUi(SearchDialog);
        QObject::connect(pushButton, &QPushButton::clicked, SearchDialog, qOverload<>(&QDialog::close));

        QMetaObject::connectSlotsByName(SearchDialog);
    } // setupUi

    void retranslateUi(QDialog *SearchDialog)
    {
        SearchDialog->setWindowTitle(QCoreApplication::translate("SearchDialog", "Dialog", nullptr));
        pushButton->setText(QCoreApplication::translate("SearchDialog", "\347\241\256\345\256\232", nullptr));
        label->setText(QCoreApplication::translate("SearchDialog", "\346\237\245\350\257\242\346\234\272\346\236\204", nullptr));
        label_2->setText(QCoreApplication::translate("SearchDialog", "\346\237\245\350\257\242\346\214\207\345\215\227", nullptr));
        label_3->setText(QCoreApplication::translate("SearchDialog", "1.\345\217\257\351\200\232\350\277\207\350\276\223\345\205\245\346\234\272\346\236\204\345\220\215\347\247\260\346\250\241\347\263\212\346\237\245\350\257\242\346\234\272\346\236\204\345\220\215\347\247\260", nullptr));
        label_4->setText(QCoreApplication::translate("SearchDialog", "2.\345\217\257\351\200\232\350\277\207\344\270\213\346\213\211\350\217\234\345\215\225\351\200\211\346\213\251\346\234\272\346\236\204\344\273\245\346\237\245\350\257\242\346\234\272\346\236\204\344\275\215\347\275\256", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SearchDialog: public Ui_SearchDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEARCHDIALOG_H
