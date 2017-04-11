#pragma once
#include <opencv2/opencv.hpp>
#include <opencv2/face/facerec.hpp>
#include <iostream>

using namespace cv;
using namespace std;

//CascadeClassifier faceCascade; //����������

Mat toGrayImg(Mat img) {
	Mat imgGray;//�Ҷ�ͼ��
	if (img.channels() == 3){   //��ɫͼ����3ͨ����RGB��,�Ҷ�ͼ���ǵ�ͨ��
		cvtColor(img, imgGray, CV_RGB2GRAY);
		return imgGray;
	}else {
		return img;
	}
}

//�������
vector<Rect> markFace(Mat img) {
	Mat imgGray;
	vector<Rect> faces;  //��������ͼ������
	imgGray = toGrayImg(img);
	faceCascade.load("./haar/haarcascade_frontalface_alt.xml");   //���ط�������������������������������  
	faceCascade.detectMultiScale(imgGray, faces, 1.2, 6, 0, Size(0, 0));   //������� ������������Լ��ڲ����˽�� 
	if (faces.size()>0) {
		for (int i = 0; i < faces.size(); i++) //����������ж�����������ѭ���þ��α��ÿ���������������ֻ��һ��������������û��Χ����Ļ���
		{
			rectangle(img, Point(faces[i].x, faces[i].y), Point(faces[i].x + faces[i].width, faces[i].y + faces[i].height), Scalar(0, 255, 0), 3, 8);    //�������λ��  
		}
	}
	return faces;
}

//ʶ��
void faceRec() {
	char key = 0;
	Mat imgGray,frame,myFace;
	vector<Rect> faces;
	Ptr<face::FaceRecognizer> model = face::createEigenFaceRecognizer();
	model->load("./train/facesModel.xml");//����ѵ���õ�ģ��
	int predictedLabel = -1;  //Ԥ��label
	double confidence = 0.0;  //����ֵ
	namedWindow("frame"); //��������ͷ����
	VideoCapture cap(0);  //��������ͷ
	if (!cap.isOpened()) {
		cout << "����ͷδ׼������\n";
		exit(1);
	}
	while (key != 'q')  //ѭ��  ���δ����q�� һֱѭ�� ������q�����˳�����
	{
		cap >> frame;  //��ȡ����ͷһ֡ͼ��
		flip(frame, frame, 1);//����תͼ��
		if (frame.empty()) {
			cout << "û������ͷͼ�񡭡�\n";
			break;
		}
		faces = markFace(frame);
		imshow("frame", frame);  //��ʾͼ��
		if (faces.size() > 0) {
			imgGray = toGrayImg(frame);
			resize(imgGray(faces[0]), myFace, Size(92, 112)); //ͼ���ʽ��
			model->predict(myFace, predictedLabel, confidence);
			cout << "Ԥ��label:" << predictedLabel << "  " << "����ֵ:" << confidence << endl;
		}
		key = waitKey(20);  //�ȴ�100ms ���������� ѭ����ȡ��Ƶ֡
	}
	destroyAllWindows(); //����p�� �������д���
	cap.release();  //�ͷ�����ͷ
}
