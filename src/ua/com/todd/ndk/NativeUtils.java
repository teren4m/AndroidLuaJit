package ua.com.todd.ndk;

public class NativeUtils {
	static {
		System.loadLibrary("dofile");
	}
	
	public static native int nativeMake();
	
	public static native int nativeDofile(byte[] str);
	
	public static native byte[] getBuffer();

}
