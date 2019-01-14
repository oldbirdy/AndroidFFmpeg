#include <jni.h>
#include <string.h>


//这里的是一个JNI基础的测试文件
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <android/log.h>
#include <malloc.h>
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavfilter/avfilter.h>
#include <android/native_window_jni.h>
#include <android/native_window.h>
#include "libyuv/libyuv.h"
#include "libswscale/swscale.h"
#define LOGI(FORMAT,...) __android_log_print(ANDROID_LOG_INFO,"xulcjni",FORMAT,##__VA_ARGS__);
#define LOGE(FORMAT,...) __android_log_print(ANDROID_LOG_ERROR,"xulcjni",FORMAT,##__VA_ARGS__);



JavaVM *javaVM = NULL;


//从jni获取字符串
JNIEXPORT jstring JNICALL
Java_com_demo_androidffmpeg_NativeBase_helloWordFromJNI(JNIEnv *env, jobject instance) {
    //这里的JNIEnv是个结构体指针  JNINativeInterface
    //env是个二级指针
    char *str = "hello world";
    //将 char*转化为jstring
    return (*env)->NewStringUTF(env, str);
}

//jni两个整数相加
JNIEXPORT jint JNICALL
Java_com_demo_androidffmpeg_NativeBase_sumInter(JNIEnv *env, jobject instance, jint a, jint b) {
    return a + b;
}

//jni字符串拼接
JNIEXPORT jstring JNICALL
Java_com_demo_androidffmpeg_NativeBase_sumString(JNIEnv *env, jobject instance, jstring str1_,
                                              jstring str2_) {

    //GetStringUTFChars可以把一个jstring指针（指向JVM内部的Unicode字符序列）转化成一个UTF-8格式的C字符串。
    const char *str1 = (*env)->GetStringUTFChars(env,str1_,NULL);
    const char *str2 = (*env)->GetStringUTFChars(env,str2_,NULL);
    //此处有在JVM上开辟内存的操作
    if(str1 == NULL || str2 == NULL){
        return NULL;
    }
    char *newStr = (char *)(malloc(strlen(str1) + strlen(str2)));    //开辟内存 需要检测是否为空
    strcpy(newStr,str1);
    strcat(newStr,str2);


    const char *s1 = "xulvcheng";
    LOGI("%#x",s1);  //打印16位 的内存地址
    const char *s2 = "xulvcheng";
    LOGI("%#x",s2);


    jstring jnewStr = (*env)->NewStringUTF(env, newStr);
    free(newStr);
    //使用完成后释放掉JVM内存
    //从GetStringUTFChars中获取的UTF-8字符串在本地代码中使用完毕后，
    // 要使用ReleaseStringUTFChars告诉JVM这个UTF-8字符串不会被使用了，因为这个UTF-8字符串占用的内存会被回收。
    (*env)->ReleaseStringUTFChars(env,str1_,str1);
    (*env)->ReleaseStringUTFChars(env,str2_,str2);
    return jnewStr;
}

//其他字符串操作函数

int compare(const void *a,const void *b){
    return (*(int*)a) - (*(int*)b);
}


JNIEXPORT void JNICALL
Java_com_demo_androidffmpeg_NativeBase_quickSort(JNIEnv *env, jobject instance, jintArray array_) {
    jint *array = (*env)->GetIntArrayElements(env, array_, NULL);
    jsize length = (*env)->GetArrayLength(env,array_);  //获取数组的长度

    //装换必须通过中间 量转换
    //方法 1：冒泡
//    int change = 0;
//    int temp;
//    for(int i=0;i<length-1;i++)
//    {
//        change = 0;
//        for(int j=length-1;j>i;j--)
//        {
//            if(array[j]<array[j-1])
//            {
//                temp=array[j];
//                array[j]=array[j-1];
//                array[j-1]=temp;
//                change=1;
//            }
//        }
//        if(!change)
//            break;
//    }

    //方法二：
    qsort(array,length, sizeof(jint),compare);


    //  0：释放 jint数组 并且更新 java数组
    //JNI_COMMIT ：对Java的数组进行更新但是不释放C/C++的数组
    //JNI_ABORT：对Java的数组不进行更新,释放C/C++的数组
    (*env)->ReleaseIntArrayElements(env, array_, array, 0);
}

