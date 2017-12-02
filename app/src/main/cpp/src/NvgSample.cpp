//
// Created by oleh on 02.12.17.
//
#include "NvgSample.h"

void NvgSample::draw() {

//    nvgBeginPath(ctx);
//    nvgRect(ctx, 100,100,200,200);
//    NVGpaint gpaint = nvgBoxGradient(ctx,100,100,200,200,5,5,nvgRGBf(.6,0,0),nvgRGBf(0,0,.7f));
//    nvgFillPaint(ctx,gpaint);
////    nvgFillColor(ctx, nvgRGBA(255,0,0,255));
//    nvgFill(ctx);




//    NVGpaint shadowPaint;
//    NVGpaint headerPaint;
//    if(hasTouch&& cornerRadius){
//        cornerRadius-=5;
//    }else if(cornerRadius < 100){
//        cornerRadius+=5;
//    }
//
//    nvgSave(ctx);
//	nvgClearState(ctx);

    // Window


    // Drop shadow
//    shadowPaint = nvgBoxGradient(ctx, x, y + 2, w, h, cornerRadius * 2, 10, nvgRGBA(0, 0, 0, 128),
//                                 nvgRGBA(0, 0, 0, 0));
//    nvgBeginPath(ctx);
//    nvgRect(ctx, x - 10, y - 10, w + 20, h + 30);
//    nvgRoundedRect(ctx, x, y, w, h, cornerRadius);
//    nvgPathWinding(ctx, NVG_HOLE);
//    nvgFillPaint(ctx, shadowPaint);
//    nvgFill(ctx);

    for (Shape &s: shapes)s.draw(ctx);


}

void NvgSample::onTouchBegin(float x, float y) {

    for (Shape &s: shapes) {
        if (s.rect.containsPoint(x, y)) {
            s.hasTouch = true;
            s.offset.Set(x - s.rect.origin.x, y - s.rect.origin.y);
            break;
        }
    }
}

void NvgSample::onTouchMove(float x, float y) {

    for (Shape &s: shapes) {
        if (s.hasTouch) {

            s.rect.origin.Set(x - s.offset.x, y - s.offset.y);
        }

    }

}

void NvgSample::onTouchEnd() {
    for (Shape &s: shapes) {
        s.hasTouch = false;

    }
}

void NvgSample::init() {
    for(int i = 0 ; i < 5;i++) {
        shapes.push_back(Shape(50 +rand()%1000, 50 + rand()%1500, 200, 200));
    }
}
