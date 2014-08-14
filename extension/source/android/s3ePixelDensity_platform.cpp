/*
 * android-specific implementation of the s3ePixelDensity extension.
 * Add any platform-specific functionality here.
 */
/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */
#include "s3ePixelDensity_internal.h"

#include "s3eEdk.h"
#include "s3eEdk_android.h"
#include <jni.h>
#include "IwDebug.h"

static jobject g_Obj;
static jmethodID g_s3ePixelDensityGetPPI;

s3eResult s3ePixelDensityInit_platform()
{
    // Get the environment from the pointer
    JNIEnv* env = s3eEdkJNIGetEnv();
    jobject obj = NULL;
    jmethodID cons = NULL;

    // Get the extension class
    jclass cls = s3eEdkAndroidFindClass("s3ePixelDensity");
    if (!cls)
        goto fail;

    // Get its constructor
    cons = env->GetMethodID(cls, "<init>", "()V");
    if (!cons)
        goto fail;

    // Construct the java class
    obj = env->NewObject(cls, cons);
    if (!obj)
        goto fail;

    // Get all the extension methods
    g_s3ePixelDensityGetPPI = env->GetMethodID(cls, "s3ePixelDensityGetPPI", "()I");
    if (!g_s3ePixelDensityGetPPI)
        goto fail;



    IwTrace(PIXELDENSITY, ("PIXELDENSITY init success"));
    g_Obj = env->NewGlobalRef(obj);
    env->DeleteLocalRef(obj);
    env->DeleteGlobalRef(cls);

    // Add any platform-specific initialisation code here
    return S3E_RESULT_SUCCESS;

fail:
    jthrowable exc = env->ExceptionOccurred();
    if (exc)
    {
        env->ExceptionDescribe();
        env->ExceptionClear();
        IwTrace(s3ePixelDensity, ("One or more java methods could not be found"));
    }
    return S3E_RESULT_ERROR;

}

void s3ePixelDensityTerminate_platform()
{
    // Add any platform-specific termination code here
}

int s3ePixelDensityGetPPI_platform()
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    return (int)env->CallIntMethod(g_Obj, g_s3ePixelDensityGetPPI);
}
