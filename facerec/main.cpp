#include <iostream>
#include <opencv2/opencv.hpp>
#include <io.h>
#include <stdlib.h>
#include <direct.h>
#include "csv.h"

using namespace cv;
using namespace std;

CascadeClassifier faceCascade; //声明分类器
int flag = 0; //0:收集人脸  1:处理人脸文件 写入csv文件

//检测人脸并拍照收集
void detect() {
	faceCascade.load("./haar/haarcascade_frontalface_alt.xml");   //加载分类器，这个分类器是用来检测人脸的  
	Mat frame;  //初始化摄像头原图像
	Mat imgGray;  //声明灰度图像
	Mat Myface; //声明保存对的人脸
	vector<Rect> faces;  //声明人脸图像容器
	string name; //人脸名字
	int i = 1;
	char key = 0; //键盘按下的键
	namedWindow("frame"); //声明摄像头窗口
	VideoCapture cap(0);  //调用摄像头
	if (!cap.isOpened()) {
		cout << "摄像头未准备……\n";
		exit(1);
	}
	cout << "请输入用户名（Enter结束）:";
	getline(cin, name);
	string dirname_str = format("./pic/%s", name);
	judgefile(dirname_str); //判断文件是否存在 不存在则创建
	while (key != 'q')  //循环  如果未按下q键 一直循环 ；按下q键则退出程序
	{
		cap >> frame;  //获取摄像头一帧图像
		flip(frame, frame, 1);//镜像翻转图像
		if (frame.empty()) {
			cout << "没有摄像头图像……\n";
			break;
		}
		if (frame.channels() == 3)  //彩色图像是3通道（RGB）,灰度图像是单通道
		{                           //如果是 3通道的彩色图像（也就是摄像头获取的原图像）则转为灰度
			cvtColor(frame, imgGray, CV_RGB2GRAY);
		}
		else
		{
			imgGray = frame;
		}
		faceCascade.detectMultiScale(imgGray, faces, 1.2, 6, 0, Size(0, 0));   //检测人脸 ，这个函数你自己在博客了解过 
		if (faces.size() > 0) //faces.size()表示检测到的人脸数
		{
			for (int i = 0; i < faces.size(); i++) //这里是如果有多张人脸，则循环用矩形标出每个人脸，正常情况只有一个人脸（如果你姐没有围观你的话）
			{
				rectangle(frame, Point(faces[i].x, faces[i].y), Point(faces[i].x + faces[i].width, faces[i].y + faces[i].height), Scalar(0, 255, 0), 3, 8);    //框出人脸位置  
			}
		}
		imshow("frame", frame);  //显示图像
		string filename = dirname_str + format("/%d.jpg", i); //pic 图像文件处理格式
		switch (key)
		{
		case'p':            //按下p  则拍照
			if (faces.size() > 0) {
				cout << "拍照：" << i << endl;  //终端显示拍照数
				i++;
				resize(imgGray(faces[0]), Myface, Size(92, 112)); //图像格式化
				//equalizeHist(Myface,Myface);//均衡直方图
				imwrite(filename, Myface);  //保存图像，Myyface表示拍到的格式化的人脸（不是摄像头的图片，只是矩形框框处的人脸（灰度）），保存人脸
			}
			else {
				cout << "没有检测到人脸" << endl;
			}
			break;
		default:
			break;
		}
		key = waitKey(100);  //等待100ms 检测键盘输入 循环获取视频帧
	}
	destroyAllWindows(); //按下p后 销毁所有窗口
	cap.release();  //释放摄像头
}
 //主程序
int main() {
	if (flag == 0) {
		detect();
	}
	else{
		trainFile();
	}
	}

