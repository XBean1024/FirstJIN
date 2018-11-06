#include <jni.h>
#include <string>

#define JNI_CLASS_PATH "com/example/binny/firstjin/MainActivity"
#define JNI_CLASS_PATH_1 "com/example/binny/firstjin/Student"

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_binny_firstjin_MainActivity_stringFromJNI(
        JNIEnv *e,
        jobject instance) {

    //1 获取Java类
    jclass clazz = e->FindClass(JNI_CLASS_PATH_1);
    //2 获取类信息
    jmethodID method_init_id = e->GetMethodID(clazz, "<init>", "()V");//构造函数
    jmethodID method_set_id = e->GetMethodID(clazz, "setAge", "(I)V");//set方法
    jmethodID method_get_id = e->GetMethodID(clazz, "getAge", "()I");//get方法
    //3 创建对象
    jobject jobject1 = e->NewObject(clazz, method_init_id);
    //4 操作对象
    e->CallVoidMethod(jobject1, method_set_id, 23);
    int age = e->CallIntMethod(jobject1, method_get_id);

    char tmp[]={0};
    sprintf(tmp,"%d",age);

    std::string hello = "Hello from C++";
    hello.append(tmp);
    return e->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_binny_firstjin_MainActivity_stringFromJNI2(JNIEnv *env, jobject instance) {

    // TODO

    return env->NewStringUTF("hello from jni2 ");
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_binny_firstjin_MainActivity_stringFromJNI3(
        JNIEnv *env, jobject instance,
        jstring str_) {
    const char *str = env->GetStringUTFChars(str_, 0);

    // TODO

    env->ReleaseStringUTFChars(str_, str);

    return env->NewStringUTF(str);
}

extern "C"
JNIEXPORT jstring JNICALL my_test_register(JNIEnv *env, jobject instance_) {
    return env->NewStringUTF("this is a test for register");
}

static JNINativeMethod g_methods[]{
        {"_test", "(Ljava/lang/String;)Ljava/lang/String;", (void *) my_test_register},
};

jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env = NULL;
    vm->GetEnv((void **) &env, JNI_VERSION_1_6);
    jclass clazz = env->FindClass(JNI_CLASS_PATH);//找到java类对象
    env->RegisterNatives(clazz, g_methods, sizeof(g_methods) / sizeof(g_methods[0]));
    return JNI_VERSION_1_6;
}