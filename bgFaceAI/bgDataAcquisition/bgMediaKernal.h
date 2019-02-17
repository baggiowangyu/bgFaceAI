#ifndef _bgMediaKernal_H_
#define _bgMediaKernal_H_

#include <queue>

// Poco 库
#include "Poco/Thread.h"
#include "Poco/DateTime.h"


// FFMpeg 库
#ifdef __cplusplus
extern "C" {
#endif
#include "libavformat\avformat.h"
#include "libavcodec\avcodec.h"
#include "libavdevice\avdevice.h"
#include "libavutil\avutil.h"
#include "libswscale\swscale.h"
#include "libavutil/rational.h"
#include "libavutil/pixdesc.h"
#include "libavutil/samplefmt.h"
#include "libswresample/swresample.h"
#include "libavutil/imgutils.h"
#ifdef __cplusplus
};
#endif

#pragma comment(lib, "avcodec.lib")
#pragma comment(lib, "avdevice.lib")
#pragma comment(lib, "avfilter.lib")
#pragma comment(lib, "avformat.lib")
#pragma comment(lib, "avutil.lib")
#pragma comment(lib, "postproc.lib")
#pragma comment(lib, "swresample.lib")
#pragma comment(lib, "swscale.lib")


// SDL2库
#include "SDL.h"

#pragma comment(lib, "SDL2.lib")

// OpenCV库
#include "opencv/cv.h"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/objdetect.hpp"

#ifdef _DEBUG
#pragma comment(lib, "opencv_core345d.lib")
//#pragma comment(lib, "opencv_highgui345d.lib")
//#pragma comment(lib, "opencv_face345d.lib")
#pragma comment(lib, "opencv_imgproc345d.lib")
#pragma comment(lib, "opencv_imgcodecs345d.lib")
#pragma comment(lib, "opencv_objdetect345d.lib")
#else
#pragma comment(lib, "opencv_core345.lib")
//#pragma comment(lib, "opencv_highgui345d.lib")
//#pragma comment(lib, "opencv_face345d.lib")
#pragma comment(lib, "opencv_imgproc345.lib")
#pragma comment(lib, "opencv_imgcodecs345.lib")
#pragma comment(lib, "opencv_objdetect345.lib")
#endif

class bgMediaKernal
{
public:
	bgMediaKernal();
	~bgMediaKernal();

public:
	int Initialize(int device_type = 0); 
	void Uninitialize();

	int Open(int device_index, void* screen_windows);
	void Close();

public:
	cv::Mat AVFrameToCVMat(AVFrame *frame);
	// 定义一个缓存，用于存放缓存下来的视频帧
	// 定义一个缓存，用于存放抠出的人脸
	// 定义一个线程，用于进行抠图
	// 定义一个线程，用于将抠出的图向上层送出

public:
	AVFormatContext *device_format_context_;
	AVInputFormat *device_input_format_;

	AVCodecContext *video_codec_context_;
	AVCodecContext *audio_codec_context_;

	AVCodec *video_codec_;
	int frame_rate_;

	void* screen_windows_;
	int screen_width_;
	int screen_height_;

private:
	Poco::Thread working_thread_;
	static void WorkingThreadFunc(void* param);

	Poco::Thread face_detect_thread_;
	static void FaceDetectThreadFunc(void* param);

public:
	std::queue<cv::Mat> image_queue_;
	std::queue<cv::Mat> face_queue_;

public:
	cv::CascadeClassifier *face_cascade_;
	cv::CascadeClassifier *eyes_cascade_;
};

#endif//_bgMediaKernal_H_