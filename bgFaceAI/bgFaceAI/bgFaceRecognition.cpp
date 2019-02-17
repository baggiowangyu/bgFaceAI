#include "bgFaceRecognition.h"

// OpenCV��
#include "opencv/cv.h"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/objdetect.hpp"
#include "opencv2/face.hpp"

#ifdef _DEBUG
#pragma comment(lib, "opencv_core345d.lib")
#pragma comment(lib, "opencv_highgui345d.lib")
#pragma comment(lib, "opencv_face345d.lib")
#pragma comment(lib, "opencv_imgproc345d.lib")
#pragma comment(lib, "opencv_imgcodecs345d.lib")
#pragma comment(lib, "opencv_objdetect345d.lib")
#else
#pragma comment(lib, "opencv_core345.lib")
#pragma comment(lib, "opencv_highgui345.lib")
#pragma comment(lib, "opencv_face345.lib")
#pragma comment(lib, "opencv_imgproc345.lib")
#pragma comment(lib, "opencv_imgcodecs345.lib")
#pragma comment(lib, "opencv_objdetect345.lib")
#endif

bgFaceRecognition::bgFaceRecognition()
	: face_recongnizer_(nullptr)
	, fisher_face_recongnizer_(nullptr)
	, lbph_face_recongnizer_(nullptr)
{}

bgFaceRecognition::~bgFaceRecognition()
{}

int bgFaceRecognition::Initialize(const char *fector_file)
{
	int errCode = 0;

	// ��ʼ������ʶ��ģʽ����
	face_recongnizer_			= cv::face::EigenFaceRecognizer::create();
	fisher_face_recongnizer_	= cv::face::FisherFaceRecognizer::create();
	//lbph_face_recongnizer_		= cv::face::LBPHFaceRecognizer::create();

	return errCode;
}

void bgFaceRecognition::Close()
{
	// �����ͷ�ʶ��ģʽ���������
}

int bgFaceRecognition::Training(int face_tag, const unsigned char *face_data, int face_data_len)
{
	/**
	 * ������ѵ�������Ľӿڣ��������¹�������ʶ������ֵ
	 */
	int errCode = 0;

	cv::Mat img = HexDataToMat(face_data, face_data_len);

	// ͼ���С��һ
	cv::resize(img, img, cv::Size(128, 128));

	std::vector<int> tags;
	std::vector<cv::Mat> faces;

	tags.push_back(face_tag);
	faces.push_back(img);

	face_recongnizer_->train(faces, tags);

	// ����һ��Ҫ������ֵ�浽xml�ļ�����ȥ���ǰɣ�

	return errCode;
}

int bgFaceRecognition::CheckFace(const unsigned char *face_data, int face_data_len)
{
	int face_tag = -1;

	cv::Mat img = HexDataToMat(face_data, face_data_len);

	// ���лҶȴ���
	cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);

	// ʶ��
	face_tag = face_recongnizer_->predict(img);

	// �˴����ص����������еı�ǩ���������������в�ѯ������ϵ���ҵ���Ӧ����Ա�����ʶ��
	return face_tag;
}

cv::Mat bgFaceRecognition::HexDataToMat(const unsigned char *image_data, int image_data_len)
{
	cv::Mat image;
	int offset = 0;
	int channl(0);
	int imagerows(0);
	int imagecols(0);
	memcpy(&channl, image_data + offset, 1);
	offset += 1;

	memcpy(&imagerows, image_data + offset, 4);
	offset += 4;

	memcpy(&imagecols, image_data + offset, 4);
	offset += 4;

	//fread(&channl, sizeof(char), 1, fpr);//��һ���ֽ� ͨ��
	//fread(&imagerows, sizeof(char), 4, fpr); //�ĸ��ֽڴ� ����
	//fread(&imagecols, sizeof(char), 4, fpr); //�ĸ��ֽڴ� ����
	if (channl == 3)
	{
		image = cv::Mat::zeros(imagerows, imagecols, CV_8UC3);
		char* pData = (char*)image.data;
		for (int i = 0; i < imagerows * imagecols; i++)
		{
			memcpy(&pData[i * 3], image_data + offset, 1);
			offset += 1;

			memcpy(&pData[i * 3 + 1], image_data + offset, 1);
			offset += 1;

			memcpy(&pData[i * 3 + 2], image_data + offset, 1);
			offset += 1;

			//fread(&pData[i * 3], sizeof(char), 1, fpr);
			//fread(&pData[i * 3 + 1], sizeof(char), 1, fpr);
			//fread(&pData[i * 3 + 2], sizeof(char), 1, fpr);
		}
	}
	else if (channl == 1)
	{
		image = cv::Mat::zeros(imagerows, imagecols, CV_8UC1);
		char* pData = (char*)image.data;
		for (int i = 0; i < imagerows*imagecols; i++)
		{
			memcpy(&pData[i], image_data + offset, 1);
			offset += 1;
			//fread(&pData[i], sizeof(char), 1, fpr);
		}
	}

	return image;
}