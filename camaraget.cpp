#include "camaraget.h"
#include "ui_camaraget.h"
#include <qapplication.h>
#include <qpushbutton.h>
#include <qfont.h>



string Int_to_String(int n)
{
    ostringstream stream;
    stream << n;
    return stream.str();
}
camaraGet::camaraGet(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::camaraGet)
{
    ui->setupUi(this);

    cam     = NULL;
    timer   = new QTimer(this);
    imag    = new QImage();         // 初始化

    ui->open->show();
    ui->pic->hide();
    ui->closeCam->hide();
    camaraGet::openCamara();

    /*信号和槽*/
    connect(timer, SIGNAL(timeout()), this, SLOT(readFarme()));  // 时间到，读取当前摄像头信息
    connect(ui->open, SIGNAL(clicked()), this, SLOT(openCamara()));
    connect(ui->pic, SIGNAL(clicked()), this, SLOT(takingPictures()));
    connect(ui->closeCam, SIGNAL(clicked()), this, SLOT(closeCamara()));
    connect(ui->mixbutton, SIGNAL(clicked()), this, SLOT(mix()));
   // connect(ui->tuichu, SIGNAL(clicked()), this, SLOT(quit()));





}
cv::Mat qimage_to_mat_cpy(QImage const &img, int format)
{
    return cv::Mat(img.height(), img.width(), format,
                   const_cast<uchar*>(img.bits()),
                   img.bytesPerLine()).clone();
}



QImage mat_to_qimage_cpy(cv::Mat const &mat,
                         QImage::Format format)
{
    return QImage(mat.data, mat.cols, mat.rows,
                  mat.step, format).copy();
}
/******************************
********* 打开摄像头 ***********
*******************************/
void camaraGet::openCamara()
{

    ui->open->hide();
    ui->pic->show();
    ui->closeCam->hide();

    cam = cvCreateCameraCapture(0);//打开摄像头，从摄像头中获取视频


    timer->start(33);              // 开始计时，超时则发出timeout()信号
}

/*********************************
********* 读取摄像头信息 ***********
**********************************/
void camaraGet::readFarme()
{


    frame = cvQueryFrame(cam);// 从摄像头中抓取并返回每一帧
    // 将抓取到的帧，转换为QImage格式。QImage::Format_RGB888不同的摄像头用不同的格式。
    QImage image((const uchar*)frame->imageData, frame->width, frame->height, QImage::Format_RGB888);
   // QImage image = QImage((const uchar*)frame->imageData, frame->width, frame->height, QImage::Format_RGB888).rgbSwapped();

    ui->label->setPixmap(QPixmap::fromImage(image.rgbSwapped()));  // 将图片显示到label上
}

/*************************
********* 拍照 ***********
**************************/
void camaraGet::takingPictures()
{

    ui->open->hide();
    ui->pic->hide();
    ui->closeCam->show();


    frame = cvQueryFrame(cam);// 从摄像头中抓取并返回每一帧

    // 将抓取到的帧，转换为QImage格式。QImage::Format_RGB888不同的摄像头用不同的格式。
    QImage image((const uchar*)frame->imageData, frame->width, frame->height, QImage::Format_RGB888);
    //QImage image = QImage((const uchar*)frame->imageData, frame->width, frame->height, QImage::Format_RGB888).rgbSwapped();
    ui->label_2->setPixmap(QPixmap::fromImage(image.rgbSwapped()));  // 将图片显示到label上

    //string src = "/home/aptx/Desktop/result.jpg";
   // Mat Q2M = qimage_to_mat_cpy(image, CV_8UC3);
  //  imwrite(src, Q2M);
    //cvNamedWindow("vedio");
    CascadeClassifier face_cascade;
    String face_cascade_name = "/root/桌面/Faceproject3/Face_Cut.xml";
    face_cascade.load(face_cascade_name);
    Mat Q2M = qimage_to_mat_cpy(image, CV_8UC3);
    vector<Rect> faces;
    Mat img_gray;

    Py_Initialize();
    cvtColor(Q2M, img_gray, COLOR_BGR2GRAY);
    equalizeHist(img_gray, img_gray);
    face_cascade.detectMultiScale(img_gray, faces, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, Size(10, 10));
    for (size_t i = 0; i < faces.size(); i++){
                    //cout << i;
                    string src = "/root/桌面/result.jpg";//"+ Int_to_String(i)+ "
                    Point rec(faces[i].x, faces[i].y);
                    Point rec2(faces[i].x + faces[i].width, faces[i].y + faces[i].height);
                    Mat roi_img = Q2M(Range(faces[i].y, faces[i].y + faces[i].height), Range(faces[i].x, faces[i].x + faces[i].width));
                    imwrite(src, roi_img);
                    QImage M2Q = mat_to_qimage_cpy(roi_img,QImage::Format_RGB888);
                    ui->label_6->setPixmap(QPixmap::fromImage(M2Q.rgbSwapped()));
                }
    fstream _file;
                _file.open("/root/桌面/result.jpg", ios::in);
                if (_file)
                {
                   // string path = "/root/桌面";
                    //string chdir_cmd = string("sys.path.append(\"") + path + "\")";
                    PyRun_SimpleString("import sys");
                    PyRun_SimpleString("sys.path.append('/root/桌面')");

                    PyObject* moduleName = PyString_FromString("send"); //模块名，不是文件名
                    PyObject* pModule = PyImport_Import(moduleName);

                    PyObject* pv = PyObject_GetAttrString(pModule, "socket_client");

                    PyObject* pRet = PyObject_CallObject(pv,0);
                    char * result;

                    PyArg_Parse(pRet,"s", &result);
                    //cout << *result << endl;
                    string c = result ;
                    cout << endl<< c << endl;
                    ui->label_3->setText(QString::fromStdString(c));
                }
                Py_Finalize();


//    ui->label_2->setPixmap(QPixmap::fromImage(image));  // 将图片显示到label上

}

/*******************************
***关闭摄像头，释放资源，必须释放***
********************************/
void camaraGet::closeCamara()
{
    ui->open->show();
    ui->pic->hide();
    ui->closeCam->hide();

    timer->stop();         // 停止读取数据。

    cvReleaseCapture(&cam);//释放内存；
}

camaraGet::~camaraGet()
{
    delete ui;
}


/*******************************
*************整合****************
********************************/


void camaraGet::mix()
{
   // camaraGet::openCamara();
    camaraGet::takingPictures();
   // camaraGet::closeCamara();
}









