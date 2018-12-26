package com.demo.androidffmpeg;

import android.content.Intent;
import android.view.View;
import android.widget.TextView;

import com.demo.androidffmpeg.base.BaseActivity;
import com.demo.androidffmpeg.ffmpeg.FFmpegTest;

public class MainActivity extends BaseActivity implements View.OnClickListener{
    private TextView tv1,tv2,tv3,tv4;


    @Override
    protected void setContentView() {
        setContentView(R.layout.activity_main);
    }

    @Override
    protected void initView() {
        tv1 = findViewById(R.id.tv1);
        tv2 = findViewById(R.id.tv2);
        tv3 = findViewById(R.id.tv3);
        tv4 = findViewById(R.id.tv4);

        tv1.setOnClickListener(this);
        tv2.setOnClickListener(this);
        tv3.setOnClickListener(this);
        tv4.setOnClickListener(this);
    }


    @Override
    public void onClick(View v) {
        switch (v.getId()){
            case R.id.tv1:
                Intent intent = new Intent(this,BaseJNIActivity.class);
                startActivity(intent);
                break;
            case R.id.tv2:
                Intent intent1 = new Intent(this,FFmpegTest.class);
                startActivity(intent1);
                break;


        }
    }
}
