#include "bgFaceAI.h"

#include "bgFaceRepository.h"
#include "bgFaceRecognition.h"

//#include "Poco/Data/Session.h"
//#include "Poco/Data/SQLite/Connector.h"
//#include "Poco/AccessExpireCache.h"
//
//// OpenCV��
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
* �������ȼ�������һ��ҵ��˵��
* ������������Ϊ����Ա������1W��ÿ�˵���������������100��
*
* ��ô��Ź������£�
* - ��Ա��ţ�00000 - 99999
* - ������ţ�0-99999
*
* ��ô���ݿ���ƹ������£�
* - ��Ա������ֶ�Ϊ��[��Ա���|��Ա����|��Ա�Ա�|��Ա����|��Ա����|��Ա����|��Ա֤������|��Ա֤������|��Աסַ|��Ա��ϵ��ʽ|��Ա״̬]
* - ����������ֶ�Ϊ��[�������(����ʶ���ǩ)|��������|��������ժҪ]
* - ��Ա��������������ֶ�Ϊ��[�������|��Ա���]
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

	// ��ʼ��������
	errCode = face_repository_->Initialize(database_type, ip, port, dbname, dbusername, dbpassword);
	if (errCode != 0)
		return errCode;

	// 1. ��ʼ��ʶ���
	errCode = face_recognition_->Initialize(nullptr);
	if (errCode != 0)
		return errCode;

	// 2. ���¹���������
	std::vector<BG_FASCE_INFO>::iterator iter;
	for (iter = face_repository_->face_info_.begin(); iter != face_repository_->face_info_.end(); ++iter)
	{
		errCode = face_recognition_->Training(iter->face_tag_, iter->face_data_, iter->face_data_len_);
		if (errCode != 0)
		{
			// ѵ��ʧ��
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

	// ���Ƚ�������ӵ���������
	for (int index = 0; index < face_count; ++index)
	{
		int face_tag = face_repository_->AddFace(&face_infos[index]);
		if (face_tag > -1)
		{
			// Ȼ��������ʶ��ģ��ѵ����Щ����
			face_recognition_->Training(face_tag, face_infos[index].face_data_, face_infos[index].face_data_len_);

			// ��󴴽�������ϵ
			face_repository_->AddBindInfo(person_number, face_tag);
		}
	}

	return errCode;
}

int bgFaceAI::RemoveFace(int person_id)
{
	int errCode = 0;

	// �������Ƴ�����������¼
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