/* include mesg_recv */
#include "mesg.h"

// 读取整个消息长度,返回消息内容长度(不含消息头长度)
ssize_t mesg_recv(int fd, struct mymesg *mptr) {
    size_t len;
    ssize_t n;
    //先读取消息头,同时通过消息头获取消息内容长度
    /* 4read message header first, to get len of data that follows */
    if((n = Read(fd, mptr, MESGHDRSIZE)) == 0)
        return (0); /* end of file */
    else if(n != MESGHDRSIZE)
        err_quit("message header: expected %d, got %d", MESGHDRSIZE, n);

    if((len = mptr->mesg_len) > 0)
        if((n = Read(fd, mptr->mesg_data, len)) != len)
            err_quit("message data: expected %d, got %d", len, n);
    return (len);
}
/* end mesg_recv */
ssize_t Mesg_recv(int fd, struct mymesg *mptr) {
    return (mesg_recv(fd, mptr));
}
