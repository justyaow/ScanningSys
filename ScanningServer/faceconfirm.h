#ifndef FACECONFIRM_H
#define FACECONFIRM_H

#include <QObject>
#include <seeta/FaceEngine.h>
#include <opencv.hpp>

class FaceConfirm : public QObject
{
    Q_OBJECT
public:
    explicit FaceConfirm(QObject *parent = nullptr);
    ~FaceConfirm();
public slots:
    int64_t regFace(cv::Mat &image); // 注册
    int selectFace(cv::Mat image); // 查询
signals:
    void send_id(int64_t id);
private:
    seeta::FaceEngine *faceConfirm;
};

#endif // FACECONFIRM_H
