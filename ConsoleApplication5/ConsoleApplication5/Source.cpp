#ifdef _DEBUG
//Debug���[�h�̏ꍇ
#pragma comment(lib,"C:\\opencv\\build\\x86\\vc12\\lib\\opencv_core249d.lib")
#pragma comment(lib,"C:\\opencv\\build\\x86\\vc12\\lib\\opencv_imgproc249d.lib")
#pragma comment(lib,"C:\\opencv\\build\\x86\\vc12\\lib\\opencv_highgui249d.lib")
#pragma comment(lib,"C:\\opencv\\build\\x86\\vc12\\lib\\opencv_objdetect249d.lib")
#pragma comment(lib,"C:\\opencv\\build\\x86\\vc12\\lib\\opencv_contrib249d.lib")
#pragma comment(lib,"C:\\opencv\\build\\x86\\vc12\\lib\\opencv_features2d249d.lib")
#pragma comment(lib,"C:\\opencv\\build\\x86\\vc12\\lib\\opencv_flann249d.lib")
#pragma comment(lib,"C:\\opencv\\build\\x86\\vc12\\lib\\opencv_gpu249d.lib")
//#pragma comment(lib,"C:\\opencv\\build\\x86\\vc12\\lib\\opencv_haartraining_engined.lib")
#pragma comment(lib,"C:\\opencv\\build\\x86\\vc12\\lib\\opencv_legacy249d.lib")
#pragma comment(lib,"C:\\opencv\\build\\x86\\vc12\\lib\\opencv_ts249d.lib")
#pragma comment(lib,"C:\\opencv\\build\\x86\\vc12\\lib\\opencv_video249d.lib")
#pragma comment(lib,"C:\\opencv\\build\\x86\\vc12\\lib\\opencv_nonfree249d.lib")
#else
//Release���[�h�̏ꍇ
#pragma comment(lib,"C:\\opencv\\build\\x86\\vc12\\lib\\opencv_core249.lib")
#pragma comment(lib,"C:\\opencv\\build\\x86\\vc12\\lib\\opencv_imgproc249.lib")
#pragma comment(lib,"C:\\opencv\\build\\x86\\vc12\\lib\\opencv_highgui249.lib")
#pragma comment(lib,"C:\\opencv\\build\\x86\\vc12\\lib\\opencv_objdetect249.lib")
#pragma comment(lib,"C:\\opencv\\build\\x86\\vc12\\lib\\opencv_contrib249.lib")
#pragma comment(lib,"C:\\opencv\\build\\x86\\vc12\\lib\\opencv_features2d249.lib")
#pragma comment(lib,"C:\\opencv\\build\\x86\\vc12\\lib\\opencv_flann249.lib")
#pragma comment(lib,"C:\\opencv\\build\\x86\\vc12\\lib\\opencv_gpu249.lib")
#pragma comment(lib,"C:\\opencv\\build\\x86\\vc12\\lib\\opencv_haartraining_engined.lib")
#pragma comment(lib,"C:\\opencv\\build\\x86\\vc12\\lib\\opencv_legacy249.lib")
#pragma comment(lib,"C:\\opencv\\build\\x86\\vc12\\lib\\opencv_ts249.lib")
#pragma comment(lib,"C:\\opencv\\build\\x86\\vc12\\lib\\opencv_video249.lib")
#endif

#include <time.h>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <fstream>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/nonfree/features2d.hpp>
#include <opencv2/nonfree/nonfree.hpp>
#include <vector>
#include <opencv2/opencv_lib.hpp>
#include <typeinfo>
#include <string>
#include <cstdlib>

//���O��Ԃ̎w��
using namespace cv;
using namespace std;

const int DIM = 64;
const int MAX_CLASTER = 500;

class serch_img//�|�C���^���܂�ł��Ȃ����炽�Ԃ�ǂ��ł��g����d�l�ɂȂ��Ă���͂��B
{
public:
	Mat img;//�o�͉摜��ۑ����邽�߂�Mat�^�ϐ�
	vector<KeyPoint> keypoints;//�����_��ۑ����邽�߂̕ϐ�
	Mat descriptors;//�����ʂ�ۑ����Ă���
	string path;//�t�@�C���p�X
	string name;//�摜��
	void output_txt();//�e�L�X�g�t�@�C���ɏo�͂��邽�߂̊֐�
	void show_window();//�摜���o�����߂̊֐�
	void output_txt(string str);//�e�L�X�g�t�@�C���ɏo�͂��邽�߂̊֐��{�t�H���_�o�͂ɑΉ��B
};

