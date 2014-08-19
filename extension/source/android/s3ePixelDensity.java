/*
java implementation of the s3ePixelDensity extension.

Add android-specific functionality here.

These functions are called via JNI from native code.
*/

import com.ideaworks3d.marmalade.LoaderAPI;
import com.ideaworks3d.marmalade.LoaderActivity;

import android.app.Activity;
import android.os.Bundle;
import android.view.Display;
import android.view.WindowManager;
import android.util.DisplayMetrics;
import android.content.Context;

class s3ePixelDensity
{
    public int s3ePixelDensityGetPPI()
    {
        DisplayMetrics metrics = LoaderAPI.getActivity().getApplicationContext().getResources().getDisplayMetrics();
        return (int)(metrics.xdpi + metrics.ydpi)/2;
    }
}
