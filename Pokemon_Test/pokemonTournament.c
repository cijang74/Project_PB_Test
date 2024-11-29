#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "player.h"

//플레이어 입력 
int scan_playerID()
{
    int PID;
    printf("플레이어의 아이디를 입력하세요 : ");
    scanf("%d", &PID);

    return PID;
}

// 서버인지 묻는 함수
int ask_if_server() {
    char response;
    printf("당신이 서버입니까? (Y/N): ");
    scanf(" %c", &response);
    return (response == 'Y' || response == 'y');
}

int main()
{
    
    int shmid;
    key_t key;
    int pid;
    struct player* shmaddr;

    key = ftok("main", 1);

    // 키 값 출력
    printf("생성된 키 값: 0x%x\n", key);
    //서버인지 클라이언트인지 확인
    int isServer = ask_if_server();

    if (isServer)
    {
        //서버 역할 : 공유 메모리 생성 및 초기화
        // 새로운 공유 메모리 생성 및 초기화
        shmid = shmget(key, sizeof(struct player) * 4, IPC_CREAT | IPC_EXCL | 0644);
        if (shmid == -1) {
            perror("공유 메모리 생성 실패.");
            exit(1);
        }
        shmaddr = (struct player*)shmat(shmid, NULL, 0);
        if (shmaddr == (void*)-1) {
            perror("shmat 실패");
            exit(1);
        }
        printf("공유 메모리를 초기화합니다.\n");
        for (int i = 0; i < 4; i++) {
            shmaddr[i].isServerRunning = 0; // 서버 실행 상태 초기화
            shmaddr[i].flag = 0;
            shmaddr[i].isMyTurn = 0;
        }
        shmaddr[0].initailized = 1; //초기화 완료 플래그 설정

        printf("서버를 실행합니다.\n");
        pid = fork();
        if (pid == 0) {
            // 서버 실행
            execl("./server", "server", NULL);
            perror("서버 실행 실패");
            exit(1);
        }
        printf("서버가 성공적으로 실행되었습니다.");
    }
    else
    {
        shmid = shmget(key, sizeof(struct player) * 4, 0644); // 기존 공유 메모리 가져오기
        if (shmid == -1) {
            perror("공유 메모리 가져오기 실패. 서버가 실행 중인지 확인하세요.");
            exit(1);
        }
        //공유메모리 연결
        shmaddr = (struct player*)shmat(shmid, NULL, 0);
        if (shmaddr == (void*)-1) {
            perror("shmat 실패");
            exit(1);
        }
        printf("공유 메모리에 연결되었습니다.\n");
    }
    
        
    int playerID = scan_playerID();


    while (1) {
        if (shmaddr->flag != 1) {
            if (shmaddr->isServerRunning != 1) {
                printf("서버가 실행되지 않았습니다. 서버를 실행합니다.\n");
                shmaddr->isServerRunning = 1; // 서버 실행 중으로 업데이트

                
                printf("서버가 성공적으로 실행되었습니다.\n");
            }
            shmaddr->flag = 1;                  // 서버에 값 전달 중 표시
            shmaddr->playerID = playerID;       // 입력된 플레이어 ID 저장
            shmaddr->processID = getpid();      // 현재 프로세스 ID 저장
            shmaddr->isMyTurn = 0;              // 초기화
            break;
        }
    }

    printf("서버와 공유 메모리 설정 완료.\n");

    char playerIDStr[10];
	int status;
    // playerID를 문자열로 변환
    sprintf(playerIDStr, "%d", playerID);

    pid = fork();
    if (pid == 0)
    {
        printf("자식프로세스에서 main.c 실행");
		execl("./main", "main", playerIDStr, NULL);
	}
	else //pokemonTournament가 종료되면, 자식 프로세스에서 입력 안 됨
	{
		int status;
		wait(&status);
	}

}