//�֐��v���g�^�C�v�錾
serch_img SURFDECT(serch_img test);
void m_serch(string dirname, vector<float>&data);
void data2txt(vector<float>data, string str);
float most_dict_serch(int i, Mat q_data, Mat database);
Mat change_data(vector<float>&data);
void class_judge();
void test_judge();

//�O���[�o���ϐ��̐錾�B�ς����ق�������
vector<float>airplanes_data;
vector<float>camera_data;
vector<float>car_side_data;
vector<float>chair_data;
vector<float>cup_data;
vector<float>pizza_data;
vector<float>watch_data;
vector<float>all_dict;
Mat airplanes_mat;
Mat camera_mat;
Mat car_side_mat;
Mat chair_mat;
Mat cup_mat;
Mat pizza_mat;
Mat watch_mat;

int main()
{
	clock_t start = clock();
	
	


	//�T���֐�
	m_serch("airplanes", airplanes_data);
	//�����Ńf�[�^���e�L�X�g�t�@�C���ɏo�͂���B
	data2txt(airplanes_data, "airplanes");
	//Mat�ɕϊ�����
	airplanes_mat = change_data(airplanes_data);
	cout << airplanes_mat.size() << endl;
	m_serch("camera", camera_data);
	data2txt(camera_data, "camera");
	camera_mat = change_data(camera_data);
	cout << camera_mat.size() << endl;


	m_serch("car_side", car_side_data);
	data2txt(car_side_data, "car_side");
	car_side_mat = change_data(car_side_data);
	cout << car_side_mat.size() << endl;

	m_serch("chair", chair_data);
	data2txt(chair_data, "chair");
	chair_mat = change_data(chair_data);
	cout << chair_mat.size() << endl;

	m_serch("cup", cup_data);
	data2txt(cup_data, "cup");
	cup_mat = change_data(cup_data);
	cout << cup_mat.size() << endl;
	/*
	m_serch("pizza", pizza_data);
	data2txt(pizza_data, "pizza");
	pizza_mat = change_data(pizza_data);
	cout << pizza_mat.size() << endl;
	*/
	m_serch("watch", watch_data);
	data2txt(watch_data, "watch");
	watch_mat = change_data(watch_data);
	cout << watch_mat.size() << endl;
	test_judge();

	
	
	return 0;
}


//�����_���o�p�֐�
serch_img SURFDECT(serch_img test)
{




	initModule_nonfree();
	test.img = imread(test.path);
	if (test.img.empty()){
		cout << "couldn't read the image." << endl;

	}


	cv::Mat gray_img;
	cv::cvtColor(test.img, gray_img, CV_BGR2GRAY);
	cv::normalize(gray_img, gray_img, 0, 255, cv::NORM_MINMAX);


	std::vector<cv::KeyPoint>::iterator itk;

	// SURF ���o��Ɋ�Â������_���o
	// hessianThreshold=4500, 
	cv::SurfFeatureDetector detector(4500);
	cv::Scalar color(100, 255, 50);
	detector.detect(gray_img, test.keypoints);
	// SURF �Ɋ�Â��f�B�X�N���v�^���o��
	cv::SurfDescriptorExtractor extractor;

	extractor.compute(gray_img, test.keypoints, test.descriptors);
	for (itk = test.keypoints.begin(); itk != test.keypoints.end(); ++itk) {
		cv::circle(test.img, itk->pt, 1, color, -1);

	}







	return test;
}

//�E�B���h���o��������֐��B
void serch_img::show_window()
{
	cv::namedWindow(name, CV_WINDOW_AUTOSIZE | CV_WINDOW_FREERATIO);
	cv::imshow(name, img);
}

