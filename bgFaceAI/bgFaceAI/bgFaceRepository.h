#ifndef _bgFaceRepository_H_
#define _bgFaceRepository_H_

#include "bgFaceAIDef.h"

#include "Poco/Data/Session.h"
#include "Poco/Data/SQLite/Connector.h"
#include "Poco/AccessExpireCache.h"

class DLL_API bgFaceRepository
{
public:
	bgFaceRepository();
	~bgFaceRepository();

public:
	//////////////////////////////////////////////////////////////////////////
	//
	// ��ʼ��������
	//
	//////////////////////////////////////////////////////////////////////////
	int Initialize(int database_type, const char *ip, int port, const char *dbname, const char *dbusername, const char *dbpassword);
	void Close();

public:
	//////////////////////////////////////////////////////////////////////////
	//
	// ��Ա����
	//
	//////////////////////////////////////////////////////////////////////////
	int AddPerson(PBG_PERSON_INFO person_info);
	int ModifyPerson(PBG_PERSON_INFO person_info);
	int QueryPersons();
	PBG_PERSON_INFO QueryPerson(const char *name, const char *sex, const char *id_type, const char *id_number);
	int DeletePerson(PBG_PERSON_INFO person_info);

public:
	//////////////////////////////////////////////////////////////////////////
	//
	// ��������
	//
	//////////////////////////////////////////////////////////////////////////

	/**
	 * �������
	 * ������
	 *	@
	 * ����ֵ��
	 *	�ɹ�����������tag
	 *	ʧ�ܣ�����-1��
	 */
	int AddFace(PBG_FASCE_INFO face_info);
	//int ModifyFace(PBG_FASCE_INFO face_info);
	//int QueryFaces();
	//PBG_FASCE_INFO QueryFace();
	int DeleteFace(int face_id);

public:
	//////////////////////////////////////////////////////////////////////////
	//
	// ��Ա������������
	//
	//////////////////////////////////////////////////////////////////////////

	/**
	 * ���
	 */
	int AddBindInfo(int person_number, int face_tag);
	int DeleteBindInfo(int person_number, int face_tag);
	int DeleteBindInfo(int person_number);
	int QueryBindInfo(int person_number);

public:
	// ����Ӧ���и��������������������ʱ���������

public:
	std::vector<BG_PERSON_INFO> person_info_;
	std::vector<BG_FASCE_INFO> face_info_;
	std::vector<int> person_face_tags;

private:
	Poco::Data::Session *session_;
};

#endif//_bgFaceRepository_H_