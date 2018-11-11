//
// Created by tlinux on 18-11-11.
//

#include "YUVTextureFrame.h"

YUVTextureFrame::YUVTextureFrame() {

}

YUVTextureFrame::~YUVTextureFrame() {
    TextureFrame::~TextureFrame();
}

int YUVTextureFrame::initTexture() {
    glGenTextures(3,textures);
    for (int i = 0; i < 3; ++i) {
        glBindTexture(GL_TEXTURE_2D,textures[1]);
        if (checkGLError("glBindTexture")) {
            return -1;
        }
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
        if (checkGLError("glTexParameteri")) {
            return -1;
        }
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
        if (checkGLError("glTexParameteri")) {
            return -1;
        }
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
        if (checkGLError("glTexParameteri")) {
            return -1;
        }
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
        if (checkGLError("glTexParameteri")) {
            return -1;
        }
        glBindTexture(GL_TEXTURE_2D,0);
    }
    return 0;
}

bool YUVTextureFrame::createTexture() {
    textures[0] = 0;
    textures[1] = 0;
    textures[2] = 0;

    int ret = initTexture();
    if (ret < 0) {
        ALOGI("init texture failed...");
        dealloc();
        return false;
    }
    return true;
}

bool YUVTextureFrame::bindTexture(GLint *uniformSamplers) {
    for (int i = 0; i < 3; ++i) {
        glActiveTexture(GL_TEXTURE0+i);
        glBindTexture(GL_TEXTURE_2D,textures[i]);
        if (checkGLError("glBindTexture")) {
            return false;
        }
        glUniform1i(uniformSamplers[i],i);
    }
}

void YUVTextureFrame::updateTexture(VideoFrame *videoFrame) {
    if (videoFrame) {
        int frameWidth = videoFrame->getWidth();
        int frameHeight = videoFrame->getHeight();
        if (frameWidth % 16 !=0) {
            glPixelStorei(GL_UNPACK_ALIGNMENT,1);
        }
        uint8_t *pixels[3] = {videoFrame->getLuma(),videoFrame->getChromaB(),videoFrame->getChromaR()};
        int widths[3] = {frameWidth,frameWidth>>1,frameWidth>>1};
        int heights[3] = {frameHeight,frameHeight>>1,frameHeight>>1};

        for (int i = 0; i < 3 ; ++i) {
            glActiveTexture(GL_TEXTURE0+1);
            glBindTexture(GL_TEXTURE_2D,textures[i]);
            if (checkGLError("glBindTexture")) {
                return ;
            }

            glTexImage2D(GL_TEXTURE_2D,0,GL_LUMINANCE,widths[i],heights[i],0,GL_LUMINANCE,GL_UNSIGNED_BYTE,pixels[i]);
        }
    }
}

void YUVTextureFrame::dealloc() {
    if (textures[0]) {
        glDeleteTextures(3,textures);
    }
}