//�S�T���f�[�^��Ԃ��֐�
void m_serch(string dirname, vector<float>&data)
{


	serch_img test;
	int i = 1;


	while (100)
	{
		string temp = to_string(i);
		//�������쐬�����A�ԃt�@�C���ǂݍ��݁B�����̂悢�ǂݍ��ݕ��͂���񂶂�Ȃ����ȁB
		if (i <= 9)
		{
			test.path = "C:\\datebase\\" + dirname + "\\image_00";

			test.path += temp + ".jpg";
		}
		else if (i <= 99 && i >= 10)
		{
			test.path = "C:\\datebase\\" + dirname + "\\image_0";
			test.path += temp + ".jpg";
		}
		else if (i <= 999 && i >= 100)
		{
			test.path = "C:\\datebase\\" + dirname + "\\image_";
			test.path += temp + ".jpg";
		}




		test.img = imread(test.path);
		if (test.img.empty())
		{
			cout << dirname << "�N���X�͍��v" << i - 1 << "������܂����B" << endl;
			break;
		}


		test.name = dirname + temp;
		test = SURFDECT(test);

		Mat_<float>::const_iterator cit = test.descriptors.begin<float>();
		for (; cit != test.descriptors.end<float>(); cit++)
			data.push_back(*cit);

		i++;
	}



}

//�ꎟ���f�[�^������������~�����_�̌��̍s��ɒ���
Mat change_data(vector<float>&data)
{
	CvMat samp;
	int rows = data.size() / DIM;  // CvMat�̍s���i=DIM���������x�N�g���̖{���j
	cvInitMatHeader(&samp, rows, DIM, CV_32FC1, &data[0]);
	Mat sample(&samp);
	return sample;
}

void data2txt(vector<float>data,string str)
{
	ofstream ofs(str+".txt");
	


	for (vector<float>::iterator itk = data.begin(); itk != data.end(); itk++)
		ofs << *itk << endl;

}

float most_dict_serch(int i, Mat q_data, Mat database)
{
	vector<float> sdistnce;
	for (int qy = 0; qy < q_data.rows; qy++)
	{
		vector<float> E_distance;//�e�v�f�̃��[�N���b�h������ۑ�����B
		//���̃��[�v�ōŏ��̃��[�N���b�h�����̓����_�𔭌�����
		for (int dy = 0; dy < database.rows;dy++)
		{
			Mat qA = q_data.row(qy);
			Mat dA = database.row(dy);
			Mat X(1, DIM, CV_32F, Scalar(0));
			X = qA - dA;
			float t_distance = 0;
			Mat_<float>::const_iterator cit = X.begin<float>();
			for (; cit != X.end<float>(); cit++)
			{
				t_distance += (*cit)*(*cit);
			}
			
			E_distance.push_back(t_distance);
		}

		//��̃��[�v�𔲂������_�œ��[���n�߂�B�ŏ��̒l�����C���f�b�N�X�ɇ@��������B
		vector<float>::iterator iter = min_element(E_distance.begin(), E_distance.end());
		size_t index = distance(E_distance.begin(), iter);//����ōŏ��̒l�����C���f�b�N�X�����߂邱�Ƃ��ł���B
		sdistnce.push_back(E_distance[index]);

	}
	vector<float>::iterator ite;
	float sum_distance=0;
	for (ite = sdistnce.begin(); ite != sdistnce.end(); ite++)
	{
		sum_distance += *ite;
	}

	return sum_distance;



}

