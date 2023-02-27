#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyPushButton(QWidget *parent = nullptr);
    //构造函数  参数一  正常显示的图片文件路径  参数2  按下后的显示图片路径
    MyPushButton(QString normalImg,QString pressImg ="");
    //弹跳特效
    void zoom1();//向下跳
    void zoom2();//向上跳

    //重写按钮按下和释放事件
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

    QString normalImgPath;
    QString pressImgPath;
signals:

};

#endif // MYPUSHBUTTON_H
