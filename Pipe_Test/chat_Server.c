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

// 채팅 프로그램: 서버(보통 파이프를 만드는 프로세스가 서버라 카드라.)
int main()
{
	int fd1, fd2, n;
	char msg[MAXLINE];

	// 1번 파이프 생성
	if (mkfifo("./chatfifo1", 0666) == -1)
	{
		// 예외처리
		perror("mkfifo");
		exit(1);
	}

	// 2번 파이프 생성
	if (mkfifo("./chatfifo2", 0666) == -1)
	{
		// 예외처리
		perror("mkfifo");
		exit(2);
	}

	// 파이프 열기: 1번파이프 -> 쓰기전용, 2번파이프 -> 읽기전용
	fd1 = open("./chatfifo1", O_WRONLY);
	fd2 = open("./chatfifo2", O_RDONLY);

	// 예외처리
	if (fd1 == -1 || fd2 == -1)
	{
		perror("open");
		exit(3);
	}

	printf("|서버 시작|\n");

	while (1)
	{
		printf("[서버]: ");

		// 키보드로부터 입력받은 값을 msg 배열에 저장
		fgets(msg, MAXLINE, stdin);

		// msg배열을 1번 파이프에 쓰기. write는 오류나면 -1, 성공적으로 쓰여지면 바이트수를 반환함.
		n = write(fd1, msg, strlen(msg) + 1);

		// 예외처리
		if (n == -1)
		{
			perror("write");
		}

		// 읽기 파이프로부터 클라이언트가 입력한 값 불러오기
		n = read(fd2, msg, MAXLINE);
		printf("[클라이언트] -> %s\n", msg);
	}
}