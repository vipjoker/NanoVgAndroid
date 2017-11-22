cmake_minimum_required(VERSION 3.4.1)


set(SOURCES nanovg/nanovg.c gl_code.cpp)


add_library(gl2jni SHARED
          ${SOURCES})

target_link_libraries(gl2jni
                      android
                      GLESv2
                      log)