JNIEXPORT void JNICALL
Java_com_demo_androidffmpeg_NativeBase_JNIChangeInstanceValue(JNIEnv *env, jobject instance) {
    jclass cla = (*env)->GetObjectClass(env,instance);
    //获取字段的 jfieldID
    //字段签名 详见 表格
    jfieldID jfield = (*env)->GetFieldID(env,cla,"hello","Ljava/lang/String;");
    jstring fieldValue = (jstring)(*env)->GetObjectField(env,instance,jfield);
    //得到jstring之后 转换成本地字符串
    const char *str = (*env)->GetStringUTFChars(env,fieldValue,NULL);
    const char *world = "world";
    LOGI("%s",str);
    char * newStr = (char *)malloc(strlen(str) + strlen(world));
    strcpy(newStr,str);
    strcat(newStr,world);
    LOGI("%s",newStr);
    (*env)->ReleaseStringUTFChars(env,fieldValue,str);
    //设置变量要转化成JAVA能够识别的jstring
    (*env)->SetObjectField(env,instance,jfield,(*env)->NewStringUTF(env,newStr));
    //释放内存
    free(newStr);
}

JNIEXPORT void JNICALL
Java_com_demo_androidffmpeg_NativeBase_JNIChangeStaticValue(JNIEnv *env, jobject instance) {
    jclass cla = (*env)->GetObjectClass(env,instance);
    jfieldID field = (*env)->GetStaticFieldID(env,cla,"world","Ljava/lang/String;");
    jstring jstr = (jstring)(*env)->GetStaticObjectField(env,cla,field);
    const char *cstr = (*env)->GetStringUTFChars(env,jstr,NULL);
    if(cstr == NULL){
        return;
    }
    const char *chello = "hello";
    char *newStr = (char *)malloc(strlen(chello) + strlen(cstr));
    strcpy(newStr,chello);
    strcat(newStr,cstr);
    jobject  returnValue = (*env)->NewStringUTF(env,newStr);
    (*env)->ReleaseStringUTFChars(env,jstr,cstr);
    (*env)->SetStaticObjectField(env,cla,field,returnValue);
    free(newStr);
}

JNIEXPORT void JNICALL
Java_com_demo_androidffmpeg_NativeBase_JNICallJAVAInstanceMethod(JNIEnv *env, jobject instance) {
    jclass cla = (*env)->GetObjectClass(env,instance);
    jmethodID methid = (*env)->GetMethodID(env,cla,"instanceMethod","(Ljava/lang/String;)Ljava/lang/String;");
    (*env)->CallObjectMethod(env,instance,methid,(*env)->NewStringUTF(env,"来自jni的值"));
}

JNIEXPORT void JNICALL
Java_com_demo_androidffmpeg_NativeBase_JNICallJAVAStaticMethod(JNIEnv *env, jobject instance,
                                                            jobject ll, jobject context) {
    jclass cla = (*env)->GetObjectClass(env,instance);
    //第四个参数是签名问题，签名问题。
    jmethodID  jmethodID1 = (*env)->GetStaticMethodID(env,cla,"staticMethod","(Landroid/widget/LinearLayout;Landroid/content/Context;Ljava/lang/String;)V");
    (*env)->CallStaticVoidMethod(env,cla,jmethodID1,ll,context,(*env)->NewStringUTF(env,"jni调用静态方法生成的一项"));

}

JNIEXPORT void JNICALL
Java_com_demo_androidffmpeg_NativeBase_JNICallJAVAConstructorMethod(JNIEnv *env, jobject instance,
                                                                 jobject context, jstring toast_) {
    jclass cla = (*env)->FindClass(env,"com/demo/androidffmpeg/NativeBase");
//    jclass cla = (*env)->GetObjectClass(env,instance);
    if(cla == NULL){
        return;
    }
    jmethodID methodId = (*env)->GetMethodID(env,cla,"<init>","(Landroid/content/Context;Ljava/lang/String;)V");
    (*env)->CallVoidMethod(env,instance,methodId,context,toast_);
}




//视频转码

struct URLProtocol;


