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
	// 初始化人脸库
	//
	//////////////////////////////////////////////////////////////////////////
	int Initialize(int database_type, const char *ip, int port, const char *dbname, const char *dbusername, const char *dbpassword);
	void Close();

public:
	//////////////////////////////////////////////////////////////////////////
	//
	// 人员管理
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
	// 人脸管理
	//
	//////////////////////////////////////////////////////////////////////////

	/**
	 * 添加人脸
	 * 参数：
	 *	@
	 * 返回值：
	 *	成功：返回人脸tag
	 *	失败：返回-1；
	 */
	int AddFace(PBG_FASCE_INFO face_info);
	//int ModifyFace(PBG_FASCE_INFO face_info);
	//int QueryFaces();
	//PBG_FASCE_INFO QueryFace();
	int DeleteFace(int face_id);

public:
	//////////////////////////////////////////////////////////////////////////
	//
	// 人员人脸关联管理
	//
	//////////////////////////////////////////////////////////////////////////

	/**
	 * 添加
	 */
	int AddBindInfo(int person_number, int face_tag);
	int DeleteBindInfo(int person_number, int face_tag);
	int DeleteBindInfo(int person_number);
	int QueryBindInfo(int person_number);

public:
	// 这里应该有个人脸锁，在添加人脸的时候必须锁上

public:
	std::vector<BG_PERSON_INFO> person_info_;
	std::vector<BG_FASCE_INFO> face_info_;
	std::vector<int> person_face_tags;

private:
	Poco::Data::Session *session_;
};

#endif//_bgFaceRepository_H_