#include "unpipc.h"

void client(int readfd, int writefd) {
    size_t len;
    ssize_t n;
    char buff[MAXLINE];

    /* 4read pathname */
	
    Fgets(buff, MAXLINE, stdin);
    len = strlen(buff); /* fgets() guarantees null byte at end */
	// 标准输出会把你的回车行符号一起读进来,把它去除
    if(buff[len - 1] == '\n')
        len--; /* delete newline from fgets() */

    /* 4write pathname to IPC channel */
    Write(writefd, buff, len);

    /* 4read from IPC, write to standard output */
	// 
    while((n = Read(readfd, buff, MAXLINE)) > 0)
        Write(STDOUT_FILENO, buff, n);
}
