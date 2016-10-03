
#include "global.h"
#include <GLES/gl.h>
#include <GLES/glext.h>
#include <GLES/glplatform.h>
//#include <GLES2/gl2.h>
//#include <GLES2/gl2ext.h>
//#include <GLES2/gl2platform.h>
#include <com_cement_jni_NativeRenderer.h>
#include <StlReader.h>
static void printGLString(const char *name, GLenum s) {
	const char *v = (const char *) glGetString(s);
	LOGI("GL %s = %s\n", name, v);
}

static void checkGlError(const char* op) {
	for (GLint error = glGetError(); error; error = glGetError()) {
		LOGI("after %s() glError (0x%x)\n", op, error);
	}
}

static const char gVertexShader[] =
		"attribute vec4 vPosition;\n"
		"void main() {\n"
		"gl_Position = vPosition;\n"
		"}\n";

static const char gFragmentShader[] =
		"precision mediump float;\n"
		"void main() {\n"
		"gl_FragColor = vec4(0.0, 1.0, 0.0, 1.0);\n"
		"}\n";

GLuint loadShader(GLenum shaderType, const char* pSource) {
	GLuint shader = glCreateShader(shaderType);
	if (shader) {
		glShaderSource(shader, 1, &pSource, NULL);
		glCompileShader(shader);
		GLint compiled = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
		if (!compiled) {
			GLint infoLen = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
			if (infoLen) {
				char* buf = (char*) malloc(infoLen);
				if (buf) {
					glGetShaderInfoLog(shader, infoLen, NULL, buf);
					LOGE("Could not compile shader %d:\n%s\n", shaderType, buf);
					free(buf);
				}
				glDeleteShader(shader);
				shader = 0;
			}
		}
	}

	return shader;
}

GLuint createProgram(const char* pVertexSource, const char* pFragmentSource) {
	GLuint vertexShader = loadShader(GL_VERTEX_SHADER, pVertexSource);
	if (!vertexShader) {
		return 0;
	}

	GLuint pixelShader = loadShader(GL_FRAGMENT_SHADER, pFragmentSource);
	if (!pixelShader) {
		return 0;
	}

	GLuint program = glCreateProgram();
	if (program) {
		glAttachShader(program, vertexShader);
		checkGlError("glAttachShader");
		glAttachShader(program, pixelShader);
		checkGlError("glAttachShader");
		glLinkProgram(program);
		GLint linkStatus = GL_FALSE;
		glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
		if (linkStatus != GL_TRUE) {
			GLint bufLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLength);
			if (bufLength) {
				char* buf = (char*) malloc(bufLength);
				if (buf) {
					glGetProgramInfoLog(program, bufLength, NULL, buf);
					LOGE("Could not link program:\n%s\n", buf);
					free(buf);
				}
			}
			glDeleteProgram(program);
			program = 0;
		}
	}
	return program;
}

GLuint gProgram;
GLuint gvPositionHandle;

bool surfaceChanged(int w, int h) {
	printGLString("Version", GL_VERSION);
	printGLString("Vendor", GL_VENDOR);
	printGLString("Renderer", GL_RENDERER);
	printGLString("Extensions", GL_EXTENSIONS);

	LOGI("setupGraphics(%d, %d)", w, h);
	gProgram = createProgram(gVertexShader, gFragmentShader);
	if (!gProgram) {
		LOGE("Could not create program.");
		return false;
	}
	gvPositionHandle = glGetAttribLocation(gProgram, "vPosition");
	checkGlError("glGetAttribLocation");
	LOGI("glGetAttribLocation(\"vPosition\") = %d\n", gvPositionHandle);

	glViewport(0, 0, w, h);
	checkGlError("glViewport");

	GLint loc = glGetUniformLocation(gProgram,"");

	//glFrustumx(1.0f,1.0f,1.0f,1.0f,1.0f,100.f);
	return true;
}

//const GLfloat gTriangleVertices[] = { 0.0f, 0.5f, -0.5f, -0.5f, 0.5f, -0.5f };
float  gTriangleVertices[] = {
		//-1.0f, 0.0f, -0.1f,
		1.0f, 0.0f, -0.1f,
		0.0f, 0.5f, -0.1f,
		0.0f, -0.5f,-0.1f,
       };
float  testVertices[] = {
		-1.0f, 0.0f, -0.1f,
		1.0f, 0.0f, -0.1f,
		0.0f, 1.0f, -0.1f,
		0.0f, -0.5f,-0.1f
       };
float  gTriangleVertices2[] = {
		-1.0f, 0.0f, -0.1f,
		1.0f, 0.0f, -0.1f,
		0.0f, 0.5f, -0.1f,
       };

float *vextxts = testVertices;
long  facetcount = 1;
void surfaceDrawing() {
	glClearColor(0.3f, 0.4f, 0.6f, 0.8f);
	checkGlError("glClearColor");
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	checkGlError("glClear");

	glUseProgram(gProgram);
	checkGlError("glUseProgram");

	glVertexAttribPointer(gvPositionHandle, 3, GL_FLOAT, GL_FALSE, 0,vextxts);
	//glVertexAttribPointer(gvPositionHandle, 3, GL_FLOAT, GL_FALSE, 14,faceVextxts);

	checkGlError("glVertexAttribPointer");
	glEnableVertexAttribArray(gvPositionHandle);
	checkGlError("glEnableVertexAttribArray");
	//glDrawArrays(GL_TRIANGLES, 12, 12);
	glDrawArrays(GL_TRIANGLES, 0, facetcount*3);
	checkGlError("glDrawArrays");
}
float* freeFloat =NULL;
JNIEXPORT void JNICALL Java_com_cement_jni_NativeRenderer_drawStlModel
  (JNIEnv *env, jclass jclazz, jstring jpath){
		const char* path = env->GetStringUTFChars(jpath,JNI_FALSE);
		extern int facet_count;
		extern float* facet_coords;
		freeFloat = vextxts;
        readStlFile(path);
		facetcount = facet_count;
		vextxts = facet_coords;
        LOGI("...................................................%ld",facetcount);
		for (int x = 0; x < facetcount*9; x++) {
		     *(vextxts+x)/=100;
		}
  		env->ReleaseStringUTFChars(jpath,path);
}

JNIEXPORT void JNICALL Java_com_cement_jni_NativeRenderer_surfaceCreated
  (JNIEnv *env, jclass jclazz){

}

JNIEXPORT void JNICALL Java_com_cement_jni_NativeRenderer_surfaceChanged
  (JNIEnv *env, jclass jclazz, jint width, jint height){
	surfaceChanged(width,height);
}

JNIEXPORT void JNICALL Java_com_cement_jni_NativeRenderer_surfaceDrawing
  (JNIEnv *env, jclass jclazz){
	surfaceDrawing();
}





