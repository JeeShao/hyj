#pragma once
#include <opencv2/opencv.hpp>
#include <QtWidgets/QMainWindow>
using namespace cv;

class Video
{
public:
	Mat frame; //cvͼ��
	Mat currentFrame;
	QImage image; //Qtͼ��
	VideoCapture capture;//����ͷ
public:
	Video();
	~Video();
public:
	Mat getCVImage();
	void captureNextFrame();
	QImage getQImageFrame();
	Mat getGrayCVImage();
	QImage Mat2QImage(Mat cvImg);
	QImage mat2QImage(Mat mat);


private:
	Mat read();
};

