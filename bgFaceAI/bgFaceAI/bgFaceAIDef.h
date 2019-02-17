#ifndef _bgFaceAIDef_H_
#define _bgFaceAIDef_H_

#ifdef BGFACEAI_EXPORTS
#define DLL_API __declspec(dllexport)
#else
#define DLL_API __declspec(dllimport)
#endif

#include <string>

namespace Poco {
	namespace Data {
		class Session;
	};
	namespace Util {
		class AccessExpireCache;
	}
};

namespace cv {
	namespace face {
		class FaceRecognizer;
		class FisherFaceRecognizer;
		class LBPHFaceRecognizer;
	};

	class Mat;
	class CascadeClassifier;
};


#define DATABASE_TYPE_MySQL		0	// MySQL
#define DATABASE_TYPE_Oracle	1	// Oracle
#define DATABASE_TYPE_SQLite3	2	// SQLite3

typedef struct _BG_FASCE_INFO_
{
	int face_tag_;						// ����ID
	unsigned char *face_data_;			// ����ͼ�����ݣ��ڲ���cv::Mat����
	int face_data_len_;					// ����ͼ�����ݳ���
	std::string face_data_hash_;		// ����ͼ������ժҪ

} BG_FASCE_INFO, *PBG_FASCE_INFO;

typedef struct _BG_PERSON_INFO_
{
	int person_number;
	std::string person_name;
	std::string person_sex;
	std::string person_birthday;
	std::string person_country;
	std::string person_nation;
	std::string person_id_type;
	std::string person_id_number;
	std::string person_address;
	std::string person_contact_way;
	int person_state;

} BG_PERSON_INFO, *PBG_PERSON_INFO;

//typedef struct _BG_PERSON_WITH_FACE_INFO_
//{
//	BG_FASCE_INFO person_info_;
//	int face_count_;						// ��������
//	BG_FASCE_INFO person_face_info_[16];	// ��Ա������Ϣ������Ԥ��16��ͼƬ���Է���Ҫʱʹ��
//
//} BG_PERSON_WITH_FACE_INFO, *PBG_PERSON_WITH_FACE_INFO;

#endif//_bgFaceAIDef_H_
