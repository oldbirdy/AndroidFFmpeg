package com.demo.androidffmpeg.ffmpeg;

import android.content.Intent;
import android.os.Environment;
import android.view.View;

import com.demo.androidffmpeg.R;
import com.demo.androidffmpeg.VedioUtils;
import com.demo.androidffmpeg.base.BaseActivity;
import com.demo.androidffmpeg.ui.VideoView;

import java.io.File;

/**
 * Created by xulc on 2018/12/24.
 */

public class FFmpegTest extends BaseActivity {
    private VideoView vv_content;
    @Override
    protected void setContentView() {
        setContentView(R.layout.activity_ffmpeg);
    }

    @Override
    protected void initView() {
        vv_content = findViewById(R.id.vv_content);

        findViewById(R.id.ffmpeg_base).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(FFmpegTest.this,FFmpegBaseTest.class);
                startActivity(intent);
            }
        });

        findViewById(R.id.tv2).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(FFmpegTest.this,VedioListActivity.class);
                startActivity(intent);
//                vv_content.setVisibility(View.VISIBLE);
//                String inputstr = Environment.getExternalStorageDirectory() + File.separator + "tencent" + File.separator + "MicroMsg" +  File.separator + "WeiXin" + File.separator + "123.mp4";
//                File file = new File(inputstr);
//                VedioUtils.playVedio(file.getAbsolutePath(),vv_content.getHolder().getSurface());
            }
        });
    }
}
