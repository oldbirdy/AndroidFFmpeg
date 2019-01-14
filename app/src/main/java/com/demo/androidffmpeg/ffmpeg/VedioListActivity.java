package com.demo.androidffmpeg.ffmpeg;

import android.content.Context;
import android.database.Cursor;
import android.provider.MediaStore;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;

import com.demo.androidffmpeg.Adapter.VedioAdapter;
import com.demo.androidffmpeg.R;
import com.demo.androidffmpeg.base.BaseActivity;
import com.demo.androidffmpeg.bean.Material;

import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.List;
import java.util.TimeZone;

/**
 * Created by xulc on 2019/1/14.
 */

public class VedioListActivity extends BaseActivity {
    private RecyclerView recyclerView;
    private VedioAdapter vadapter;
    private List<Material> list = new ArrayList<>();
    @Override
    protected void setContentView() {
        setContentView(R.layout.activity_vedio_list);
    }

    @Override
    protected void initView() {
        recyclerView =  findViewById(R.id.recyclerView);
        recyclerView.setLayoutManager(new LinearLayoutManager(this,LinearLayoutManager.VERTICAL,false));
        getAllLocalVideos(this,100);
        vadapter = new VedioAdapter(list,this);
        recyclerView.setAdapter(vadapter);;
    }

    /**
     * 获取本地所有的视频
     *
     * @return list
     */
    public static List<Material> getAllLocalVideos(Context context, int uid) {
        long totalUploadCount = 1000;
        String[] projection = {
                MediaStore.Video.Media.DATA,
                MediaStore.Video.Media.DISPLAY_NAME,
                MediaStore.Video.Media.DURATION,
                MediaStore.Video.Media.SIZE
        };
        //全部格式
        String where = MediaStore.Images.Media.MIME_TYPE + "=? or "
                + MediaStore.Video.Media.MIME_TYPE + "=? or "
                + MediaStore.Video.Media.MIME_TYPE + "=? or "
                + MediaStore.Video.Media.MIME_TYPE + "=? or "
                + MediaStore.Video.Media.MIME_TYPE + "=? or "
                + MediaStore.Video.Media.MIME_TYPE + "=? or "
                + MediaStore.Video.Media.MIME_TYPE + "=? or "
                + MediaStore.Video.Media.MIME_TYPE + "=? or "
                + MediaStore.Video.Media.MIME_TYPE + "=?";
        String[] whereArgs = {"video/mp4", "video/3gp", "video/aiv", "video/rmvb", "video/vob", "video/flv",
                "video/mkv", "video/mov", "video/mpg"};

        Cursor cursor = context.getContentResolver().query(MediaStore.Video.Media.EXTERNAL_CONTENT_URI,
                projection, where, whereArgs, MediaStore.Video.Media.DATE_ADDED + " DESC ");

        if (cursor == null) {
            return list;
        }
        try {
            while (cursor.moveToNext()) {
                long size = cursor.getLong(cursor.getColumnIndexOrThrow(MediaStore.Video.Media.SIZE)); // 大小
                if (size < 600 * 1024 * 1024) {//<600M
                    Material materialBean = new Material();
                    String path = cursor.getString(cursor.getColumnIndexOrThrow(MediaStore.Video.Media.DATA)); // 路径
                    long duration = cursor.getInt(cursor.getColumnIndexOrThrow(MediaStore.Video.Media.DURATION)); // 时长
                    materialBean.setTitle(cursor.getString(cursor.getColumnIndex(MediaStore.Video.Media.DISPLAY_NAME)));
                    materialBean.setFilePath(path);
                    materialBean.setFileId(totalUploadCount++);
                    materialBean.setUploadedSize(0);
                    materialBean.setTimeStamps(System.currentTimeMillis() + "");
                    SimpleDateFormat format = new SimpleDateFormat("HH:mm:ss");
                    format.setTimeZone(TimeZone.getTimeZone("GMT+0"));
                    String t = format.format(duration);
//                    materialBean.setTime(context.getString(R.string.video_len) + t);
//                    materialBean.setFileSize(size);
                    list.add(materialBean);
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            cursor.close();
        }
        return list;
    }
}
