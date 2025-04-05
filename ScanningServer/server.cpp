#include "server.h"

int cnt = -1;

Server::Server(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("服务端");
    resize(1000, 600);
    byteSize = 0;

    // 多线程进行人脸识别判断
    QThread *thread = new QThread();
    face.moveToThread(thread);
    thread->start();
    connect(this, &Server::select, &face, &FaceConfirm::selectFace);
    connect(&face, &FaceConfirm::send_id, this, &Server::receiveId);

    // 布局设计
    centralWidget = new QWidget(this);
    centralWidget->setFixedSize(1000, 600);
    mainLayout = new QVBoxLayout(centralWidget);
    tabWidget = new QTabWidget(centralWidget);
    mainWidget = new QWidget(centralWidget);
    optWidget = new QWidget(centralWidget);
    tabWidget->addTab(mainWidget, "实时显示");
    tabWidget->addTab(optWidget, "注册");
    mainLayout->addWidget(tabWidget);

    // 实时显示界面
    QHBoxLayout *mainingLayout = new QHBoxLayout(mainWidget);
    imageLabel = new QLabel(this);
    imageLabel->setFixedSize(500, 600);
    imageLabel->setStyleSheet("background-color: blue");
    QWidget *leftWidget = new QWidget(mainWidget);
    mainingLayout->addWidget(leftWidget);
    mainingLayout->addWidget(imageLabel);

    // 注册界面
    QHBoxLayout *optLayout = new QHBoxLayout(optWidget);
    QWidget *optLeftWidget = new QWidget(optWidget);
    QWidget *optRightWidget = new QWidget(optWidget);
    optLayout->addWidget(optLeftWidget);
    optLayout->addWidget(optRightWidget);
    QVBoxLayout *optLeftLayout = new QVBoxLayout(optLeftWidget);
    QVBoxLayout *optRightLayout = new QVBoxLayout(optRightWidget);
    // QVBoxLayout *optLeftLayout = new QVBoxLayout(optWidget);
    // QVBoxLayout *optRightLayout = new QVBoxLayout(optWidget);
    // optLayout->addLayout(optLeftLayout);
    // optLayout->addLayout(optRightLayout);

    // 左侧注册界面
    // 姓名
    QWidget *nameWidget = new QWidget(optLeftWidget);
    QHBoxLayout *nameLayout = new QHBoxLayout(nameWidget);
    QLabel *nameLabel = new QLabel("姓名：", nameWidget);
    nameText = new QLineEdit(nameWidget);
    nameLayout->addWidget(nameLabel);
    nameLayout->addWidget(nameText);
    optLeftLayout->addWidget(nameWidget);

    // 学号
    QWidget *numWidget = new QWidget(optLeftWidget);
    QHBoxLayout *numLayout = new QHBoxLayout(numWidget);
    QLabel *numLabel = new QLabel("学号：", numWidget);
    numText = new QLineEdit(numWidget);
    numLayout->addWidget(numLabel);
    numLayout->addWidget(numText);
    optLeftLayout->addWidget(numWidget);

    // 性别
    QWidget *sexWidget = new QWidget(optLeftWidget);
    QHBoxLayout *sexLayout = new QHBoxLayout(sexWidget);
    QLabel *sexLabel = new QLabel("性别：", sexWidget);
    sexText = new QLineEdit(sexWidget);
    sexLayout->addWidget(sexLabel);
    sexLayout->addWidget(sexText);
    optLeftLayout->addWidget(sexWidget);

    // 右侧注册界面
    headLabel = new QLabel("照片显示区域", optRightWidget);
    optRightLayout->addWidget(headLabel);
    // headLabel->setStyleSheet("background-color: green");
    headLabel->setFixedSize(400, 400);
    //headLabel->setStyleSheet("background-color: blue");
    headLabel->setStyleSheet("border:1px solid #313236");
    // headLabel->setStyleSheet("border:1px solid #313236"
    //                          "border-radius:4px"
    //                          "background-color: blue");
    QWidget *photoFileWidget = new QWidget(optRightWidget);
    QHBoxLayout *photoFileLayout = new QHBoxLayout(photoFileWidget);
    photoFilePath = new QLineEdit(photoFileWidget);
    photoFilePath->setFixedWidth(400);
    photoLabel = new QLabel(photoFileWidget);
    photoFileLayout->addWidget(photoLabel);
    photoFileLayout->addWidget(photoFilePath);
    optRightLayout->addWidget(photoFileWidget);
    QWidget *capWidget = new QWidget(optRightWidget);
    QHBoxLayout *capLayout = new QHBoxLayout(capWidget);
    openCap = new QPushButton("打开摄像头", capWidget);
    connect(openCap, &QPushButton::clicked, this, &Server::onOpenCap);
    QPushButton *takePhoto = new QPushButton("拍照", capWidget);
    connect(takePhoto, &QPushButton::clicked, this, &Server::onTakePhoto);
    QPushButton *change = new QPushButton("注册",capWidget);
    connect(change, &QPushButton::clicked, this, &Server::onChange);
    openCap->setFixedSize(100, 50);
    takePhoto->setFixedSize(100, 50);
    change->setFixedSize(100, 50);
    capLayout->addWidget(openCap);
    capLayout->addWidget(takePhoto);
    capLayout->addWidget(change);
    optRightLayout->addWidget(capWidget);

    // 接受数据以及端口监听
    connect(&server, &QTcpServer::newConnection, this, &Server::receiveClient);
    server.listen(QHostAddress::Any, 8888);
}

