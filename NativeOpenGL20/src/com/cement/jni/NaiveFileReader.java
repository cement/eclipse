package com.cement.jni;

public class NaiveFileReader {
	
	    public native int NativeFileOpen(String filename, String mode);  
	   
	    public native int NativeFileRead(int fd, byte[] buf, int sizes);  
	  
	    public native int NativeFileWrite(int fd, byte[] buf, int sizes);  
	  
	    public native long NativeFileSeek(int fd, long Offset, int where);  
	  
	    public native int NativeFileClose(int fd);  
}
