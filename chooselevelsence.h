#ifndef CHOOSELEVELSENCE_H
#define CHOOSELEVELSENCE_H

#include <QMainWindow>
#include"playsence.h"

class ChooseLevelSence : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevelSence(QWidget *parent = nullptr);

    //画背景图
    void paintEvent(QPaintEvent * );

    //游戏场景对象指针
    PlaySence * playsence=NULL;
    //
    void nextplayscene();

signals:
    //写一个自定义的信号，告诉主场景 点击了返回
    void chooseSceneBack();

};

#endif // CHOOSELEVELSENCE_H