void Server::timerEvent(QTimerEvent *e) {
    if (cap.isOpened()) {
        cap >> image;
        if (image.data == nullptr) {
            return;
        }
    }
    cv::Mat t;
    cv::cvtColor(image, t, cv::COLOR_BGR2RGB);
    QImage img(t.data, t.cols, t.rows, t.step1(), QImage::Format_RGB888);
    QPixmap m = QPixmap::fromImage(img);
    m = m.scaledToWidth(headLabel->width());
    headLabel->setPixmap(m);
}

void Server::receiveClient() {
    qDebug() << "已接收到客户端";
    socket = server.nextPendingConnection(); // 获取客户端套接字
    connect(socket, &QTcpSocket::readyRead, this, &Server::receiveData);
}

void Server::receiveData() {
    QDataStream stream(socket);
    stream.setVersion(QDataStream::Qt_6_6);

    if (byteSize == 0) {
        if (socket->bytesAvailable() < static_cast<qint64>(byteSize)) {
            return;
        }
        stream >> byteSize;
    }

    if (socket->bytesAvailable() < static_cast<qint64>(byteSize)) {
        return;
    }
    QByteArray data;
    stream >> data;
    byteSize = 0;
    if (data.size() == 0) { // 没有读取到数据
        return;
    }

    QPixmap image;
    image.loadFromData(data);
    image = image.scaled(imageLabel->size());
    imageLabel->setPixmap(image);

    cv::Mat faceImage;
    std::vector<uchar> decode(data.size());
    memcpy(decode.data(), data.data(), data.size());
    faceImage = cv::imdecode(decode, cv::IMREAD_COLOR);
    qRegisterMetaType<cv::Mat>("cv::Mat");
    emit select(faceImage);
    qDebug() << "成功进行识别";
}

void Server::onOpenCap() {
    if (openCap->text() == "打开摄像头") {
        if (cap.open(0)) {
            openCap->setText("关闭摄像头");
            id = startTimer(100);
        }
    } else {
        killTimer(id); // 关闭定时器
        openCap->setText("打开摄像头");
        headLabel->setPixmap(QPixmap());
        headLabel->setText("个人照片");
        cap.release();
    }
}

