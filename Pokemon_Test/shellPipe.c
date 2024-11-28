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
	int fd1, fd2, fd3, fd4;
	int pid1, pid2, status;
	int who_am_i = 0;
	char who_am_i_str[MAXLINE];
	char message[MAXLINE];
	char buffer[MAXLINE];

	// 1번 파이프 생성
	if (mkfifo("./testfifo1", 0666) == -1)
	{
		// 예외처리
		perror("mkfifo");
		//exit(1);
	}

	// 2번 파이프 생성
	if (mkfifo("./testfifo2", 0666) == -1)
	{
		// 예외처리
		perror("mkfifo");
		//exit(1);
	}

	// 파이프 열기: 1번파이프 -> 쓰기전용, 2번파이프 -> 읽기전용
	fd1 = open("./testfifo1", O_WRONLY);
	fd2 = open("./testfifo2", O_RDONLY);

	// 예외처리
	if (fd1 == -1 || fd2 == -1)
	{
		perror("open");
		exit(3);
	}

	if (fd3 == -1 || fd4 == -1)
	{
		perror("open");
		exit(4);
	}

	printf("who_am_i 입력: ");
	scanf("%d", &who_am_i);

	if (who_am_i == 1)
	{
		if ((pid1 = fork()) == 0)
		{
			printf("Debuf");

			snprintf(who_am_i_str, sizeof(who_am_i_str), "%d", who_am_i);
			execl("./test", "./test", who_am_i_str, NULL);

			perror("execl");
			exit(5);
		}
	}

	if (who_am_i == 2)
	{
		if ((pid2 = fork()) == 0)
		{
			snprintf(who_am_i_str, sizeof(who_am_i_str), "%d", who_am_i);
			execl("./test", "./test", who_am_i_str, NULL);

			perror("execl");
			exit(5);
		}
	}
}