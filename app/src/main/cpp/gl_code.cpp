
#include <jni.h>
#include <android/log.h>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "b2Utils.h"

#define  LOG_TAG    "libgl2jni"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

#define NANOVG_GLES2_IMPLEMENTATION

#include "nanovg/nanovg.h"
#include "nanovg/nanovg_gl.h"
#include "android/asset_manager_jni.h"
#include "Box2D/Box2D.h"
#include "b2Renderer.h"
#include "NvgSample.h"

std::unique_ptr<NvgSample>nvgSamplePointer;
float verticeX(float angle);

float verticeY(float angle);

void update();

static void printGLString(const char *name, GLenum s) {
    const char *v = (const char *) glGetString(s);
    LOGI("GL %s = %s\n", name, v);
}

static void checkGlError(const char *op) {
    for (GLint error = glGetError(); error; error
                                                    = glGetError()) {
        LOGI("after %s() glError (0x%x)\n", op, error);
    }
}


struct NVGcontext *vg;

int _w, _h;

float rotation,             // final value
        currentRotation;    // current animated value
float r, g, b, a;      // bg
int w, h;
float x, y;
float x2 = 10;
float  angle = 0;

float newx = -1;
float newy = -1;
std::vector<std::shared_ptr<b2Vec2>> points;
std::unique_ptr<b2World> world;
std::shared_ptr<b2Renderer> renderer;
bool fontLoaded  = false;
std::string fontPath;

void setupBox2d() {
    b2BodyDef bodyDef;
    bodyDef.type = b2BodyType::b2_staticBody;
    b2EdgeShape edgeShape;
    edgeShape.Set(b2Vec2(0, 50), b2Vec2(30, 50));
    world->CreateBody(&bodyDef)->CreateFixture(&edgeShape, 1);

}

void createBall(float x, float y) {
    b2BodyDef bodyDef;
    bodyDef.type = b2BodyType::b2_dynamicBody;
    bodyDef.position.Set(x, y);


    b2CircleShape shape;
    shape.m_radius = 1;

    world->CreateBody(&bodyDef)->CreateFixture(&shape, 1);

}


bool setupGraphics(int _w, int _h) {
    w = _w;
    h = _h;


    world = std::unique_ptr<b2World>(new b2World(b2Vec2(0, 9.8f)));

    printGLString("Version", GL_VERSION);
    printGLString("Vendor", GL_VENDOR);
    printGLString("Renderer", GL_RENDERER);
    printGLString("Extensions", GL_EXTENSIONS);

    LOGI("setupGraphics(%d, %d)", w, h);
    vg = nvgCreateGLES2(NVG_ANTIALIAS | NVG_STENCIL_STROKES | NVG_DEBUG);
    nvgSamplePointer = std::unique_ptr<NvgSample>( new NvgSample(vg));
    renderer = std::shared_ptr<b2Renderer>(new b2Renderer(vg));
    renderer->SetFlags(b2Draw::e_shapeBit | b2Draw::e_jointBit | b2Draw::e_pairBit |
                       b2Draw::e_centerOfMassBit);


    world->SetDebugDraw(renderer.get());


    setupBox2d();


    glViewport(0, 0, w, h);
    checkGlError("glViewport");

    glClearColor(r, g, b, a);
    checkGlError("glClearColor");
    return true;
}


