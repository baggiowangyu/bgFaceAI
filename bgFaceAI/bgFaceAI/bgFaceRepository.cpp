#include "bgFaceRepository.h"

bgFaceRepository::bgFaceRepository()
	: session_(nullptr)
{
	Poco::Data::SQLite::Connector::registerConnector();
}

bgFaceRepository::~bgFaceRepository()
{
	Poco::Data::SQLite::Connector::unregisterConnector();
}

//////////////////////////////////////////////////////////////////////////
//
// ��ʼ��������
//
//////////////////////////////////////////////////////////////////////////

int bgFaceRepository::Initialize(int database_type, const char *ip, int port, const char *dbname, const char *dbusername, const char *dbpassword)
{
	int errCode = 0;
	std::string errstr;

	try
	{
		switch (database_type)
		{
		case DATABASE_TYPE_MySQL:
			break;
		case DATABASE_TYPE_Oracle:
			break;
		case DATABASE_TYPE_SQLite3:
			session_ = new Poco::Data::Session(Poco::Data::SQLite::Connector::KEY, ip);
			break;
		default:
			break;
		}
	}
	catch (Poco::Exception e)
	{
		errstr = e.displayText();
		errCode = e.code();

		return errCode;
	}

	// 2. ��ѯ��Ա�⣬��һ�������
	QueryPersons();

	return errCode;
}

void bgFaceRepository::Close()
{

}

//////////////////////////////////////////////////////////////////////////
//
// ��Ա����
//
//////////////////////////////////////////////////////////////////////////

int bgFaceRepository::AddPerson(PBG_PERSON_INFO person_info)
{
	int errCode = -1;
	std::string errstr;

	// ���ȼ���Ƿ���ڴ��û�
	// ʶ���û����㷨���£�
	// 1. �������
	// 2. ����Ա�
	// 3. ���֤�����
	// 4. ���֤����
	// ���϶���ͬ��������϶���ͬһ����Ա��Ϣ
	char sql[4096] = { 0 };
	sprintf(sql,
		"SELECT COUNT(*) "
		"FROM people_info "
		"WHERE person_name='%s' AND person_sex='%s' AND person_id_type='%s' AND person_id='%s';",
		person_info->person_name.c_str(),
		person_info->person_sex.c_str(),
		person_info->person_id_type.c_str(),
		person_info->person_id_number.c_str());

	try
	{
		int is_same_user = -1;
		*session_ << sql, Poco::Data::Keywords::into(is_same_user), Poco::Data::Keywords::now;
		if (is_same_user == 0)
		{
			// û���ҵ�ָ�����û�
			// �����û���Ϣ
			sprintf(sql,
				"INSERT "
				"INTO 'people_info'(person_name, person_sex, person_birthday, person_country, person_nation, person_id_type, person_id_number, person_address, person_contact_way, person_state) "
				"VALUES('%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', 1);",
				person_info->person_name.c_str(),
				person_info->person_sex.c_str(),
				person_info->person_birthday.c_str(),
				person_info->person_country.c_str(),
				person_info->person_nation.c_str(),
				person_info->person_id_type.c_str(),
				person_info->person_id_number.c_str(),
				person_info->person_address.c_str(),
				person_info->person_contact_way.c_str());

			*session_ << sql, Poco::Data::Keywords::into(is_same_user), Poco::Data::Keywords::now;

			// ��֤�Ƿ���ӳɹ���ֻ��Ҫ��ѯһ�ѾͿ�����
			sprintf(sql,
				"SELECT COUNT(*) "
				"FROM people_info "
				"WHERE person_name='%s' AND person_sex='%s' AND person_id_type='%s' AND person_id='%s';",
				person_info->person_name.c_str(),
				person_info->person_sex.c_str(),
				person_info->person_id_type.c_str(),
				person_info->person_id_number.c_str());

			int is_find_user = -1;
			*session_ << sql, Poco::Data::Keywords::into(is_find_user), Poco::Data::Keywords::now;
			if (is_find_user == 1)
				errCode = 0;
			else
				errCode = -1;
		}
	}
	catch (Poco::Exception e)
	{
		errstr = e.displayText();
		errCode = e.code();
	}

	return errCode;
}

int bgFaceRepository::ModifyPerson(PBG_PERSON_INFO person_info)
{
	int errCode = -1;
	std::string errstr;

	return errCode;
}

