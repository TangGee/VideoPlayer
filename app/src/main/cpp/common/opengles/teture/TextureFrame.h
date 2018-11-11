//
// Created by tlinux on 18-11-11.
//

#ifndef MYAPPLICATION6_TEXUREFRAME_H
#define MYAPPLICATION6_TEXUREFRAME_H


#include <alog.h>
#define LOG_TAG "TextureFrame"


#include <GLES2/gl2.h>
#include <opengles/media/VideoFrame.h>

class TextureFrame {
protected:
    bool checkGLError(const char* op);

public:
    TextureFrame();
    virtual ~TextureFrame();

    virtual bool createTexture() = 0;
    virtual void updateTexture(VideoFrame *videoFrame) =0;
    virtual bool bindTexture(GLint* uniformSamplers) =0;
    virtual void dealloc() =0;
};


#endif //MYAPPLICATION6_TEXUREFRAME_H
