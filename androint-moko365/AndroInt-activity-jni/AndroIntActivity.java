/*
  File: AndroInt Projects Exercise 4 / AndroIntActivity.java

  Description: Android Integration Exercise activity / Activity source

  Copyright (C) 2010- by "William W.-Y. Liang" @ EPS Lab of NTUT.CSIE

  Date: $Date: 2011-02-24 07:29:43 $
  Version: $Revision: 1.3 $

  History:

  $Log: AndroIntActivity.java,v $
  Revision 1.3  2011-02-24 07:29:43  wyliang
  solve override problem

  Revision 1.2  2010-07-05 05:49:53  wyliang
  Set EditText input type as numberic type

  Revision 1.1.1.1  2010-07-03 09:11:51  wyliang
  initial import into CVS


 */

package com.eps.william.androint;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

public class AndroIntActivity extends Activity {
	private EditText mEditText1;
	private EditText mEditText2;
	private Button mButton;

	public native int addJNI(int a, int b);

	static {
		System.loadLibrary("androint-jni");
	}

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
	}

	private OnClickListener mAddListener = new OnClickListener() {
		public void onClick(View view) {
			int a = Integer.parseInt(mEditText1.getText().toString());
			int b = Integer.parseInt(mEditText2.getText().toString());

			int result = addJNI(a, b);

			mButton.setText(String.valueOf("A+B=" + result));
		}
	};
}
