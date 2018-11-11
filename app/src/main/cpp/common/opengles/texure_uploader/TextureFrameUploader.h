//
// Created by tlinux on 18-11-11.
//

#ifndef MYAPPLICATION6_TEXTUREFRAMEUPLOADER_H
#define MYAPPLICATION6_TEXTUREFRAMEUPLOADER_H


#include <opengles/core/EGLCore.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GLES2/gl2.h>
#include <opengles/media/VideoFrame.h>
#include <opengles/teture/TextureFrame.h>

class TextureFrameUploader {
private:
    int width;
    int height;

    EGLCore *eglCore;

    EGLSurface copyTextureSurface;
    GLuint mFBO;
    GLuint outputTextureId;

protected:
    TextureFrame *textureFrame;

public:
    TextureFrameUploader();
    ~TextureFrameUploader();

    virtual void init(int width,int height);
    virtual bool updateTexImage(VideoFrame *videoFrame);
};


#endif //MYAPPLICATION6_TEXTUREFRAMEUPLOADER_H
