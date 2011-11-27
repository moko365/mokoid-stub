/*
  File: AndroInt Projects Exercise 1 / AndroIntActivity.java

  Description: Android Integration Exercise activity / Activity source

  Copyright (C) 2010- by "William W.-Y. Liang" @ EPS Lab of NTUT.CSIE

  Date: $Date: 2011-02-12 13:56:09 $
  Version: $Revision: 1.3 $

  History:

  $Log: AndroIntActivity.java,v $
  Revision 1.3  2011-02-12 13:56:09  wyliang
  remove @Override in classes which implement interfaces

  Revision 1.2  2010-07-05 05:41:39  wyliang
  Set EditText input type as numberic type

  Revision 1.1.1.1  2010-07-03 08:52:53  wyliang
  initial import into CVS


 */

package com.eps.william.androint;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;

public class AndroIntActivity extends Activity {
	private EditText mEditText1;
	private EditText mEditText2;
	private Button mButton;

	/** Called when the activity is first created. */
	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.main);

		mEditText1 = (EditText) this.findViewById(R.id.EditText01);
		mEditText2 = (EditText) this.findViewById(R.id.EditText02);

		int inputtype = android.text.InputType.TYPE_CLASS_NUMBER
				| android.text.InputType.TYPE_NUMBER_FLAG_SIGNED;
		mEditText1.setInputType(inputtype);
		mEditText2.setInputType(inputtype);

		mButton = (Button) this.findViewById(R.id.Button01);
		mButton.setOnClickListener(mAddListener);
	}

	private OnClickListener mAddListener = new OnClickListener() {
		public void onClick(View view) {
			int a = Integer.parseInt(mEditText1.getText().toString());
			int b = Integer.parseInt(mEditText2.getText().toString());
			int result = a + b;

			mButton.setText(String.valueOf("A+B=" + result));
		}
	};
}
