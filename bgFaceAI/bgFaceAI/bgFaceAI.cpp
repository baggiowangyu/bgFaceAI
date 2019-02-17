#include "bgFaceAI.h"

#include "bgFaceRepository.h"
#include "bgFaceRecognition.h"

//#include "Poco/Data/Session.h"
//#include "Poco/Data/SQLite/Connector.h"
//#include "Poco/AccessExpireCache.h"
//
//// OpenCV库
//#include "opencv/cv.h"
//#include "opencv2/imgproc.hpp"
//#include "opencv2/imgcodecs.hpp"
//#include "opencv2/objdetect.hpp"
//#include "opencv2/face.hpp"
//
//#ifdef _DEBUG
//#pragma comment(lib, "opencv_core345d.lib")
//#pragma comment(lib, "opencv_highgui345d.lib")
//#pragma comment(lib, "opencv_face345d.lib")
//#pragma comment(lib, "opencv_imgproc345d.lib")
//#pragma comment(lib, "opencv_imgcodecs345d.lib")
//#pragma comment(lib, "opencv_objdetect345d.lib")
//#endif


/**
* 在这里先简单描述用一下业务说明
* 本组件设计容量为：人员不超过1W，每人的人脸数量不超过100张
*
* 那么编号规则如下：
* - 人员编号：00000 - 99999
* - 人脸编号：0-99999
*
* 那么数据库设计规则如下：
* - 人员表设计字段为：[人员编号|人员姓名|人员性别|人员生日|人员国籍|人员民族|人员证件类型|人员证件号码|人员住址|人员联系方式|人员状态]
* - 人脸表设计字段为：[人脸编号(人脸识别标签)|人脸数据|人脸数据摘要]
* - 人员人脸关联表设计字段为：[人脸编号|人员编号]
*/

bgFaceAI::bgFaceAI()
	: face_repository_(new bgFaceRepository())
	, face_recognition_(new bgFaceRecognition())
{
}

bgFaceAI::~bgFaceAI()
{
	if (face_repository_)
		delete face_repository_;
	face_repository_ = nullptr;

	if (face_recognition_)
		delete face_recognition_;
	face_recognition_ = nullptr;
}

int bgFaceAI::Initialize(int database_type, const char *ip, int port, const char *dbname, const char *dbusername, const char *dbpassword)
{
	int errCode = 0;
	std::string errstr;

	// 初始化人脸库
	errCode = face_repository_->Initialize(database_type, ip, port, dbname, dbusername, dbpassword);
	if (errCode != 0)
		return errCode;

	// 1. 初始化识别库
	errCode = face_recognition_->Initialize(nullptr);
	if (errCode != 0)
		return errCode;

	// 2. 重新构建特征库
	std::vector<BG_FASCE_INFO>::iterator iter;
	for (iter = face_repository_->face_info_.begin(); iter != face_repository_->face_info_.end(); ++iter)
	{
		errCode = face_recognition_->Training(iter->face_tag_, iter->face_data_, iter->face_data_len_);
		if (errCode != 0)
		{
			// 训练失败
		}
	}

	return errCode;
}

int bgFaceAI::Initialize(const char *connection_string)
{
	int errCode = -99;
	std::string errstr;

	return errCode;
}

void bgFaceAI::Close()
{

}

int bgFaceAI::AddPerson(BG_PERSON_INFO &person_info)
{
	int errCode = face_repository_->AddPerson(&person_info);
	return errCode;
}

int bgFaceAI::AddFace(int person_number, int face_count, PBG_FASCE_INFO face_infos)
{
	int errCode = 0;

	// 首先将人脸添加到人脸库中
	for (int index = 0; index < face_count; ++index)
	{
		int face_tag = face_repository_->AddFace(&face_infos[index]);
		if (face_tag > -1)
		{
			// 然后让人脸识别模块训练这些人脸
			face_recognition_->Training(face_tag, face_infos[index].face_data_, face_infos[index].face_data_len_);

			// 最后创建关联关系
			face_repository_->AddBindInfo(person_number, face_tag);
		}
	}

	return errCode;
}

int bgFaceAI::RemoveFace(int person_id)
{
	int errCode = 0;

	// 这里是移除人脸关联记录
	face_repository_->DeleteBindInfo(person_id);

	return errCode;
}

int bgFaceAI::QueryPersonBegin()
{
	person_iter_ = face_repository_->person_info_.begin();
	return 0;
}

int bgFaceAI::QueryNextPerson(BG_PERSON_INFO &person_info)
{
	if (person_iter_ == face_repository_->person_info_.end())
		return -1;

	person_info.person_number = person_iter_->person_number;
	person_info.person_name = person_iter_->person_name;
	person_info.person_sex = person_iter_->person_sex;
	person_info.person_birthday = person_iter_->person_birthday;
	person_info.person_country = person_iter_->person_country;
	person_info.person_nation = person_iter_->person_nation;
	person_info.person_id_type = person_iter_->person_id_type;
	person_info.person_id_number = person_iter_->person_id_number;
	person_info.person_address = person_iter_->person_address;
	person_info.person_contact_way = person_iter_->person_contact_way;
	person_info.person_state = person_iter_->person_state;

	return 0;
}

int bgFaceAI::QueryPersonEnd()
{
	person_iter_ = face_repository_->person_info_.end();
	return 0;
}

int bgFaceAI::QueryFaceByPerson(int person_number, std::vector<int> &face_tags)
{
	int errCode = face_repository_->QueryBindInfo(person_number);
	face_tags = face_repository_->person_face_tags;

	return errCode;
}