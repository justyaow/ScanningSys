#ifndef CLIENT_H
#define CLIENT_H

#include <QMainWindow>
#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <opencv.hpp>
#include <QTcpSocket>
#include <QTimer>
#include <QImage>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QLineEdit>

class Client : public QMainWindow
{
    Q_OBJECT

public:
    Client(QWidget *parent = nullptr);
    ~Client();
    void timerEvent(QTimerEvent *e); // 定时器事件响应
private slots:
    void restartConnect(); // 断线重连
    void processConnect(); // 连接成功后处理
    void timerConnect(); // 定时连接
    void receiveServer(); // 接收客户端数据
private:
    QWidget *centralWidget; // 中心部分
    QWidget *leftWidget; // 左侧部分
    QWidget *rightWidget; // 右侧部分

    QHBoxLayout *mainLayout; // 主布局
    QVBoxLayout *rightLayout; // 右侧布局

    QLabel *faceLabel; // 显示图像区域
    QLabel *headLabel; // 锁定头像位置
    QLabel *imageLabel; // 显示个人头像位置

    cv::VideoCapture cap; // 摄像头
    cv::CascadeClassifier cascade; // 级联分类器

    QTcpSocket tcpSocket; // tcp套接字
    QTimer timer; // 定时器

    int flag; // 标志位

    QLineEdit *nameText; // 姓名显示框
    QLineEdit *numText; // 学号显示框
    QLineEdit *sexText; // 性别显示框
};
#endif // CLIENT_H