void drawWindow(NVGcontext *vg, const char *title, float x, float y, float w, float h) {


    float cornerRadius = 3.0f;
    NVGpaint shadowPaint;
    NVGpaint headerPaint;

    nvgSave(vg);
//	nvgClearState(vg);

    // Window
    nvgBeginPath(vg);
    nvgRoundedRect(vg, x, y, w, h, cornerRadius);
    nvgFillColor(vg, nvgRGBA(28, 30, 34, 192));
//	nvgFillColor(vg, nvgRGBA(0,0,0,128));
    nvgFill(vg);

    // Drop shadow
    shadowPaint = nvgBoxGradient(vg, x, y + 2, w, h, cornerRadius * 2, 10, nvgRGBA(0, 0, 0, 128),
                                 nvgRGBA(0, 0, 0, 0));
    nvgBeginPath(vg);
    nvgRect(vg, x - 10, y - 10, w + 20, h + 30);
    nvgRoundedRect(vg, x, y, w, h, cornerRadius);
    nvgPathWinding(vg, NVG_HOLE);
    nvgFillPaint(vg, shadowPaint);
    nvgFill(vg);

    // Header
    headerPaint = nvgLinearGradient(vg, x, y, x, y + 15, nvgRGBA(255, 255, 255, 8),
                                    nvgRGBA(0, 0, 0, 16));
    nvgBeginPath(vg);
    nvgRoundedRect(vg, x + 1, y + 1, w - 2, 30, cornerRadius - 1);
    nvgFillPaint(vg, headerPaint);
    nvgFill(vg);
    nvgBeginPath(vg);
    nvgMoveTo(vg, x + 0.5f, y + 0.5f + 30);
    nvgLineTo(vg, x + 0.5f + w - 1, y + 0.5f + 30);
    nvgStrokeColor(vg, nvgRGBA(0, 0, 0, 32));
    nvgStroke(vg);

    nvgFontSize(vg, 50.0f);
    nvgFontFace(vg, "sans-bold");
    nvgTextAlign(vg, NVG_ALIGN_CENTER | NVG_ALIGN_MIDDLE);

    nvgFontBlur(vg, 2);
    nvgFillColor(vg, nvgRGBA(0, 0, 0, 128));
    nvgText(vg, x + w / 2, y + 16 + 1, title, NULL);

    nvgFontBlur(vg, 0);
    nvgFillColor(vg, nvgRGBA(220, 220, 220, 160));
    nvgText(vg, x + w / 2, y + 16, title, NULL);

    nvgRestore(vg);


}


void renderFrame(float dt) {
    // currentRotation = currentRotation*0.9f + rotation * 0.1f;


    glStencilMask(0xff);
    checkGlError("glStencilMask");
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    checkGlError("glClear");

    nvgBeginFrame(vg, w, h, w/h);


    nvgEndFrame(vg);

    if(!fontPath.empty() && !fontLoaded ){
        int re = nvgCreateFont(vg,"sans-bold",fontPath.c_str());
        LOGI("FONT PATH FOUND %s result %d",fontPath.c_str(),re);
        fontLoaded = true;
    }


    update();

    nvgBeginFrame(vg, w, h, w > h ? w / h : h / w);
    if(fontLoaded){
        nvgBeginPath(vg);
        nvgFontFace(vg,"Varela");
        nvgText(vg,100,100,"HELLO WORLD",NULL);
        nvgFill(vg);
    }
    drawWindow(vg,"HELLO WORLD" ,100,100,500,500);


//    nvgTransformTranslate(vg,angle,0);



    world->Step(dt, 8, 3);
    world->DrawDebugData();
    nvgSamplePointer->draw();

    nvgBeginPath(vg);
    nvgMoveTo(vg, verticeX(90.f), verticeY(90.f));
    nvgLineTo(vg, verticeX(90.f + 120.0f), verticeY(90.0f + 120.0f));
    nvgLineTo(vg, verticeX(90.f + 240.f), verticeY(90.0f + 240.0f) );
    nvgClosePath(vg);
    nvgFillColor(vg, nvgRGBA(255,192,0,255));
    nvgFill(vg);
    nvgFillColor(vg, nvgRGBA(255,192,0,255));




    nvgBeginPath(vg);
    nvgRect(vg, 10,10,100,200);
    nvgFillColor(vg, nvgRGBA(255,0,0,255));
    nvgFill(vg);

    nvgBeginPath(vg);
    nvgCircle(vg,x2++,50,50);
    nvgFillColor(vg,nvgRGB(200,100,200));
    nvgFill(vg);


angle+=dt;

//    for(int i = 0 ; i < 50;i++){
//        drawWindow(vg,"HELLO",sin(angle) * 50 + 300,i * 5 + 300,300,200);
//    }

    nvgEndFrame(vg);

}

void update() {
    if (newx != -1 && newy != -1) {

           createBall(newx, newy);
        newx = -1;
        newy = -1;
    }
}

//inline float sqr(float x){return x*x};
float len() {
    return sqrt(0.25f * w * w + 0.25f * h * h) * 0.5f; // 0.75 of 0.5w * 0.5w + 0.5h*0.5h
}

float verticeX(float angle) {
    return x + w / 2.0f + cos(nvgDegToRad(angle + currentRotation)) * len();
}

float verticeY(float angle) {
    return y + h / 2.0f - sin(nvgDegToRad(angle + currentRotation)) * len();
}

