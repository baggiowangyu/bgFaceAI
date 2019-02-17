// bgFaceDemo.cpp : 定义控制台应用程序的入口点。
//
//
// 本范例主要做两个方面的尝试
// 1. 从图像中检测人脸。
// 2. 根据人脸图片，识别出他/她(/它?)是谁。
//
// 关于学习训练、人脸库与人脸识别检索定义
// 1. 学习训练，
//

#include "stdafx.h"

#include "opencv2\opencv.hpp"
#include "opencv2\face.hpp"

#include "Poco\Timestamp.h"
#include "Poco\Timespan.h"
#include "Poco\Timezone.h"
#include "Poco\DateTime.h"

#include <iostream>
#include <string>

#pragma comment(lib, "opencv_core345d.lib")
#pragma comment(lib, "opencv_highgui345d.lib")
#pragma comment(lib, "opencv_face345d.lib")
#pragma comment(lib, "opencv_imgproc345d.lib")
#pragma comment(lib, "opencv_imgcodecs345d.lib")
#pragma comment(lib, "opencv_objdetect345d.lib")

// 从目前测试来看，只能是睁眼的人脸
void CheckFace(const char *source_image_path, cv::Mat &founded_face)
{
	cv::Mat src_image = cv::imread(source_image_path);
	cv::Mat frame = src_image.clone();
	cv::Mat facesROI;

	// 图像缩放，采用双线性插值（这里暂不使用）
	//cv::resize(src_image, src_image, cv::Size(128, 128), 0, 0, cv::INTER_LINEAR);

	// 图像灰度化（必要操作）
	cv::cvtColor(src_image, src_image, cv::COLOR_BGR2GRAY);

	// 直方图均衡化，图像增强，暗的变亮，亮的变暗
	cv::equalizeHist(src_image, src_image);

	// 加载分类器，分类器有两种：脸部分类器、眼睛分类器

	cv::String face_cascade_name = "E:\\opensource\\OpenCV\\opencv\\vs2013\\install\\etc\\haarcascades\\haarcascade_frontalface_alt.xml";
	cv::String eyes_cascade_name = "E:\\opensource\\OpenCV\\opencv\\vs2013\\install\\etc\\haarcascades\\haarcascade_eye_tree_eyeglasses.xml";

	cv::CascadeClassifier face_cascade, eyes_cascade;

	if (!face_cascade.load(face_cascade_name))
	{
		std::cout << "加载脸部分类器%s失败！" << face_cascade_name.c_str() << std::endl;
		return;
	}

	if (!eyes_cascade.load(eyes_cascade_name))
	{
		std::cout << "加载眼睛分类器%s失败！" << face_cascade_name.c_str() << std::endl;
		return;
	}

	// 检测到的脸部矩形区域
	std::vector<cv::Rect> faces;
	face_cascade.detectMultiScale(src_image, faces, 1.1, 2, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30));

	for (size_t index = 0; index < faces.size(); ++index)
	{
		// 绘制矩形 BGR
		cv::rectangle(frame, faces[index], cv::Scalar(0, 0, 255), 1);

		// 获取矩形中心点
		//cv::Point center(faces[index].x + faces[index].width / 2, faces[index].y + faces[index].height / 2);

		// 绘制圆形
		//cv::ellipse(frame, center, cv::Size(faces[index].width / 2, faces[index].height / 2), 0, 0, 360, cv::Scalar(255, 0, 255), 4, 8, 0);

		// 获取脸部矩形区域
		//cv::Mat faceROI = src_image(faces[index]);

		// 存储找到的眼睛矩形
		//std::vector<cv::Rect> eyes;
		//eyes_cascade.detectMultiScale(faceROI, eyes, 1.1, 2, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30));
		//for (int index_j = 0; index_j < eyes.size(); ++index_j)
		//{
		//	cv::Point eye_center(faces[index].x + eyes[index_j].x + eyes[index_j].width / 2, faces[index].y + eyes[index_j].y + eyes[index_j].height / 2);
		//	int radius = cvRound((eyes[index_j].width + eyes[index_j].height) * 0.25);
		//	cv::circle(frame, eye_center, radius, cv::Scalar(255, 0, 0), 4, 8, 0);
		//}

		// 截取人脸
		facesROI = frame(faces[index]);

		// 图像缩放
		cv::resize(facesROI, facesROI, cv::Size(128, 128), 0, 0, cv::INTER_LINEAR);

		// 保存图像
		founded_face = facesROI;

		// 根据当前时间作为文件名存储
		Poco::Timestamp timestamp;
		timestamp.update();

		Poco::DateTime current_time(timestamp);
		
		char output_file_name[4096] = { 0 };
		sprintf(output_file_name, "face_%d%02d%02d_%02d%02d%02d.jpg",
			current_time.year(), current_time.month(), current_time.day(),
			current_time.hour(), current_time.minute(), current_time.second());
		cv::imwrite(output_file_name, facesROI);
	}
}


