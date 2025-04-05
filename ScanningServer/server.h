#ifndef SERVER_H
#define SERVER_H

#include "faceconfirm.h"

#include <QMainWindow>
#include <QTcpSocket>
#include <QTcpServer>
#include <QDebug>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTabWidget>
#include <QLabel>
#include <QImage>
#include <QPushButton>
#include <QLineEdit>
#include <opencv.hpp>
#include <QTimer>
#include <QThread>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDir>
#include <QMetaType>

class Server : public QMainWindow
{
    Q_OBJECT

public:
    Server(QWidget *parent = nullptr);
    ~Server();
    void timerEvent(QTimerEvent *e);
private slots:
    void receiveClient(); // 接收客户端连接
    void receiveData(); // 接收数据
    void onOpenCap(); // 打开摄像头
    void receiveId(int64_t id); // 接收人脸识别结果
    void onTakePhoto(); // 拍照
    void onChange(); // 注册
signals:
    void select(cv::Mat image); // 查询图像
private:
    QWidget *centralWidget; // 中心界面
    QVBoxLayout *mainLayout; // 主界面
    QWidget *mainWidget; // 注册界面
    QWidget *optWidget; // 操作界面

    QLabel *imageLabel; // 图像实时显示区域
    QLabel *headLabel; // 注册照片区域
    QLabel *photoLabel; // 图像路径标签

    QPushButton *openCap; // 摄像头开关

    quint64 byteSize; // 读取内容大小

    QTabWidget *tabWidget; // 导航栏

    QTcpSocket *socket; // 套接字
    QTcpServer server; // 服务端

    cv::VideoCapture cap; // 摄像头
    cv::Mat image;

    int id; // 定时器编号

    FaceConfirm face; // 人脸识别

    QLineEdit *nameText, *numText, *sexText; // 姓名，学号，性别文本框
    QLineEdit *photoFilePath; // 照片地址
};
#endif // SERVER_H
