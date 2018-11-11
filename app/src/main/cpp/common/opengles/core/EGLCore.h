//
// Created by tlinux on 18-11-4.
//

#ifndef MYAPPLICATION6_EGLCORE_H
#define MYAPPLICATION6_EGLCORE_H

#include <EGL/egl.h>
#include <EGL/eglext.h>


class EGLCore {
public:
    EGLCore();
    virtual ~EGLCore();

    bool init();
    bool init(EGLContext shareContext);
    bool initWithShaderContext();

    EGLSurface  createWindowSurface(ANativeWindow* _window);
    EGLSurface  createOffscreenSurface(int width,int height);

    bool makeCurrent(EGLSurface eglSurface);
    void doneCurrent();
    bool swapBuffers(EGLSurface eglSurface);

    int  querySurface(EGLSurface surface,int what);
    int setPresentationTime(EGLSurface surface, khronos_stime_nanoseconds_t nsecs );
    void releaseSurface(EGLSurface eglSurface);
    void release();

    const EGLContext getContext() const ;
    const EGLDisplay getDisplay() const ;
    const EGLConfig  getConfig() const ;

private:
    EGLDisplay display;
    EGLConfig  config;
    EGLContext context;

    PFNEGLPRESENTATIONTIMEANDROIDPROC pfneglPresentationTimeANDROID;
};


#endif //MYAPPLICATION6_EGLCORE_H
