#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    // status는 프로세스의 종료상태를 받음
    int pid1, pid2, status;
    pid1 = fork(); // 자식 프로세스 생성

    if (pid1 == 0)
    {
        // 상대경로 fork파일을 실행
        execl("./fork", NULL);
        exit(1);
    }

    waitpid(pid1, &status, 0); // 첫째 프로세스가 끝날 때 까지 기다라기

    pid2 = fork();
    if (pid2 == 0)
    {
        printf("[%d] 나는 둘째 자식프로세스\n", getpid());
        exit(0);
    }

    waitpid(pid2, &status, 0); // 둘째 프로세스가 끝날 때 까지 기다라기

    // 부모프로세스가 해당 블록 실행
    printf("[%d] 나는 부모 프로세스 \n", getpid());
}