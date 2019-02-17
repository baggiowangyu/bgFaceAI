#ifndef _bgFaceRecognition_H_
#define _bgFaceRecognition_H_

/**
 * 此类是人脸别类
 * 此类主要有两个工作
 * 1. 通过训练、构建特征库
 * 2. 根据传入的人脸图像，识别人脸标签
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
	// 这里训练人脸特征值
	int Training(int face_tag, const unsigned char *face_data, int face_data_len);

public:
	int CheckFace(const unsigned char *face_data, int face_data_len);

private:
	cv::Mat HexDataToMat(const unsigned char *image_data, int image_data_len);

private:
	cv::face::FaceRecognizer *face_recongnizer_;				// 特征脸识别器
	cv::face::FisherFaceRecognizer *fisher_face_recongnizer_;	// 高级特征脸识别器
	cv::face::LBPHFaceRecognizer *lbph_face_recongnizer_;		// 直方图识别器
};

#endif//_bgFaceRecognition_H_
