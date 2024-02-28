#include "csapp.h"

void echo(int connfd) {
    size_t n; 
    char buf[MAXLINE], last_buf[MAXLINE]; 
    int hare_step = 0, turtle_step = 0;
    rio_t rio;

    Rio_readinitb(&rio, connfd);
    while((n = Rio_readlineb(&rio, buf, MAXLINE)) != 0) {
        if (hare_step % 2 == 0) { // 거북이는 두 번에 한 번씩 움직입니다.
            if (strcmp(buf, last_buf) == 0) {
                // 데이터 패턴이 반복됨을 감지
                printf("501? 502? error\n");
                break; // 연결 종료
            }
            strcpy(last_buf, buf);
        }
        hare_step++; // 토끼는 매번 움직입니다.

        printf("server received %d bytes\n", (int)n);
        Rio_writen(connfd, buf, n);
    }
}
