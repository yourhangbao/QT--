#include "mycoin.h"
#include<QDebug>
#include<QSound>

//MyCoin::MyCoin(QWidget *parent) : QPushButton(parent)
//{

//}
MyCoin::MyCoin(QString btnImg){
    QPixmap pix;
    bool ret = pix.load(btnImg);
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

    //初始化定时器对象
    time1 = new QTimer(this);
    time2 = new QTimer(this);


    //监听信号并且  正面翻反面 反转金币
    connect(time1,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str=QString(":/res/Coin000%1.png").arg(this->min++);
        pix.load(str);
        pix=pix.scaled(pix.width()*1.5,pix.height()*1.5);
        //设置按钮的固定大小 应该和图片保持一致
        this->setFixedSize(pix.width(),pix.height());
        //设置不规则图片的样式
        this->setStyleSheet("QPushButton{border:0px;}");
        //设置按钮图标  也就是把上面的pix弄进去
        this->setIcon(pix);
        //设置图标的大小
        this->setIconSize(QSize(pix.width(),pix.height()));
        //反转完成  恢复数据
        if(this->min>this->max){
            this->min=1;
            isAnimation=false;
            time1->stop();
        }
    });

    //监听信号并且  反面翻正面 反转金币
    connect(time2,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str=QString(":/res/Coin000%1.png").arg(this->max--);
        pix.load(str);
        pix=pix.scaled(pix.width()*1.5,pix.height()*1.5);
        //设置按钮的固定大小 应该和图片保持一致
        this->setFixedSize(pix.width(),pix.height());
        //设置不规则图片的样式
        this->setStyleSheet("QPushButton{border:0px;}");
        //设置按钮图标  也就是把上面的pix弄进去
        this->setIcon(pix);
        //设置图标的大小
        this->setIconSize(QSize(pix.width(),pix.height()));
        //反转完成  恢复数据
        if(this->max<this->min){
            this->max=8;
            isAnimation=false;
            time2->stop();
        }
    });
}

void MyCoin::changeFlag(){
    //如果是正面

    if(this->flag){
        time1->start(30);
        isAnimation=true;
        this->flag=false;
    }
    else{
        time2->start(30);
        isAnimation=true;
        this->flag=true;
    }
}
void MyCoin::mousePressEvent(QMouseEvent *e){
    if(this->isAnimation||this->isWin){
        return;
    }
    QPushButton::mousePressEvent(e);
}
