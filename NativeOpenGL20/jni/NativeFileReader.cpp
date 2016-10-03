#include <com_cement_jni_NaiveFileReader.h>
JNIEXPORT jint JNICALL Java_com_cement_jni_NaiveFileReader_NativeFileOpen
  (JNIEnv *env, jobject jobj, jstring jpath, jstring jmode){
	const char *filePath= env->GetStringUTFChars(jpath,JNI_FALSE);
		const char *fileMode= env->GetStringUTFChars(jmode,JNI_FALSE);
		FILE *fd = fopen(filePath,fileMode);
		env->ReleaseStringUTFChars(jpath,filePath);
		env->ReleaseStringUTFChars(jmode,fileMode);
	return fd;
}
JNIEXPORT jint JNICALL Java_com_cement_jni_NaiveFileReader_NativeFileRead
  (JNIEnv *, jobject, jint, jbyteArray, jint){
	return 0;
}
JNIEXPORT jint JNICALL Java_com_cement_jni_NaiveFileReader_NativeFileWrite
  (JNIEnv *, jobject, jint, jbyteArray, jint){
	return 0;
}
JNIEXPORT jlong JNICALL Java_com_cement_jni_NaiveFileReader_NativeFileSeek
  (JNIEnv *, jobject, jint, jlong, jint){
	return 0;
}
JNIEXPORT jint JNICALL Java_com_cement_jni_NaiveFileReader_NativeFileClose
  (JNIEnv *, jobject, jint){
	return 0;
}
