#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAXLINE 256

int main()
{
	int fd1, fd2, fd3, fd4, n;
	char msg[MAXLINE];

	// 서버와 토너먼트 조를 연결할 파이프들 //

	// 1번 파이프 생성
	if (mkfifo("./Server-Team_1", 0666) == -1)
	{
		// 예외처리
		perror("mkfifo");
		exit(1);
	}

	// 2번 파이프 생성
	if (mkfifo("./Server-Team_2", 0666) == -1)
	{
		// 예외처리
		perror("mkfifo");
		exit(2);
	}

	// 3번 파이프 생성
	if (mkfifo("./Server-Team_3", 0666) == -1)
	{
		// 예외처리
		perror("mkfifo");
		exit(3);
	}

	// 4번 파이프 생성
	if (mkfifo("./Server-Team_4", 0666) == -1)
	{
		// 예외처리
		perror("mkfifo");
		exit(4);
	}

	

}