// 人脸样本训练
// 如何标记一个人？使用ID
// 传入一张脸，需要一个标签

int SamplesTraining(const char *person_id, cv::Mat &sample_img, const char *label)
{
	try
	{
		std::vector<cv::Mat> samples;
		std::vector<int> labels;

		// 读取样本
		cv::Mat src_img = sample_img;

		samples.push_back(src_img);
		labels.push_back(1);

		// 图像大小归一
		cv::resize(src_img, src_img, cv::Size(128, 128));

		// 训练

		// 这里创建三种识别模式对象

		// 特征脸算法（据说光照不好、或其他情况会失效）
		cv::Ptr<cv::face::FaceRecognizer> face_class = cv::face::EigenFaceRecognizer::create();

		// 主成分分析是一种基于特征脸的方法，找到使数据中最大方差的特征线性组合（据说光照不好、或其他情况会失效）
		//cv::Ptr<cv::face::FisherFaceRecognizer> fisher_class = cv::face::FisherFaceRecognizer::create();

		// 局部二值模式直方图算法(听说优选这个)
		//cv::Ptr<cv::face::LBPHFaceRecognizer> lbph_class = cv::face::LBPHFaceRecognizer::create();

		face_class->train(samples, labels);
		//fisher_class->train(samples, labels);
		//lbph_class->train(samples, labels);

		// 将训练结果保存到分类器中
		face_class->save("face_class.xml");
		//fisher_class->save("fisher_class.xml");
		//lbph_class->save("lbph_class.xml");
	}
	catch (cv::Exception ex)
	{
		//
		const char *errinfo = ex.what();
		OutputDebugStringA(errinfo);
	}

	return 0;
}

int SamplesTraining(const char *person_id, const char *sample_img, const char *label)
{
	// 读取样本
	cv::Mat src_img = cv::imread(sample_img, CV_LOAD_IMAGE_GRAYSCALE);

	int errCode = SamplesTraining(person_id, src_img, label);

	return errCode;
}



int FaceRecognize(cv::Mat &sample_img)
{
	try
	{
		cv::cvtColor(sample_img, sample_img, cv::COLOR_BGR2GRAY);

		// 首先加载训练结果分类器
		cv::Ptr<cv::face::FaceRecognizer> face_class = cv::face::EigenFaceRecognizer::create();
		//cv::face::FisherFaceRecognizer *fisher_class = cv::face::FisherFaceRecognizer::create();
		//cv::face::LBPHFaceRecognizer *lbph_class = cv::face::LBPHFaceRecognizer::create();

		face_class->read("face_class.xml");
		//fisher_class->read("fisher_class.xml");
		//lbph_class->read("lbph_class.xml");

		// 使用训练好的分类器进行预测
		int label = 0;
		double confidence = 0.0;
		//label = face_class->predict(sample_img);
		face_class->predict(sample_img, label, confidence);
		switch (label)
		{
		case 1:
			break;
		default:
			break;
		}
	}
	catch (cv::Exception ex)
	{
		//
		const char *errinfo = ex.what();
		OutputDebugStringA(errinfo);
	}

	return 0;
}

int FaceRecognize(const char *sample_img)
{
	// 读取样本
	cv::Mat src_img = cv::imread(sample_img, CV_LOAD_IMAGE_GRAYSCALE);

	return FaceRecognize(src_img);
}




int _tmain(int argc, _TCHAR* argv[])
{
	const char *face_img = "C:\\Users\\WANGY\\Desktop\\img资源\\特朗普.jpg";
	cv::Mat founded_face;
	
	// 检测人脸
	CheckFace(face_img, founded_face);

	// 训练人脸，保存到分类器中
	SamplesTraining("001", founded_face, "川普");

	// 识别
	const char *face_img2 = "C:\\Users\\WANGY\\Desktop\\img资源\\川普.jpg";
	cv::Mat founded_face2;
	CheckFace(face_img2, founded_face2);

	// 最后输入图像，进行识别
	FaceRecognize(founded_face2);

	return 0;
}

