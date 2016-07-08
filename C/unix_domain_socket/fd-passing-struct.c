/*
 * =====================================================================================
 *
 *       Filename:  fd-passing.c
 *
 *    Description:  fd-passing through unix domain 
 *                  fd change to struct type
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


union {      /*Ancillary data buffer, wrapped in a union in order to ensure it is suitably aligned*/
    char buf[CMSG_SPACE(sizeof(custom_type))];
    struct cmsghdr align;
}u;

#define NUM_FD  10
int myfds[NUM_FD];  /*  Contains the file descriptors to pass */
union {         /*  Ancillary data buffer, wrapped in a union
                    in order to ensure it is suitably aligned */
    char buf[CMSG_SPACE(sizeof(myfds))];
    struct cmsghdr align;
} ufd;


static
void send_fd(int socket, int fd)  // send fd by socket
{
    struct msghdr msg = { 0 };
#ifdef _USE_STRUCT
    int *fdptr;
    myfds[0] = fd;
    myfds[1] = 0;
#else
    char buf[CMSG_SPACE(sizeof(fd))];
#endif
    struct iovec io = { .iov_base = "ABC", .iov_len = 3 };

    msg.msg_iov = &io;
    msg.msg_iovlen = 1;
    msg.msg_control = ufd.buf;   //see /proc/sys/net/core/optmem_max
    msg.msg_controllen = sizeof(ufd.buf);


    struct cmsghdr * cmsg = CMSG_FIRSTHDR(&msg);
    cmsg->cmsg_level = SOL_SOCKET;
//    cmsg->cmsg_type = SCM_RIGHTS;
    cmsg->cmsg_type = SCM_CREDENTIALS;
#ifdef _USE_STRUCT
//    cmsg->cmsg_len = CMSG_LEN(sizeof(ct));
    cmsg->cmsg_len = CMSG_LEN(sizeof(int) * NUM_FD);

#else
    cmsg->cmsg_len = CMSG_LEN(sizeof(fd));
#endif

#ifdef _USE_STRUCT
//    *((custom_type *) CMSG_DATA(cmsg)) = ct;
     fdptr = (int *) CMSG_DATA(cmsg);    /*  Initialize the payload */
//     memcpy(fdptr,&ct, sizeof(ct));
     memcpy(fdptr, myfds, NUM_FD * sizeof(int));
//     err_remark("put fd %d\n", ct.fd);
//     err_remark("put fd->type %d\n", ct.type);
#else
    *((int *) CMSG_DATA(cmsg)) = fd;
#endif

    msg.msg_controllen = cmsg->cmsg_len;

    if (sendmsg(socket, &msg, 0) < 0)
        err_syserr("Failed to send message\n");
}

static int recv_fd(int socket)  // receive fd from socket
{
    struct msghdr msg = {0};

    char m_buffer[256];
    struct iovec io = { .iov_base = m_buffer, .iov_len = sizeof(m_buffer) };
    msg.msg_iov = &io;
    msg.msg_iovlen = 1;

    char c_buffer[256];
    msg.msg_control = c_buffer;
    msg.msg_controllen = sizeof(c_buffer);

    if (recvmsg(socket, &msg, 0) < 0)
        err_syserr("Failed to receive message\n");

    struct cmsghdr * cmsg = CMSG_FIRSTHDR(&msg);

    err_remark("About to extract fd\n");
#ifdef _USE_STRUCT
//    custom_type ct = *((custom_type*) data);
//    custom_type ct = {.fd = 0, .type = 0};
//    err_remark("Extracted fd %d\n", ct.fd);
//    err_remark("Extracted fd->type %d\n", ct.type);
//    memmove(&ct, CMSG_DATA(cmsg), sizeof(ct));
    memmove(myfds, CMSG_DATA(cmsg), NUM_FD * sizeof(int));
//    err_remark("Extracted fd %d\n", ct.fd);
//    err_remark("Extracted fd->type %d\n", ct.type);
    err_remark("Extracted fd %d\n", myfds[0]);
    err_remark("Extracted fd->type %d\n", myfds[1]);
//    return ct.fd;
    return myfds[0];
#else
    void * data = CMSG_DATA(cmsg);
    int fd = *((int*) data);
    err_remark("Extracted fd %d\n", fd);
    return fd;
#endif
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
