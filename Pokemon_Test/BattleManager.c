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

// 두 플레이어 간의 상호작용을 도와주는 배틀 메니저. (사실상 서버 역할임)
int main()
{
	int fd1, fd2, fd3, fd4;
	int pid1, pid2, status;
	int child = 0;
	int who_am_i = 0;
	char who_am_i_str[MAXLINE];
	char message[MAXLINE];
	char buffer[MAXLINE];

	//// 1번 파이프 생성
	//if (mkfifo("./[p1]who_am_i_fifo1", 0666) == -1)
	//{
	//	// 예외처리
	//	perror("mkfifo");
	//	//exit(1);
	//}

	//// 2번 파이프 생성
	//if (mkfifo("./[p1]who_am_i_fifo2", 0666) == -1)
	//{
	//	// 예외처리
	//	perror("mkfifo");
	//	//exit(2);
	//} 

	//// 3번 파이프 생성
	//if (mkfifo("./[p2]who_am_i_fifo3", 0666) == -1)
	//{
	//	// 예외처리
	//	perror("mkfifo");
	//	//exit(1);
	//}

	//// 4번 파이프 생성
	//if (mkfifo("./[p2]who_am_i_fifo4", 0666) == -1)
	//{
	//	// 예외처리
	//	perror("mkfifo");
	//	//exit(2);
	//}

	//// 파이프 열기: 1번파이프 -> 쓰기전용, 2번파이프 -> 읽기전용
	//fd1 = open("./[p1]who_am_i_fifo1", O_WRONLY);
	//fd2 = open("./[p1]who_am_i_fifo2", O_RDONLY);
	//fd3 = open("./[p2]who_am_i_fifo3", O_WRONLY);
	//fd4 = open("./[p2]who_am_i_fifo4", O_RDONLY);

	//// 예외처리
	//if (fd1 == -1 || fd2 == -1)
	//{
	//	perror("open");
	//	exit(3);
	//}

	//if (fd3 == -1 || fd4 == -1)
	//{
	//	perror("open");
	//	exit(4);
	//}

	printf("[Battle Manager]: |서버 구동 시작...|\n");
	printf("[Battle Manager]: 당신의 플레이어 숫자는? 1 or 2?: ");

	// 사용자 입력 받기
	fgets(buffer, sizeof(buffer), stdin);
	sscanf(buffer, "%d", &who_am_i);

	if (who_am_i == 1)
	{
		sleep(1);
		if ((pid1 = fork()) == 0)
		{
			printf("\n[Battle Manager]: 플레이어 1 배틀 프로세스 시작..\n");
			//sprintf(message, "%d", who_am_i);

			//// 예외처리
			//if (write(fd1, message, strlen(message) + 1) == -1)
			//{
			//	perror("write");
			//	exit(4);
			//}

			//fsync(fd1);
			//close(fd1);

			snprintf(who_am_i_str, sizeof(who_am_i_str), "%d", who_am_i);
			execl("./Battle_Client_UI", "./Battle_Client_UI", who_am_i_str, NULL);
			perror("execl");
			exit(5);
		}
	}

	if (who_am_i == 2)
	{
		sleep(1);
		if ((pid2 = fork()) == 0)
		{
			printf("\n[Battle Manager]: 플레이어 2 배틀 프로세스 시작..\n");
			//sprintf(message, "%d", who_am_i);

			//// 예외처리
			//if (write(fd3, message, strlen(message) + 1) == -1)
			//{
			//	perror("write");
			//	exit(4);
			//}

			//fsync(fd3);
			//close(fd1);

			snprintf(who_am_i_str, sizeof(who_am_i_str), "%d", who_am_i);
			execl("./Battle_Client_UI", "./Battle_Client_UI", who_am_i_str, NULL);
			perror("execl");
			exit(5);
		}
	}

	child = wait(&status);

	//read(fd2, who_am_i, sizeof(int));
	//prinf("\n승리자: %d\n", who_am_i);
	//prinf("프로그램 종료 하시겠습니까?");

	//scanf("%d", &who_am_i);
	//return 0;
}