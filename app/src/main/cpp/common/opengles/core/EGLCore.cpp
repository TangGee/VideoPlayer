//
// Created by tlinux on 18-11-4.
//

#include "EGLCore.h"
#include "EglShareContext.h"
#include <alog.h>
#include <android/native_window.h>

#define LOG_TAG "EGLCore"

EGLCore::EGLCore() {
    pfneglPresentationTimeANDROID =0;
    display = EGL_NO_DISPLAY;
    context = EGL_NO_CONTEXT;
}

EGLCore::~EGLCore() {}

void EGLCore::release() {
    if (EGL_NO_DISPLAY!=display  && EGL_NO_CONTEXT != context) {
        eglMakeCurrent(display,EGL_NO_SURFACE,EGL_NO_SURFACE,EGL_NO_CONTEXT);
        ALOGI("after eglMakeCurrent...");
        eglDestroyContext(display,context);
        ALOGI("after eglDestroyContext...");
    }

    display = EGL_NO_DISPLAY;
    context = EGL_NO_CONTEXT;
}

void EGLCore::releaseSurface(EGLSurface eglSurface) {
    eglDestroySurface(display,eglSurface);
}


const EGLConfig EGLCore::getConfig() const {
    return config;
}

const EGLContext EGLCore::getContext() const {
    return context;
}

const EGLDisplay EGLCore::getDisplay() const {
    return display;
}

EGLSurface EGLCore::createWindowSurface(ANativeWindow *_window) {

    EGLint format;

    if (_window == nullptr) {
        ALOGE("EGLCore::createWindowSurface  _window is NULL");
        return nullptr;
    }
    if (!eglGetConfigAttrib(display,config,EGL_NATIVE_VISUAL_ID,&format)) {
        ALOGE("eglGetConfigAttrib() returned error %d", eglGetError());
        release();
        return nullptr;
    }

    ANativeWindow_setBuffersGeometry(_window,0,0,format);

    EGLSurface surface = eglCreateWindowSurface(display,config,_window,0) ;
    if (!surface) ALOGE("eglCreateWindowSurface() returned error %d", eglGetError());
    return surface;
}

EGLSurface EGLCore::createOffscreenSurface(int width, int height) {
    EGLint PbufferAttributes[] = { EGL_WIDTH, width, EGL_HEIGHT, height, EGL_NONE, EGL_NONE };

    EGLSurface surface = eglCreatePbufferSurface(display,config,PbufferAttributes);
    if (!surface) ALOGE("eglCreatePbufferSurface() returned error %d", eglGetError());
    return surface;
}

int EGLCore::setPresentationTime(EGLSurface surface, khronos_stime_nanoseconds_t nsecs) {
    pfneglPresentationTimeANDROID(display, surface, nsecs);
    return 0;
}

int EGLCore::querySurface(EGLSurface surface, int what) {
    EGLint value;
    eglQuerySurface(display,surface,what,&value);
    return value;
}

bool EGLCore::swapBuffers(EGLSurface eglSurface) {
    return eglSwapBuffers(display,eglSurface);
}

bool EGLCore::makeCurrent(EGLSurface eglSurface) {
    return eglMakeCurrent(display,eglSurface,eglSurface,context);
}

void EGLCore::doneCurrent() {
    eglMakeCurrent(display,EGL_NO_SURFACE,EGL_NO_SURFACE,context);
}

bool EGLCore::init() {
    init(EGL_NO_CONTEXT);
}

bool EGLCore::initWithShaderContext() {
    EGLContext thisContext = EglShareContext::getSharedContext();
    if (thisContext == EGL_NO_CONTEXT) return false;
    return init(thisContext);
}

bool EGLCore::init(EGLContext shareContext) {
    EGLint numConfigure;
    EGLint width;
    EGLint height;

    const EGLint attribs[] = { EGL_BUFFER_SIZE, 32, EGL_ALPHA_SIZE, 8, EGL_BLUE_SIZE, 8,
                               EGL_GREEN_SIZE, 8, EGL_RED_SIZE, 8, EGL_RENDERABLE_TYPE,
                               EGL_OPENGL_ES2_BIT, EGL_SURFACE_TYPE, EGL_WINDOW_BIT, EGL_NONE };

    if ((display = eglGetDisplay(EGL_DEFAULT_DISPLAY)) == EGL_NO_DISPLAY) {
        ALOGE("eglGetDisplay() returned error %d", eglGetError());
        return false;
    }

    if (!eglInitialize(display,0,0)) {
        ALOGE("eglInitialize() returned error %d", eglGetError());
        return false;
    }

    if (!eglChooseConfig(display,attribs,&config,1,&numConfigure)) {
        ALOGE("eglChooseConfig() returned error %d", eglGetError());
        release();
        return false;
    }

    EGLint eglContextAttributes[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE };
    if (!(context = eglCreateContext(display,config,shareContext,eglContextAttributes))) {
        ALOGE("eglCreateContext() returned error %d", eglGetError());
        release();
        return false;
    }

    pfneglPresentationTimeANDROID = (PFNEGLPRESENTATIONTIMEANDROIDPROC)eglGetProcAddress("eglPresentationTimeANDROID");
    if (!pfneglPresentationTimeANDROID) {
        ALOGE("eglPresentationTimeANDROID is not available!");
    }

    return true;
}