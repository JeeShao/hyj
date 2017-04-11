#pragma once
#include <opencv2/opencv.hpp>
#include <opencv2/face/facerec.hpp>
#include <iostream>

using namespace cv;
using namespace std;

//CascadeClassifier faceCascade; //声明分类器

Mat toGrayImg(Mat img) {
	Mat imgGray;//灰度图形
	if (img.channels() == 3){   //彩色图像是3通道（RGB）,灰度图像是单通道
		cvtColor(img, imgGray, CV_RGB2GRAY);
		return imgGray;
	}else {
		return img;
	}
}

//标记人脸
vector<Rect> markFace(Mat img) {
	Mat imgGray;
	vector<Rect> faces;  //声明人脸图像容器
	imgGray = toGrayImg(img);
	faceCascade.load("./haar/haarcascade_frontalface_alt.xml");   //加载分类器，这个分类器是用来检测人脸的  
	faceCascade.detectMultiScale(imgGray, faces, 1.2, 6, 0, Size(0, 0));   //检测人脸 ，这个函数你自己在博客了解过 
	if (faces.size()>0) {
		for (int i = 0; i < faces.size(); i++) //这里是如果有多张人脸，则循环用矩形标出每个人脸，正常情况只有一个人脸（如果你姐没有围观你的话）
		{
			rectangle(img, Point(faces[i].x, faces[i].y), Point(faces[i].x + faces[i].width, faces[i].y + faces[i].height), Scalar(0, 255, 0), 3, 8);    //框出人脸位置  
		}
	}
	return faces;
}

//识别
void faceRec() {
	char key = 0;
	Mat imgGray,frame,myFace;
	vector<Rect> faces;
	Ptr<face::FaceRecognizer> model = face::createEigenFaceRecognizer();
	model->load("./train/facesModel.xml");//加载训练好的模型
	int predictedLabel = -1;  //预测label
	double confidence = 0.0;  //置信值
	namedWindow("frame"); //声明摄像头窗口
	VideoCapture cap(0);  //调用摄像头
	if (!cap.isOpened()) {
		cout << "摄像头未准备……\n";
		exit(1);
	}
	while (key != 'q')  //循环  如果未按下q键 一直循环 ；按下q键则退出程序
	{
		cap >> frame;  //获取摄像头一帧图像
		flip(frame, frame, 1);//镜像翻转图像
		if (frame.empty()) {
			cout << "没有摄像头图像……\n";
			break;
		}
		faces = markFace(frame);
		imshow("frame", frame);  //显示图像
		if (faces.size() > 0) {
			imgGray = toGrayImg(frame);
			resize(imgGray(faces[0]), myFace, Size(92, 112)); //图像格式化
			model->predict(myFace, predictedLabel, confidence);
			cout << "预测label:" << predictedLabel << "  " << "置信值:" << confidence << endl;
		}
		key = waitKey(20);  //等待100ms 检测键盘输入 循环获取视频帧
	}
	destroyAllWindows(); //按下p后 销毁所有窗口
	cap.release();  //释放摄像头
}
