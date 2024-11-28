#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main()
{
    int shmid;
    key_t key;
    char* shmaddr; // 공유 메모리 저장 공간

    // 키값(키 정보) 설정
    key = ftok("Key_file", 74);

    // 공유메모리 생성
    shmid = shmget(key, 1024, 0);

    // 예외처리
    if (shmid == -1)
    {
        perror("shmget");
        exit(1);
    }

    printf("shmid: %d\n", shmid);

    // 공유메모리를 해당 프로세스에 부착
    shmaddr = (char*)shmat(shmid, NULL, 0);

    // 공유메모리에 삽입되어있는 "hello shared memory" 문자열 출력
    printf("%s\n", shmaddr);

    return 0;
}