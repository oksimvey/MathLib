#include "CIntegrationJ.h"

JNIEXPORT jlong JNICALL Java_CIntegrationJ_add
  (JNIEnv *env, jobject obj, jint a, jint b)
{
  long long result = 0;
     for (long long i = 0; i < 10000000000LL; i++) {
        result += i * i;
    }
    return (jlong)result;
}