int bgFaceRepository::QueryPersons()
{
	int errCode = 0;
	std::string errstr;

	person_info_.clear();

	std::vector<int> person_number;
	std::vector<std::string> person_name;
	std::vector<std::string> person_sex;
	std::vector<std::string> person_birthday;
	std::vector<std::string> person_country;
	std::vector<std::string> person_nation;
	std::vector<std::string> person_id_type;
	std::vector<std::string> person_id_number;
	std::vector<std::string> person_address;
	std::vector<std::string> person_contact_way;
	std::vector<int> person_state;
	try
	{
		*session_ << "SELECT * FROM 'people_info'",
			Poco::Data::Keywords::into(person_number),
			Poco::Data::Keywords::into(person_name),
			Poco::Data::Keywords::into(person_sex),
			Poco::Data::Keywords::into(person_birthday),
			Poco::Data::Keywords::into(person_country),
			Poco::Data::Keywords::into(person_nation),
			Poco::Data::Keywords::into(person_id_type),
			Poco::Data::Keywords::into(person_id_number),
			Poco::Data::Keywords::into(person_address),
			Poco::Data::Keywords::into(person_contact_way),
			Poco::Data::Keywords::into(person_state),
			Poco::Data::Keywords::now;
	}
	catch (Poco::Exception e)
	{
		errstr = e.displayText();
		errCode = e.code();
		return errCode;
	}

	// �������
	for (int index = 0; index < person_number.size(); ++index)
	{
		wchar_t utf8_buffer[4096] = { 0 };
		char gbk_buffer[4096] = { 0 };

		// ����ĺ��ֲ���Ҫ��UTF8תΪGBK
		// δ�������ת��Ҫ��Poco��ʵ��
		BG_PERSON_INFO person_info;
		person_info.person_number = person_number[index];

		MultiByteToWideChar(CP_UTF8, 0, person_name[index].c_str(), -1, utf8_buffer, 4096);
		WideCharToMultiByte(CP_ACP, 0, utf8_buffer, -1, gbk_buffer, 4096, nullptr, nullptr);
		person_info.person_name = gbk_buffer;

		MultiByteToWideChar(CP_UTF8, 0, person_sex[index].c_str(), -1, utf8_buffer, 4096);
		WideCharToMultiByte(CP_ACP, 0, utf8_buffer, -1, gbk_buffer, 4096, nullptr, nullptr);
		person_info.person_sex = gbk_buffer;

		MultiByteToWideChar(CP_UTF8, 0, person_birthday[index].c_str(), -1, utf8_buffer, 4096);
		WideCharToMultiByte(CP_ACP, 0, utf8_buffer, -1, gbk_buffer, 4096, nullptr, nullptr);
		person_info.person_birthday = gbk_buffer;

		MultiByteToWideChar(CP_UTF8, 0, person_country[index].c_str(), -1, utf8_buffer, 4096);
		WideCharToMultiByte(CP_ACP, 0, utf8_buffer, -1, gbk_buffer, 4096, nullptr, nullptr);
		person_info.person_country = gbk_buffer;

		MultiByteToWideChar(CP_UTF8, 0, person_nation[index].c_str(), -1, utf8_buffer, 4096);
		WideCharToMultiByte(CP_ACP, 0, utf8_buffer, -1, gbk_buffer, 4096, nullptr, nullptr);
		person_info.person_nation = gbk_buffer;

		MultiByteToWideChar(CP_UTF8, 0, person_id_type[index].c_str(), -1, utf8_buffer, 4096);
		WideCharToMultiByte(CP_ACP, 0, utf8_buffer, -1, gbk_buffer, 4096, nullptr, nullptr);
		person_info.person_id_type = gbk_buffer;

		MultiByteToWideChar(CP_UTF8, 0, person_id_number[index].c_str(), -1, utf8_buffer, 4096);
		WideCharToMultiByte(CP_ACP, 0, utf8_buffer, -1, gbk_buffer, 4096, nullptr, nullptr);
		person_info.person_id_number = gbk_buffer;

		MultiByteToWideChar(CP_UTF8, 0, person_address[index].c_str(), -1, utf8_buffer, 4096);
		WideCharToMultiByte(CP_ACP, 0, utf8_buffer, -1, gbk_buffer, 4096, nullptr, nullptr);
		person_info.person_address = gbk_buffer;

		MultiByteToWideChar(CP_UTF8, 0, person_contact_way[index].c_str(), -1, utf8_buffer, 4096);
		WideCharToMultiByte(CP_ACP, 0, utf8_buffer, -1, gbk_buffer, 4096, nullptr, nullptr);
		person_info.person_contact_way = gbk_buffer;

		person_info.person_state = person_state[index];

		person_info_.push_back(person_info);
	}

	return errCode;
}

