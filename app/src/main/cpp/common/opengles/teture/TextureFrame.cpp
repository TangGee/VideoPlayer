//
// Created by tlinux on 18-11-11.
//

#include "TextureFrame.h"



TextureFrame::TextureFrame() {}

TextureFrame::~TextureFrame() {}

bool TextureFrame::checkGLError(const char* op) {
    GLint error;

    bool ret = false;
    for (error = glGetError(); error; error = glGetError()) {
        ALOGI("error::after %s() getError (0x%x\n)", op, error);
        ret = true;
    }

    return ret;
}