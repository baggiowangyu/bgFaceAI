#ifndef _bgMedia_H_
#define _bgMedia_H_

#ifdef BGDATAACQUISITION_EXPORTS
#define DLL_API __declspec(dllexport)
#else
#define DLL_API __declspec(dllimport)
#endif

#define MEDIATYPE_CAMERA		0	// ����ͷ
#define MEDIATYPE_MICROPHONE	1	// ��˷�

class bgMediaKernal;


#define MEDIANOTIFY_TYPE_FACE_IMAGE		0x00001001	// ��̬ץȡ����

// ������ʵ��
class bgMediaNotify
{
public:
	virtual void DataCallback(int notify_type, void* notify_data) = 0;
};

class DLL_API bgMedia
{
public:
	bgMedia();
	~bgMedia();

public:
	// ��ʼ���豸
	// ������
	//	@media_type		�豸����
	int Initialize(int media_type);

	// �ͷ���Դ
	void Uninitialize();

	// ���豸
	int Open(int index, void* screen_windows);

	// �ر��豸
	void Close();

	// ����ץȡƵ��

private:
	bgMediaKernal *media_kernal_;
};

#endif//_bgMedia_H_