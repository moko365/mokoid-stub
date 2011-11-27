/*
  File: AndroInt Projects Exercise 2 / AndroIntService.java

  Description: Android Integration Exercise / Service source

  Copyright (C) 2010- by "William W.-Y. Liang" @ EPS Lab of NTUT.CSIE

  Date: $Date: 2011-02-24 03:30:46 $
  Version: $Revision: 1.2 $

  History:

  $Log: AndroIntService.java,v $
  Revision 1.2  2011-02-24 03:30:46  wyliang
  solve override problem, remove redundant code

  Revision 1.1.1.1  2010-07-03 09:08:55  wyliang
  initial import into CVS


 */
package com.eps.william.androint;

import android.app.Service;
import android.content.Context;
import android.content.Intent;
import android.os.Binder;
import android.os.IBinder;
import android.os.Parcel;
import android.os.RemoteException;
import android.util.Log;

public class AndroIntService extends Service {
	private IBinder mBinder = null;

	private static final String LOG_TAG = "AdroIntService";

	@Override
	public void onCreate() {
		mBinder = new AndroIntBinder();
		Log.i(LOG_TAG, "Service created, binder interface initialized");
	}

	@Override
	public int onStartCommand(Intent intent, int flags, int startId) {
		Log.i(LOG_TAG, "Service receives start id " + startId + ": " + intent);

		return START_STICKY;
	}

	@Override
	public IBinder onBind(Intent arg0) {
		Log.i(LOG_TAG, "Service bind requestd");
		return mBinder;
	}

	public void onDestroy() {
		Log.i("AndroIntService", "Service destroyed.");
	}

	private int add(int a, int b) {
		return a+b;
	}
	
	private class AndroIntBinder extends Binder {
		private Context ctx;
		private static final String LOG_TAG = "AndroIntBinder";

		@Override
		public boolean onTransact(int code, Parcel data, Parcel reply, int flags)
				throws RemoteException {
			int a, b, result;

			a = data.readInt();
			b = data.readInt();
			
			result = add(a, b);

			reply.writeInt(result);

			return true;
		}

	}
}
