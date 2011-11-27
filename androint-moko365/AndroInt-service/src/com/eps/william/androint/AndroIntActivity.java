/*
  File: AndroInt Projects Exercise 2 / AndroIntActivity.java

  Description: Android Integration Exercise activity / Activity source

  Copyright (C) 2010- by "William W.-Y. Liang" @ EPS Lab of NTUT.CSIE

  Date: $Date: 2011-02-24 03:30:46 $
  Version: $Revision: 1.3 $

  History:

  $Log: AndroIntActivity.java,v $
  Revision 1.3  2011-02-24 03:30:46  wyliang
  solve override problem, remove redundant code

  Revision 1.2  2010-07-05 05:47:48  wyliang
  Set EditText input type as numberic type

  Revision 1.1.1.1  2010-07-03 09:08:55  wyliang
  initial import into CVS


*/
package com.eps.william.androint;

import android.app.Activity;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.ServiceConnection;
import android.os.Bundle;
import android.os.IBinder;
import android.os.Parcel;
import android.os.RemoteException;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

public class AndroIntActivity extends Activity {
	private EditText mEditText1;
	private EditText mEditText2;
	private Button mButton;
	private IBinder ib;

	/** Called when the activity is first created. */
	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.main);

		mEditText1 = (EditText) this.findViewById(R.id.EditText01);
		mEditText2 = (EditText) this.findViewById(R.id.EditText02);

		int inputtype = android.text.InputType.TYPE_CLASS_NUMBER|android.text.InputType.TYPE_NUMBER_FLAG_SIGNED; 
		mEditText1.setInputType(inputtype);
		mEditText2.setInputType(inputtype);

		mButton = (Button) this.findViewById(R.id.Button01);
		mButton.setOnClickListener(mAddListener);

		bindService(new Intent(AndroIntActivity.this, AndroIntService.class),
				mConnection, Context.BIND_AUTO_CREATE);
	}

	private ServiceConnection mConnection = new ServiceConnection() {
		public void onServiceConnected(ComponentName className, IBinder ibinder) {
			ib = ibinder;
		}
		
		public void onServiceDisconnected(ComponentName className) {
			ib = null;
		}
	};

	private OnClickListener mAddListener = new OnClickListener() {
		public void onClick(View view) {
			int a = Integer.parseInt(mEditText1.getText().toString());
			int b = Integer.parseInt(mEditText2.getText().toString());
			int result = 0;

			try {
				Parcel data = Parcel.obtain();
				Parcel reply = Parcel.obtain();

				data.writeInt(a);
				data.writeInt(b);

				ib.transact(0, data, reply, 0);

				result = reply.readInt();

			} catch (RemoteException e) {
				e.printStackTrace();
			}

			mButton.setText(String.valueOf("A+B=" + result));
		}
	};

}
