//
// Created by oleh on 01.12.17.
//

#ifndef NANOVGANDROID_B2RENDERER_H
#define NANOVGANDROID_B2RENDERER_H

#include "Box2D/Box2D.h"
#include "nanovg/nanovg.h"

class b2Renderer :public b2Draw{

public:
    NVGcontext *ctx;
    b2Renderer(NVGcontext *_ctx):ctx(_ctx){};
    virtual void DrawPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &color);

    virtual void DrawSolidPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &color);

    virtual void DrawCircle(const b2Vec2 &center, float32 radius, const b2Color &color);

    virtual void
    DrawSolidCircle(const b2Vec2 &center, float32 radius, const b2Vec2 &axis, const b2Color &color);

    virtual void DrawSegment(const b2Vec2 &p1, const b2Vec2 &p2, const b2Color &color);

    virtual void DrawTransform(const b2Transform &xf);

};


#endif //NANOVGANDROID_B2RENDERER_H
