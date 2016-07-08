/*
 * =====================================================================================
 *
 *       Filename:  fd-passing.c
 *
 *    Description:  fd-passing through unix domain 
 *                  send above 1 msg
 *
 *        Version:  1.0
 *        Created:  2016年07月07日 11时11分37秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  yong.huang@ngaa.com.cn, 
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
#include <errno.h>

typedef enum {
    NORMAL_FD = 0,
    TRANSPARANT_FD,
    HTTPS_FD 
}fd_type;

typedef struct _custom_type {
    int fd ;
    int type;
}custom_type;

static
void send_fd(int socket, int fd)  // send fd by socket
{
    struct msghdr msg = { 0 };
    char buf[CMSG_SPACE(sizeof(fd))];

    memset(buf, '\0', sizeof(buf));
    struct iovec io[2] = {
                         { .iov_base = "ABC", .iov_len = 3 },
                         { .iov_base = "CDE", .iov_len = 3 },
                         };

    msg.msg_iov = io;
    msg.msg_iovlen = 2;
    msg.msg_control = buf;
    msg.msg_controllen = sizeof(buf);


    struct cmsghdr * cmsg = CMSG_FIRSTHDR(&msg);
    cmsg->cmsg_level = SOL_SOCKET;
    cmsg->cmsg_type = SCM_RIGHTS;
    cmsg->cmsg_len = CMSG_LEN(sizeof(fd));

    err_remark("put fd %d\n", fd);
    *((int *) CMSG_DATA(cmsg)) = fd;

    msg.msg_controllen = cmsg->cmsg_len;

    if (sendmsg(socket, &msg, 0) < 0)
        err_syserr("Failed to send message\n");
}

static int recv_fd(int socket)  // receive fd from socket
{
    struct msghdr msg = {0};

    char m_buffer[256];
//    struct iovec io = { .iov_base = m_buffer, .iov_len = sizeof(m_buffer) };
    char buf1[10] = {0};
    char buf2[10] = {0};
    struct iovec io[2];
    io[0].iov_base = buf1;
    io[0].iov_len = 3;

    io[1].iov_base = buf2;
    io[2].iov_len = 3;
    
//    msg.msg_iov = &io;
    msg.msg_iov = io;
    msg.msg_iovlen = 2;

    char c_buffer[256];
    msg.msg_control = c_buffer;
    msg.msg_controllen = sizeof(c_buffer);

    if (recvmsg(socket, &msg, 0) < 0)
        err_syserr("Failed to receive message\n");

    struct cmsghdr * cmsg = CMSG_FIRSTHDR(&msg);

//    unsigned char * data = CMSG_DATA(cmsg);
    void * data = CMSG_DATA(cmsg);

    err_remark("About to extract fd\n");
    int fd = *((int*) data);
    err_remark("Extracted fd %d\n", fd);
    err_remark("Extracted buf1 %s\n", buf1);
    err_remark("Extracted buf2 %s\n", buf2);
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

        int fd = open(filename, O_RDONLY|O_CREAT);
        if (fd < 0)
            err_syserr("Failed to open file %s for reading\n", filename);

        printf("Create %d!\n", fd);
        send_fd(sock, fd);

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

        int fd = recv_fd(sock);
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
