//#include <opencv2/opencv.hpp>  
//#include <opencv2/face/facerec.hpp>
//#include <iostream>  
//#include <fstream>  
//#include <sstream>  
//#include <math.h>  
//#include "csv.h"
//
//using namespace cv;
//using namespace std;
//using namespace face;
//
///*
//static Mat norm_0_255(InputArray _src) {
//	Mat src = _src.getMat();
//	// 创建和返回一个归一化后的图像矩阵:  
//	Mat dst;
//	switch (src.channels()) {
//	case1:
//		cv::normalize(_src, dst, 0, 255, NORM_MINMAX, CV_8UC1);
//		break;
//	case3:
//		cv::normalize(_src, dst, 0, 255, NORM_MINMAX, CV_8UC3);
//		break;
//	default:
//		src.copyTo(dst);
//		break;
//	}
//	return dst;
//}
//*/
//
//int main()
//{
//	//读取你的CSV文件路径.  
//	string csv_addr = ".\\train\\faces.csv";
//	// 2个容器来存放图像数据和对应的标签  
//	vector<Mat> images;
//	vector<int> labels;
//	// 读取数据. 如果文件不合法就会出错  
//	// 输入的文件名已经有了.  
//	try
//	{
//		read_csv(csv_addr, images, labels);
//	}
//	catch (cv::Exception& e)
//	{
//		cerr << "Error opening file \"" << csv_addr << "\". Reason: " << e.msg << endl;
//		// 文件有问题，我们啥也做不了了，退出了  
//		exit(1);
//	}
//	// 如果没有读取到足够图片，也退出.  
//	if (images.size() <= 1) {
//		string error_message = "This demo needs at least 2 images to work. Please add more images to your data set!";
//		CV_Error(CV_StsError, error_message);
//	}
//	// 下面的几行代码仅仅是从你的数据集中移除最后一张图片  
//	//[gm:自然这里需要根据自己的需要修改，他这里简化了很多问题]  
//	Mat testSample = images[images.size() - 1];
//	int testLabel = labels[labels.size() - 1];
//	images.pop_back();
//	labels.pop_back();
//	// 下面几行创建了一个特征脸模型用于人脸识别，  
//	// 通过CSV文件读取的图像和标签训练它。  
//	// T这里是一个完整的PCA变换  
//	//如果你只想保留10个主成分，使用如下代码  
//	//      cv::createEigenFaceRecognizer(10);  
//	// 如果你还希望使用置信度阈值来初始化，使用以下语句：  
//	//      cv::createEigenFaceRecognizer(10, 123.0);  
//	// 如果你使用所有特征并且使用一个阈值，使用以下语句：  
//	//      cv::createEigenFaceRecognizer(0, 123.0);  
//
//	Ptr<FaceRecognizer> model = createEigenFaceRecognizer();
//	model->train(images, labels);
//	model->save("./train/facesModel.xml");
//
//	// 下面对测试图像进行预测，predictedLabel是预测标签结果  
//	int predictedLabel = model->predict(testSample);
//
//	// 还有一种调用方式，可以获取结果同时得到阈值:  
//	//      int predictedLabel = -1;  
//	//      double confidence = 0.0;  
//	//      model->predict(testSample, predictedLabel, confidence);  
//
//	string result_message = format("Predicted class = %d / Actual class = %d.", predictedLabel, testLabel);
//	cout << result_message << endl;
//
//	getchar();
//	return 0;
//}