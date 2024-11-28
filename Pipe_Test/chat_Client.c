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

// 채팅 프로그램: 클라이언트
int main()
{
	int fd1, fd2, n;
	char inmsg[MAXLINE];

	// 파이프 열기: 1번파이프 -> 읽기전용, 2번파이프 -> 쓰기전용 (서버와 반대로)
	fd1 = open("./chatfifo1", O_RDONLY);
	fd2 = open("./chatfifo2", O_WRONLY);

	// 예외처리
	if (fd1 == -1 || fd2 == -1)
	{
		perror("open");
		exit(3);
	}

	printf("|클라이언트 시작|\n");

	while (1)
	{
		n = read(fd1, inmsg, MAXLINE);

		printf("[서버] -> %s\n", inmsg);
		printf("[클라이언트]: ");

		// 키보드로부터 입력받은 값을 inmsg 배열에 저장
		fgets(inmsg, MAXLINE, stdin);

		// inmsg배열을 2번 파이프에 쓰기. write는 오류나면 -1, 성공적으로 쓰여지면 바이트수를 반환함.
		write(fd2, inmsg, strlen(inmsg) + 1);
	}
}