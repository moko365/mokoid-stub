#include <fcntl.h>
#include <jni.h>

#define DEVFILE "/dev/androint"
#define BUFLEN  128

JNIEXPORT jint JNICALL Java_com_eps_william_androint_AndroIntActivity_addJNI
  (JNIEnv *env, jobject thiz, jint a, jint b)
{
        int fd;
        int buf[2] = {a, b};
        int result;

        fd = open(DEVFILE, O_RDWR);
        write(fd, buf, sizeof(int)*2);
        read(fd, &result, sizeof(int));
        close(fd);

        return result;
}
