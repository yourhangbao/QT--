#ifndef PLAYSENCE_H
#define PLAYSENCE_H

#include <QMainWindow>
#include"mycoin.h"

class PlaySence : public QMainWindow
{
    Q_OBJECT
public:
    //explicit PlaySence(QWidget *parent = nullptr);
    PlaySence(int levelNum);
    //画背景图
    void paintEvent(QPaintEvent * );

    int levelIndex;

    int gameArray[4][4];//二维数组 维护每个关卡的具体数据
    MyCoin* coinArray[4][4];//二位硬币数组  用于后期维护

    //判断胜利的标志
    bool isWin;

signals:
    //写一个自定义的信号，告诉选择场景 点击了返回
    void playSceneBack();
    //下一关信号
    void nextPlayScene();

};

#endif // PLAYSENCE_H
