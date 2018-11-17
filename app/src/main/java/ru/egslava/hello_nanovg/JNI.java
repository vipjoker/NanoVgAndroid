/*
 * Copyright (C) 2007 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package ru.egslava.hello_nanovg;

// Wrapper for native library

import android.content.res.AssetManager;

public class JNI {

    static {
     System.loadLibrary("nanoLib");
    }

    public static native void setBackgroundColor(float R, float G, float B, float A);
    public static native void setRotation(float rotation);
    public static native void setTranslation(float x, float y);

    public static native void onTouchBegin(float x,float y);
    public static native void onTouchMove(float x,float y);
    public static native void onTouchEnd();


    public static native void init(int width, int height);
    public static native void step(float dt);
    public static native void setAssets(AssetManager manager);
    public static native void sendFontPath(String string);
    public static native void allocate();
    public static native void remove();
}
