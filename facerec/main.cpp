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
	CascadeClassifier faceCascade; //����������
	cout << "ѡ����:" << endl;
	cout << "    1:¼������" << endl;
	cout << "    2:ʶ������" << endl;
	cout << "    3:��  ��\n" << endl;

	while (k == 0) {
		cout << "�����빦�ܱ��:";
		cin >> flag;
		cin.clear();    //���������cin.clear(istream::failbit); �ǲ��е�
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); //���������
		switch (flag){
		case('1'):detect(); trainFace(); getchar(); k = 1; break;
			case('2'):faceRec(); k = 1; break;
			case('3'):exit(1); k = 1; break;
			default: cout << "������������������!"; break;
		}
	}
	//getchar();
	//trainFace();
	//faceRec();
	//getchar();
}