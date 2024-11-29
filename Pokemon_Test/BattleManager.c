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

#include "player.h"
#include "monster.h"

#define MAXLINE 256

void Check_Loser(int playerID, struct player* shmp);
int findPlayerIndexByID(struct player* shmp, int playerID);

// 두 플레이어 간의 상호작용을 도와주는 배틀 메니저. (사실상 서버 역할임)
int main(int argc, char*argv[]) // 플레이어 ID 넘겨 받을것.
{
	struct player* shmp; // 플레이어 공유 메모리 저장 공간

	int pid, pid2, pid3, pid4, status;
	int child = 0;

	int playerID = 0;
	int processID = 0;
	playerID = atoi(argv[1]); // 플레이어 아이디 ex(1, 281, 19, 22)

	char processID_str[MAXLINE];

	int shmid;
	key_t key;

	// 키값(키 정보) 설정
	key = ftok("main", 10597); 

	//공유 메모리 접근
	shmid = shmget(key, sizeof(struct player) * 4, 0); // 플레이어

	// 접근 예외처리
	if (shmid == -1) 
	{
		perror("공유 메모리 접근 실패.");
		exit(1);
	}

	// 해당 프로세스에 플레이어 공유 메모리 부착
	shmp = (int*)shmat(shmid, NULL, 0);
	processID = findPlayerIndexByID(shmp, playerID); // 생성할 때 순차적으로 부여되는 프로세스 아이디 (1, 2, 3, 4..)

	printf("[Battle Manager]: |서버 구동 시작...|\n");

	Check_Loser(processID, shmp);

	if (processID + 1 == 1) // who am i == 1
	{
		sleep(1);
		if ((pid = fork()) == 0)
		{
			printf("\n[Battle Manager]: 플레이어 %d 배틀 프로세스 시작..\n", processID + 1);

			// 플레이어 아이디를 Battle Client에 넘겨주기 위해 문자열로 만들기
			snprintf(processID_str, sizeof(processID_str), "%d", processID);

			// Battle Client 실행
			execl("./Battle_Client_UI", "./Battle_Client_UI", processID_str, NULL);
			perror("execl");
			exit(5);
		}
	}

	if (processID + 1 == 2) // who am i == 1
	{
		sleep(1);
		if ((pid2 = fork()) == 0)
		{
			printf("\n[Battle Manager]: 플레이어 %d 배틀 프로세스 시작..\n", processID + 1);

			// 플레이어 아이디를 Battle Client에 넘겨주기 위해 문자열로 만들기
			snprintf(processID_str, sizeof(processID_str), "%d", processID);

			// Battle Client 실행
			execl("./Battle_Client_UI", "./Battle_Client_UI", processID_str, NULL);
			perror("execl");
			exit(5);
		}
	}

	if (processID + 1 == 3) // who am i == 1
	{
		sleep(1);
		if ((pid3 = fork()) == 0)
		{
			printf("\n[Battle Manager]: 플레이어 %d 배틀 프로세스 시작..\n", processID + 1);

			// 플레이어 아이디를 Battle Client에 넘겨주기 위해 문자열로 만들기
			snprintf(processID_str, sizeof(processID_str), "%d", processID);

			// Battle Client 실행
			execl("./Battle_Client_UI", "./Battle_Client_UI", processID_str, NULL);
			perror("execl");
			exit(5);
		}
	}

	if (processID + 1 == 4) // who am i == 1
	{
		sleep(1);
		if ((pid4 = fork()) == 0)
		{
			printf("\n[Battle Manager]: 플레이어 %d 배틀 프로세스 시작..\n", processID + 1);

			// 플레이어 아이디를 Battle Client에 넘겨주기 위해 문자열로 만들기
			snprintf(processID_str, sizeof(processID_str), "%d", processID);

			// Battle Client 실행
			execl("./Battle_Client_UI", "./Battle_Client_UI", processID_str, NULL);
			perror("execl");
			exit(5);
		}
	}

	child = wait(&status);
	Check_Loser(processID, shmp);
}

void Check_Loser(int processID, struct player* shmp)
{
	// processID: who am i | shmp[~]: is_dead
	if (processID == 1 && shmp[processID].is_dead == 1) //shmp[3]: is_dead
	{
		printf("\n당신은 패배하였다. (프로그램 종료)\n");
		exit(0);
	}
	return;
}

// 플레이어 ID를 사용해 프로세스 ID를 탐색 (플레이어가 생성된 순서대로 부여되는 번호)
int findPlayerIndexByID(struct player* shmp, int playerID)
{
	for (int i = 0; i < 4; i++)
	{ // 4명 기준
		if (shmp[i].playerID == playerID)
		{
			return i; // 해당 플레이어의 인덱스 반환
		}
	}
	perror("noFoundPID");
	exit(1);
}