#ifndef _bgFaceRecognition_H_
#define _bgFaceRecognition_H_

/**
 * ��������������
 * ������Ҫ����������
 * 1. ͨ��ѵ��������������
 * 2. ���ݴ��������ͼ��ʶ��������ǩ
 */

#include "bgFaceAIDef.h"

class DLL_API bgFaceRecognition
{
public:
	bgFaceRecognition();
	~bgFaceRecognition();

public:
	int Initialize(const char *fector_file);
	void Close();

public:
	// ����ѵ����������ֵ
	int Training(int face_tag, const unsigned char *face_data, int face_data_len);

public:
	int CheckFace(const unsigned char *face_data, int face_data_len);

private:
	cv::Mat HexDataToMat(const unsigned char *image_data, int image_data_len);

private:
	cv::face::FaceRecognizer *face_recongnizer_;				// ������ʶ����
	cv::face::FisherFaceRecognizer *fisher_face_recongnizer_;	// �߼�������ʶ����
	cv::face::LBPHFaceRecognizer *lbph_face_recongnizer_;		// ֱ��ͼʶ����
};

#endif//_bgFaceRecognition_H_