PBG_PERSON_INFO bgFaceRepository::QueryPerson(const char *name, const char *sex, const char *id_type, const char *id_number)
{
	int errCode = -1;
	std::string errstr;

	PBG_PERSON_INFO person_info = nullptr;

	std::vector<int> person_number;
	std::vector<std::string> person_name;
	std::vector<std::string> person_sex;
	std::vector<std::string> person_birthday;
	std::vector<std::string> person_country;
	std::vector<std::string> person_nation;
	std::vector<std::string> person_id_type;
	std::vector<std::string> person_id_number;
	std::vector<std::string> person_address;
	std::vector<std::string> person_contact_way;
	std::vector<int> person_state;

	// ���ȼ���Ƿ���ڴ��û�
	// ʶ���û����㷨���£�
	// 1. �������
	// 2. ����Ա�
	// 3. ���֤�����
	// 4. ���֤����
	// ���϶���ͬ��������϶���ͬһ����Ա��Ϣ
	char sql[4096] = { 0 };
	sprintf(sql,
		"SELECT * "
		"FROM people_info "
		"WHERE person_name='%s' AND person_sex='%s' AND person_id_type='%s' AND person_id='%s';",
		name,
		sex,
		id_type,
		id_number);

	try
	{
		int is_same_user = -1;
		*session_ << sql, 
			Poco::Data::Keywords::into(person_number),
			Poco::Data::Keywords::into(person_name),
			Poco::Data::Keywords::into(person_sex),
			Poco::Data::Keywords::into(person_birthday),
			Poco::Data::Keywords::into(person_country),
			Poco::Data::Keywords::into(person_nation),
			Poco::Data::Keywords::into(person_id_type),
			Poco::Data::Keywords::into(person_id_number),
			Poco::Data::Keywords::into(person_address),
			Poco::Data::Keywords::into(person_contact_way),
			Poco::Data::Keywords::into(person_state),
			Poco::Data::Keywords::now;
		if (person_number.size() == 0)
			person_info = nullptr;
		else
		{
			person_info = new BG_PERSON_INFO;
			person_info->person_number = person_number[0];
			person_info->person_name = person_name[0];
			person_info->person_sex = person_sex[0];
			person_info->person_birthday = person_birthday[0];
			person_info->person_country = person_country[0];
			person_info->person_nation = person_nation[0];
			person_info->person_id_type = person_id_type[0];
			person_info->person_id_number = person_id_number[0];
			person_info->person_address = person_address[0];
			person_info->person_contact_way = person_contact_way[0];
			person_info->person_state = person_state[0];
		}
	}
	catch (Poco::Exception e)
	{
		errstr = e.displayText();
		errCode = e.code();
		return nullptr;
	}

	return person_info;
}

int bgFaceRepository::DeletePerson(PBG_PERSON_INFO person_info)
{
	int errCode = -1;
	std::string errstr;

	

	return errCode;
}

//////////////////////////////////////////////////////////////////////////
//
// ��������
//
//////////////////////////////////////////////////////////////////////////

int bgFaceRepository::AddFace(PBG_FASCE_INFO face_info)
{
	// ��������������Ѿ������������

	int errCode = -1;
	std::string errstr;

	// �����жϣ��Ƿ������ͬ��������ʹ���������ݵ�ɢ��ֵ���м���
	char sql[4096] = { 0 };
	sprintf(sql,
		"SELECT face_tag "
		"FROM face_info "
		"WHERE face_hash='%s';",
		face_info->face_data_hash_);

	try
	{
		std::vector<int> face_tag;
		*session_ << sql, Poco::Data::Keywords::into(face_tag), Poco::Data::Keywords::now;

		// �����������0����˵���Ѿ�����ͬ�������ˣ���������ID
		if (face_tag.size() > 0)
			return face_tag[1];
	}
	catch (Poco::Exception e)
	{
		errstr = e.displayText();
		errCode = e.code();

		errCode = -1;
		return errCode;
	}

	// ���û����ͬ����������������ݿ�����������tagֵ��1���õ�����������tag��ǩ
	sprintf(sql,
		"SELECT MAX(face_tag) "
		"FROM face_info;");

	try
	{
		int max_tag = -1;
		*session_ << sql, Poco::Data::Keywords::into(max_tag), Poco::Data::Keywords::now;

		max_tag += 1;

		// ��������������������
		sprintf(sql,
			"INSERT "
			"INTO 'face_info'(face_tag, face_data, face_hash) "
			"VALUES(%d, :img, '%s'); ", max_tag, face_info->face_data_hash_.c_str());

		Poco::Data::BLOB image(face_info->face_data_, face_info->face_data_len_);
		*session_ << sql, Poco::Data::Keywords::use(image), Poco::Data::Keywords::now;

		errCode = max_tag;

		// ִ����ɺ����²�ѯһ�Σ��õ�
		// ����˵������ʧ�ܻ��׳��쳣��
	}
	catch (Poco::Exception e)
	{
		errstr = e.displayText();
		errCode = e.code();

		errCode = -1;
	}

	return errCode;
}