void Server::receiveId(int64_t id) {
    qDebug() << "已接受到人脸数据";
    if (id < 0) {
        QString ans = QString("{\"id\":\" \",\"name\":\"\",\"num\":\"\",\"sex\":\"\",\"photo_id\":\"\"}");
        socket->write(ans.toUtf8());
        qDebug() << "没有找到当前人脸";
        return;
    }
    QSqlQuery query;
    query.prepare("SELECT * FROM stuinfo WHERE id = :id");
    query.bindValue(":id", id);
    if (!query.exec()) {
        qDebug() << "查询失败";
        return;
    }

    // 查询信息发送到客户端
    if (query.next()) {
        qDebug() << "查询到信息准备发送给客户端";
        QString ID = QString::number(id);
        QString name = query.value(1).toString();
        QString num = query.value(2).toString();
        QString sex = query.value(3).toString();
        QString photoId = query.value(4).toString();
        QString ans = QString("{\"id\": \"" + ID + "\", \"name\": \"" + name + "\", \"num\": \"" + num + "\", \"sex\": \"" + sex + "\", \"photo_id\": \"" + photoId + "\"}");
        // query.prepare("INSERT INTO stuinfo(id, name, num, sex) VALUES(:id, :name, :num, :sex)");
        // query.bindValue(":id", id);
        // query.bindValue(":name", name);
        // query.bindValue(":num", num);
        // query.bindValue(":sex", sex);
        // if (!query.exec()) {
        //     ans = QString("{\"id\":\" \",\"name\":\"\",\"num\":\"\",\"sex\":\"\"}");
        //     socket->write(ans.toUtf8());
        //     qDebug() << query.lastError();
        // } else {
        //     socket->write(ans.toUtf8());
        // }
        socket->write(ans.toUtf8());
        qDebug() << "成功发送到客户端";
    }

    // 实时同步日志信息
}

void Server::onTakePhoto() {
    if (openCap->text() == "打开摄像头") {
        QMessageBox::warning(this, "摄像头未打开", "请先打开摄像头");
        return;
    }
    QString dirPath = QString("D:/Course/projects/ScanningServer/data/");
    QDir dir(dirPath);
    if (!dir.exists()) {
        if (dir.mkpath(dirPath)) {
            qDebug() << "创建新目录";
        } else {
            qDebug() << "创建新目录失败";
            return;
        }
    }
    dir.setNameFilters(QStringList() << "*");
    dir.setFilter(QDir::Files | QDir::NoDotAndDotDot);
    QStringList fileList = dir.entryList();
    cnt = static_cast<int>(fileList.size());
    ++cnt;
    QString headFile = QString("D:/Course/projects/ScanningServer/data/" + QString::number(cnt) + ".jpg");
    photoLabel->setText("图像已保存至: ");
    photoFilePath->setText(headFile);
    cv::imwrite(headFile.toUtf8().data(), image);
    killTimer(id);
    openCap->setText("打开摄像头");
    cap.release();
}

void Server::onChange() {
    if (cnt == -1) {
        QMessageBox::warning(this, "没有可用照片", "请先拍照作为识别面目再进行注册");
        return;
    }
    if (numText->text() == "" || nameText->text() == "" || sexText->text() == "") {
        QMessageBox::warning(this, "信息不完整", "注册信息填写不完整，请先完善个人信息");
        return;
    }
    FaceConfirm tFace;
    cv::Mat tImage = cv::imread(photoFilePath->text().toUtf8().data());
    int ID = tFace.regFace(tImage);
    QString name = nameText->text();
    QString num = numText->text();
    QString sex = sexText->text();
    QSqlQuery query;
    query.prepare("INSERT INTO stuinfo(id, name, num, sex, photo_id) VALUES(:id, :name, :num, :sex, :photo_id)");
    query.bindValue(":id", ID);
    query.bindValue(":name", name);
    query.bindValue(":num", num);
    query.bindValue(":sex", sex);
    query.bindValue(":photo_id", cnt);
    if (query.exec()) {
        QMessageBox::information(this, "注册成功", "成功注册相关信息");
    } else {
        QMessageBox::critical(this, "注册失败", "注册失败，请稍后重试");
    }
}

Server::~Server() {
    if (cap.isOpened()) {
        cap.release();
    }
}
