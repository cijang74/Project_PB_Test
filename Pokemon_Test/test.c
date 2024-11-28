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

int main(int argc, char* argv[])
{
	int fd1, fd2, fd3, fd4;
	int pid1, pid2, status;
	int who_am_i = 0;
	int answer = 0;
	char who_am_i_str[MAXLINE];
	char message[MAXLINE];
	char buffer[MAXLINE];

	// 파이프 열기: 1번파이프 -> 쓰기전용, 2번파이프 -> 읽기전용
	fd1 = open("./testfifo1", O_RDONLY);
	fd2 = open("./testfifo2", O_WRONLY);

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

	if (who_am_i == 1)
	{
		printf("\nwho_am_i: %d 확인.\n");
		printf("입력: ");
		scanf("%d", &answer);
		printf("\n출력: %d\n", answer);
	}

	if (who_am_i == 2)
	{
		printf("\nwho_am_i: %d 확인.\n");
		printf("입력: ");
		scanf("%d", &answer);
		printf("\n출력: %d\n", answer);
	}
}