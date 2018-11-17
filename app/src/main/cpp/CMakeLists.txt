cmake_minimum_required(VERSION 3.4.1)


set(SOURCES nanovg/nanovg.c
        gl_code.cpp
        src/b2Renderer.cpp
        src/bodyCreator.cpp
        src/NvgSample.cpp
        src/Shapes.cpp
        android_fopen.c
        )

include_directories(nanovg . include)

add_library(nanoLib
        SHARED
        ${SOURCES})

add_subdirectory(Box2D)

target_link_libraries(nanoLib
        box2d
        android
        GLESv2
        log)
