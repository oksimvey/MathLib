#include "CIntegrationJ.h"

JNIEXPORT jint JNICALL Java_CIntegrationJ_add
  (JNIEnv *env, jobject obj, jint a, jint b)
{
    return a * b;
}