int bgFaceRepository::DeleteFace(int face_id)
{
	int errCode = 0;
	std::string errstr;

	char sql[4096] = { 0 };
	sprintf(sql,
		"DELETE "
		"FROM face_info"
		"WHERE face_tag = %d;", face_id);

	try
	{
		*session_ << sql, Poco::Data::Keywords::now;
	}
	catch (Poco::Exception e)
	{
		errstr = e.displayText();
		errCode = e.code();

		errCode = -1;
	}

	return errCode;
}

//////////////////////////////////////////////////////////////////////////
//
// ��Ա������������
//
//////////////////////////////////////////////////////////////////////////

int bgFaceRepository::AddBindInfo(int person_number, int face_tag)
{
	int errCode = 0;
	std::string errstr;

	// ����Ͳ������ˣ�ֱ�ӿ���
	//char sql[4096] = { 0 };
	//sprintf(sql,
	//	"INSERT "
	//	"INTO people_face_info(face_tag, person_number)"
	//	"VALUES(%d, %d);", face_tag, person_number);

	try
	{
		*session_ << "INSERT INTO people_face_info(face_tag, person_number) VALUES(:ft, :pn);",
			Poco::Data::Keywords::use(face_tag),
			Poco::Data::Keywords::use(person_number),
			Poco::Data::Keywords::now;
	}
	catch (Poco::Exception e)
	{
		errstr = e.displayText();
		errCode = e.code();
	}

	return errCode;
}

int bgFaceRepository::DeleteBindInfo(int person_number, int face_tag)
{
	int errCode = 0;
	std::string errstr;

	// ����Ͳ������ˣ�ֱ�ӿ���
	//char sql[4096] = { 0 };
	//sprintf(sql,
	//	"INSERT "
	//	"INTO people_face_info(face_tag, person_number)"
	//	"VALUES(%d, %d);", face_tag, person_number);

	try
	{
		*session_ << "DELETE FROM people_face_info WHERE face_tag=:ft AND person_number=:pn;",
			Poco::Data::Keywords::use(face_tag),
			Poco::Data::Keywords::use(person_number),
			Poco::Data::Keywords::now;
	}
	catch (Poco::Exception e)
	{
		errstr = e.displayText();
		errCode = e.code();
	}

	return errCode;
}

int bgFaceRepository::DeleteBindInfo(int person_number)
{
	int errCode = 0;
	std::string errstr;

	// ����Ͳ������ˣ�ֱ�ӿ���
	//char sql[4096] = { 0 };
	//sprintf(sql,
	//	"INSERT "
	//	"INTO people_face_info(face_tag, person_number)"
	//	"VALUES(%d, %d);", face_tag, person_number);

	try
	{
		*session_ << "DELETE FROM people_face_info WHERE person_number=:pn;",
			Poco::Data::Keywords::use(person_number),
			Poco::Data::Keywords::now;
	}
	catch (Poco::Exception e)
	{
		errstr = e.displayText();
		errCode = e.code();
	}

	return errCode;
}

int bgFaceRepository::QueryBindInfo(int person_number)
{
	int errCode = 0;
	std::string errstr;

	person_face_tags.clear();
	
	try
	{
		*session_ << "SELECT face_tag FROM people_face_info WHERE person_number=:pn;",
			Poco::Data::Keywords::use(person_number),
			Poco::Data::Keywords::into(person_face_tags),
			Poco::Data::Keywords::now;
	}
	catch (Poco::Exception e)
	{
		errstr = e.displayText();
		errCode = e.code();
	}

	return errCode;
}