//
// Created by tlinux on 18-11-10.
//

#include "VideoFrame.h"


VideoFrame::VideoFrame(int width, int height,float position, float duration,
                       uint8_t *luma, uint8_t *chomB,uint8_t * chomR)
        :MovieFrame(position,duration)
        ,width(width),height(height)
        ,luma(luma),chromaB(chomB),chromaR(chomR){
}

VideoFrame::~VideoFrame() {
    if (luma) {
        delete []luma;
    }

    if (chromaB) {
        delete []chromaB;
    }

    if (chromaR) {
        delete []chromaR;
    }
}