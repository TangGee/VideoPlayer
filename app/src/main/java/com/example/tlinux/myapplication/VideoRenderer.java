package com.example.tlinux.myapplication;

import android.content.Context;
import android.opengl.GLES20;
import android.opengl.GLSurfaceView;

import java.nio.ByteBuffer;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class VideoRenderer implements GLSurfaceView.Renderer {

    private Context mContext;
    private int mVideoWidth = -1, mVideoHeight = -1;
    private ByteBuffer y;
    private ByteBuffer u;
    private ByteBuffer v;
    private GLProgram mGLProgram = new GLProgram();
    private GLSurfaceView mTargetSurface;

    public VideoRenderer(Context context, GLSurfaceView surfaceView) {
        mContext = context;
        mTargetSurface = surfaceView;
    }

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        if (!mGLProgram.isProgramBuilt()) {
            mGLProgram.buildProgram();
        }
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        mVideoWidth = width;
        mVideoHeight = height;
        GLES20.glViewport(0, 0, width, height);

    }

    @Override
    public void onDrawFrame(GL10 gl) {
        synchronized (this) {
            if (y != null) {
            // reset position, have to be done
                y.position(0);
                u.position(0);
                v.position(0); mGLProgram.buildTextures(y, u, v, mVideoWidth, mVideoHeight);
                GLES20.glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
                GLES20.glClear(GLES20.GL_COLOR_BUFFER_BIT);
                mGLProgram.drawFrame();
            }
        }
    }

    public void update(int w, int h) {
        if (w > 0 && h > 0) {
            if (w != mVideoWidth && h != mVideoHeight) {
                this.mVideoWidth = w;
                this.mVideoHeight = h;
                int yarraySize = w * h;
                int uvarraySize = yarraySize / 4;
                synchronized (this) {
                    y = ByteBuffer.allocate(yarraySize);
                    u = ByteBuffer.allocate(uvarraySize);
                    v = ByteBuffer.allocate(uvarraySize);
                }
            }
        }
    }

    public void update(byte[] ydata, byte[] udata, byte[] vdata) {
        synchronized (this) {
            y.clear();
            u.clear();
            v.clear();
            y.put(ydata, 0, ydata.length);
            u.put(udata, 0, udata.length);
            v.put(vdata, 0, vdata.length);
        }
        mTargetSurface.requestRender();
    }

}
