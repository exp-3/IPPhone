#include <jni.h>

#include "native.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <stdio.h>

#include "opensles_io.h"

#define BUFFERFRAMES 1024
#define VECSAMPS_MONO 64
#define VECSAMPS_STEREO 128
#define SR 44100


#define N 256

int socket_create(const char *ip, int port);

JNIEXPORT void JNICALL Java_com_experiment17_ipphone_MyAsyncTask_hello(JNIEnv *env, jobject obj) {
    jclass clsj = (*env)->GetObjectClass(env, obj);

    /*
    // ipの受け取り
    jfieldID ipfid = (*env)->GetFieldID(env, clsj, "ip", "Ljava/lang/String;");
    jstring jip = (jstring) (*env)->GetObjectField(env, obj, ipfid);
    const char *ip = (*env)->GetStringUTFChars(env, jip, 0);

    jfieldID portfid = (*env)->GetFieldID(env, clsj, "port", "I");
    int port = (*env)->GetIntField(env, obj, portfid);

    int s = socket_create(ip, port);

    send(s, "hello, world\n", 13, 0);

    shutdown(s, SHUT_WR);
    */

    static int on;
    OPENSL_STREAM *p;
    int samps, i, j;
    float inbuffer[VECSAMPS_MONO], outbuffer[VECSAMPS_STEREO];
    p = android_OpenAudioDevice(SR, 1, 2, BUFFERFRAMES);
    if (p == NULL) return;
    on = 1;
    while (on) {
        samps = android_AudioIn(p, inbuffer, VECSAMPS_MONO);
        for (i = 0, j = 0; i < samps; i++, j += 2)
            outbuffer[j] = outbuffer[j + 1] = inbuffer[i];
        android_AudioOut(p, outbuffer, samps * 2);
    }
    android_CloseAudioDevice(p);


    return;
}

int socket_create(const char *ip, int port) {
    // socketを作る
    int s = socket(PF_INET, SOCK_STREAM, 0);
    if (s == -1) {
        perror("socket");
    }

    // connect
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    if (inet_aton(ip, &addr.sin_addr) == 0) {
        perror("address");
    }
    addr.sin_port = htons(port);
    int ret = connect(s, (struct sockaddr *) &addr, sizeof(addr));
    if (ret == -1) {
        perror("connect");
    }

    return s;
}
