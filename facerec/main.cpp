#include<iostream>
//#include <fstream>
//#include <direct.h>
//#include <io.h>
#include "train.h";
#include "recognize.h";

using namespace std;


int main() {
	char flag;
	int k = 0;
	CascadeClassifier faceCascade; //声明分类器
	cout << "选择功能:" << endl;
	cout << "    1:录入人脸" << endl;
	cout << "    2:识别人脸" << endl;
	cout << "    3:退  出\n" << endl;

	while (k == 0) {
		cout << "请输入功能编号:";
		cin >> flag;
		cin.clear();    //这里如果用cin.clear(istream::failbit); 是不行的
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); //清空输入流
		switch (flag){
		case('1'):detect(); trainFace(); getchar(); k = 1; break;
			case('2'):faceRec(); k = 1; break;
			case('3'):exit(1); k = 1; break;
			default: cout << "输入有误，请重新输入!"; break;
		}
	}
	//getchar();
	//trainFace();
	//faceRec();
	//getchar();
}