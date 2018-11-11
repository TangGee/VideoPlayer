//
// Created by tlinux on 18-11-11.
//

#include <alog.h>
#include "TextureFrameUploader.h"

#define LOG_TAG "TextureFrameUploader"

TextureFrameUploader::TextureFrameUploader() {

}

TextureFrameUploader::~TextureFrameUploader() {
    if (eglCore) {
        eglCore->release();
        delete eglCore;
    }
}


void TextureFrameUploader::init(int width,int height) {

    this->width = width;
    this->height = height;

    eglCore = new EGLCore;
    ALOGI("eglCore init");
    eglCore->initWithShaderContext();
    ALOGI("eglCore init with initWithShaderContext");
    copyTextureSurface = eglCore->createOffscreenSurface(width,height);
    eglCore->makeCurrent(copyTextureSurface);

    glGenFramebuffers(1,&mFBO);
    glGenTextures(1,&outputTextureId);
    glBindTexture(GL_TEXTURE_2D,outputTextureId);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,0);
    glBindTexture(GL_TEXTURE_2D,0);


}