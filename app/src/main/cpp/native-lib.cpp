#include <jni.h>
#include <string>

extern "C"
jstring
Java_ru_ilnarsoultanov_pushtest_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";

    return env->NewStringUTF(hello.c_str());
}

extern "C"
jlong
Java_ru_ilnarsoultanov_pushtest_MainActivity_apiKey(
        JNIEnv *env,
        jobject /* this */, jstring content, jstring key) {
    jclass date = env->FindClass("java/util/Date");
    jmethodID dateTypeConstructor= env->GetMethodID(date, "<init>", "()V");
    if(dateTypeConstructor == NULL){
        return 0;
    }
    jobject dateObjectStart = env->NewObject(date, dateTypeConstructor);
    if(dateObjectStart  == NULL){
        return 0;
    }

    jmethodID getTime = env->GetMethodID(date, "getTime", "()J");
    if(getTime == NULL){
        return 0;
    }
    jlong a = env->CallLongMethod(dateObjectStart, getTime);

    int length = env->GetStringLength(content);
    const jchar* charContent = env->GetStringChars(content, false);
    const jchar* charKey = env->GetStringChars(key, false);

    jchar result[length];
    if(length > 0) {
        for (int i = 0; i < length; ++i) {
            result[i] = charContent[i] ^ charKey[i];
        }
    }

    //return env->NewString(result, length);
    return a;
}


