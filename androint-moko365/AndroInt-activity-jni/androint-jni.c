#include <jni.h>

JNIEXPORT jint JNICALL Java_com_eps_william_androint_AndroIntActivity_addJNI
  (JNIEnv *env, jobject thiz, jint a, jint b)
{
	return a+b;
}
