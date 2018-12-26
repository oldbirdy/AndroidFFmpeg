package com.demo.androidffmpeg.ui;

import android.content.Context;
import android.support.annotation.Nullable;
import android.util.AttributeSet;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.LinearLayout;
import android.widget.TextView;

import com.demo.androidffmpeg.R;

/**
 * Created by xulc on 2018/12/19.
 *
 */

public class LableTextView extends LinearLayout {
    private Context mcontext;
    private TextView tv_lable;
    private TextView tv_value;

    public LableTextView(Context context) {
        this(context,null);
    }

    public LableTextView(Context context, @Nullable AttributeSet attrs) {
        super(context, attrs);
        this.mcontext = context;
        initView();

    }

    private void initView() {
        this.setOrientation(HORIZONTAL);
        this.setLayoutParams(new LayoutParams(LayoutParams.MATCH_PARENT,LayoutParams.WRAP_CONTENT));
        LayoutInflater.from(mcontext).inflate(R.layout.layout_view_lable_text,this);
        tv_lable = findViewById(R.id.tv_lable);
        tv_value = findViewById(R.id.tv_value);
    }


    public View setLableValue(String lable, String value){
        tv_lable.setText(lable);
        tv_value.setText(value);
        return this;
    }
}
