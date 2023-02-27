#include "chooselevelsence.h"
#include<QPainter>
#include<QMenuBar>
#include<QDebug>
#include<QPropertyAnimation>
#include"mypushbutton.h"
#include<QLabel>
#include"playsence.h"
#include<QTimer>
#include<QSound>

//跳转至下一关的函数
void ChooseLevelSence::nextplayscene(){
    //监听下一关信号
    if(this->playsence->levelIndex==20){
        return ;
    }
    connect(playsence,&PlaySence::nextPlayScene,[=](){
        QTimer::singleShot(250,this,[=](){
            int temp=playsence->levelIndex+1;
            delete playsence;
            //进去游戏场景
            playsence=new PlaySence(temp);
            playsence->show();
            //监听返回信号
            connect(playsence,&PlaySence::playSceneBack,[=](){
                qDebug()<<"监听了返回信号";
                //回到上一级  隐藏游戏场景场景  回到选择场景
                QTimer::singleShot(250,this,[=](){
                    this->setGeometry(playsence->geometry());
                    delete playsence;
                    playsence=NULL;
                    this->show();
                });
            });
            nextplayscene();
        });
    });
}

ChooseLevelSence::ChooseLevelSence(QWidget *parent) : QMainWindow(parent)
{
    //配置选择关卡场景
    // 设置固定的大小
    setFixedSize(500,800);
    setWindowIcon(QIcon(":/res/Coin0001.png"));
    //设置标题
    setWindowTitle("选择关卡场景");
    //创建菜单栏
    QMenuBar * bar=new QMenuBar();
    setMenuBar(bar);
    //创建开始菜单
    QMenu * startMenu = bar->addMenu("开始");
    //菜单中创建退出选项
    QAction * exitAction = startMenu->addAction("退出");
    connect(exitAction,&QAction::triggered,[=](){
        this->close();
    });
    //返回按钮音效
    QSound *backsound=new QSound(":/res/TapButtonSound.wav",this);

    //返回按钮
    MyPushButton * backbtn=new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backbtn->setParent(this);
    backbtn->move(this->width()-backbtn->width(),this->height()-backbtn->height());

    connect(backbtn,&MyPushButton::clicked,[=](){
        backsound->play();
        emit this->chooseSceneBack();
    });

    //选择关卡音效
    QSound * choosesound=new QSound(":/res/TapButtonSound.wav",this);

    //创建选择按钮
    int tempx=50;
    int tempy=250;
    for(int i=1;i<=20;i++){
        MyPushButton *menubtn=new MyPushButton(":/res/LevelIcon.png");
        menubtn->setParent(this);
        menubtn->move(tempx,tempy);
        //监听每一个按钮他的信号
        connect(menubtn,&MyPushButton::clicked,[=](){
            //播放选择音效
            choosesound->play();
            QString str=QString("你选择的是第%1关").arg(i);
            qDebug()<< str;
            this->hide();
            //进去游戏场景
            playsence=new PlaySence(i);
            //监听返回信号
            connect(playsence,&PlaySence::playSceneBack,[=](){
                qDebug()<<"监听了返回信号";
                //回到上一级  隐藏游戏场景场景  回到选择场景
                QTimer::singleShot(250,this,[=](){
                    this->setGeometry(playsence->geometry());
                    delete playsence;
                    playsence=NULL;
                    this->show();
                });
            });

            //监听下一关信号
            this->nextplayscene();
//            connect(playsence,&PlaySence::nextPlayScene,[=](){
//                QTimer::singleShot(250,this,[=](){
//                    int temp=playsence->levelIndex+1;
//                    delete playsence;
//                    //进去游戏场景
//                    playsence=new PlaySence(temp);
//                    playsence->show();
//                    //监听返回信号
//                    connect(playsence,&PlaySence::playSceneBack,[=](){
//                        qDebug()<<"监听了返回信号";
//                        //回到上一级  隐藏游戏场景场景  回到选择场景
//                        QTimer::singleShot(250,this,[=](){
//                            this->setGeometry(playsence->geometry());
//                            delete playsence;
//                            playsence=NULL;
//                            this->show();
//                        });
//                    });
//                });
//            });
            playsence->setGeometry(this->geometry());
            playsence->show();
        });


        QLabel * menulabel=new QLabel(QString::number(i),this);
        menulabel->setFixedSize(menubtn->width(),menubtn->height());
        //直接设置水平居中
        menulabel->setAlignment(Qt::AlignVCenter|Qt::AlignHCenter);
        menulabel->move(tempx,tempy);
        //设置让鼠标进行穿透
        menulabel->setAttribute(Qt::WA_TransparentForMouseEvents);
//        if(i>=10){
//            menulabel->move(tempx+menubtn->width()*0.5-10,tempy+menubtn->height()*0.5-menulabel->height()*0.5);
//        }else{
//            menulabel->move(tempx+menubtn->width()*0.5-5,tempy+menubtn->height()*0.5-menulabel->height()*0.5);
//        }

        if(i%4!=0){
            tempx=tempx+menubtn->width()+10;

        }else{
            tempx=50;
            tempy=tempy+menubtn->height()+20;
        }
    }

}


void ChooseLevelSence::paintEvent(QPaintEvent * ){

    //新建一个画家
    QPainter painter(this);
    //创建一个Qpixmap对象
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");
    //设置了背景图
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    pix.load(":/res/Title.png");
    //缩放图片
    pix=pix.scaled(pix.width()*1.5,pix.height()*1.5);
    //绘制标题
    painter.drawPixmap((this->width()-pix.width())*0.5,50,pix.width(),pix.height(),pix);


}
