#pragma once
#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <io.h>
#include <stdlib.h>
#include <direct.h>
#include <ctime>
#include "config.h"

using namespace cv;
using namespace std;

void judgefile(string dirname_str) {
	const char* dirname = dirname_str.c_str(); //�ַ�������
	char c;
	if (_access(dirname, 0) != 0) {  //Ŀ¼�������򴴽���0:���� -1:�����ڣ�
			if (_mkdir(dirname) == -1) { //����ʧ�����˳� ��0:�ɹ� -1:ʧ�ܣ�
				cout << "�ļ�Ŀ¼����ʧ�ܣ�" << endl;
				exit(1);
			}
			else {
				cout << dirname << "Ŀ¼�����ɹ�!" << endl;
			}
	}
	else
	{
		cout <<"\n"<<dirname<< "Ŀ¼�Ѹ���!"<<endl;
	}
}


//��ȡ�����ļ�·��(����pic������ļ�)
vector<string> dir(string path)
{
	vector<string> files;//����ļ���
	long hFile = 0;
	struct _finddata_t fileInfo;
	string pathName, subDir, filePath;
	if ((hFile = _findfirst(pathName.assign(path).append("\\*").c_str(), &fileInfo)) == -1) {
		cout << "ľ���ļ�" << endl;
	}
	do
	{
		if (strcmp(fileInfo.name, ".") != 0 && strcmp(fileInfo.name, "..") != 0) {
			subDir = pathName.substr(0, pathName.length() - 1).append(fileInfo.name);
			//dir(subDir);
			filePath = pathName.substr(0, pathName.length() - 1);
			files.push_back(filePath.append(fileInfo.name));
			filePath.clear();
		}
		/*else
		{
		filePath = pathName.substr(0, pathName.length() - 1);
		files.push_back(filePath.append(fileInfo.name));
		cout << "�ļ���" <<files.capacity() << endl;
		filePath.clear();
		}*/
	} while (_findnext(hFile, &fileInfo) == 0);
	_findclose(hFile);
	/*for (int i = 0; i < files.size(); i++) {
		cout << files[i] << endl;  
	}*/
	return files;
}

//д��csv
bool write_csv(const vector<string> images, const vector<int> labels, const char *addr, char separator = ';')
{
	ofstream fout(addr);
	if (!fout.is_open())
	{
		cout << addr << " �޷��� " << endl;
		return false;
	}
	for (int i = 0; i<(int)images.size(); i++)
	{
		fout << images[i];  //�������ļ�·��д��csv
		fout << separator;  //�ָ���;
		fout << labels[i] << endl; //���������д��csv
	}
	fout.close();
	return true;
}



//ʹ��CSV�ļ�ȥ��ͼ��ͱ�ǩ����Ҫʹ��stringstream��getline����  
static void read_csv(const string& csv_addr, vector<Mat>& images, vector<int>& labels, char separator = ';') {
	string str;
	std::ifstream file(csv_addr.c_str(), ifstream::in);
	if (!file) {
		string error_message = "No valid input file was given, please check the given filename.";
		CV_Error(CV_StsBadArg, error_message);
	}
	string line, path, label;
	while (getline(file, line)) {
		stringstream liness(line);
		getline(liness, path, separator);
		getline(liness, label);
		if (!path.empty() && !label.empty()) {
			//try {
			images.push_back(imread(path, 0));
			labels.push_back(atoi(label.c_str()));
			//}
			//catch (cv::Exception& e)
			//{
			//	cerr << "�ļ�������:"<< path <<"\n"<< e.msg << endl;
			//	// �ļ������⣬����ɶҲ�������ˣ��˳���  
			//	exit(1);
			//}
		}
		
	}
}



//��ȡ����ͼƬ������csv�ļ�
int trainFile() {
	string path = FACES_PIC_DIR;
	string csv_addr = CSV_FILE;
	vector<string> cates = dir(path); //�����ļ�Ŀ¼·������./pic/1; ./pic/2����
	vector<string> images;
	//ͼƬID  
	vector<int> labels;
	for (int i = 0; i<(int)cates.size(); i++)
	{
		//��ȡ�����Ե�ַ  
		string cate_dir = cates[i];
		//��ȡͼƬ  
		vector<string> imgs = dir(cate_dir);
		//�ж�ͼƬ�Ƿ����  
		if ((int)imgs.size() == 0)
		{
			cout << cate_dir << "����ľ��ͼƬ" << endl;
			getchar();
			exit(1);
		}

		//���þ��Ե�ַ  
		for (int j = 0; j<(int)imgs.size(); j++)
		{
			string img_dir =  imgs[j];
			images.push_back(img_dir);//����������ͼƬ�ļ�����images
			labels.push_back(i); //����ID  ע��˴�������++i����i++
		}
	}
	time_t start = clock();
	//����csv�ļ�  
	if (!write_csv(images, labels, csv_addr.c_str())) {
		cout << "csv�ļ�д��ʧ��!";
			getchar();
			exit(1);
	};
	time_t end = clock();
	double time = (double)(end - start) / CLOCKS_PER_SEC; //���㺯��ʹ��ʱ�䣬�����  
	cout << "csv�ļ�д���ʱ: " << time << " s" << endl;
	return 0;
}