#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<QPaintEvent>
#include<QPainter>
#include <QMainWindow>
#include<QWidget>
#include<QPixmap>
#include"chooselevelsence.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    //画背景图
    void paintEvent(QPaintEvent * );

    ChooseLevelSence * chooseSence=NULL;

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
