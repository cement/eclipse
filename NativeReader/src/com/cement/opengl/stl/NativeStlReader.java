package com.cement.opengl.stl;

public class NativeStlReader {

	static{
		System.loadLibrary("NativeReader");
	}
	public native boolean nativeReadFile(String path);
	public native boolean transmitFilePath(String path);
}
