#ifndef _bgMedia_H_
#define _bgMedia_H_

#ifdef BGDATAACQUISITION_EXPORTS
#define DLL_API __declspec(dllexport)
#else
#define DLL_API __declspec(dllimport)
#endif

#define MEDIATYPE_CAMERA		0	// 摄像头
#define MEDIATYPE_MICROPHONE	1	// 麦克风

class bgMediaKernal;


#define MEDIANOTIFY_TYPE_FACE_IMAGE		0x00001001	// 动态抓取人脸

// 调用者实现
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
	// 初始化设备
	// 参数：
	//	@media_type		设备类型
	int Initialize(int media_type);

	// 释放资源
	void Uninitialize();

	// 打开设备
	int Open(int index, void* screen_windows);

	// 关闭设备
	void Close();

	// 设置抓取频率

private:
	bgMediaKernal *media_kernal_;
};

#endif//_bgMedia_H_