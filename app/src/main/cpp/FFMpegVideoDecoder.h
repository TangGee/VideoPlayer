//
// Created by tlinux on 18-11-10.
//

#ifndef MYAPPLICATION6_FFMPEGVIDEODECODER_H
#define MYAPPLICATION6_FFMPEGVIDEODECODER_H


#include <opengles/media/VideoFrame.h>
#include <libavutil/frame.h>
#include "common/FFMPeg.h"

#define LOG_TAG "FFMpegVideoDecoder"
#define LOG_NDEBUG 0

#include <alog.h>

class FFMpegVideoDecoder {
private:
    AVCodecContext *avCodecContext;

public:
    FFMpegVideoDecoder(AVCodecContext* avCodecContext):avCodecContext(avCodecContext) {
    }

    VideoFrame *handleVideoFrame(AVFrame *avFrame);

    void copyFrameData(uint8_t *dst, uint8_t *src, int width,int height, int lineSize) ;
};


#endif //MYAPPLICATION6_FFMPEGVIDEODECODER_H
