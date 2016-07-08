# fd-passing 
[UnixDomainSocket](http://linux.die.net/man/7/unix) sockets for local interprocess communication

##msghdr discription
```
struct iovec {                    /* Scatter/gather array items */
    void  *iov_base;              /* Starting address */
    size_t iov_len;               /* Number of bytes to transfer */
};
```
```
struct msghdr {
    void         *msg_name;       /* optional address */
    socklen_t     msg_namelen;    /* size of address */
    struct iovec *msg_iov;        /* scatter/gather array */
    size_t        msg_iovlen;     /* # elements in msg_iov */
    void         *msg_control;    /* ancillary data, see below */
    size_t        msg_controllen; /* ancillary data buffer len */
    int           msg_flags;      /* flags on received message */
};
```

* The msg_name field points to a caller-allocated buffer that is used to return the source address if the socket is unconnected.  The
caller should set msg_namelen to the size of this buffer before this call; upon return from a successful call, msg_namelen will contain
the length of the returned address.  If the application does not need to know the source address, msg_name can be specified as NULL.

* The fields msg_iov and msg_iovlen describe scatter-gather locations,as discussed in readv(2).

* The field msg_control, which has length msg_controllen, points to a buffer for other protocol control-related messages or miscellaneous
ancillary data.  When recvmsg() is called, msg_controllen should contain the length of the available buffer in msg_control; upon
return from a successful call it will contain the length of the control message sequence.

* The messages are of the form:
    ```
    struct cmsghdr {
        size_t cmsg_len;    /* Data byte count, including header
                               (type is socklen_t in POSIX) */
        int    cmsg_level;  /* Originating protocol */
        int    cmsg_type;   /* Protocol-specific type */
        /* followed by
           unsigned char cmsg_data[]; */
    };
    ```

Ancillary data should be accessed only by the macros defined in cmsg(3).

As an example, Linux uses this ancillary data mechanism to pass extended errors, IP options, or file descriptors over UNIX domain sockets.

##Ancillary messages

Ancillary data is sent and received using sendmsg(2) and recvmsg(2). 
For historical reasons the ancillary message types listed below are specified with a SOL_SOCKET type even though they are AF_UNIX specific. 
To send them set the cmsg_level field of the struct cmsghdr to SOL_SOCKET and the cmsg_type field to the type. For more information see cmsg(3).

SCM_RIGHTS
Send or receive a set of open file descriptors from another process. The data portion contains an integer array of the file descriptors.
The passed file descriptors behave as though they have been created with dup(2).

SCM_CREDENTIALS
Send or receive UNIX credentials. This can be used for authentication. The credentials are passed as a struct ucred ancillary message. 
Thus structure is defined in <sys/socket.h> as follows:

```
struct ucred {
    pid_t pid;    /* process ID of the sending process */
    uid_t uid;    /* user ID of the sending process */
    gid_t gid;    /* group ID of the sending process */
};
```

Since glibc 2.8, the _GNU_SOURCE feature test macro must be defined (before including any header files) in order to obtain the definition of this structure.
The credentials which the sender specifies are checked by the kernel. A process with effective user ID 0 is allowed to specify values that do not match its own. The sender must specify its own process ID (unless it has the capability CAP_SYS_ADMIN), its user ID, effective user ID, or saved set-user-ID (unless it has CAP_SETUID), and its group ID, effective group ID, or saved set-group-ID (unless it has CAP_SETGID). To receive a struct ucred message the SO_PASSCRED option must be enabled on the socket.

##FD-PASSING example

* [fd-passing.c](#fd-passing)
* [fd-passing-offset.c](#fd-passing-file-offset)
* [fd-passing-multi.c](#fd-passing-multi)
