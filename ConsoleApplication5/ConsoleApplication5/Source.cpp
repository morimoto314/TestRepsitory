#ifdef _DEBUG
//Debugモードの場合
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
//Releaseモードの場合
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

//名前空間の指定
using namespace cv;
using namespace std;

const int DIM = 64;
const int MAX_CLASTER = 500;

class serch_img//ポインタを含んでいないからたぶんどこでも使える仕様になっているはず。
{
public:
	Mat img;//出力画像を保存するためのMat型変数
	vector<KeyPoint> keypoints;//特徴点を保存するための変数
	Mat descriptors;//特徴量を保存している
	string path;//ファイルパス
	string name;//画像名
	void output_txt();//テキストファイルに出力するための関数
	void show_window();//画像を出すための関数
	void output_txt(string str);//テキストファイルに出力するための関数＋フォルダ出力に対応。
};

//関数プロトタイプ宣言
serch_img SURFDECT(serch_img test);
void m_serch(string dirname, vector<float>&data);
void data2txt(vector<float>data, string str);
float most_dict_serch(int i, Mat q_data, Mat database);
Mat change_data(vector<float>&data);
void class_judge();
void test_judge();

//グローバル変数の宣言。変えたほうがいい
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
	
	


	//探索関数
	m_serch("airplanes", airplanes_data);
	//ここでデータをテキストファイルに出力する。
	data2txt(airplanes_data, "airplanes");
	//Matに変換する
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


//特徴点検出用関数
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

	// SURF 検出器に基づく特徴点検出
	// hessianThreshold=4500, 
	cv::SurfFeatureDetector detector(4500);
	cv::Scalar color(100, 255, 50);
	detector.detect(gray_img, test.keypoints);
	// SURF に基づくディスクリプタ抽出器
	cv::SurfDescriptorExtractor extractor;

	extractor.compute(gray_img, test.keypoints, test.descriptors);
	for (itk = test.keypoints.begin(); itk != test.keypoints.end(); ++itk) {
		cv::circle(test.img, itk->pt, 1, color, -1);

	}







	return test;
}

//ウィンドを出現させる関数。
void serch_img::show_window()
{
	cv::namedWindow(name, CV_WINDOW_AUTOSIZE | CV_WINDOW_FREERATIO);
	cv::imshow(name, img);
}

//全探索データを返す関数
void m_serch(string dirname, vector<float>&data)
{


	serch_img test;
	int i = 1;


	while (100)
	{
		string temp = to_string(i);
		//無理やり作成した連番ファイル読み込み。効率のよい読み込み方はあるんじゃないかな。
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
			cout << dirname << "クラスは合計" << i - 1 << "枚ありました。" << endl;
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

//一次元データを特徴次元数×特徴点の個数の行列に直す
Mat change_data(vector<float>&data)
{
	CvMat samp;
	int rows = data.size() / DIM;  // CvMatの行数（=DIM次元特徴ベクトルの本数）
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
		vector<float> E_distance;//各要素のユークリッド距離を保存する。
		//このループで最小のユークリッド距離の特徴点を発見する
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

		//上のループを抜けた時点で投票を始める。最小の値をもつインデックスに①をあげる。
		vector<float>::iterator iter = min_element(E_distance.begin(), E_distance.end());
		size_t index = distance(E_distance.begin(), iter);//これで最小の値をもつインデックスを求めることができる。
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
			//無理やり作成した連番ファイル読み込み。効率のよい読み込み方はあるんじゃないかな。
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
		cout << dirname << "の正答率は" << true_n*100 / 10.000<<"%です"<<endl;
		


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