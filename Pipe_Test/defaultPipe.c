#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define MAXLINE 100

int main()
{
    int n, length, fd[2], pid;
    char message[MAXLINE], line[MAXLINE];

    // 파이프 생성
    pipe(fd);

    // 자식 프로세스 생성, 아래 블록 실행
    if (pid = fork() == 0)
    {
        // 읽기 파이프 해제
        close(fd[0]);

        sprintf(message, "안녕. 내 프로세스 아이디는 %d (이)야.\n", getpid());
        length = strlen(message) + 1;

        // 쓰기 파이프에 메시지 송신
        write(fd[1], message, length);
    }

    // 부모 프로세스는 아래 블록 실행
    else
    {
        // 쓰기 파이프 해제
        close(fd[1]);

        // 읽기 파이프에 있는 메시지 수신
        n = read(fd[0], line, MAXLINE);

        printf("[%d] %s", getpid(), line);
    }

    exit(0);
}