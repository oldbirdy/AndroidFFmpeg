package com.demo.androidffmpeg;

import android.widget.LinearLayout;

import com.demo.androidffmpeg.base.BaseActivity;
import com.demo.androidffmpeg.ui.LableTextView;

/**
 * Created by xulc on 2018/12/3.
 * JNI基础
 */

public class BaseJNIActivity extends BaseActivity {
    private LinearLayout ll_content;
    private NativeBase nativeBase;


    @Override
    protected void setContentView() {
        setContentView(R.layout.activity_basejni);
    }

    @Override
    protected void initView() {
        ll_content = findViewById(R.id.ll_content);
        nativeBase = new NativeBase();
        initData();
    }


    private void initData() {
        ll_content.addView(new LableTextView(this).setLableValue("HELLO WORLD:",nativeBase.helloWordFromJNI()));
        ll_content.addView(new LableTextView(this).setLableValue("3和5相加:","" + nativeBase.sumInter(3,5)));
        ll_content.addView(new LableTextView(this).setLableValue("HELLO加WORLD:",nativeBase.sumString("HELLO","WORLD")));
        int[] array = new int[]{5,8,3,2,6};
        ll_content.addView(new LableTextView(this).setLableValue("整形数组排序之前:",getIntArrayStr(array)));
        nativeBase.quickSort(array);
        ll_content.addView(new LableTextView(this).setLableValue("整形数组排序之后:",getIntArrayStr(array)));
        ll_content.addView(new LableTextView(this).setLableValue("修改对象的成员变量之前:",nativeBase.hello));
        nativeBase.JNIChangeInstanceValue();
        ll_content.addView(new LableTextView(this).setLableValue("修改对象的成员变量之后:",nativeBase.hello));
        ll_content.addView(new LableTextView(this).setLableValue("修改类的静态变量之前:",NativeBase.world));
        nativeBase.JNIChangeStaticValue();
        ll_content.addView(new LableTextView(this).setLableValue("修改类的静态变量之后:",NativeBase.world));
        ll_content.addView(new LableTextView(this).setLableValue("调用java的实例方法之前:",nativeBase.logTag));
        nativeBase.JNICallJAVAInstanceMethod();
        ll_content.addView(new LableTextView(this).setLableValue("调用java的实例方法之后:",nativeBase.logTag));
        nativeBase.JNICallJAVAStaticMethod(ll_content,this);
        nativeBase.JNICallJAVAConstructorMethod(this,"来自jni调用构造方法生成的context");
    }

    private String getIntArrayStr(int[] arr){
        StringBuilder sb = new StringBuilder();
        for (int i=0;i<arr.length;i++){
            sb.append(arr[i]);
            sb.append("-");
        }
        return sb.toString();
    }

}
