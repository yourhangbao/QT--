#include "playsence.h"
#include<QMenuBar>
#include<QPainter>
#include<QPushButton>
#include"mypushbutton.h"
#include<QDebug>
#include<QLabel>
#include"mycoin.h"
#include"dataconfig.h"
#include<QPropertyAnimation>
#include<QSound>

//PlaySence::PlaySence(QWidget *parent) : QMainWindow(parent)
//{

//}
PlaySence::PlaySence(int levelNum){
    this->levelIndex=levelNum;
    //配置选择关卡场景
    // 设置固定的大小
    setFixedSize(500,800);
    setWindowIcon(QIcon(":/res/Coin0001.png"));
    //设置标题
    setWindowTitle("翻金币场景");
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
    //创建返回按钮
    MyPushButton * backbtn=new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backbtn->setParent(this);
    backbtn->move(this->width()-backbtn->width(),this->height()-backbtn->height());

    connect(backbtn,&MyPushButton::clicked,[=](){
        backsound->play();
        emit this->playSceneBack();
        qDebug()<<"发出来返回信号";
    });

    //创建一个重新开始的按钮
    MyPushButton * remakebtn=new MyPushButton(":/res/remake.jpeg");
    remakebtn->setIconSize(QSize(50,50));
    remakebtn->setFixedSize(50,50);
    remakebtn->setStyleSheet("QPushButton{border:0px;}");
    remakebtn->setParent(this);
    remakebtn->move(this->width()-remakebtn->width(),remakebtn->height()+20);

    connect(remakebtn,&MyPushButton::clicked,[=](){
        backsound->play();
        dataConfig config;
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                gameArray[i][j]=config.mData[levelNum][i][j];

                QString str;
                if(gameArray[i][j]==1){
                    str=":/res/Coin0001.png";
                    //创建金币

                }else{
                    //创建银币
                    str=":/res/Coin0008.png";
                }
                QPixmap pix;
                pix.load(str);
                pix=pix.scaled(pix.width()*1.5,pix.height()*1.5);
                coinArray[i][j]->setIcon(pix);
                coinArray[i][j]->flag=gameArray[i][j];
                coinArray[i][j]->isWin=false;
            }
        }
    });





    //创建一个关卡显示的标签
    QLabel *label=new QLabel;
    label->setParent(this);
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(25);
    label->setFont(font);
    QString str=QString("Level:%1").arg(levelNum);
    label->setText(str);
    label->setAttribute(Qt::WA_TransparentForMouseEvents);
    label->setGeometry(30,this->height()-80,200,50);

    dataConfig config;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            gameArray[i][j]=config.mData[levelNum][i][j];
        }
    }
    //胜利图片显示
    QLabel * winlabel=new QLabel;
    QPixmap pix;
    pix.load(":/res/LevelCompletedDialogBg.png");
    winlabel->setGeometry(0,0,pix.width(),pix.height());
    winlabel->setPixmap(pix);
    winlabel->setParent(this);
    winlabel->move((this->width()-pix.width())*0.5,-pix.height());

    //创建一个下一关的按钮
    MyPushButton * nextbtn=new MyPushButton(":/res/next.jpeg");
    nextbtn->setIconSize(QSize(50,50));
    nextbtn->setFixedSize(50,50);
    nextbtn->setStyleSheet("QPushButton{border:0px;}");
    nextbtn->setParent(this);
    nextbtn->move(0.5*(this->width()-nextbtn->width()),-(this->height()-nextbtn->height()-80));

    connect(nextbtn,&MyPushButton::clicked,[=](){
        backsound->play();
        emit this->nextPlayScene();

    });

    //反转金币的音效
    QSound * coinsound=new QSound(":/res/ConFlipSound.wav",this);
    //胜利的音效
    QSound * successsound=new QSound(":/res/LevelWinSound.wav",this);
    //显示金币背景图案
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            //绘制背景图片
            QLabel *label=new QLabel;
            QPixmap pix = QPixmap(":/res/BoardNode.png");
            pix=pix.scaled(90,90);
            label->setPixmap(pix);
            label->setParent(this);
            label->setAttribute(Qt::WA_TransparentForMouseEvents);
            label->move(70+i*90,70+j*90);


            QString str;
            if(gameArray[i][j]==1){
                str=":/res/Coin0001.png";
                //创建金币

            }else{
                //创建银币
                str=":/res/Coin0008.png";
            }
            MyCoin *coin=new MyCoin(str);
            coin->setParent(this);
            coin->move(80+i*90,275+j*90);
            coin->posX=i;
            coin->posY=j;
            coin->flag=gameArray[i][j];
            coin->isWin=false;
            coinArray[i][j] = coin;

            connect(coin,&MyCoin::clicked,[=](){

                //播放反转音效
                coinsound->play();
                //反转包括周围四个
                coin->changeFlag();
                this->gameArray[i][j]=this->gameArray[i][j]==0?1:0;
                QTimer::singleShot(300,this,[=](){
                    //反转右侧金币
                    if(coin->posX<3){
                        coinArray[i+1][j]->changeFlag();
                        this->gameArray[i+1][j]=this->gameArray[i+1][j]==0?1:0;
                    }
                    if(coin->posX>0){
                        coinArray[i-1][j]->changeFlag();
                        this->gameArray[i-1][j]=this->gameArray[i-1][j]==0?1:0;
                    }
                    if(coin->posY<3){
                        coinArray[i][j+1]->changeFlag();
                        this->gameArray[i][j+1]=this->gameArray[i][j+1]==0?1:0;
                    }
                    if(coin->posY>0){
                        coinArray[i][j-1]->changeFlag();
                        this->gameArray[i][j-1]=this->gameArray[i][j-1]==0?1:0;
                    }

                    this->isWin=true;
                    for(int i=0;i<4;i++){
                        for(int j=0;j<4;j++){
                            if(coinArray[i][j]->flag==false){
                                this->isWin=false;
                                break;
                            }
                        }
                    }

                    if(this->isWin==true){
                        qDebug()<<"游戏胜利";
                        //播放胜利音效
                        successsound->play();
                        //将所有的硬币胜利标志变为true
                        for(int i=0;i<4;i++){
                            for(int j=0;j<4;j++){
                                coinArray[i][j]->isWin=true;
                            }
                        }
                        if(this->levelIndex!=20){
                            //将下一关的按钮移动下来
                            QPropertyAnimation *animation2=new QPropertyAnimation(nextbtn,"geometry");
                            //设置时间间隔
                            animation2->setDuration(1000);
                            //设置起始位置
                            animation2->setStartValue(QRect(nextbtn->x(),nextbtn->y(),nextbtn->width(),nextbtn->height()));
                            //设置结束位置
                            animation2->setEndValue(QRect(0.5*(this->width()-nextbtn->width()),(this->height()-nextbtn->height()-80),nextbtn->width(),nextbtn->height()));
                            //设置缓和曲线
                            animation2->setEasingCurve(QEasingCurve::OutBounce);
                            //执行动画
                            animation2->start();
                        }




                        //将胜利的图片移动下来
                        QPropertyAnimation *animation=new QPropertyAnimation(winlabel,"geometry");
                        //设置时间间隔
                        animation->setDuration(1000);
                        //设置起始位置
                        animation->setStartValue(QRect(winlabel->x(),winlabel->y(),winlabel->width(),winlabel->height()));
                        //设置结束位置
                        animation->setEndValue(QRect(winlabel->x(),winlabel->y()+180,winlabel->width(),winlabel->height()));
                        //设置缓和曲线
                        animation->setEasingCurve(QEasingCurve::OutBounce);
                        //执行动画
                        animation->start();


                    }
                });
            });




        }
    }
}

void PlaySence::paintEvent(QPaintEvent * ){
    //新建一个画家
    QPainter painter(this);
    //创建一个Qpixmap对象
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    //设置了背景图
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    pix.load(":/res/Title.png");
    //缩放图片
    pix=pix.scaled(pix.width()*0.7,pix.height()*0.7);
    //绘制标题
    painter.drawPixmap(10,30,pix.width(),pix.height(),pix);
}

