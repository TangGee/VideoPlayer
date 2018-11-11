//
// Created by tlinux on 18-11-4.
//

#ifndef MYAPPLICATION6_EGLSHARECONTEXT_H
#define MYAPPLICATION6_EGLSHARECONTEXT_H


#include <EGL/egl.h>

class EglShareContext {
public:
    ~EglShareContext() {
    }
    static EGLContext getSharedContext() {
        if (instance_->sharedDisplay == EGL_NO_DISPLAY){
            instance_->init();
        }
        return instance_->sharedContext;
    }
protected:
    EglShareContext();
    void init();


private:
    static EglShareContext* instance_;
    EGLContext sharedContext;
    EGLDisplay sharedDisplay;
};

#endif //MYAPPLICATION6_EGLSHARECONTEXT_H
