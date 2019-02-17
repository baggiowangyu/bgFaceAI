#ifndef _bgFaceAI_H_
#define _bgFaceAI_H_

#include <string>
#include <vector>

#include "bgFaceAIDef.h"

class bgFaceRepository;
class bgFaceRecognition;


/**
 * ������һ������ֻ��ʶ���������Ҫ�����¼������ܣ�
 * 1. ������Ĺ���
 *    - ��Ա��Ϣ������Ա�Ļ�����Ϣ��
 *    - ������Ϣ����������Ϣ��������ͼƬ������ͼƬ��ժҪ������ѵ������ʶ������������ǩ��
 *    - ��Ա��������Ӧ��ϵ����һ����Ա���Թ������������һ������ֻ����һ����Ա��
 * 2. ����ʶ��ģ��Ĺ���
 *    - ��������ֵ��ѵ����ѵ����Դ��������1.���ݿⱣ���������������ǩ�����ڴ�0��ʼ�������������⣻2.�����ӵ�����������������������⣩
 *    - �ṩ�ӿڽ�������ʶ��
 */
class DLL_API bgFaceAI
{
public:
	bgFaceAI();
	~bgFaceAI();

public:
	// ��ʼ�����������ݿ�
	// ���ݿ�Ӧ��֧��MySQL��Oracle��SQLite3�ȳ�����ϵ�����ݿ�(ʹ��ODBC��ʽ)
	// ���ڿ��Կ���ʹ��MongoDB
	// �����SQLite������ip����д���ݿ�·������������
	int Initialize(int database_type, const char *ip, int port, const char *dbname, const char *dbusername, const char *dbpassword);
	int Initialize(const char *connection_string);
	void Close();

public:
	// ����������������ԭʼͼƬ������ԭʼͼƬ��ֻ�ܰ���һ������
	int AddPerson(BG_PERSON_INFO &person_info);
	int AddFace(int person_number, int face_count, PBG_FASCE_INFO face_infos);
	int RemoveFace(int person_id);

	int QueryPersonBegin();
	int QueryNextPerson(BG_PERSON_INFO &person_info);
	int QueryPersonEnd();

	int QueryFaceByPerson(int person_number, std::vector<int> &face_tags);

public:
	// ʶ������
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
