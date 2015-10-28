#ifndef __BATTLE_H_INCLUDED__
#define __BATTLE_H_INCLUDED__

#include "Enemy.h"
#include <string>
#include <vector>
#include "Player.h"

class Battle{
private:
	int src,src1,src2,src3,src4,src5,src6,src7,src8,src9,src10,src11;
	int* hit;
	int white;
	int enemycount;
	int i,j;
	int* p_src;
	int count;
	int window;
	int cursor,cursor1;
	int damage;
	int playertarget;
	int enemytarget;
	int playercount;
	int BANPEI;
	int BANPEI1;
	int use;
	int power;
	int mp;
	Player* party;
	std::string playeraction;
	std::string name;
	Enemy* enemy;
	Enemy* encountenemy;
	bool encount;
	bool draw;
	bool battle;
	int point;
	int gold;
	bool dead;
	bool guard;
	bool* esp;
	bool attack_end;
	int nowplayer;
	int damaged_player;
	std::string error_mesage;
	bool power_select;
	bool dead_end;
	//�v���C���[�̃X�e�[�^�X
	int hit_p;
	int maxhit;
	int saiko;
	int maxsaiko;
	int speed;
	int jukurenndo;
	int keikenti;
	int level;
	int state;
	int defense;
	int arm;
	int guard_p;
	int gold_p;
	int pk;
	int jump;
	int telepathy;
	int shield;
	int nextPoint;
	bool tele;
	int mem;
	std::vector<int> p_list;
	bool include(int i);
	int sdef[4];
	int def[4];
public:
	void Initialize();    //�������������I�[�o�[���C�h�B
    void Finalize();        //�I���������I�[�o�[���C�h�B
	void Update(Player * player,int nowStage,int count,int member);        //�X�V�������I�[�o�[���C�h�B
    void Draw();            //�`�揈�����I�[�o�[���C�h�B
	//�퓬�I����m�点��֐�
	bool EndBattle();
	//���S��m�点��֐�
	bool getDead();
	bool getTele();
};

#endif