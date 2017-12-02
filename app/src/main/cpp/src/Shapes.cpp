//
// Created by oleh on 02.12.17.
//

#include "Shapes.h"

Rect::Rect(Vec2 v, float width, float height) {
    this->origin = v;
    this->width = width;
    this->height = height;
}

Rect::Rect(float x, float y, float width, float height) {
    this->origin.Set(x, y);
    this->width = width;
    this->height = height;
}

bool Rect::containsPoint(float x, float y) {
    return (x > origin.x && x < origin.x + width && y > origin.y && y < origin.y + width);
}

void Shape::draw(NVGcontext *ctx) {
    nvgBeginPath(ctx);
    nvgRoundedRect(ctx, rect.origin.x, rect.origin.y, rect.width, rect.height, radius);
    nvgFillColor(ctx, nvgRGBA(28, 30, 34, 192));



    nvgFill(ctx);

    nvgStrokeWidth(ctx,5);

    nvgStrokeColor(ctx,nvgRGBf(0.8f,0,0));

    nvgStroke(ctx);
}

Shape::Shape(float x, float y, float width, float height) {
    rect.origin.Set(x, y);
    rect.width = width;
    rect.height = height;
}
