//
// Created by oleh on 02.12.17.
//

#ifndef NANOVGANDROID_SHAPES_H
#define NANOVGANDROID_SHAPES_H

#include "Box2D/Box2D.h"
#include "nanovg.h"
typedef b2Vec2 Vec2;


class Rect {

public:
    float height;
    float width;
    Vec2 origin;

    Rect(){}
    Rect(Vec2 v, float width, float height);

    Rect(float x, float y, float width, float height);

    bool containsPoint(float x, float y);
};

class Shape{
public:
    bool hasTouch;
    Shape(){}
    Shape(float x,float y, float width,float height);
    Vec2 offset;
    Rect rect;
    float radius = 10;
    void draw(NVGcontext *ctx);
};




#endif //NANOVGANDROID_SHAPES_H
