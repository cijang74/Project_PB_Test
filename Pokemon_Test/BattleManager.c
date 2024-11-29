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

void Check_Loser(int who_am_i, int* shmp, int* shmp2, int* shmp3, int* shmp4);

// 두 플레이어 간의 상호작용을 도와주는 배틀 메니저. (사실상 서버 역할임)
int main(int argc, char*argv[]) // 플레이어 ID 넘겨 받을것.
{
	int pid1, pid2, pid3, pid4, status;
	int child = 0;
	int who_am_i = 0;

	char who_am_i_str[MAXLINE];
	char buffer[MAXLINE];

	int shmid, shmid2, shmid3, shmid4;
	key_t key, key2, key3, key4;
	int* shmp; // p1 공유 메모리 저장 공간
	int* shmp2; // p2 공유 메모리 저장 공간
	int* shmp3; // p3 공유 메모리 저장 공간
	int* shmp4; // p4 공유 메모리 저장 공간

	// 키값(키 정보) 설정
	key = ftok("Player_file", 75);
	key2 = ftok("Player2_file", 76);
	key3 = ftok("Player3_file", 77);
	key4 = ftok("Player4_file", 78);

	// 공유메모리 접근
	shmid = shmget(key, 10 * sizeof(int), 0); // 플레이어 1
	shmid2 = shmget(key2, 10 * sizeof(int), 0); // 플레이어 2
	shmid3 = shmget(key3, 10 * sizeof(int), 0); // 플레이어 3
	shmid4 = shmget(key4, 10 * sizeof(int), 0); // 플레이어 4

	// 예외처리
	if (shmid == -1)
	{
		perror("shmget");
		exit(1);
	}

	// 공유메모리를 해당 프로세스에 부착
	shmp = (int*)shmat(shmid, NULL, 0); // 플레이어 초기 값: shmp[0]: hp=10, shmp[1]: speed=5, shmp[2]: attack=3, shmp[3]: is_dead=0
	shmp2 = (int*)shmat(shmid2, NULL, 0); // 상대 포켓몬 값: shmp[0]: hp=10, shmp[1]: speed=5, shmp[2]: attack=3, shmp[3]: is_dead=0
	shmp3 = (int*)shmat(shmid3, NULL, 0); // 플레이어 초기 값: shmp[0]: hp=10, shmp[1]: speed=5, shmp[2]: attack=3, shmp[3]: is_dead=0
	shmp4 = (int*)shmat(shmid4, NULL, 0); // 상대 포켓몬 값: shmp[0]: hp=10, shmp[1]: speed=5, shmp[2]: attack=3, shmp[3]: is_dead=0

	printf("[Battle Manager]: |서버 구동 시작...|\n");
	printf("[Battle Manager]: 당신의 플레이어 숫자는? 1 or 2?: ");

	// 사용자 입력 받기 (나중에는 넘겨받은 PID 사용할것)
	fgets(buffer, sizeof(buffer), stdin);
	sscanf(buffer, "%d", &who_am_i);

	Check_Loser(who_am_i, shmp, shmp2, shmp3, shmp4);

	if (who_am_i == 1) // shmp[5]: isbattleEnd
	{
		sleep(1);
		if ((pid1 = fork()) == 0)
		{
			printf("\n[Battle Manager]: 플레이어 1 배틀 프로세스 시작..\n");

			snprintf(who_am_i_str, sizeof(who_am_i_str), "%d", who_am_i);

			execl("./Battle_Client_UI", "./Battle_Client_UI", who_am_i_str, NULL);
			perror("execl");
			exit(5);
		}
	}

	if (who_am_i == 2) // shmp[5]: isbattleEnd
	{
		sleep(1);
		if ((pid2 = fork()) == 0)
		{
			printf("\n[Battle Manager]: 플레이어 2 배틀 프로세스 시작..\n");

			snprintf(who_am_i_str, sizeof(who_am_i_str), "%d", who_am_i);

			execl("./Battle_Client_UI", "./Battle_Client_UI", who_am_i_str, NULL);
			perror("execl");
			exit(5);
		}
	}

	if (who_am_i == 3) // shmp[5]: isbattleEnd
	{
		sleep(1);
		if ((pid3 = fork()) == 0)
		{
			printf("\n[Battle Manager]: 플레이어 3 배틀 프로세스 시작..\n");

			snprintf(who_am_i_str, sizeof(who_am_i_str), "%d", who_am_i);

			execl("./Battle_Client_UI", "./Battle_Client_UI", who_am_i_str, NULL);
			perror("execl");
			exit(5);
		}
	}

	if (who_am_i == 4) // shmp[5]: isbattleEnd
	{
		sleep(1);
		if ((pid4 = fork()) == 0)
		{
			printf("\n[Battle Manager]: 플레이어 4 배틀 프로세스 시작..\n");

			snprintf(who_am_i_str, sizeof(who_am_i_str), "%d", who_am_i);

			execl("./Battle_Client_UI", "./Battle_Client_UI", who_am_i_str, NULL);
			perror("execl");
			exit(5);
		}
	}

	child = wait(&status);
	Check_Loser(who_am_i, shmp, shmp2, shmp3, shmp4);
}

void Check_Loser(int who_am_i, int* shmp, int* shmp2, int* shmp3, int* shmp4)
{
	if (who_am_i == 1 && shmp[3] == 1) //shmp[3]: is_dead
	{
		printf("\n당신은 패배하였다. (프로그램 종료)\n");
		exit(0);
	}

	if (who_am_i == 2 && shmp2[3] == 1) //shmp[3]: is_dead
	{
		printf("\n당신은 패배하였다. (프로그램 종료)\n");
		exit(0);
	}

	if (who_am_i == 3 && shmp3[3] == 1) //shmp[3]: is_dead
	{
		printf("\n당신은 패배하였다. (프로그램 종료)\n");
		exit(0);
	}

	if (who_am_i == 4 && shmp4[3] == 1) //shmp[3]: is_dead
	{
		printf("\n당신은 패배하였다. (프로그램 종료)\n");
		exit(0);
	}

	return;
}