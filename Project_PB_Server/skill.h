#define START_ATTACKSKILL_ID 0
#define START_BUFFSKILL_ID 100
#define START_DEBUFFSKILL_ID 200
#define START_HEALSKILL_ID 300

#define ATTACK 1
#define DEFENSE 2
#define SPEED 4         //2개 이상의 버프(디버프)를 조합하는 경우 { if buff_type == 6  |  DEFENSE + SPEED } 

#define ATTACKSKILL 0
#define BUFFSKILL 1
#define DEBUFFSKILL 2
#define HEALSKILL 3


// 스킬 종류별로 구조체 만듦
struct attackSkill
{
    int sid;
    char skill_name[50];
    int skill_damage;
    char property[50];
};

struct buffSkill
{
    int sid;
    char skill_name[50];
    int buff_type;
    
    int attack_up_value;
    int defense_up_value;
    int speed_up_value;
};

struct debuffSkill
{
    int sid;
    char skill_name[50];
    int debuff_type;

    int attack_down_value;
    int defense_down_value;
    int speed_down_value;
};

struct healSkill
{
    int sid;
    char skill_name[50];
    int heal_value;
};