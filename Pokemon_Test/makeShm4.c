#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>

// 구조체 공유메모리 만들기 귀찮아서 땜빵용으로 정수 배열 공유 메모리 만듦
int main()
{
    int shmid;
    key_t key;
    int* shmp; // 공유 메모리 저장 공간

    // 키값(키 정보) 설정
    // key = ftok("Player_file", 75);
    // key = ftok("Player2_file", 76);
    // key = ftok("Player3_file", 77);
    key = ftok("Player4_file", 78);

    // 공유메모리 생성 int배열 10개짜리
    shmid = shmget(key, 10 * sizeof(int), IPC_CREAT | 0644);

    // 예외처리
    if (shmid == -1)
    {
        perror("shmget");
        exit(1);
    }

    // 공유메모리를 해당 프로세스에 부착
    shmp = (int*)shmat(shmid, NULL, 0);

    // 공유메모리 주소를 통해 공유메모리에 값 넣기
    shmp[0] = 10; // 체력
    shmp[1] = 5; // 스피드
    shmp[2] = 3; // 공격력
    shmp[3] = 0; // 죽었는지 판단

    printf("shmid: %d\n", shmid);

    printf("체력: %d\n", shmp[0]);
    printf("스피드: %d\n", shmp[1]);
    printf("공격력: %d\n", shmp[2]);
    printf("죽었는가: %d\n", shmp[3]);

    return 0;
}