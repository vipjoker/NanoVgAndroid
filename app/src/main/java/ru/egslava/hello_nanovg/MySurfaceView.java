package ru.egslava.hello_nanovg;

import android.content.Context;
import android.graphics.Point;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;
import android.util.Log;
import android.view.MotionEvent;
import android.view.TextureView;
import android.widget.TextView;

import java.util.ArrayList;
import java.util.List;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;


/**
 * Created by oleh on 01.12.17.
 */

public class MySurfaceView extends GLSurfaceView {
    private static final String TAG = "GLES3JNI";
    private static final boolean DEBUG = true;
    private TextView logView;
    public MySurfaceView(Context context) {
        super(context);

        // Pick an EGLConfig with RGB8 color, 16-bit depth, no stencil,
        // supporting OpenGL ES 2.0 or later backwards-compatible versions.
//        setEGLConfigChooser(5, 6, 5, 0, 16, 0);

        init();



    }


    public MySurfaceView(Context context, AttributeSet attrs) {
        super(context, attrs);
        init();
    }

    public void setLogView(TextView view){
        this.logView = view;
    }
    private void init(){
        setEGLConfigChooser(5, 6, 5, 0, 0, 0);
        setEGLContextClientVersion(2);
        setRenderer(new Renderer());
//        JNI.setBackgroundColor(0.1f, 0.1f, 0.2f, 1);
        JNI.setBackgroundColor(1f, 1f, 1f, 1);
    }
    private class Renderer implements GLSurfaceView.Renderer {
        private long currentTime = System.currentTimeMillis();

        public void onDrawFrame(GL10 gl) {
            long temp = currentTime;
            currentTime = System.currentTimeMillis();
            float res = (currentTime -temp)/1000.0f;
            float frameRate =1.0f/res;
       //     Log.i(TAG, "onDrawFrame: " + res);
            getRootView().post(()->{
                if(logView!= null)    logView.setText("Frame rate: " + frameRate);
            });

            JNI.step(res);
        }

        public void onSurfaceChanged(GL10 gl, int width, int height) {
            JNI.init(width, height);
        }

        public void onSurfaceCreated(GL10 gl, EGLConfig config) {
//                JNI.init();
        }
    }


    @Override
    public boolean onTouchEvent(MotionEvent event) {
        if(event.getAction() == MotionEvent.ACTION_DOWN){
            JNI.onTouchBegin(event.getX(),event.getY());

        }else if(event.getAction() == MotionEvent.ACTION_MOVE){
            JNI.onTouchMove(event.getX(),event.getY());
        }else if(event.getAction() == MotionEvent.ACTION_UP){
            JNI.onTouchEnd();
        }

        return true;
    }

}
