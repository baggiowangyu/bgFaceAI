#include "bgMediaKernal.h"

bgMediaKernal::bgMediaKernal()
	: device_format_context_(nullptr)
	, device_input_format_(nullptr)
	, video_codec_context_(nullptr)
	, audio_codec_context_(nullptr)
	, video_codec_(nullptr)
	, frame_rate_(0)
	, screen_windows_(nullptr)
	, screen_width_(0)
	, screen_height_(0)
	, face_cascade_(new cv::CascadeClassifier())
	, eyes_cascade_(new cv::CascadeClassifier())
{}

bgMediaKernal::~bgMediaKernal()
{}

int bgMediaKernal::Initialize(int device_type)
{
	int errCode = 0;

	av_register_all();
	avformat_network_init();
	avdevice_register_all();
	avcodec_register_all();

	device_format_context_ = avformat_alloc_context();
	if (device_format_context_ == nullptr)
		return -1;

	device_input_format_ = av_find_input_format("vfwcap");
	if (device_input_format_ == nullptr)
		return -2;

	// �������������
	bool bret = face_cascade_->load("haarcascade_frontalface_alt.xml");
	if (!bret)
		return -3;

	return errCode;
}

void bgMediaKernal::Uninitialize()
{}

int bgMediaKernal::Open(int device_index, void* screen_windows)
{
	int errCode = 0;

	// ��鵱ǰ�豸�Ƿ����ڹ���
	if (working_thread_.isRunning())
		return -99;

	screen_windows_ = screen_windows;

	// ȡ�ô��ڵĿ��
	RECT rc;
	GetWindowRect((HWND)screen_windows_, &rc);
	screen_width_ = rc.right - rc.left;
	screen_height_ = rc.bottom - rc.top;

	errCode = avformat_open_input(&device_format_context_, "0", device_input_format_, NULL);
	if (errCode != 0)
		return -1;

	errCode = avformat_find_stream_info(device_format_context_, NULL);
	if (errCode < 0)
		return -2;

	int video_stream_index = -1;
	//int audio_stream_index = -1;

	for (int index = 0; index < device_format_context_->nb_streams; ++index)
	{
		switch (device_format_context_->streams[index]->codec->codec_type)
		{
		case AVMEDIA_TYPE_VIDEO:
			video_stream_index = index;
			frame_rate_ = device_format_context_->streams[index]->avg_frame_rate.num / device_format_context_->streams[index]->avg_frame_rate.den;
			break;
		//case AVMEDIA_TYPE_AUDIO:
		//	audio_stream_index = index;
		//	break;
		default:
			break;
		}
	}

	video_codec_context_ = device_format_context_->streams[video_stream_index]->codec;
	//audio_codec_context_ = device_format_context_->streams[audio_stream_index]->codec;

	video_codec_ = avcodec_find_decoder(video_codec_context_->codec_id);
	if (video_codec_ == NULL)
		return -3;

	errCode = avcodec_open2(video_codec_context_, video_codec_, NULL);
	if (errCode < 0)
		return -4;

	// �����̣߳���������
	working_thread_.start(bgMediaKernal::WorkingThreadFunc, this);
	Poco::Thread::sleep(1);

	// �����̣߳�ץȡ����
	face_detect_thread_.start(bgMediaKernal::FaceDetectThreadFunc, this);
	Poco::Thread::sleep(1);

	return errCode;
}

void bgMediaKernal::Close()
{}

cv::Mat bgMediaKernal::AVFrameToCVMat(AVFrame *frame)
{
	AVFrame dst;
	cv::Mat m;

	memset(&dst, 0, sizeof(dst));

	int w = frame->width, h = frame->height;
	m = cv::Mat(h, w, CV_8UC3);
	dst.data[0] = (uint8_t *)m.data;
	avpicture_fill((AVPicture *)&dst, dst.data[0], AV_PIX_FMT_BGR24, w, h);

	struct SwsContext *convert_ctx = NULL;
	enum AVPixelFormat src_pixfmt = (enum AVPixelFormat)frame->format;
	enum AVPixelFormat dst_pixfmt = AV_PIX_FMT_BGR24;
	convert_ctx = sws_getContext(w, h, src_pixfmt, w, h, dst_pixfmt, SWS_FAST_BILINEAR, NULL, NULL, NULL);
	sws_scale(convert_ctx, frame->data, frame->linesize, 0, h, dst.data, dst.linesize);
	sws_freeContext(convert_ctx);

	return m;
}

