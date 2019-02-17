#include "bgDevice.h"
#include "bgMediaKernal.h"

bgMedia::bgMedia()
	: media_kernal_(new bgMediaKernal())
{}

bgMedia::~bgMedia()
{
	if (media_kernal_)
		delete media_kernal_;
	media_kernal_ = nullptr;
}

int bgMedia::Initialize(int media_type)
{
	return media_kernal_->Initialize(media_type);
}

void bgMedia::Uninitialize()
{}

int bgMedia::Open(int index, void* screen_windows)
{
	return media_kernal_->Open(index, screen_windows);
}

void bgMedia::Close()

{}