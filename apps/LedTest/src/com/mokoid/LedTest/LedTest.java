/*
 * Copyright (C) 2007 The Android Open Source Project
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

package com.mokoid.LedTest;
import mokoid.hardware.Led;
import mokoid.hardware.LedManager;
import mokoid.hardware.LedEventListener;
import com.mokoid.server.LedService;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;
import android.widget.Button;
import android.content.Intent;
import android.view.View;
import android.os.Debug;

public class LedTest extends Activity implements View.OnClickListener,
							LedEventListener {
    private LedManager mLedManager = null;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        //Debug.startMethodTracing("led");

        // Start LedService in a seperated process.
        startService(new Intent("com.mokoid.systemserver"));

	// Just for testing. !! PLEASE DON't DO THIS !!
	//LedService ls = new LedService();

        Button btn = new Button(this);
        btn.setText("Click to turn LED 1 On");
	btn.setOnClickListener(this);

        setContentView(btn);

        //Debug.stopMethodTracing();
    }

    public void onClick(View v) {

        // Get LedManager.
        if (mLedManager == null) {
            Log.i("LedTest", "Creat a new LedManager object.");
            mLedManager = new LedManager();
            mLedManager.registerListener(this);
        }

        if (mLedManager != null) {
	        Log.i("LedTest", "Got LedManager object.");
	    }

        /** Call methods in LedService via proxy object 
         * which is provided by LedManager. 
         */

        mLedManager.LedOn(1); 

        /* Using Native LedService */
        Led led = new Led();
        led.LedOn(1);

        TextView tv = new TextView(this);
        tv.setText("LED 1 is On.");
        setContentView(tv);
    }

    public void onLedChanged() {
        Log.i("LedTest", " in LedTest::onLedChanged");
    }
}
