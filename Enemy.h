#ifndef __ENEMY_H_INCLUDED__
#define __ENEMY_H_INCLUDED__

#include<string>

class Enemy{
private:
	int src;
	int maxhit;
	int hit;
	int defense;
	int attack;
	int point;
	std::string name;
	bool dead;
	int x,y;
	int gold;
	bool saiko;
	std::string attack_name;
	bool esc;
	int state;
	int race;
public:
	Enemy(int src,std::string,int e_point,int e_gold,int e_defense,int e_attack,int e_hit,bool e_saiko,int e_race); 
	Enemy();
	void* operator new(size_t size, void* buf);
	void operator delete(void* p, void* buf);
	void Initialize(int e_x,int e_y); //�������������I�[�o�[���C�h�B
    //void Finalize() override ;        //�I���������I�[�o�[���C�h�B
    void Update(int damage);        //�X�V�������I�[�o�[���C�h�B
    void Draw();            //�`�揈�����I�[�o�[���C�h�B
	int getDamage(int p_defense);
	int getHP();
	std::string getName();
	std::string getAttackName();
	bool getEsc();
	void becomeEsc();
	void Encount();
	bool getDead();
	int getPoint();
	int getGold();
	int getDefense();
	bool getSaiko();
	void setAttackName(std::string a_name);
	int getState();
	void becomeState(int error);
	int getRace();
};

#endif