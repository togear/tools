/*
 * =====================================================================================
 *
 *       Filename:  fd-passing-1.c
 *
 *    Description:  fd-passing through unix domain
 *                  It also has the parent process read (up to) 32 bytes of the file before passing the file descriptor to the child. The child continues reading where the parent left off. This demonstrates that the file descriptor transferred includes the file offset
 *
 *        Version:  1.0
 *        Created:  2016年07月07日 12时00分39秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  yong.huang@ngaa.com.cn
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include "stderr.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

static
void wyslij(int socket, int fd)  // send fd by socket
{
    struct msghdr msg = { 0 };
    char buf[CMSG_SPACE(sizeof(fd))];
    memset(buf, '\0', sizeof(buf));

    /*  On Mac OS X, the struct iovec is needed, even if it points to minimal data */
    struct iovec io = { .iov_base = "", .iov_len = 1 };

    msg.msg_iov = &io;
    msg.msg_iovlen = 1;
    msg.msg_control = buf;
    msg.msg_controllen = sizeof(buf);

    struct cmsghdr * cmsg = CMSG_FIRSTHDR(&msg);
    cmsg->cmsg_level = SOL_SOCKET;
    cmsg->cmsg_type = SCM_RIGHTS;
    cmsg->cmsg_len = CMSG_LEN(sizeof(fd));

    memmove(CMSG_DATA(cmsg), &fd, sizeof(fd));

    msg.msg_controllen = cmsg->cmsg_len;

    if (sendmsg(socket, &msg, 0) < 0)
        err_syserr("Failed to send message\n");
}

static
int odbierz(int socket)  // receive fd from socket
{
    struct msghdr msg = {0};

    /*  On Mac OS X, the struct iovec is needed, even if it points to minimal data */
    char m_buffer[1];
    struct iovec io = { .iov_base = m_buffer, .iov_len = sizeof(m_buffer) };
    msg.msg_iov = &io;
    msg.msg_iovlen = 1;

    char c_buffer[256];
    msg.msg_control = c_buffer;
    msg.msg_controllen = sizeof(c_buffer);

    if (recvmsg(socket, &msg, 0) < 0)
        err_syserr("Failed to receive message\n");

    struct cmsghdr *cmsg = CMSG_FIRSTHDR(&msg);

    err_remark("About to extract fd\n");
    int fd;
    memmove(&fd, CMSG_DATA(cmsg), sizeof(fd));
    err_remark("Extracted fd %d\n", fd);

    return fd;
}

int main(int argc, char **argv)
{
    const char *filename = "./z7.c";

    err_setarg0(argv[0]);
    err_setlogopts(ERR_PID);
    if (argc > 1)
        filename = argv[1];

    int sv[2];
    if (socketpair(AF_UNIX, SOCK_DGRAM, 0, sv) != 0)
        err_syserr("Failed to create Unix-domain socket pair\n");

    int pid = fork();
    if (pid > 0)  // in parent
    {
        err_remark("Parent at work\n");
        close(sv[1]);
        int sock = sv[0];

        int fd = open(filename, O_RDONLY);
        if (fd < 0)
            err_syserr("Failed to open file %s for reading\n", filename);

        /*  Read some data to demonstrate that file offset is passed */
        char buffer[32];
        int nbytes = read(fd, buffer, sizeof(buffer));
        if (nbytes > 0)
            err_remark("Parent read: [[%.*s]]\n", nbytes, buffer);

        wyslij(sock, fd);

        close(fd);
        nanosleep(&(struct timespec){ .tv_sec = 1, .tv_nsec = 500000000}, 0);
        err_remark("Parent exits\n");
    }
    else  // in child
    {
        err_remark("Child at play\n");
        close(sv[0]);
        int sock = sv[1];

        nanosleep(&(struct timespec){ .tv_sec = 0, .tv_nsec = 500000000}, 0);

        int fd = odbierz(sock);
        printf("Read %d!\n", fd);
        char buffer[256];
        ssize_t nbytes;
        while ((nbytes = read(fd, buffer, sizeof(buffer))) > 0)
            write(1, buffer, nbytes);

        printf("Done!\n");
        close(fd);
    }
    return 0;
}
