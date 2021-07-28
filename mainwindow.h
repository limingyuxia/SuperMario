#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QPainter>
#include <QString>
#include <QMediaPlayer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int x, y;
    int walk_state;

    int blockX, blockY;

    int startRolePosx;

    int mapX;

    QMediaPlayer *player;

    void paintEvent(QPaintEvent *);
private slots:

    void on_down_clicked();

    void on_left_clicked();

    void on_right_clicked();

    void on_fire_clicked();

    void on_jump_pressed();

    void on_jump_released();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
