#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"mypushbutton.h"
#include<QDebug>
#include<QTimer>
#include<QSound>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // 设置固定的大小
    setFixedSize(500,800);
    setWindowIcon(QIcon(":/res/Coin0001.png"));
    connect(ui->actionexit,&QAction::triggered,[=](){
        this->close();
    });

    QSound * startsound=new QSound(":/res/TapButtonSound.wav",this);

    //放入一个开始按钮
    MyPushButton * startbtn=new MyPushButton(":/res/MenuSceneStartButton.png");
    startbtn->setParent(this);
    startbtn->move(this->width()*0.5-startbtn->width()*0.5,this->height()*0.7);

    //实例化一个选择关卡的场景
    chooseSence = new ChooseLevelSence;

    connect(startbtn,&MyPushButton::clicked,[=](){
        //播放音效
        startsound->play();

        startbtn->zoom1();
        startbtn->zoom2();

        //延时进入到选择关卡场景
        QTimer::singleShot(500,this,[=](){
            //自身场景隐藏
            this->hide();
            chooseSence->setGeometry(this->geometry());
            chooseSence->show();
        });
    });
    //监听返回信号
    connect(chooseSence,&ChooseLevelSence::chooseSceneBack,[=](){
        //回到上一级  隐藏选择关卡场景  回到开始场景
        QTimer::singleShot(500,this,[=](){
            chooseSence->hide();
            this->setGeometry(chooseSence->geometry());
            this->show();
        });

    });


}

void MainWindow::paintEvent(QPaintEvent * ){
    //新建一个画家
    QPainter painter(this);
    //创建一个Qpixmap对象
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");
    //设置了背景图
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    pix.load(":/res/Title.png");
    //缩放图片
    pix=pix.scaled(pix.width()*0.7,pix.height()*0.7);
    //绘制标题
    painter.drawPixmap(10,30,pix.width(),pix.height(),pix);

}

MainWindow::~MainWindow()
{
    delete ui;
}

