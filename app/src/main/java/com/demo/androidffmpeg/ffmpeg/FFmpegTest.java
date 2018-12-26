package com.demo.androidffmpeg.ffmpeg;

import android.view.View;
import android.widget.TextView;

import com.demo.androidffmpeg.R;
import com.demo.androidffmpeg.VedioUtils;
import com.demo.androidffmpeg.base.BaseActivity;

/**
 * Created by xulc on 2018/12/24.
 */

public class FFmpegTest extends BaseActivity {
    private TextView tv_test;
    @Override
    protected void setContentView() {
        setContentView(R.layout.activity_ffmpeg);
    }

    @Override
    protected void initView() {
        tv_test = findViewById(R.id.tv_test);
        findViewById(R.id.tv1).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                tv_test.setText(VedioUtils.configuration());
            }
        });
        findViewById(R.id.tv2).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                tv_test.setText(VedioUtils.urlProtocolInfo());
            }
        });
        findViewById(R.id.tv3).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                tv_test.setText(VedioUtils.avformatInfo());
            }
        });
        findViewById(R.id.tv4).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                tv_test.setText(VedioUtils.avcodecInfo());
            }
        });
        findViewById(R.id.tv5).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                tv_test.setText(VedioUtils.avfilterInfo());
            }
        });
    }
}
