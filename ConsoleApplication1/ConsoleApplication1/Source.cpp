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

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include<opencv2\highgui\highgui.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include<fstream>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/nonfree/features2d.hpp>
#include <opencv2/nonfree/nonfree.hpp>
#define OPENCV_VERSION(a,b,c) (((a) << 16) + ((b) << 8) + (c))
#define OPENCV_VERSION_CODE OPENCV_VERSION(CV_MAJOR_VERSION, CV_MINOR_VERSION, CV_SUBMINOR_VERSION)

#if OPENCV_VERSION_CODE>=OPENCV_VERSION(2,4,0)
#include <opencv2/nonfree/features2d.hpp>
#endif




using namespace std;
using namespace cv;


// 画像表示
int main(int argc, char* argv[])
{
	

	cv::Scalar color(100, 255, 50);
	


	for (int i = 0; i < 7; i++)
	{
		initModule_nonfree();
		Mat img2;
		string imgname2;
		if (i == 0)
		{
			imgname2 = "C:\\datebase\\airplanes\\image_001.jpg";
			img2 = cv::imread(imgname2);
		}
		else if (i == 1)
		{
			imgname2 = "C:\\datebase\\camera\\image_001.jpg";
			img2 = cv::imread(imgname2);

		}
		else if (i == 2)
		{
			imgname2 = "C:\\datebase\\car_side\\image_001.jpg";
			img2 = cv::imread(imgname2);

		}
		else if (i == 3)
		{
			imgname2 = "C:\\datebase\\chair\\image_001.jpg";
			img2 = cv::imread(imgname2);

		}
		else if (i == 4)
		{
			imgname2 = "C:\\datebase\\cup\\image_001.jpg";
			img2 = cv::imread(imgname2);

		}
		else if (i == 5)
		{
			imgname2 = "C:\\datebase\\pizza\\image_001.jpg";
			img2 = cv::imread(imgname2);

		}
		else if (i == 6)
		{
			imgname2 = "C:\\datebase\\watch\\image_001.jpg";
			img2 = cv::imread(imgname2);

		}

		/*
		switch (i)
		{
		case 0:
		char imgName2[100] = "C:\\datebase\\airplanes\\image_001.jpg";
		img2 = imread(imgName2);
		break;
		case 1:
		char imgName2[100] = "C:\\datebase\\camera\\image_001.jpg";
		img2 = imread(imgName2);
		break;
		case 2:
		char imgName2[100] = "C:\\datebase\\car_side\\image_001.jpg";
		img2 = imread(imgName2);
		break;
		case 3:
		char imgName2[100] = "C:\\datebase\\chair\\image_001.jpg";
		img2 = imread(imgName2);
		break;
		case 4:
		char imgName2[100] = "C:\\datebase\\cup\\image_001.jpg";
		img2 = imread(imgName2);
		break;
		case 5:
		char imgName2[100] = "C:\\datebase\\pizza\\image_001.jpg";
		img2 = imread(imgName2);
		break;
		case 6:
		char imgName2[100] = "C:\\datebase\\watch\\image_001.jpg";
		img2 = imread(imgName2);
		break;
		}
		*/

		cv::Mat gray_img2;
		cv::cvtColor(img2, gray_img2, CV_BGR2GRAY);
		cv::normalize(gray_img2, gray_img2, 0, 255, cv::NORM_MINMAX);

		std::vector<cv::KeyPoint> keypoints2;
		std::vector<cv::KeyPoint>::iterator itk2;
		cv::Mat descriptors2;
		ofstream ofs2("text_surf_r.txt");
		ofstream ofs3("test.txt");
		// SURF 検出器に基づく特徴点検出
		// hessianThreshold=4500, 
		cv::SurfFeatureDetector detector2(4500);

		detector2.detect(gray_img2, keypoints2);
		// SURF に基づくディスクリプタ抽出器
		cv::SurfDescriptorExtractor extractor2;
		extractor2.compute(gray_img2, keypoints2, descriptors2);
		for (itk2 = keypoints2.begin(); itk2 != keypoints2.end(); ++itk2) {
			cv::circle(img2, itk2->pt, 1, color, -1);
			cv::circle(img2, itk2->pt, itk2->size, color, 1, CV_AA);
			if (itk2->angle >= 0) {
				cv::Point pt2(itk2->pt.x + cos(itk2->angle)*itk2->size, itk2->pt.y + sin(itk2->angle)*itk2->size);
				cv::line(img2, itk2->pt, pt2, color, 1, CV_AA);
			}
		}

		cout << descriptors2.size()<<endl;
		
		cv::namedWindow("SURF Features2", CV_WINDOW_AUTOSIZE | CV_WINDOW_FREERATIO);
		cv::imshow("SURF Features2", img2);
		
		Mat_<float>::const_iterator cit = descriptors2.begin<float>();
		for (; cit != descriptors2.end<float>(); ++cit)
		{
			ofs3 << *cit << ",";
		}
		for (int i = 0; i<descriptors2.rows; ++i) 
		{
			cv::Mat d(descriptors2, cv::Rect(0, i, descriptors2.cols, 1));
			ofs2 << d << std::endl;
		}

	}



	return 0;
}

