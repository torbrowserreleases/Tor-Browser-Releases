package org.torproject.android;

import android.app.Service;
import android.content.Intent;
import android.os.IBinder;

public class TorService extends Service {
    private TorController torController;
    private boolean isRunning = false;

    @Override
    public void onCreate() {
        super.onCreate();
        torController = new TorController(getApplicationContext());
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        if (!isRunning) {
            startTor();
        }
        return START_STICKY;
    }

    private void startTor() {
        new Thread(() -> {
            torController.startTor();
            isRunning = true;
            sendBroadcast(new Intent("org.torproject.android.TOR_STARTED"));
        }).start();
    }

    @Override
    public void onDestroy() {
        if (isRunning) {
            torController.stopTor();
        }
        super.onDestroy();
    }

    @Override
    public IBinder onBind(Intent intent) {
        return null;
    }
}