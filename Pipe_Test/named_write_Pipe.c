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

#define MAXLINE 100

// 생성된 파이프에 문장을 입력하는 코드
int main()
{
	int fd, length;
	char message[MAXLINE];

	// message 배열에 문장 집어넣기
	sprintf(message, "Hello from PID %d", getpid());
	length = strlen(message) + 1;

	// 파이프 만들어지기 전에 write가 실행되지 않도록 하는 반복문
	do
	{
		// 파이프를 쓰기모드로 열기
		fd = open("myPipe", O_WRONLY);

		if (fd == -1)
		{
			sleep(1);
		}
	} while (fd == -1);

	// 쓰기모드 파이프에 message를 4번 송신
	for (int i = 0; i <= 3; i++)
	{
		write(fd, message, length);
		sleep(3);
	}

	close(fd);
	return 0;
}