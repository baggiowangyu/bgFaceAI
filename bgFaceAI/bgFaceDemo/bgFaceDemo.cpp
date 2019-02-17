// bgFaceDemo.cpp : �������̨Ӧ�ó������ڵ㡣
//
//
// ��������Ҫ����������ĳ���
// 1. ��ͼ���м��������
// 2. ��������ͼƬ��ʶ�����/��(/��?)��˭��
//
// ����ѧϰѵ����������������ʶ���������
// 1. ѧϰѵ����
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

// ��Ŀǰ����������ֻ�������۵�����
void CheckFace(const char *source_image_path, cv::Mat &founded_face)
{
	cv::Mat src_image = cv::imread(source_image_path);
	cv::Mat frame = src_image.clone();
	cv::Mat facesROI;

	// ͼ�����ţ�����˫���Բ�ֵ�������ݲ�ʹ�ã�
	//cv::resize(src_image, src_image, cv::Size(128, 128), 0, 0, cv::INTER_LINEAR);

	// ͼ��ҶȻ�����Ҫ������
	cv::cvtColor(src_image, src_image, cv::COLOR_BGR2GRAY);

	// ֱ��ͼ���⻯��ͼ����ǿ�����ı��������ı䰵
	cv::equalizeHist(src_image, src_image);

	// ���ط������������������֣��������������۾�������

	cv::String face_cascade_name = "E:\\opensource\\OpenCV\\opencv\\vs2013\\install\\etc\\haarcascades\\haarcascade_frontalface_alt.xml";
	cv::String eyes_cascade_name = "E:\\opensource\\OpenCV\\opencv\\vs2013\\install\\etc\\haarcascades\\haarcascade_eye_tree_eyeglasses.xml";

	cv::CascadeClassifier face_cascade, eyes_cascade;

	if (!face_cascade.load(face_cascade_name))
	{
		std::cout << "��������������%sʧ�ܣ�" << face_cascade_name.c_str() << std::endl;
		return;
	}

	if (!eyes_cascade.load(eyes_cascade_name))
	{
		std::cout << "�����۾�������%sʧ�ܣ�" << face_cascade_name.c_str() << std::endl;
		return;
	}

	// ��⵽��������������
	std::vector<cv::Rect> faces;
	face_cascade.detectMultiScale(src_image, faces, 1.1, 2, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30));

	for (size_t index = 0; index < faces.size(); ++index)
	{
		// ���ƾ��� BGR
		cv::rectangle(frame, faces[index], cv::Scalar(0, 0, 255), 1);

		// ��ȡ�������ĵ�
		//cv::Point center(faces[index].x + faces[index].width / 2, faces[index].y + faces[index].height / 2);

		// ����Բ��
		//cv::ellipse(frame, center, cv::Size(faces[index].width / 2, faces[index].height / 2), 0, 0, 360, cv::Scalar(255, 0, 255), 4, 8, 0);

		// ��ȡ������������
		//cv::Mat faceROI = src_image(faces[index]);

		// �洢�ҵ����۾�����
		//std::vector<cv::Rect> eyes;
		//eyes_cascade.detectMultiScale(faceROI, eyes, 1.1, 2, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30));
		//for (int index_j = 0; index_j < eyes.size(); ++index_j)
		//{
		//	cv::Point eye_center(faces[index].x + eyes[index_j].x + eyes[index_j].width / 2, faces[index].y + eyes[index_j].y + eyes[index_j].height / 2);
		//	int radius = cvRound((eyes[index_j].width + eyes[index_j].height) * 0.25);
		//	cv::circle(frame, eye_center, radius, cv::Scalar(255, 0, 0), 4, 8, 0);
		//}

		// ��ȡ����
		facesROI = frame(faces[index]);

		// ͼ������
		cv::resize(facesROI, facesROI, cv::Size(128, 128), 0, 0, cv::INTER_LINEAR);

		// ����ͼ��
		founded_face = facesROI;

		// ���ݵ�ǰʱ����Ϊ�ļ����洢
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


// ��������ѵ��
// ��α��һ���ˣ�ʹ��ID
// ����һ��������Ҫһ����ǩ

int SamplesTraining(const char *person_id, cv::Mat &sample_img, const char *label)
{
	try
	{
		std::vector<cv::Mat> samples;
		std::vector<int> labels;

		// ��ȡ����
		cv::Mat src_img = sample_img;

		samples.push_back(src_img);
		labels.push_back(1);

		// ͼ���С��һ
		cv::resize(src_img, src_img, cv::Size(128, 128));

		// ѵ��

		// ���ﴴ������ʶ��ģʽ����

		// �������㷨����˵���ղ��á������������ʧЧ��
		cv::Ptr<cv::face::FaceRecognizer> face_class = cv::face::EigenFaceRecognizer::create();

		// ���ɷַ�����һ�ֻ����������ķ������ҵ�ʹ��������󷽲������������ϣ���˵���ղ��á������������ʧЧ��
		//cv::Ptr<cv::face::FisherFaceRecognizer> fisher_class = cv::face::FisherFaceRecognizer::create();

		// �ֲ���ֵģʽֱ��ͼ�㷨(��˵��ѡ���)
		//cv::Ptr<cv::face::LBPHFaceRecognizer> lbph_class = cv::face::LBPHFaceRecognizer::create();

		face_class->train(samples, labels);
		//fisher_class->train(samples, labels);
		//lbph_class->train(samples, labels);

		// ��ѵ��������浽��������
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
	// ��ȡ����
	cv::Mat src_img = cv::imread(sample_img, CV_LOAD_IMAGE_GRAYSCALE);

	int errCode = SamplesTraining(person_id, src_img, label);

	return errCode;
}



int FaceRecognize(cv::Mat &sample_img)
{
	try
	{
		cv::cvtColor(sample_img, sample_img, cv::COLOR_BGR2GRAY);

		// ���ȼ���ѵ�����������
		cv::Ptr<cv::face::FaceRecognizer> face_class = cv::face::EigenFaceRecognizer::create();
		//cv::face::FisherFaceRecognizer *fisher_class = cv::face::FisherFaceRecognizer::create();
		//cv::face::LBPHFaceRecognizer *lbph_class = cv::face::LBPHFaceRecognizer::create();

		face_class->read("face_class.xml");
		//fisher_class->read("fisher_class.xml");
		//lbph_class->read("lbph_class.xml");

		// ʹ��ѵ���õķ���������Ԥ��
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
	// ��ȡ����
	cv::Mat src_img = cv::imread(sample_img, CV_LOAD_IMAGE_GRAYSCALE);

	return FaceRecognize(src_img);
}




int _tmain(int argc, _TCHAR* argv[])
{
	const char *face_img = "C:\\Users\\WANGY\\Desktop\\img��Դ\\������.jpg";
	cv::Mat founded_face;
	
	// �������
	CheckFace(face_img, founded_face);

	// ѵ�����������浽��������
	SamplesTraining("001", founded_face, "����");

	// ʶ��
	const char *face_img2 = "C:\\Users\\WANGY\\Desktop\\img��Դ\\����.jpg";
	cv::Mat founded_face2;
	CheckFace(face_img2, founded_face2);

	// �������ͼ�񣬽���ʶ��
	FaceRecognize(founded_face2);

	return 0;
}

