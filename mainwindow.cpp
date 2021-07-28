#include "mainwindow.h"
#include "./ui_mainwindow.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 设置窗口放大如何放大游戏方块
    // this->setFixedSize(800, 600);
    this->setSizeIncrement(800, 600);
    // 设置主窗口标题
    this->setWindowTitle("Super Mario");
    // 设置主窗口图标
    QApplication::setWindowIcon(QIcon(":/resource/images/ico.bmp"));

    // 设置按钮长按点击
    // 如果按钮按下超过100ms，就每隔6ms模拟按一下键
    ui->left->setAutoRepeat(true);
    ui->left->setAutoRepeatDelay(100);
    ui->left->setAutoRepeatInterval(6);

    ui->right->setAutoRepeat(true);
    ui->right->setAutoRepeatDelay(100);
    ui->right->setAutoRepeatInterval(6);

    // 设置游戏中一个快的大小
    blockX = 32;
    blockY = 32;

    // 设置按钮大小
    int buttonSize = 2 * blockX;
    ui->left->resize(buttonSize, buttonSize);
    ui->right->resize(buttonSize, buttonSize);
    ui->down->resize(buttonSize, buttonSize);
    ui->fire->resize(buttonSize, buttonSize);
    ui->jump->resize(buttonSize, buttonSize);

    // 设置按钮位置
    int buttonStart = 13; // 按钮在第13个方块的地方显示
    ui->left->move(2 * buttonSize, buttonStart * blockX);
    ui->right->move(5 * buttonSize, buttonStart * blockX);
    ui->down->move(3.5 * buttonSize, (buttonStart + 1) * blockX);
    ui->jump->move(8 * buttonSize, buttonStart * blockX);
    ui->fire->move(10 * buttonSize, buttonStart * blockX);

    // 角色的初始位置
    startRolePosx = 2.5 * blockX;

    // 角色的初始坐标
    x = startRolePosx;
    y = 12 * blockX;

    player = new QMediaPlayer(this);
    player->setSource(QUrl(":/resource/music/overworld.wav"));
    //player->setActiveAudioTrack(18);

    mapX = x;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    player->play();

    QPainter painter(this);
    QPixmap backGround;
    backGround.load(":/resource/images/11.bmp");


    /*
        struct specialBlock{
            pos
            QPixmap
        };
    */
    /*
        特殊快和特殊快的坐标 -- 通过photoshop取特殊快的像素点得知它的坐标
        (2, 12) (3, 12)  地图上人物的初始位置
        (21, 9)  第一个蘑菇的位置
        (64, 8)  第一个命蘑菇的位置
        (78, 9)  第二个蘑菇的位置
        (94, 9)  第一个可以顶的金币的位置
        (101, 9) 第一个星星的位置
        (109, 5) 第三个蘑菇的位置
    */


    // 画背景
    int i, j;
    for (i = 0;i < 225; i++) {
        for (j = 0; j < 16; j++) {
            if (i == 2 && j == 12) {
                 painter.drawPixmap(startRolePosx - x + i * blockX, j * blockY, blockX, blockY, QPixmap(":/resource/images/bush_center_1.bmp"));
                 continue;
            }
            if (i == 3 && j == 12) {
                 painter.drawPixmap(startRolePosx - x + i * blockX, j * blockY, blockX, blockY, QPixmap(":/resource/images/bush_center_0.bmp"));
                 continue;
            }
            if (i == 21 && j == 9) {
                painter.drawPixmap(startRolePosx - x + i * blockX, j * blockY, blockX, blockY, QPixmap(":/resource/images/blockq_0.bmp"));
                continue;
            }
            if (i == 64 && j == 8) {
                painter.drawPixmap(startRolePosx - x + i * blockX, j * blockY, blockX, blockY, backGround, (i - 1) * 32, j *32, 32, 32);
                continue;
            }
            if (i == 78 && j == 9) {
                painter.drawPixmap(startRolePosx - x + i * blockX, j * blockY, blockX, blockY, QPixmap(":/resource/images/blockq_0.bmp"));
                continue;
            }
            if (i == 94 && j == 9) {
                painter.drawPixmap(startRolePosx - x + i * blockX, j * blockY, blockX, blockY, QPixmap(":/resource/images/brickred.bmp"));
                continue;
            }
            if (i == 101 && j == 9) {
                painter.drawPixmap(startRolePosx - x + i * blockX, j * blockY, blockX, blockY, QPixmap(":/resource/images/brickred.bmp"));
                continue;
            }
            if (i == 109 && j == 5) {
                painter.drawPixmap(startRolePosx - x + i * blockX, j * blockY, blockX, blockY, QPixmap(":/resource/images/blockq_0.bmp"));
                continue;
            }

            painter.drawPixmap(startRolePosx - x + i * blockX, j * blockY, blockX, blockY, backGround, i * 32, j *32, 32, 32);
        }
    }

    // 绘制角色  
    painter.drawPixmap(mapX, y, blockX, blockY, QPixmap(":/resource/images/mario.bmp"));

    // 设置画笔颜色
    painter.setPen(QColor(255, 242, 0));
    QFont font;
    // 设置字体格式
    int fontSize = 16;
    font.setPointSize(fontSize);
    painter.setFont(font);

    // 展示界面信息
    qint8 texInterval = 3 * blockX;


    QString score = "MARIO:";
    qint64 previousTextLen = 2 * blockX;
    painter.drawText(previousTextLen, blockY, score);
    previousTextLen = previousTextLen + score.length() * fontSize;
    painter.drawText(previousTextLen, blockY, QString::number(100000));

    QString coin = "COIN:";
    previousTextLen = previousTextLen + texInterval;
    painter.drawText(previousTextLen, blockY, coin);
    previousTextLen = previousTextLen + coin.length() * fontSize;
    painter.drawText(previousTextLen, blockY, QString::number(00));

    QString world = "WORLD:";
    previousTextLen = previousTextLen + texInterval;
    painter.drawText(previousTextLen, blockY, world);
    previousTextLen = previousTextLen + world.length() * fontSize;
    painter.drawText(previousTextLen, blockY, "1-1");

    QString time = "TIME:";
    previousTextLen = previousTextLen + texInterval;
    painter.drawText(previousTextLen, blockY, time);
    previousTextLen = previousTextLen + time.length() * fontSize;
    painter.drawText(previousTextLen, blockY, QString::number(300));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_down_clicked()
{
    qDebug() << "down click";
}


void MainWindow::on_left_clicked()
{
    if (mapX - startRolePosx <= 0) {
        return ;
    }

    if (x <= 12 * blockX) {
        x -= 5;
        mapX -= 5;
    } else {
        x -= 5;
    }

    update();
}


void MainWindow::on_right_clicked()
{
    if (x > 225 * blockX) {
        return ;
    }

    if (x < 12 * blockX) {
        x += 5;
        mapX += 5;
    } else {
        x += 5;
    }

    update();
}


void MainWindow::on_fire_clicked()
{
    qDebug() << "fire click";
}


void MainWindow::on_jump_pressed()
{
    y -= 4 * blockX;
    update();
}


void MainWindow::on_jump_released()
{
    y += 4 * blockX;
    update();
}

