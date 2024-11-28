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

// 파이프를 생성하고 읽어오는 코드
int main()
{
	int fd;
	char str[MAXLINE];

	// 파이프 생성
	unlink("myPipe");
	mkfifo("myPipe", 0660);

	// 파이프를 읽기 모드로 열기
	fd = open("myPipe", O_RDONLY);

	// 읽기 파이프에 있는 글자를 입력
	while (readLine(fd, str))
	{
		printf("%s \n", str);
		close(fd);
		return 0;
	}
}

int readLine(int fd, char* str)
{
	// char 하나하나를 읽기 파이프에서 읽어오기
	int n;

	do
	{
		n = read(fd, str, 1);
	} while (n > 0 && *str++ != NULL);

	return (n > 0);
}