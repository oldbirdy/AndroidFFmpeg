package com.demo.androidffmpeg.bean;

/**
 * Created by xulc on 2019/1/14.
 */

public class Material {
    private String title;
    private String filePath;
    private long fileId;
    private int uploadedSize;
    private String timeStamps;

    public void setTitle(String title) {
        this.title = title;
    }

    public void setFilePath(String filePath) {
        this.filePath = filePath;
    }

    public void setFileId(long fileId) {
        this.fileId = fileId;
    }

    public void setUploadedSize(int uploadedSize) {
        this.uploadedSize = uploadedSize;
    }

    public void setTimeStamps(String timeStamps) {
        this.timeStamps = timeStamps;
    }
}
