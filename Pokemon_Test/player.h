// 플레이어 정보 구조체 

#ifndef PLAYER_H
#define PLAYER_H

#include "monster.h"

struct player
{
    int flag;       //상태 플래그 (데이터 저장 여부)
    int playerID;
    int processID;
    int isServerRunning;    //서버 실행 여부
    int isMyTurn;
    int initailized;        //초기화 완료 여부
    struct monster selectedMonster;
};

#endif