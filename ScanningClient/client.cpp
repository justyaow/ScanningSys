#include "client.h"

Client::Client(QWidget *parent)
    : QMainWindow(parent)
{
    // 整体布局设计
    setWindowTitle("客户端");
    resize(1000, 500);
    centralWidget = new QWidget(this);
    centralWidget->setFixedSize(1000, 500);
    mainLayout = new QHBoxLayout(centralWidget);
    leftWidget = new QWidget(centralWidget);
    leftWidget->setFixedSize(600, 500);
    // leftWidget->setStyleSheet("background-color: black;");
    mainLayout->addWidget(leftWidget);
    rightWidget = new QWidget(centralWidget);
    mainLayout->addWidget(rightWidget);

    // 左侧部分设计
    faceLabel = new QLabel(leftWidget);
    headLabel = new QLabel(leftWidget);
    headLabel->setStyleSheet("border-image: url(:/crc.png)");
    faceLabel->setFixedSize(600, 500);
    headLabel->setGeometry(100, 50, 400, 400);
    // faceLabel->setStyleSheet("background-color: green");
    cap.open(0); // 摄像头开启
    startTimer(100); // 开启定时器，每100ms刷新一次
    cascade.load("D:/Course/opencv452/etc/haarcascades/haarcascade_frontalface_alt2.xml"); // 导入级联分类器

    // 右侧部分设计
    rightLayout = new QVBoxLayout(rightWidget);
    imageLabel = new QLabel(rightWidget);
    imageLabel->setFixedSize(300, 300);
    imageLabel->setStyleSheet("background-color: blue;"
                              "border-radius: 150px;");
    rightLayout->addWidget(imageLabel);
    QWidget *nameWidget = new QWidget(rightWidget);
    QHBoxLayout *nameLayout = new QHBoxLayout(nameWidget);
    QLabel *nameLabel = new QLabel("姓名：");
    nameLayout->addWidget(nameLabel);
    nameText = new QLineEdit(rightWidget);
    nameLayout->addWidget(nameText);
    rightLayout->addWidget(nameWidget);
    QWidget *numWidget = new QWidget(rightWidget);
    QHBoxLayout *numLayout = new QHBoxLayout(numWidget);
    QLabel *numLabel = new QLabel("学号：");
    numLayout->addWidget(numLabel);
    numText = new QLineEdit(rightWidget);
    numLayout->addWidget(numText);
    rightLayout->addWidget(numWidget);
    QWidget *sexWidget = new QWidget(rightWidget);
    QHBoxLayout *sexLayout = new QHBoxLayout(sexWidget);
    QLabel *sexLabel = new QLabel("性别：");
    sexLayout->addWidget(sexLabel);
    sexText = new QLineEdit(rightWidget);
    sexLayout->addWidget(sexText);
    rightLayout->addWidget(sexWidget);

    // 连接处理
    connect(&tcpSocket, &QTcpSocket::disconnected, this, &Client::restartConnect);
    connect(&tcpSocket, &QTcpSocket::connected, this, &Client::processConnect);
    connect(&tcpSocket, &QTcpSocket::readyRead, this, &Client::receiveServer);
    connect(&timer, &QTimer::timeout, this, &Client::timerConnect);
    timer.start(5000);
    flag = 0;
}

void Client::timerEvent(QTimerEvent *e) {
    cv::Mat image;
    if (cap.grab()) {
        cap.read(image);
    }
    cv::resize(image, image, cv::Size(600, 500));

    // 转换灰度图像
    cv::Mat gray;
    cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);
    cv::equalizeHist(gray, gray);

    // 检测人脸
    std::vector<cv::Rect> faces;
    cascade.detectMultiScale(gray, faces);
    // for (size_t i = 0; i < faces.size(); ++i) {
    //     cv::rectangle(image, faces[i], cv::Scalar(255, 0, 0), 2);
    // }
    if (faces.size() > 0 && flag >= 0) {
        cv::Rect t = faces[0];
        headLabel->move(t.x, t.y);
        if (flag > 2) {
            std::vector<uchar> buffer;
            cv::imencode(".jpg", image, buffer);
            QByteArray ans((const char*)buffer.data(), buffer.size());
            quint64 numSize = ans.size();
            QByteArray send;
            QDataStream stream(&send, QIODevice::WriteOnly);
            stream.setVersion(QDataStream::Qt_6_6);
            stream << numSize << ans;
            tcpSocket.write(send);
            flag = -1;
        }
        ++flag;
    }
    if (faces.empty()) {
        headLabel->move(100, 50);
        flag = 0;
    }

    if (image.data == nullptr) {
        return;
    }
    cv::cvtColor(image, image, cv::COLOR_BGR2RGB);
    QImage faceImage(image.data, image.cols, image.rows, image.step1(), QImage::Format_RGB888);
    QPixmap m = QPixmap::fromImage(faceImage);
    faceLabel->setPixmap(m);
}

void Client::restartConnect() {
    qDebug() << "断开连接重新启动连接";
    timer.start(5000);
}

void Client::processConnect() {
    qDebug() << "已连接";
    timer.stop();
}

void Client::timerConnect() {
    qDebug() << "正在连接服务器";
    tcpSocket.connectToHost("localhost", 8888);
}

void Client::receiveServer() {
    QByteArray data = tcpSocket.readAll();
    qDebug() << data;
    QJsonParseError err;
    QJsonDocument jsonFile = QJsonDocument::fromJson(data, &err);
    if (err.error != QJsonParseError::NoError) {
        qDebug() << "json数据错误";
        return;
    }
    QJsonObject obj = jsonFile.object();
    // QString id = obj.value("id").toString();
    QString name = obj.value("name").toString();
    QString num = obj.value("num").toString();
    QString sex = obj.value("sex").toString();
    QString photo_id = obj.value("photo_id").toString();
    qDebug() << "photo_id: " << photo_id;
    nameText->setText(name);
    numText->setText(num);
    sexText->setText(sex);
    QString path = QString("D:/Course/projects/ScanningServer/data/" + photo_id + ".jpg");
    QPixmap pixmap(path);
    if (pixmap.isNull()) {
        qDebug() << "头像加载失败";
    } else {
        imageLabel->setPixmap(pixmap);
        imageLabel->setScaledContents(true);
    }
}

Client::~Client() {
    if (cap.isOpened()) {
        cap.release();
    }
}
