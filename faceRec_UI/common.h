#pragma once
#include <iostream>  
#include <string>  
#include <direct.h>
#include <io.h>

using namespace std;

/*
�����ļ���
*/
bool traverseFiles(string path)
{
	_finddata_t file_info;
	string current_path = path + "/*.*"; 
	int handle = _findfirst(current_path.c_str(), &file_info);
	//����ֵΪ-1�����ʧ��  
	if (-1 == handle)
		return false;
	do
	{
		//�ж��Ƿ���Ŀ¼  
		string attribute;
		if (file_info.attrib == _A_SUBDIR) //��Ŀ¼  
		{

		}
		else //�ļ�
		{

		}
		//cout << file_info.name << ' ' << file_info.time_write << ' ' << file_info.size << ' ' << attribute << endl; //��õ�����޸�ʱ����time_t��ʽ�ĳ����ͣ���Ҫ����������ת������ʱ����ʾ  
	} while (!_findnext(handle, &file_info));  //����0�������  
 //�ر��ļ����  
	_findclose(handle);
	return true;
}

/*
�ж��ļ��Ƿ���� �������򴴽� �����򸲸�
*/
bool judgefile(string dirname_str) {
	const char* dirname = dirname_str.c_str(); //�ַ�������
	//char c;
	if (_access(dirname, 0)!=0 && _mkdir(dirname)==-1) {  //Ŀ¼�������򴴽���0:���� -1:�����ڣ�
		//if (_mkdir(dirname) == -1) { //����ʧ�����˳� ��0:�ɹ� -1:ʧ�ܣ�
		//	cout << "�ļ�Ŀ¼����ʧ�ܣ�" << endl;
		//	exit(1);
		//}
		//else {
		//	cout << dirname << "Ŀ¼�����ɹ�!" << endl;
		//}
		return false;
	}
	return true;
	//else
	//{
	//	cout << "\n" << dirname << "Ŀ¼�Ѹ���!" << endl;
	//}
}


int getResLabel(int (&recRse)[200])
{
	int num = sizeof(recRse);
	int max_num = 0; //��¼���ֵ����Сֵ���±꣬��ʼֵ��0
	for (int i = 0; i < sizeof(recRse) / sizeof(recRse[0]); i++)
	{
		if (recRse[i] >= 10)
		{
			max_num = i;
			break;
		}
		if (recRse[i] > recRse[max_num]) //��ǰ���������ֵ��
			max_num = i;
	}
	return max_num;
}