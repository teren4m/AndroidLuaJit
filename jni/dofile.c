#include <jni.h>
#include <android/log.h>
#include <math.h>
#include <stdio.h>
#include <android/log.h>
#include <stdlib.h>
#include <unistd.h>

#include "src/lua.h"
#include "src/lualib.h"
#include "src/lauxlib.h"

#define MAX_LEN 50

    lua_State* L;

    char buffer[MAX_LEN+1] = {0};
    int out_pipe[2];
    int saved_stdout;

    JNIEXPORT jint JNICALL Java_ua_com_todd_ndk_NativeUtils_nativeMake()
    {
        L=lua_open();

        luaopen_base(L);
    	luaopen_string(L);
    	luaopen_table(L);
    	luaopen_math(L);
    	luaopen_debug(L);
        luaopen_io(L);

        return 1;
    }

    JNIEXPORT jint JNICALL Java_ua_com_todd_ndk_NativeUtils_nativeDofile(JNIEnv *env, jclass class, jbyteArray byteArray){


    	char *buff;

    	saved_stdout = dup(STDOUT_FILENO);

    	        if( pipe(out_pipe) != 0 ) {          /* make a pipe */
    	            return 0;
    	          }

    	        dup2(out_pipe[1], STDOUT_FILENO);   /* redirect stdout to the pipe */
    	          close(out_pipe[1]);

    	buff =(*env)->GetByteArrayElements(env,byteArray,0);

    	int i;
    	for(i = 0; i < MAX_LEN; i++){
    		buffer[i] = (char)0;
    	}

    	luaL_dostring(L, buff);

    	fflush(stdout);

    	__android_log_write(ANDROID_LOG_INFO, "tag here", "message here");

    	lua_close(L);


    	return 2;
    }

    JNIEXPORT jbyteArray JNICALL Java_ua_com_todd_ndk_NativeUtils_getBuffer(JNIEnv *env, jobject obj){

    	read(out_pipe[0], buffer, MAX_LEN);

    	jbyteArray buffer1 = (*env)->NewByteArray(env,MAX_LEN);

    	(*env)->SetByteArrayRegion(env, buffer1,0, MAX_LEN, buffer);

    	return buffer1;
    }

