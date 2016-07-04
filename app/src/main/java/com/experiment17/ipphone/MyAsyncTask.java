package com.experiment17.ipphone;

import android.os.AsyncTask;

import java.io.DataOutputStream;
import java.io.IOException;
import java.net.InetAddress;
import java.net.Socket;

/**
 * Created by takaaki on 16/07/02.
 */
public class MyAsyncTask extends AsyncTask<Integer, Integer, Integer> {
    static {
        System.loadLibrary("native");
    }
    public native void hello();

    private String ip;
    private int port;

    public MyAsyncTask(String ip, int port) {
        super();
        this.ip = ip;
        this.port = port;
    }

    @Override
    protected Integer doInBackground(Integer... params) {
        hello();
        return 0;
    }
}
