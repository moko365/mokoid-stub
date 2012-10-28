/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Original file: /Users/jollen/Documents/workspace-instant/SimpleBrowser/src/com/moko365/browser/simple/ILedService.aidl
 */
package com.moko365.browser.simple;
public interface ILedService extends android.os.IInterface
{
	/** Local-side IPC implementation stub class. */
	public static abstract class Stub extends android.os.Binder 
						implements com.moko365.browser.simple.ILedService
	{
		private static final java.lang.String DESCRIPTOR = "com.moko365.browser.simple.ILedService";
		/** Construct the stub at attach it to the interface. */
		public Stub()
		{
			this.attachInterface(this, DESCRIPTOR);
		}
		/**
		 * Cast an IBinder object into an com.moko365.browser.simple.ILedService interface,
		 * generating a proxy if needed.
		 */
		public static com.moko365.browser.simple.ILedService asInterface(android.os.IBinder obj)
		{
			if ((obj==null)) {
				return null;
			}
			android.os.IInterface iin = (android.os.IInterface)obj.queryLocalInterface(DESCRIPTOR);
			if (((iin!=null)&&(iin instanceof com.moko365.browser.simple.ILedService))) {
				return ((com.moko365.browser.simple.ILedService)iin);
			}
			return new com.moko365.browser.simple.ILedService.Stub.Proxy(obj);
		}
		public android.os.IBinder asBinder()
		{
			return this;
		}
		@Override public boolean onTransact(int code, android.os.Parcel data, android.os.Parcel reply, int flags) throws android.os.RemoteException
		{
			switch (code)
			{
			case INTERFACE_TRANSACTION:
			{
				reply.writeString(DESCRIPTOR);
				return true;
			}
			case TRANSACTION_setOn:
			{
				data.enforceInterface(DESCRIPTOR);
				int _arg0;
				_arg0 = data.readInt();
				boolean _result = this.setOn(_arg0);
				reply.writeNoException();
				reply.writeInt(((_result)?(1):(0)));
				return true;
			}
			case TRANSACTION_setOff:
			{
				data.enforceInterface(DESCRIPTOR);
				int _arg0;
				_arg0 = data.readInt();
				boolean _result = this.setOff(_arg0);
				reply.writeNoException();
				reply.writeInt(((_result)?(1):(0)));
				return true;
			}
			}
			return super.onTransact(code, data, reply, flags);
		}
		private static class Proxy implements com.moko365.browser.simple.ILedService
		{
			private android.os.IBinder mRemote;
			Proxy(android.os.IBinder remote)
			{
				mRemote = remote;
			}
			public android.os.IBinder asBinder()
			{
				return mRemote;
			}
			public java.lang.String getInterfaceDescriptor()
			{
				return DESCRIPTOR;
			}
			public boolean setOn(int led) throws android.os.RemoteException
			{
				android.os.Parcel _data = android.os.Parcel.obtain();
				android.os.Parcel _reply = android.os.Parcel.obtain();
				boolean _result;
				try {
					_data.writeInterfaceToken(DESCRIPTOR);
					_data.writeInt(led);
					mRemote.transact(Stub.TRANSACTION_setOn, _data, _reply, 0);
					_reply.readException();
					_result = (0!=_reply.readInt());
				}
				finally {
					_reply.recycle();
					_data.recycle();
				}
				return _result;
			}
			public boolean setOff(int led) throws android.os.RemoteException
			{
				android.os.Parcel _data = android.os.Parcel.obtain();
				android.os.Parcel _reply = android.os.Parcel.obtain();
				boolean _result;
				try {
					_data.writeInterfaceToken(DESCRIPTOR);
					_data.writeInt(led);
					mRemote.transact(Stub.TRANSACTION_setOff, _data, _reply, 0);
					_reply.readException();
					_result = (0!=_reply.readInt());
				}
				finally {
					_reply.recycle();
					_data.recycle();
				}
				return _result;
			}
		}
		static final int TRANSACTION_setOn = (android.os.IBinder.FIRST_CALL_TRANSACTION + 0);
		static final int TRANSACTION_setOff = (android.os.IBinder.FIRST_CALL_TRANSACTION + 1);
	}
	public boolean setOn(int led) throws android.os.RemoteException;
	public boolean setOff(int led) throws android.os.RemoteException;
}
