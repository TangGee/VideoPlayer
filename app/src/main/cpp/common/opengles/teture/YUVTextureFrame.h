//
// Created by tlinux on 18-11-11.
//

#ifndef MYAPPLICATION6_YUVTEXTUREFRAME_H
#define MYAPPLICATION6_YUVTEXTUREFRAME_H


#include <opengles/media/VideoFrame.h>
#include "TextureFrame.h"

class YUVTextureFrame : TextureFrame{
private:
    GLuint textures[3];
    int initTexture();

public:
    YUVTextureFrame();
    virtual ~YUVTextureFrame();


    bool createTexture();

    void updateTexture(VideoFrame *videoFrame);
    bool bindTexture(GLint* uniformSamplers);
    void dealloc();
};


#endif //MYAPPLICATION6_YUVTEXTUREFRAME_H
