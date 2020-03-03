#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
int main(int argc, char **argv)
{
    char msg[9+1] = "Hello LKM";
    static char rx_buf[20];
    int fd, i;

    printf("opening file /dev/ce3003\n");
    fd = open("/dev/ce3003", O_RDWR);
    if (fd < 0)
    { printf("open /dev/ce3003 failed\n");
        exit (-1);
    }
    else
        printf("open /dev/ce3003 successfully\n");
    i = write(fd, msg, 9+1);
    printf ("Message sent to LKM: \"%s\" \n", msg);
    i = read(fd, rx_buf, 20);

    if (i < 0)
    { printf ("read error\n");
        close(fd);
        exit (-1);
    }

    else
        printf ("Message received from LKM = \"%s \n, buf);
    close(fd);
    exit(0);
} /* main */


