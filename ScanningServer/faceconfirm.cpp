#include "faceconfirm.h"

FaceConfirm::FaceConfirm(QObject *parent) : QObject(parent) {
    seeta::ModelSetting  FDmode("D:/Course/SeetaFace/bin/model/fd_2_00.dat",seeta::ModelSetting::CPU,0);
    seeta::ModelSetting  PDmode("D:/Course/SeetaFace/bin/model/pd_2_00_pts5.dat",seeta::ModelSetting::CPU,0);
    seeta::ModelSetting  FRmode("D:/Course/SeetaFace/bin/model/fr_2_10.dat",seeta::ModelSetting::CPU,0);
    faceConfirm = new seeta::FaceEngine(FDmode, PDmode, FRmode);
    faceConfirm->Load("D:/Course/projects/ScanningServer/face.db");
}

int64_t FaceConfirm::regFace(cv::Mat &image) {
    seeta::ImageData imageData;
    imageData.data = image.data;
    imageData.width = image.cols;
    imageData.height = image.rows;
    imageData.channels = image.channels();
    int64_t id = faceConfirm->Register(imageData); // 注册的id
    if (id >= 0) {
        faceConfirm->Save("D:/Course/projects/ScanningServer/face.db");
    }
    return id;
}

int FaceConfirm::selectFace(cv::Mat image) {
    seeta::ImageData imageData;
    imageData.data = image.data;
    imageData.width = image.cols;
    imageData.height = image.rows;
    imageData.channels = image.channels();
    float similar = 0;
    int id = faceConfirm->Query(imageData, &similar);
    if (similar > 0.7) {
        emit send_id(id);
    } else {
        emit send_id(-1);
    }
    return id;
}

FaceConfirm::~FaceConfirm() {
    delete faceConfirm;
}