JNIEXPORT jstring JNICALL
Java_com_demo_androidffmpeg_VedioUtils_urlProtocolInfo(JNIEnv *env, jclass type) {

    char info[40000]={0};
    av_register_all();

    struct URLProtocol *pup = NULL;
    //Input
    struct URLProtocol **p_temp = &pup;
    avio_enum_protocols((void **)p_temp, 0);
    while ((*p_temp) != NULL){
        sprintf(info, "%s[In ][%10s]\n", info, avio_enum_protocols((void **)p_temp, 0));
    }
    pup = NULL;
    //Output
    avio_enum_protocols((void **)p_temp, 1);
    while ((*p_temp) != NULL){
        sprintf(info, "%s[Out][%10s]\n", info, avio_enum_protocols((void **)p_temp, 1));
    }


    return (*env)->NewStringUTF(env, info);
}

JNIEXPORT jstring JNICALL
Java_com_demo_androidffmpeg_VedioUtils_avformatInfo(JNIEnv *env, jclass type) {
    char info[40000] = { 0 };

    av_register_all();

    AVInputFormat *if_temp = av_iformat_next(NULL);
    AVOutputFormat *of_temp = av_oformat_next(NULL);
    //Input
    while(if_temp!=NULL){
        sprintf(info, "%s[In ][%10s]\n", info, if_temp->name);
        if_temp=if_temp->next;
    }
    //Output
    while (of_temp != NULL){
        sprintf(info, "%s[Out][%10s]\n", info, of_temp->name);
        of_temp = of_temp->next;
    }
    //LOGE("%s", info);
    return (*env)->NewStringUTF(env, info);
}

JNIEXPORT jstring JNICALL
Java_com_demo_androidffmpeg_VedioUtils_avcodecInfo(JNIEnv *env, jclass type) {

    char info[40000] = { 0 };

    av_register_all();

    AVCodec *c_temp = av_codec_next(NULL);

    while(c_temp!=NULL){
        if (c_temp->decode!=NULL){
            sprintf(info, "%s[Dec]", info);
        }
        else{
            sprintf(info, "%s[Enc]", info);
        }
        switch (c_temp->type){
            case AVMEDIA_TYPE_VIDEO:
                sprintf(info, "%s[Video]", info);
                break;
            case AVMEDIA_TYPE_AUDIO:
                sprintf(info, "%s[Audio]", info);
                break;
            default:
                sprintf(info, "%s[Other]", info);
                break;
        }
        sprintf(info, "%s[%10s]\n", info, c_temp->name);


        c_temp=c_temp->next;
    }


    return (*env)->NewStringUTF(env, info);
}

JNIEXPORT jstring JNICALL
Java_com_demo_androidffmpeg_VedioUtils_avfilterInfo(JNIEnv *env, jclass type) {
    const char *str = "";
    return (*env)->NewStringUTF(env, str);
}


//获取ffmpeg的avcodec的configuration信息
JNIEXPORT jstring JNICALL
Java_com_demo_androidffmpeg_VedioUtils_configuration(JNIEnv *env, jclass type) {
    const char *str = avcodec_configuration();
    return (*env)->NewStringUTF(env, str);
}



//视频转码 MP4转WMV
JNIEXPORT jstring JNICALL
Java_com_demo_androidffmpeg_VedioUtils_mp4Twmv(JNIEnv *env, jclass type, jstring inputStr_,
                                            jstring outputStr_) {
    const char *inputStr = (*env)->GetStringUTFChars(env, inputStr_, 0);
    const char *outputStr = (*env)->GetStringUTFChars(env, outputStr_, 0);
    av_register_all();


    (*env)->ReleaseStringUTFChars(env, inputStr_, inputStr);
    (*env)->ReleaseStringUTFChars(env, outputStr_, outputStr);

    return (*env)->NewStringUTF(env, "");
}

JNIEXPORT jint JNICALL
JNI_OnLoad(JavaVM *vm,void *reserve){
    javaVM = vm;
    JNIEnv env;
    if((*vm)->GetEnv(vm,(void**)&env,JNI_VERSION_1_4) != JNI_OK){
        LOGE("GETENV FAILED");
    }
    return JNI_VERSION_1_4;
}