extern "C" {
JNIEXPORT void JNICALL
Java_ru_egslava_hello_1nanovg_JNI_init(JNIEnv *env, jobject obj, jint width, jint height);
JNIEXPORT void JNICALL
Java_ru_egslava_hello_1nanovg_JNI_step(JNIEnv *env, jobject obj, jfloat delta);
JNIEXPORT void JNICALL
Java_ru_egslava_hello_1nanovg_JNI_setRotation(JNIEnv *env, jclass type, jfloat _rotation);
JNIEXPORT void JNICALL
Java_ru_egslava_hello_1nanovg_JNI_setBackgroundColor(JNIEnv *env, jclass type, jfloat R, jfloat G,
                                                     jfloat B, jfloat A);
JNIEXPORT void JNICALL
Java_ru_egslava_hello_1nanovg_JNI_onTouchBegin(JNIEnv *env, jclass type, jfloat x, jfloat y);
JNIEXPORT void JNICALL
Java_ru_egslava_hello_1nanovg_JNI_setTranslation(JNIEnv *env, jclass type, jfloat _x, jfloat _y);
};

JNIEXPORT void JNICALL
Java_ru_egslava_hello_1nanovg_JNI_init(JNIEnv *env, jobject obj, jint width, jint height) {
    setupGraphics(width, height);
}

JNIEXPORT void JNICALL Java_ru_egslava_hello_1nanovg_JNI_step(JNIEnv *env, jobject obj, jfloat dt) {
    renderFrame(dt);
}

JNIEXPORT void JNICALL
Java_ru_egslava_hello_1nanovg_JNI_setRotation(JNIEnv *env, jclass type, jfloat _rotation) {
    rotation = _rotation;
}

JNIEXPORT void JNICALL
Java_ru_egslava_hello_1nanovg_JNI_setBackgroundColor(JNIEnv *env, jclass type, jfloat R, jfloat G,
                                                     jfloat B, jfloat A) {

    r = R;
    g = G;
    b = B;
    a = A;     // if method was called before initialization, save params and defer...
    glClearColor(r, g, b, a);      // if method is called after GL initialization
    checkGlError("glClearColor");
}

JNIEXPORT void JNICALL
Java_ru_egslava_hello_1nanovg_JNI_setTranslation(JNIEnv *env, jclass type, jfloat _x, jfloat _y) {
    x = _x;
    y = _y;
}

extern "C"
JNIEXPORT void JNICALL
Java_ru_egslava_hello_1nanovg_JNI_allocate(JNIEnv *env, jclass type) {




}extern "C"
JNIEXPORT void JNICALL
Java_ru_egslava_hello_1nanovg_JNI_remove(JNIEnv *env, jclass type) {


}extern "C"
JNIEXPORT void JNICALL
Java_ru_egslava_hello_1nanovg_JNI_setAssets(JNIEnv *env, jclass type, jobject manager) {
AAssetManager *aAssetManager =  AAssetManager_fromJava(env,manager);
    AAsset *asset= AAssetManager_open(aAssetManager,"VarelaRound-Regular.ttf",AASSET_MODE_UNKNOWN);

//    "VarelaRound-Regular.ttf"





}


JNIEXPORT void JNICALL
Java_ru_egslava_hello_1nanovg_JNI_onTouchBegin(JNIEnv *env, jclass type, jfloat x, jfloat y) {

    newx = toBox2d(x);
    newy = toBox2d(y);
    nvgSamplePointer->onTouchBegin(x,y);

}



extern "C"
JNIEXPORT void JNICALL
Java_ru_egslava_hello_1nanovg_JNI_onTouchMove(JNIEnv *env, jclass type, jfloat x, jfloat y) {

    nvgSamplePointer->onTouchMove(x,y);

}extern "C"
JNIEXPORT void JNICALL
Java_ru_egslava_hello_1nanovg_JNI_onTouchEnd(JNIEnv *env, jclass type) {

    nvgSamplePointer->onTouchEnd();

}extern "C"
JNIEXPORT void JNICALL
Java_ru_egslava_hello_1nanovg_JNI_sendFontPath(JNIEnv *env, jclass type, jstring string_) {
    const char *string = env->GetStringUTFChars(string_, 0);

    fontPath = string;

    env->ReleaseStringUTFChars(string_, string);
}