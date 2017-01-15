#include "pxcsensemanager.h"
#include <stdio.h>

void main() {
	// Create the session manager
	PXCSenseManager *sense_mgr = PXCSenseManager::CreateInstance();
	// Select the stream. Note that if the format of the stream is not supported, the Init() will fail
	sense_mgr->EnableStream(PXCCapture::STREAM_TYPE_DEPTH, 640, 480, 30);
	sense_mgr->EnableStream(PXCCapture::STREAM_TYPE_COLOR, 640, 480, 30);
	// Start the camera. If the stream size is wrong, the following will fail
	pxcStatus status = sense_mgr->Init();
	if (PXC_STATUS_NO_ERROR != status)
	{
		printf_s("Status is %d\n", status);
		return;
	}

	// Processing the image
	for (;;) {
		// This function blocks until a sample is ready
		if (sense_mgr->AcquireFrame(true)<PXC_STATUS_NO_ERROR) break;
		// retrieve the sample
		PXCCapture::Sample *sample = sense_mgr->QuerySample();

		// work on the image sample->color
		PXCImage *image = sample->depth;
		PXCImage::ImageInfo imageInfo = image->QueryInfo();

		// go fetching the next sample
		sense_mgr->ReleaseFrame();
	}

	// Close down
	sense_mgr->Release();
}