void bgMediaKernal::WorkingThreadFunc(void* param)
{
	bgMediaKernal *kernal_ = (bgMediaKernal *)param;

	//////////////////////////////////////////////////////////////////////////
	//
	// ��Ƶͼ��ת����ǰ�ڲ�����׼��ת��ΪYUV�ļ�
	//
	//////////////////////////////////////////////////////////////////////////
	AVFrame *video_frame_yuv = av_frame_alloc();

	int video_frame_yuv_buffer_size = av_image_get_buffer_size(AV_PIX_FMT_YUV420P, kernal_->video_codec_context_->width, kernal_->video_codec_context_->height, 1);
	unsigned char *video_frame_yuv_buffer = (unsigned char *)av_malloc(video_frame_yuv_buffer_size);
	av_image_fill_arrays(video_frame_yuv->data, video_frame_yuv->linesize, video_frame_yuv_buffer, AV_PIX_FMT_YUV420P,
		kernal_->video_codec_context_->width, kernal_->video_codec_context_->height, 1);

	struct SwsContext *image_convert_context = sws_getContext(kernal_->video_codec_context_->width, kernal_->video_codec_context_->height, kernal_->video_codec_context_->pix_fmt,
		kernal_->video_codec_context_->width, kernal_->video_codec_context_->height, AV_PIX_FMT_YUV420P, SWS_BICUBIC, NULL, NULL, NULL);


	int source_width = kernal_->video_codec_context_->width;
	int source_height = kernal_->video_codec_context_->height;
	int screen_width = kernal_->screen_width_;
	int screen_height = kernal_->screen_height_;

	int errCode = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER);
	if (errCode != 0)
		return ;

	SDL_Window *sdl_window_ = SDL_CreateWindowFrom(kernal_->screen_windows_);
	if (!sdl_window_)
		return ;

	SDL_Renderer *sdl_renderer_ = SDL_CreateRenderer(sdl_window_, -1, 0);
	if (!sdl_renderer_)
		return ;

	// ����һ��ָ����С������
	SDL_Texture *sdl_texture_ = SDL_CreateTexture(sdl_renderer_, SDL_PIXELFORMAT_IYUV, SDL_TEXTUREACCESS_STREAMING, source_width, source_height);
	if (!sdl_texture_)
		return ;

	SDL_Rect rect;
	rect.x = 0;
	rect.y = 0;
	rect.w = screen_width;
	rect.h = screen_height;

	//////////////////////////////////////////////////////////////////////////
	//
	// ��ʼ��ȡ����ͷ����Ƶ����
	//
	//////////////////////////////////////////////////////////////////////////
	int index = 0;
	int frame_count = 0;
	AVPacket av_packet;
	while (true)
	{
		errCode = av_read_frame(kernal_->device_format_context_, &av_packet);
		if (errCode < 0)
			break;

		int got_pic = 0;
		AVFrame *av_frame = av_frame_alloc();
		errCode = avcodec_decode_video2(kernal_->video_codec_context_, av_frame, &got_pic, &av_packet);
		if (errCode < 0)
			continue;

		if (!got_pic)
			continue;

		// ���ﰴ�ղ���(Ĭ��1��)������Ƶ֡ת��ΪMat���������
		// ��������һ�������߳�����
		if (frame_count > (kernal_->frame_rate_ / 4))
		{
			// ת����Mat�����
			cv::Mat opencv_image = kernal_->AVFrameToCVMat(av_frame);
			kernal_->image_queue_.push(opencv_image);
			frame_count = 0;
			++index;
		}

		// ͼ���ʽת��
		sws_scale(image_convert_context, (const unsigned char* const*)av_frame->data, av_frame->linesize, 0,
			kernal_->video_codec_context_->height, video_frame_yuv->data, video_frame_yuv->linesize);

		// ͼ����Ҫ�����񣬲�Ȼ��ʾ�Ĳ���....

		SDL_UpdateTexture(sdl_texture_, NULL, video_frame_yuv->data[0], video_frame_yuv->linesize[0]);
		SDL_RenderCopy(sdl_renderer_, sdl_texture_, NULL, &rect);
		SDL_RenderPresent(sdl_renderer_);

		av_frame_free(&av_frame);

		++frame_count;
	}
}

void bgMediaKernal::FaceDetectThreadFunc(void* param)
{
	bgMediaKernal *kernal_ = (bgMediaKernal *)param;

	// ����ֻ��һ�����񣬾��Ǽ�黺�����Ƿ����δ�����ͼ������У�����û��������
	while (true)
	{
		if (kernal_->image_queue_.empty())
		{
			Poco::Thread::sleep(100);
			continue;
		}

		cv::Mat original_image = kernal_->image_queue_.front();
		kernal_->image_queue_.pop();

		cv::Mat frame = original_image.clone();

		// ͼ��ҶȻ�����Ҫ������
		cv::cvtColor(original_image, original_image, cv::COLOR_BGR2GRAY);

		// ֱ��ͼ���⻯��ͼ����ǿ�����ı��������ı䰵
		cv::equalizeHist(original_image, original_image);

		// ��⵽��������������
		std::vector<cv::Rect> faces;
		kernal_->face_cascade_->detectMultiScale(original_image, faces, 1.1, 2, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30));

		for (size_t index = 0; index < faces.size(); ++index)
		{
			// ���ƾ��� BGR
			cv::rectangle(frame, faces[index], cv::Scalar(0, 0, 255), 1);

			// ��ȡ����
			cv::Mat facesROI = frame(faces[index]);

			// ͼ������
			cv::resize(facesROI, facesROI, cv::Size(128, 128), 0, 0, cv::INTER_LINEAR);

			// ����ͼ��
			cv::Mat founded_face = facesROI;

			// ����Ӧ����һ���ص�������������ͼ��ص����ϲ㣬���ϲ�ȥ����

			// ���ݵ�ǰʱ����Ϊ�ļ����洢
			Poco::Timestamp timestamp;
			timestamp.update();

			Poco::DateTime current_time(timestamp);

			char output_file_name[4096] = { 0 };
			sprintf(output_file_name, "face_%d%02d%02d_%02d%02d%02d.jpg",
				current_time.year(), current_time.month(), current_time.day(),
				current_time.hour(), current_time.minute(), current_time.second());

			cv::imwrite(output_file_name, facesROI);
		}
	}
}