void class_judge()
{

	for (int class_n = 0; class_n < 7; class_n++)
	{
		string dirname;
		switch (class_n)
		{
		case 0:
			dirname = "airplanes";
			break;
		case 1:
			dirname = "camera";
			break;
		case 2:
			dirname = "car_side";
			break;
		case 3:
			dirname = "chair";
			break;
		case 4:
			dirname = "cup";
			break;
		case 5:
			dirname = "pizza";
			break;
		case 6:
			dirname = "watch";
			break;
		}
		serch_img test;
		int i = 50;

		int true_n = 0;
		float answer_per;
		cout << dirname << endl;
		while (100)
		{
			cout << i;
			string temp = to_string(i);
			//�������쐬�����A�ԃt�@�C���ǂݍ��݁B�����̂悢�ǂݍ��ݕ��͂���񂶂�Ȃ����ȁB
			if (i <= 9)
			{
				test.path = "C:\\Users\\morimoto\\Desktop\\101_ObjectCategories\\" + dirname + "\\image_00";

				test.path += temp + ".jpg";
			}
			else if (i <= 99 && i >= 10)
			{
				test.path = "C:\\Users\\morimoto\\Desktop\\101_ObjectCategories\\" + dirname + "\\image_0";
				test.path += temp + ".jpg";
			}
			else if (i <= 999 && i >= 100)
			{
				test.path = "C:\\Users\\morimoto\\Desktop\\101_ObjectCategories\\" + dirname + "\\image_";
				test.path += temp + ".jpg";
			}




			test.img = imread(test.path);
			if (test.img.empty())
			{
				break;
			}


			test.name = dirname + temp;
			test = SURFDECT(test);
			vector<float> image2class_distance;
			for (int d_class = 0; d_class < 7; d_class++)
			{
				switch (d_class)
				{
				case 0:
					image2class_distance.push_back(most_dict_serch(d_class, test.descriptors, airplanes_mat));
					break;
				case 1:
					image2class_distance.push_back(most_dict_serch(d_class, test.descriptors, camera_mat));
					break;
				case 2:
					image2class_distance.push_back(most_dict_serch(d_class, test.descriptors, car_side_mat));
					break;
				case 3:
					image2class_distance.push_back(most_dict_serch(d_class, test.descriptors, chair_mat));
					break;
				case 4:
					image2class_distance.push_back(most_dict_serch(d_class, test.descriptors, cup_mat));
					break;
				case 5:
					image2class_distance.push_back(most_dict_serch(d_class, test.descriptors, pizza_mat));
					break;
				case 6:
					image2class_distance.push_back(most_dict_serch(d_class, test.descriptors, watch_mat));
					break;
				}

			}

			vector<float>::iterator iter = min_element(image2class_distance.begin(), image2class_distance.end());
			size_t index = distance(image2class_distance.begin(), iter);
			if (index == class_n)
			{
				true_n++;
			}
			i++;
			if (i == 60)
			{
				break;
			}


		}//while
		cout << endl;
		cout << dirname << "�̐�������" << true_n*100 / 10.000<<"%�ł�"<<endl;
		


	}//for
	
	
}

void test_judge()
{
	serch_img test;
	test.path = "C:\\Users\\morimoto\\Desktop\\101_ObjectCategories\\airplanes\\image_059.jpg";
	test.name = "test";
	test = SURFDECT(test);

	vector<float>image2class_distance;
	for (int d_class = 0; d_class < 7; d_class++)
	{
		
		switch (d_class)
		{
		case 0:
			image2class_distance.push_back(most_dict_serch(d_class, test.descriptors, airplanes_mat));
			break;
		case 1:
			image2class_distance.push_back(most_dict_serch(d_class, test.descriptors, camera_mat));
			break;
		case 2:
			image2class_distance.push_back(most_dict_serch(d_class, test.descriptors, car_side_mat));
			break;
		case 3:
			image2class_distance.push_back(most_dict_serch(d_class, test.descriptors, chair_mat));
			break;
		case 4:
			image2class_distance.push_back(most_dict_serch(d_class, test.descriptors, cup_mat));
			break;
		case 5:
			image2class_distance.push_back(most_dict_serch(d_class, test.descriptors, pizza_mat));
			break;
		case 6:
			image2class_distance.push_back(most_dict_serch(d_class, test.descriptors, watch_mat));
			break;
		}

	}

	vector<float>::iterator iter = min_element(image2class_distance.begin(), image2class_distance.end());
	size_t index = distance(image2class_distance.begin(), iter);
	switch (index)
	{
	case 0:
		cout << "airplane" << endl;
		break;
	case 1:
		cout << "camera" << endl;
		break;
	case 2:
		cout << "car_side" << endl;
		break;
	case 3:
		cout << "chair" << endl;
		break;
	case 4:
		cout << "cup" << endl;
		break;
	case 5:
		cout << "pizza" << endl;
		break;
	case 6:
		cout << "watch" << endl;
		break;
	}
}