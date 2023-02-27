#include "mypushbutton.h"
#include<QDebug>
#include<QPropertyAnimation>

//MyPushButton::MyPushButton(QWidget *parent) : QPushButton(parent)
//{

//}
MyPushButton::MyPushButton(QString normalImg,QString pressImg)
{
    this->normalImgPath=normalImg;
    this->pressImgPath=pressImg;

    QPixmap pix;
    bool ret = pix.load(normalImg);
    if(!ret){
        qDebug()<<"图片加载错误！";
        return ;
    }
    pix=pix.scaled(pix.width()*1.5,pix.height()*1.5);
    //设置按钮的固定大小 应该和图片保持一致
    this->setFixedSize(pix.width(),pix.height());
    //设置不规则图片的样式
    this->setStyleSheet("QPushButton{border:0px;}");
    //设置按钮图标  也就是把上面的pix弄进去
    this->setIcon(pix);
    //设置图标的大小
    this->setIconSize(QSize(pix.width(),pix.height()));


}

void MyPushButton::zoom1(){
    //创建一个动态对象
    QPropertyAnimation * animation = new QPropertyAnimation(this,"geometry");
    //设置动画时间间隔
    animation->setDuration(200);
    //起始位置
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //最终位置
    animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    //设置弹跳效果
    animation->setEasingCurve(QEasingCurve::OutCubic);
    //执行动画
    animation->start();
}
void MyPushButton::zoom2(){
    //创建一个动态对象
    QPropertyAnimation * animation = new QPropertyAnimation(this,"geometry");
    //设置动画时间间隔
    animation->setDuration(200);
    //起始位置
    animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    //最终位置
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //设置弹跳效果
    animation->setEasingCurve(QEasingCurve::OutCubic);
    //执行动画
    animation->start();
}
void MyPushButton::mousePressEvent(QMouseEvent *e){
    //如果传入的按下按钮图片路径  也就是第二参数不为空 就应该触发按下切换图片的功能
    if(this->pressImgPath != ""){
        QPixmap pix;
        bool ret = pix.load(this->pressImgPath);
        if(!ret){
            qDebug()<<"图片加载错误！";
            return ;
        }
        pix=pix.scaled(pix.width()*1.5,pix.height()*1.5);
        //设置按钮的固定大小 应该和图片保持一致
        this->setFixedSize(pix.width(),pix.height());
        //设置不规则图片的样式
        this->setStyleSheet("QPushButton{border:0px;}");
        //设置按钮图标  也就是把上面的pix弄进去
        this->setIcon(pix);
        //设置图标的大小
        this->setIconSize(QSize(pix.width(),pix.height()));
    }
    //剩下的问题抛给父类  让父类执行其他的内容
    return QPushButton::mousePressEvent(e);
}
void MyPushButton::mouseReleaseEvent(QMouseEvent *e){
    //如果传入的按下按钮图片路径  也就是第二参数不为空 就应该触发按下切换图片的功能
    if(this->pressImgPath != ""){
        QPixmap pix;
        bool ret = pix.load(this->normalImgPath);
        if(!ret){
            qDebug()<<"图片加载错误！";
            return ;
        }
        pix=pix.scaled(pix.width()*1.5,pix.height()*1.5);
        //设置按钮的固定大小 应该和图片保持一致
        this->setFixedSize(pix.width(),pix.height());
        //设置不规则图片的样式
        this->setStyleSheet("QPushButton{border:0px;}");
        //设置按钮图标  也就是把上面的pix弄进去
        this->setIcon(pix);
        //设置图标的大小
        this->setIconSize(QSize(pix.width(),pix.height()));
    }
    //剩下的问题抛给父类  让父类执行其他的内容
    return QPushButton::mouseReleaseEvent(e);
}
