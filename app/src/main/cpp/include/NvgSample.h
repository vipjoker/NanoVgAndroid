//
// Created by oleh on 02.12.17.
//

#ifndef NANOVGANDROID_NVGSAMPLE_H
#define NANOVGANDROID_NVGSAMPLE_H

#include "nanovg.h"
#include "Shapes.h"

class NvgSample{
    NVGcontext *ctx;
    bool hasTouch = false;
public:
    std::vector<Shape> shapes;
    Vec2 offset;
    int cornerRadius =  50;
    NvgSample(NVGcontext *_ctx):ctx(_ctx){init();}
    void init();
    void draw();
    void onTouchBegin(float x,float y);
    void onTouchMove(float x,float y);
    void onTouchEnd();
};
#endif //NANOVGANDROID_NVGSAMPLE_H
