#include "train.h"
#include "csv.h"

Train::Train()
{
	path = FACES_PIC_DIR;
	csv_addr = CSV_FILE;
}


int Train::facetoCsv() {
	vector<string> cates = dir(path); //�����ļ�Ŀ¼·������./pic/1; ./pic/2����
	vector<string> images;
	//ͼƬID  
	vector<int> labels;
	if ((int)cates.size() > 0) {
		for (int i = 0; i<(int)cates.size(); i++)
		{
			//��ȡ�����Ե�ַ  
			string cate_dir = cates[i];
			//��ȡͼƬ  
			vector<string> imgs = dir(cate_dir); 
			for (int j = 0; j<(int)imgs.size(); j++)
			{
				string img_dir = imgs[j];
				images.push_back(img_dir);//����������ͼƬ�ļ�����images
				labels.push_back(i); //����ID  ע��˴�������++i����i++
			}
		}
		if (!write_csv(images, labels, csv_addr.c_str())) {
			return 0; //csvд��ʧ��
		};
		return 1;//д��ɹ�
	}
	return -1; //Ŀ¼����û�������ļ�
}

void Train::trainFace()
{
	// 2�����������ͼ�����ݺͶ�Ӧ�ı�ǩ  
	vector<Mat> images;
	vector<int> labels;
	// ��ȡ����. ����ļ����Ϸ��ͻ����  
	// ������ļ����Ѿ�����.  
	try
	{
		read_csv(csv_addr, images, labels);
	}
	catch (cv::Exception& e)
	{
		cerr << "Error opening file \"" << csv_addr << "\". Reason: " << e.msg << endl;
		// �ļ������⣬����ɶҲ�������ˣ��˳���  
		//exit(1);
	}
	// ���û�ж�ȡ���㹻ͼƬ��Ҳ�˳�.  
	if (images.size() <= 1) {
		string error_message = "ͼƬ̫�٣�����Ӹ���������ѵ��!";
		CV_Error(CV_StsError, error_message);
		//exit(1);
	}
	model = RECOGNIZE;  //����ʶ���㷨����config.h�������������㷨�����Ը��������޸ģ�
	model->train(images, labels);  //ѵ������
	model->save(TRAINMODEL_FILE);  //����ģ�ͣ�ʶ��ʱ���ظ�ģ��
}

void Train::run()
{
	facetoCsv();
	trainFace();
}