JNIEXPORT void JNICALL
Java_com_demo_androidffmpeg_VedioUtils_playVedio(JNIEnv *env, jclass type, jstring inputStr_,
                                                 jobject surface) {

    const char* input_cstr = (*env)->GetStringUTFChars(env,inputStr_,NULL);
    //1.注册组件
    av_register_all();

    //封装格式上下文
    AVFormatContext *pFormatCtx = avformat_alloc_context();
    LOGE("%s", input_cstr );
    //2.打开输入视频文件
    if(avformat_open_input(&pFormatCtx,input_cstr,NULL,NULL) != 0){
        LOGE("%s","打开输入视频文件失败");
        return;
    }
    //3.获取视频信息
    if(avformat_find_stream_info(pFormatCtx,NULL) < 0){
        LOGE("%s","获取视频信息失败");
        return;
    }

    //视频解码，需要找到视频对应的AVStream所在pFormatCtx->streams的索引位置
    int video_stream_idx = -1;
    int i = 0;
    for(; i < pFormatCtx->nb_streams;i++){
        //根据类型判断，是否是视频流
        if(pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO){
            video_stream_idx = i;
            break;
        }
    }

    //4.获取视频解码器
    AVCodecContext *pCodeCtx = pFormatCtx->streams[video_stream_idx]->codec;
    AVCodec *pCodec = avcodec_find_decoder(pCodeCtx->codec_id);
    if(pCodec == NULL){
        LOGE("%s","无法解码");
        return;
    }

    //5.打开解码器
    if(avcodec_open2(pCodeCtx,pCodec,NULL) < 0){
        LOGE("%s","解码器无法打开");
        return;
    }

    //编码数据
    AVPacket *packet = (AVPacket *)av_malloc(sizeof(AVPacket));

    //像素数据（解码数据）
    AVFrame *yuv_frame = av_frame_alloc();
    AVFrame *rgb_frame = av_frame_alloc();

    //native绘制
    //窗体
    ANativeWindow* nativeWindow = ANativeWindow_fromSurface(env,surface);
    //绘制时的缓冲区
    ANativeWindow_Buffer outBuffer;

    int len ,got_frame, framecount = 0;
    //6.一阵一阵读取压缩的视频数据AVPacket
    while(av_read_frame(pFormatCtx,packet) >= 0){
        //解码AVPacket->AVFrame
        len = avcodec_decode_video2(pCodeCtx, yuv_frame, &got_frame, packet);

        //Zero if no frame could be decompressed
        //非零，正在解码
        if(got_frame){
            LOGI("解码%d帧",framecount++);
            //lock
            //设置缓冲区的属性（宽、高、像素格式）
            ANativeWindow_setBuffersGeometry(nativeWindow, pCodeCtx->width, pCodeCtx->height,WINDOW_FORMAT_RGBA_8888);
            ANativeWindow_lock(nativeWindow,&outBuffer,NULL);

            //设置rgb_frame的属性（像素格式、宽高）和缓冲区
            //rgb_frame缓冲区与outBuffer.bits是同一块内存
            avpicture_fill((AVPicture *)rgb_frame, outBuffer.bits, AV_PIX_FMT_RGBA, pCodeCtx->width, pCodeCtx->height);

            //YUV->RGBA_8888
            I420ToARGB(yuv_frame->data[0],yuv_frame->linesize[0],
                       yuv_frame->data[2],yuv_frame->linesize[2],
                       yuv_frame->data[1],yuv_frame->linesize[1],
                       rgb_frame->data[0], rgb_frame->linesize[0],
                       pCodeCtx->width,pCodeCtx->height);

            //unlock
            ANativeWindow_unlockAndPost(nativeWindow);

            usleep(1000 * 16);

        }

        av_free_packet(packet);
    }

    ANativeWindow_release(nativeWindow);
    av_frame_free(&yuv_frame);
    avcodec_close(pCodeCtx);
    avformat_free_context(pFormatCtx);

    (*env)->ReleaseStringUTFChars(env, inputStr_, input_cstr);
}


JNIEXPORT void JNICALL
Java_com_demo_androidffmpeg_VedioUtils_playVedioNew(JNIEnv *env, jclass type, jstring inputStr_,
                                                    jobject surface) {
    const char *inputStr = (*env)->GetStringUTFChars(env, inputStr_, NULL);
    av_register_all();
    AVFormatContext * avFormatContext = avformat_alloc_context();
    if(avformat_open_input(&avFormatContext,inputStr,NULL,NULL)!=0){
        LOGE("打开文件失败");
    }
    avformat_find_stream_info(avFormatContext,"");

    (*env)->ReleaseStringUTFChars(env, inputStr_, inputStr);
}