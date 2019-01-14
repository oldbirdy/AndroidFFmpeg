package com.demo.androidffmpeg.Adapter;


import android.content.Context;
import android.support.v7.widget.RecyclerView;
import android.view.LayoutInflater;
import android.view.ViewGroup;

import com.demo.androidffmpeg.R;


/**
 * Created by xulc on 2019/1/14.
 */

public class VedioAdapter extends RecyclerView.Adapter<VedioHolder> {

    private Context context;

    @Override
    public VedioHolder onCreateViewHolder(ViewGroup parent, int viewType) {
        return new VedioHolder(LayoutInflater.from(context).inflate(R.layout.item_vedio,parent,false));
    }

    @Override
    public void onBindViewHolder(VedioHolder holder, int position) {

    }

    @Override
    public int getItemCount() {
        return 0;
    }
}
