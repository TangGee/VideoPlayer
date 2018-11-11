//
// Created by tlinux on 18-11-11.
//

#ifndef MYAPPLICATION6_YUVTEXTUREFRAMEUPLOADER_H
#define MYAPPLICATION6_YUVTEXTUREFRAMEUPLOADER_H


#include "TextureFrameUploader.h"

class YUVTextureFrameUploader : TextureFrameUploader {


public:
    YUVTextureFrameUploader();
    virtual ~YUVTextureFrameUploader();

    void init(int width,int height);
};


#endif //MYAPPLICATION6_YUVTEXTUREFRAMEUPLOADER_H
