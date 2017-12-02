//
// Created by oleh on 01.12.17.
//

#include "b2Renderer.h"
#include "b2Utils.h"
void b2Renderer::DrawPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &color) {
    nvgBeginPath(ctx);
    for (int i = 0; i < vertexCount; i++) {

        if (i == 0)nvgMoveTo(ctx, vertices[i].x *B2_RATIO, vertices[i].y*B2_RATIO);
        else nvgLineTo(ctx, vertices[i].x *B2_RATIO, vertices[i].y *B2_RATIO);
    }
    nvgStrokeColor(ctx,nvgRGBf(color.r, color.g, color.b));
    nvgStroke(ctx);
}

void b2Renderer::DrawSolidPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &color) {
    nvgBeginPath(ctx);
    for (int i = 0; i < vertexCount; i++) {
        if (i == 0)nvgMoveTo(ctx, vertices[i].x *B2_RATIO, vertices[i].y *B2_RATIO);
        else nvgLineTo(ctx, vertices[i].x *B2_RATIO, vertices[i].y*B2_RATIO);
    }
    nvgFillColor(ctx,nvgRGBf(color.r, color.g, color.b));
    nvgFill(ctx);
}

void b2Renderer::DrawCircle(const b2Vec2 &center, float32 radius, const b2Color &color) {

    nvgBeginPath(ctx);
    nvgCircle(ctx, center.x *B2_RATIO, center.y*B2_RATIO, radius*B2_RATIO);
    nvgStrokeColor(ctx, nvgRGBf(color.r, color.g, color.b));
    nvgStroke(ctx);
}

void b2Renderer::DrawSolidCircle(const b2Vec2 &center, float32 radius, const b2Vec2 &axis,
                                 const b2Color &color) {
    nvgBeginPath(ctx);
    nvgCircle(ctx, center.x*B2_RATIO, center.y*B2_RATIO, radius*B2_RATIO);
    nvgFillColor(ctx, nvgRGBf(color.r, color.g, color.b));
    nvgFill(ctx);

}

void b2Renderer::DrawSegment(const b2Vec2 &p1, const b2Vec2 &p2, const b2Color &color) {

    nvgBeginPath(ctx);
    nvgMoveTo(ctx, p1.x *B2_RATIO, p1.y *B2_RATIO);
    nvgLineTo(ctx, p2.x * B2_RATIO, p2.y * B2_RATIO);
    nvgStrokeColor(ctx, nvgRGBf(color.r, color.g, color.b));
    nvgStroke(ctx);
}

void b2Renderer::DrawTransform(const b2Transform &xf) {

}

