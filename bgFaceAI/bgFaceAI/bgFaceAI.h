#ifndef _bgFaceAI_H_
#define _bgFaceAI_H_

#include <string>
#include <vector>

#include "bgFaceAIDef.h"

class bgFaceRepository;
class bgFaceRecognition;


/**
 * 本类是一个人脸只能识别类对象，主要有以下几个功能：
 * 1. 人脸库的管理
 *    - 人员信息管理（人员的基本信息）
 *    - 人脸信息管理（人脸信息保存人脸图片、人脸图片的摘要、用于训练人脸识别器的人脸标签）
 *    - 人员与人脸对应关系管理（一个人员可以关联多个人脸，一个人脸只属于一个人员）
 * 2. 人脸识别模块的管理
 *    - 人脸特征值的训练（训练来源有两个：1.数据库保存的人脸与人脸标签，用于从0开始构建人脸特征库；2.新增加的人脸，入库后更新人脸特征库）
 *    - 提供接口进行人脸识别
 */
class DLL_API bgFaceAI
{
public:
	bgFaceAI();
	~bgFaceAI();

public:
	// 初始化，连接数据库
	// 数据库应当支持MySQL、Oracle、SQLite3等常见关系型数据库(使用ODBC方式)
	// 后期可以考虑使用MongoDB
	// 如果是SQLite，则在ip处填写数据库路径，其他随意
	int Initialize(int database_type, const char *ip, int port, const char *dbname, const char *dbusername, const char *dbpassword);
	int Initialize(const char *connection_string);
	void Close();

public:
	// 增加人脸，可以是原始图片，但是原始图片中只能包含一个人脸
	int AddPerson(BG_PERSON_INFO &person_info);
	int AddFace(int person_number, int face_count, PBG_FASCE_INFO face_infos);
	int RemoveFace(int person_id);

	int QueryPersonBegin();
	int QueryNextPerson(BG_PERSON_INFO &person_info);
	int QueryPersonEnd();

	int QueryFaceByPerson(int person_number, std::vector<int> &face_tags);

public:
	// 识别人脸
	int Recognition(const unsigned char *face_data, int face_data_len);

//private:
	//cv::Mat HexDataToMat(const char *image_data, int image_data_len);

private:
	std::vector<BG_PERSON_INFO>::iterator person_iter_;

private:
	bgFaceRepository *face_repository_;
	bgFaceRecognition *face_recognition_;
	
};

#endif//_bgFaceAI_H_
