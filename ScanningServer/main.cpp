#include "server.h"

#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMetaType>
#include <opencv.hpp>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Server w;
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("scanningsys");
    db.setUserName("root");
    db.setPassword("200422");
    db.setPort(3306);
    if (!db.open()) {
        qDebug() << "打开数据库失败" << db.lastError();
    }
    qRegisterMetaType<cv::Mat>("cv::Mat");
    w.show();
    int ret = a.exec();
    if (db.open()) {
        db.close();
        qDebug() << "关闭数据库";
    }
    return ret;
}
