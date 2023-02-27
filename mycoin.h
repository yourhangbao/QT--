#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>
#include<QTimer>

class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyCoin(QWidget *parent = nullptr);


    MyCoin(QString btnImg);

    //添加x，y，以及正反属性
    int posX;
    int posY;
    bool flag;

    //改变标志的方法
    void changeFlag();
    QTimer* time1;
    QTimer* time2;
    int max=8;
    int min=1;

    //执行动画的标志
    bool isAnimation = false;

    //重写按下事件
    void mousePressEvent(QMouseEvent *e);

    //游戏胜利的标志
    bool isWin;

signals:

};

#endif // MYCOIN_H
