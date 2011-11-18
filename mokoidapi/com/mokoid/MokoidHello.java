
package com.mokoid;

import android.util.Config;
import android.util.Log;
import android.content.Context;
import android.os.Binder;
import android.os.Bundle;
import android.os.RemoteException;
import android.os.IBinder;

public final class MokoidHello {

  static {
        System.load("/system/lib/libmokoid.so");
    }

  public void SayHello() {
    Log.i("MokoidPlatform", "This is MokoidHello.");
	_say_hello();
    return;
    }

  private static native void _say_hello();
}


