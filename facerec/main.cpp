#include <iostream>
#include <opencv2/opencv.hpp>
#include <io.h>
#include <stdlib.h>
#include <direct.h>
#include "csv.h"

using namespace cv;
using namespace std;

CascadeClassifier faceCascade; //����������
int flag = 0; //0:�ռ�����  1:���������ļ� д��csv�ļ�

//��������������ռ�
void detect() {
	faceCascade.load("./haar/haarcascade_frontalface_alt.xml");   //���ط�������������������������������  
	Mat frame;  //��ʼ������ͷԭͼ��
	Mat imgGray;  //�����Ҷ�ͼ��
	Mat Myface; //��������Ե�����
	vector<Rect> faces;  //��������ͼ������
	string name; //��������
	int i = 1;
	char key = 0; //���̰��µļ�
	namedWindow("frame"); //��������ͷ����
	VideoCapture cap(0);  //��������ͷ
	if (!cap.isOpened()) {
		cout << "����ͷδ׼������\n";
		exit(1);
	}
	cout << "�������û�����Enter������:";
	getline(cin, name);
	string dirname_str = format("./pic/%s", name);
	judgefile(dirname_str); //�ж��ļ��Ƿ���� �������򴴽�
	while (key != 'q')  //ѭ��  ���δ����q�� һֱѭ�� ������q�����˳�����
	{
		cap >> frame;  //��ȡ����ͷһ֡ͼ��
		flip(frame, frame, 1);//����תͼ��
		if (frame.empty()) {
			cout << "û������ͷͼ�񡭡�\n";
			break;
		}
		if (frame.channels() == 3)  //��ɫͼ����3ͨ����RGB��,�Ҷ�ͼ���ǵ�ͨ��
		{                           //����� 3ͨ���Ĳ�ɫͼ��Ҳ��������ͷ��ȡ��ԭͼ����תΪ�Ҷ�
			cvtColor(frame, imgGray, CV_RGB2GRAY);
		}
		else
		{
			imgGray = frame;
		}
		faceCascade.detectMultiScale(imgGray, faces, 1.2, 6, 0, Size(0, 0));   //������� ������������Լ��ڲ����˽�� 
		if (faces.size() > 0) //faces.size()��ʾ��⵽��������
		{
			for (int i = 0; i < faces.size(); i++) //����������ж�����������ѭ���þ��α��ÿ���������������ֻ��һ��������������û��Χ����Ļ���
			{
				rectangle(frame, Point(faces[i].x, faces[i].y), Point(faces[i].x + faces[i].width, faces[i].y + faces[i].height), Scalar(0, 255, 0), 3, 8);    //�������λ��  
			}
		}
		imshow("frame", frame);  //��ʾͼ��
		string filename = dirname_str + format("/%d.jpg", i); //pic ͼ���ļ������ʽ
		switch (key)
		{
		case'p':            //����p  ������
			if (faces.size() > 0) {
				cout << "���գ�" << i << endl;  //�ն���ʾ������
				i++;
				resize(imgGray(faces[0]), Myface, Size(92, 112)); //ͼ���ʽ��
				//equalizeHist(Myface,Myface);//����ֱ��ͼ
				imwrite(filename, Myface);  //����ͼ��Myyface��ʾ�ĵ��ĸ�ʽ������������������ͷ��ͼƬ��ֻ�Ǿ��ο�򴦵��������Ҷȣ�������������
			}
			else {
				cout << "û�м�⵽����" << endl;
			}
			break;
		default:
			break;
		}
		key = waitKey(100);  //�ȴ�100ms ���������� ѭ����ȡ��Ƶ֡
	}
	destroyAllWindows(); //����p�� �������д���
	cap.release();  //�ͷ�����ͷ
}
 //������
int main() {
	if (flag == 0) {
		detect();
	}
	else{
		trainFile();
	}
	}

