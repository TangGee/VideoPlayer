#include <jni.h>
#include <string>

extern "C"
#ifdef __cplusplus

extern "C" {
#endif
#include "demuxing_decoding.h"
#ifdef __cplusplus
}
#endif


extern "C" JNIEXPORT jstring JNICALL
Java_com_example_tlinux_myapplication_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}


extern "C" JNIEXPORT void JNICALL
Java_com_example_tlinux_myapplication_MainActivity_startDeMuxing(
        JNIEnv* env,
        jobject /* this */) {

    char*argv[4]  = {"haha",
                     "/sdcard/haha.mp4",
                     "/sdcard/video.stream",
                     "/sdcard/audio.stream"
                     };
    start(4,argv);
}
