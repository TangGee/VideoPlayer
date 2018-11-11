//
// Created by tlinux on 18-11-10.
//

#include "FFMpegVideoDecoder.h"



VideoFrame* FFMpegVideoDecoder::handleVideoFrame(AVFrame *avFrame) {
    if (!avFrame) {
        ALOGE("handleVideoFrame avFrame is nullptr");
        return nullptr;
    }
    //YUV 420
    int width = FFMIN(avFrame->linesize[0],avCodecContext->width);
    int height = avCodecContext->height;

    int yWidth = width;

    int lumaLength = width *height;
    uint8_t *luma = new uint8_t[lumaLength];
    copyFrameData(luma,avFrame->data[0],width,height,avFrame->linesize[0]);

    width = FFMIN(avFrame->linesize[1],avCodecContext->width/2);
    height = avCodecContext->height/2;
    int chomaBLength = width*height;
    uint8_t *chomaB = new uint8_t[chomaBLength];
    copyFrameData(chomaB,avFrame->data[1],width,height,avFrame->linesize[1]);


    width = FFMIN(avFrame->linesize[2],avCodecContext->width/2);
    int chomaRLength = width*height;
    uint8_t *chomaR = new uint8_t[chomaRLength];
    copyFrameData(chomaR,avFrame->data[2],width,height,avFrame->linesize[1]);

    ALOGI("lumaLength: %d, chomaBLength: %d, chomaRLength: %d, height: %d", lumaLength,
          chomaBLength,chomaRLength,avCodecContext->height );
    return new VideoFrame(yWidth,avCodecContext->height,avFrame->best_effort_timestamp,
                          avFrame->pkt_duration,luma,chomaB,chomaR);
}

void FFMpegVideoDecoder::copyFrameData(uint8_t *dst, uint8_t *src, int width, int height,
                                       int lineSize) {
    for (int i = 0; i < height; ++i) {
        memcpy(dst,src,width);
        dst += width;
        src += lineSize;
    }
}