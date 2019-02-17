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
	int face_tag_;						// 人脸ID
	unsigned char *face_data_;			// 人脸图像数据，内部是cv::Mat数据
	int face_data_len_;					// 人脸图像数据长度
	std::string face_data_hash_;		// 人脸图像数据摘要

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
//	int face_count_;						// 人脸数量
//	BG_FASCE_INFO person_face_info_[16];	// 人员人脸信息，这里预留16张图片，以防需要时使用
//
//} BG_PERSON_WITH_FACE_INFO, *PBG_PERSON_WITH_FACE_INFO;

#endif//_bgFaceAIDef_H_
