package com.demo.androidffmpeg;

import android.content.Context;
import android.widget.LinearLayout;
import android.widget.Toast;

import com.demo.androidffmpeg.ui.LableTextView;

/**
 * Created by xulc on 2018/12/3.
 */

public class NativeBase {
    public String hello = "hello";
    public  static String world = "world";
    public String logTag = "JAVA中的值";


    public static void staticMethod(LinearLayout ll_content,Context context,String result){
        ll_content.addView(new LableTextView(context).setLableValue("调用java的静态方法:",result));
    }

    public String instanceMethod(String logTag){
        this.logTag = logTag;
        return logTag;
    }

    public NativeBase(){

    }

    public NativeBase(Context context,String toast){
        Toast.makeText(context, toast, Toast.LENGTH_SHORT).show();
    }

    //从jni获取字符串
    public native String helloWordFromJNI();
    //jni两个整数相加
    public native int sumInter(int a,int b);
    //jni字符串拼接
    public native String sumString(String str1,String str2);
    //jni数组排序
    public native void quickSort(int array[]);
    //jni修改实例 变量的值
    public native void JNIChangeInstanceValue();
    //jni修改静态变量的值
    public native void JNIChangeStaticValue();
    //jni调用 实例方法
    public native void JNICallJAVAInstanceMethod();
    //jni调用 静态方法
    public native void JNICallJAVAStaticMethod(LinearLayout ll,Context context);
    //jni调用 构造方法
    public native void  JNICallJAVAConstructorMethod(Context context,String toast);
}
