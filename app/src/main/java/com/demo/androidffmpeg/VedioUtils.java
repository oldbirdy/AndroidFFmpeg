package com.demo.androidffmpeg;

import android.view.Surface;

/**
 * Created by 好好奋斗 on 2018/12/16.
 */

public class VedioUtils {

    public native static String configuration();
    //协议信息
    public native static String urlProtocolInfo();
    //avformat信息
    public native static String avformatInfo();
    //avcodec信息
    public native static String avcodecInfo();
    //avfilter信息  具体报错
    public native static String avfilterInfo();

    //视频转码
    public native static String mp4Twmv(String inputStr,String outputStr);

    public native static void playVedio(String inputStr, Surface surface);

    public native static void playVedioNew(String inputStr, Surface surface);
}
