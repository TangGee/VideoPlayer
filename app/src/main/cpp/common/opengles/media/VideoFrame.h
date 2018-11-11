//
// Created by tlinux on 18-11-10.
//

#ifndef MYAPPLICATION6_VIDEOFRAME_H
#define MYAPPLICATION6_VIDEOFRAME_H


#include <MovieFrame.h>
#include "../../../../../../../../../Android/Sdk/ndk-bundle/sources/cxx-stl/llvm-libc++/include/cstdint"
#include "../../../../../../../../../Android/Sdk/ndk-bundle/sources/cxx-stl/llvm-libc++/include/cstring"

class VideoFrame : MovieFrame{
private:
    uint8_t *luma;
    uint8_t *chromaB;
    uint8_t *chromaR;

    int width;
    int height;

public:
    VideoFrame(int width,int height ,float position, float duration,
               uint8_t *luma, uint8_t *chomB,uint8_t * chomR);
    ~VideoFrame();

    virtual int getWidth() const {
        return width;
    }

    virtual int getHeight() const {
        return height;
    }

    virtual uint8_t *getLuma() const {
        return luma;
    }

    virtual uint8_t *getChromaB() const {
        return chromaB;
    }

    virtual uint8_t *getChromaR() const {
        return chromaR;
    }


    MovieFrameType getType() {
        return MOVIE_TYPE_VIDEO;
    }

    VideoFrame* clone() {
        size_t lumaLength = sizeof(luma);
        uint8_t *luma = new uint8_t[lumaLength];
        memcpy(luma,this->luma,lumaLength);

        size_t chromaLength = lumaLength/4;
        uint8_t *chromaB = new uint8_t[chromaLength];
        memcpy(chromaB,this->chromaB,chromaLength);

        uint8_t *chromaR = new uint8_t[chromaLength];
        memcpy(chromaR,this->chromaR,chromaLength);

        return new VideoFrame(width,height,position,duration,luma,chromaB,chromaR);
    }
};


#endif //MYAPPLICATION6_VIDEOFRAME_H
