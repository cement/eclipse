#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <android/log.h>
#include <com_cement_opengl_stl_NativeStlReader.h>
#define TAG "NativeReader"
#define LOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, TAG, __VA_ARGS__)

//#define true 1;
//#define false 0;
using namespace std;



struct facet{
	float normal[3];
	float coords[9];
	short attrib[1];
};
float* readStlFile(const char* filePath){
	    long length;
		char name[80];
		long count;
		FILE *file = fopen(filePath,"rb");
		if(!file){
			LOGV("open file failure: %s",filePath);
			return NULL;
		}else{
			length = fseek(file,0,SEEK_END);
			long len    = ftell(file);
			LOGV("open file success: %s",filePath);
			//length = fseek(file,0,SEEK_END);
			if(fseek(file,0,SEEK_SET)!=-1&&fread(name,80,1,file)!=0){
				LOGV("file name is : %s",name);
			}else {
				return NULL;
			}

			if(fseek(file,80,SEEK_SET)!=-1&&fread(&count,4,1,file)!=0){
				LOGV("file length is : %ld",length);
				LOGV("file len    is : %ld",len);
				LOGV("face number is : %ld",count);
				facet* face_buf = (facet*)malloc(sizeof(facet)*count);
			    if(fseek(file,84,SEEK_SET)!=-1){
			    	if(!fread(face_buf,sizeof(facet),count,file)){
			    		LOGV(".................Error................");
			    	}
			    	int var;
			    	for (var = 0; var < count; ++var) {
			    		int i;
			    		for (i = 0; i < 9; i++) {
						  LOGV("%f; \t",face_buf->coords[i]);
						}
			    		LOGV("\r\n");
					}
			    	free(face_buf);
			    	return NULL;
			    }else {
			    	return NULL;
				}
			}else{
				return NULL;
			}

		}
	return NULL;
}
JNIEXPORT jboolean JNICALL Java_com_cement_opengl_stl_NativeStlReader_nativeReadFile
  (JNIEnv *env, jobject jobj, jstring jstr){
	const char* filePath = env->GetStringUTFChars(jstr,JNI_FALSE);

	if(readStlFile(filePath)==NULL){
		return JNI_FALSE;
	}
	return JNI_TRUE;
}
JNIEXPORT jboolean JNICALL Java_com_cement_opengl_stl_NativeStlReader_transmitFilePath
  (JNIEnv *env, jobject jobj, jstring jstr){
	const char* cp_filePath;
	cp_filePath = env->GetStringUTFChars(jstr,JNI_FALSE);
	return cp_filePath == NULL? JNI_FALSE:JNI_TRUE;
}
