#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "searchdialog.h"
#include<QComboBox>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void combobox(QComboBox* box);
    void paintEvent(QPaintEvent *);
private slots:

    void on_action_2_triggered();

    void on_action_1_triggered();

    void on_action_3_triggered();

    void on_action_4_triggered();

    void on_action_6_triggered();

    void on_action_7_triggered();

    void on_action_HUSTMAP_triggered();

    void on_action_5_triggered();

    void mousePressEvent(QMouseEvent *event);

    void choosebegin(int index);

    void choosefinish(int index);

    void focusorg(int index);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    SearchDialog* searchdialog;
};
#endif // MAINWINDOW_H
