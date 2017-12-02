//
// Created by oleh on 01.12.17.
//

#ifndef NANOVGANDROID_B2UTILS_H
#define NANOVGANDROID_B2UTILS_H
#define B2_RATIO 32
namespace {
    float toBox2d(float point){
        return point/B2_RATIO;
    }

    float fromBox2d(float point){
        return point * B2_RATIO;
    }
}


#endif //NANOVGANDROID_B2UTILS_H
