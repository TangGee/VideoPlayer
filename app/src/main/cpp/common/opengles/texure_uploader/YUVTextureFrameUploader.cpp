//
// Created by tlinux on 18-11-11.
//

#include <alog.h>
#include <opengles/teture/YUVTextureFrame.h>
#include "YUVTextureFrameUploader.h"


#define LOG_TAG "YUVTextureFrameUploader"

YUVTextureFrameUploader::YUVTextureFrameUploader() {
    ALOGI("new YUVTextureFrameUploader");
}

YUVTextureFrameUploader::~YUVTextureFrameUploader() {
    ALOGI("new YUVTextureFrameUploader");
    TextureFrameUploader::~TextureFrameUploader();
}

void YUVTextureFrameUploader::init(int width, int height) {
    TextureFrameUploader::init(width,height);
    textureFrame = new YUVTextureFrame;
    textureFrame->createTexture();
}