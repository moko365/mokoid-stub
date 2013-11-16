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
public class Led
{
    private static final String TAG = "Led";

    static {
        System.load("/system/lib/libled_native.so");
    }

    public Led() {
        _init();
    }
    
    public boolean LedOn(int n) {
        return _led_on(n);
    }

    public boolean LedOff(int n) {
        return _led_off(n);
    }

    private static native boolean _init();
    private static native boolean _led_on(int n);
    private static native boolean _led_off(int n);
}
