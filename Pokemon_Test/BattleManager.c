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
int main(int argc, char*argv[])
{
	//int fd1, fd2, fd3, fd4;
	//char fd1_str[MAXLINE];
	//char fd2_str[MAXLINE];
	//char fd3_str[MAXLINE];
	//char fd4_str[MAXLINE];

	int pid1, pid2, status;
	int child = 0;
	int who_am_i = 0;

	char who_am_i_str[MAXLINE];
	char message[MAXLINE];
	char buffer[MAXLINE];

	int shmid, shmid2;
	key_t key, key2;
	int* shmp; // p1 공유 메모리 저장 공간
	int* shmp2; // p2 공유 메모리 저장 공간

	// 키값(키 정보) 설정
	key = ftok("Player_file", 75);
	key2 = ftok("Player2_file", 76);

	// 공유메모리 접근
	shmid = shmget(key, 10 * sizeof(int), 0); // 플레이어 1
	shmid2 = shmget(key2, 10 * sizeof(int), 0); // 플레이어 2

	// 예외처리
	if (shmid == -1)
	{
		perror("shmget");
		exit(1);
	}

	// 공유메모리를 해당 프로세스에 부착
	shmp = (int*)shmat(shmid, NULL, 0); // 플레이어 초기 값: shmp[0]: hp=10, shmp[1]: speed=5, shmp[2]: attack=3, shmp[3]: is_dead=0
	shmp2 = (int*)shmat(shmid2, NULL, 0); // 상대 포켓몬 값: shmp[0]: hp=10, shmp[1]: speed=5, shmp[2]: attack=3, shmp[3]: is_dead=0

	shmp[5] = 0;
	shmp2[5] = 0;

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

	printf("\n결과2: shm[5]: %d, shm2[5]: %d\n", shmp[5], shmp2[5]);

	printf("[Battle Manager]: |서버 구동 시작...|\n");
	printf("[Battle Manager]: 당신의 플레이어 숫자는? 1 or 2?: ");

	// 사용자 입력 받기
	fgets(buffer, sizeof(buffer), stdin);
	sscanf(buffer, "%d", &who_am_i);

	if (who_am_i == 1 && shmp[5] != 1) // shmp[5]: isbattleEnd
	{
		sleep(1);
		if ((pid1 = fork()) == 0)
		{
			printf("\n[Battle Manager]: 플레이어 1 배틀 프로세스 시작..\n");

			//// 파이프 열기: 1번파이프 -> 쓰기전용, 2번파이프 -> 읽기전용
			//fd1 = open("./[p1]who_am_i_fifo1", O_WRONLY);
			//// fd2 = open("./[p1]who_am_i_fifo2", O_RDONLY);

			//// 예외처리
			//if (fd1 == -1 || fd2 == -1)
			//{
			//	perror("open");
			//	exit(3);
			//}

			//// fd1파이프에 who_am_i 값 전달 (구조체 자체 전달도 가능)
			//if(write(fd1, &who_am_i, sizeof(who_am_i) < 0))
			//{
			//	// 예외처리
			//	perror("write");
			//	close(fd1);
			//	exit(0);
			//}
			//// close(fd1);

			snprintf(who_am_i_str, sizeof(who_am_i_str), "%d", who_am_i);
			//snprintf(fd1_str, sizeof(fd1_str), "%d", fd1);

			execl("./Battle_Client_UI", "./Battle_Client_UI", who_am_i_str, NULL);
			perror("execl");
			exit(5);
		}
	}

	if (who_am_i == 2 && shmp2[5] != 1) // shmp[5]: isbattleEnd
	{
		sleep(1);
		if ((pid2 = fork()) == 0)
		{
			printf("\n[Battle Manager]: 플레이어 2 배틀 프로세스 시작..\n");

			//// 파이프 열기: 1번파이프 -> 쓰기전용, 2번파이프 -> 읽기전용
			//fd3 = open("./[p2]who_am_i_fifo3", O_WRONLY);
			//// fd4 = open("./[p2]who_am_i_fifo4", O_RDONLY);

			//// 예외처리
			//if (fd3 == -1 || fd4 == -1)
			//{
			//	perror("open");
			//	exit(4);
			//}

			//// fd1파이프에 who_am_i 값 전달 (구조체 자체 전달도 가능)
			//if (write(fd3, &who_am_i, sizeof(who_am_i) < 0))
			//{
			//	// 예외처리
			//	perror("write");
			//	close(fd3);
			//	exit(0);
			//}
			//// close(fd3);

			snprintf(who_am_i_str, sizeof(who_am_i_str), "%d", who_am_i);
			//snprintf(fd2_str, sizeof(fd2_str), "%d", fd2);

			execl("./Battle_Client_UI", "./Battle_Client_UI", who_am_i_str, NULL);
			perror("execl");
			exit(5);
		}
	}

	child = wait(&status);

	//if (shmp[5] == 1)
	//{
	//	fd2 = atoi(argv[1]);

	//	if (read(fd2, &who_am_i, sizeof(who_am_i) < 0))
	//	{
	//		// 예외처리
	//		perror("write");
	//		close(fd2);
	//		exit(0);
	//	}
	//	close(fd2);
	//}

	//else if (shmp2[5] == 1)
	//{
	//	fd4 = atoi(argv[1]);

	//	if (read(fd4, &who_am_i, sizeof(who_am_i) < 0))
	//	{
	//		// 예외처리
	//		perror("write");
	//		close(fd4);
	//		exit(0);
	//	}
	//	close(fd4);
	//}

	//printf("\n[Battle Manager]: ||결과: 승리자: %d ||\n", who_am_i);
	//printf("[Battle Manager]: 프로그램을 종료하시겠습니가?\n");
	//printf("[Battle Manager]: 예: 1, 아니요: ");

	//scanf("%d", &who_am_i);
	//printf("\n[Battle Manager]: 프로그램이 종료되었습니다.\n");
	//return 0;
}

void check_winnder(who_am_i)
{
	// 누가 이겼는지를 체크
}