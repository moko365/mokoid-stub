/*
 * Copyright (C) 2009 The Mokoid Open Source Project
 * Copyright (C) 2009 Moko365 Inc
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package mokoid.hardware;

import android.content.Context;
import android.os.Binder;
import android.os.Bundle;
import android.os.Parcelable;
import android.os.ParcelFileDescriptor;
import android.os.Process;
import android.os.RemoteException;
import android.os.Handler;
import android.os.Message;
import android.os.ServiceManager;
import android.util.Log;
import mokoid.hardware.ILedService;

/**
 * Class that lets you access the Mokoid LedService.
 */
public class LedManager
{
    private static final String TAG = "LedManager";
    private ILedService mLedService;

    public LedManager() {
	// ILedService, IBinder
        mLedService = ILedService.Stub.asInterface(
                             ServiceManager.getService("led"));

		if (mLedService != null) {
	            Log.i(TAG, "The LedManager object is ready.");
		}
		
    }
    
	private Thread mThread = new MyThread();
	private Handler mHandler = new MyHandler();
	
	private class MyHandler extends Handler {

		@Override
		public void handleMessage(Message msg) {
			Log.i("LedManager", "IPC is returned.");
			mContext.onLedFinish();
			super.handleMessage(msg);
		}
		
	}

    private class MyThread extends Thread {

		@Override
		public void run() {
	    		try {
					mLedService.setOn(1);
					
					Message msg = new Message();
					mHandler.sendMessage(msg);
					
				} catch (RemoteException e) {
					e.printStackTrace();
				}			
			super.run();
		}
    	    	
    	
    }

    public boolean LedOn(int n) {
    		mThread.run(); // async method call
    		return true;
    }

    public boolean LedOff(int n) {
        boolean result = false;

        try {
            result = mLedService.setOff(n);
        } catch (RemoteException e) {
            Log.e(TAG, "RemoteException in LedManager.LedOff:", e);
        }
        return result;
    }
    
	private LedEventListener mContext;

    public void registerListener(LedEventListener context) { // registerListener(this);
    		mContext = context;
    }
}
