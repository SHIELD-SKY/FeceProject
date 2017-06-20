#ifndef CAMARAGET_H
#define CAMARAGET_H

#include <QWidget>
#include <QImage>
#include <QTimer>     // 设置采集数据的间隔时间

#include <highgui.h>  //包含opencv库头文件
#include <cv.h>
#include "Python.h"
#include <opencv.hpp>
#include <fstream>
namespace Ui {
    class camaraGet;
}

class camaraGet : public QWidget
{
    Q_OBJECT

public:
    explicit camaraGet(QWidget *parent = 0);
    ~camaraGet();

private slots:
    void openCamara();      // 打开摄像头
    void readFarme();       // 读取当前帧信息
    void closeCamara();     // 关闭摄像头。
    void takingPictures();  // 拍照
    void mix();

private:
    Ui::camaraGet *ui;
    QTimer    *timer;
    QImage    *imag;
    CvCapture *cam;// 视频获取结构， 用来作为视频获取函数的一个参数
    IplImage  *frame;//申请IplImage类型指针，就是申请内存空间来存放每一帧图像
};
using namespace std;
using namespace cv;
#endif // CAMARAGET_H
