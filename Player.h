#ifndef __PLAYER_H_INCLUDED__
#define __PLAYER_H_INCLUDED__

#include "DxLib.h"
#include "Task.h"
#include <string>
#include <vector>
#include "Item.h"


class Player:public Task{
private:
	//�v���C���[�̃u���b�N��̈ʒu
	int playerx;
	int playery;
	//�v���C���[�̉摜�̕ϐ�
	int src[16];
	int src1;
	int src2;
	int src3;
	//�v���C���[�̉摜��؂�ւ���ϐ�
	int srcSelect;
	int count;
	//���̃v���C���[���g�p�\�`����֐�
	bool mate;
	//�v���C���[�̃X�e�[�^�X
	int hit;
	int maxhit;
	int saiko;
	int maxsaiko;
	int speed;
	int jukurenndo;
	int keikenti;
	int level;
	int state;
	int defense;
	int arms;
	int guard;
	int gold;
	int pk;
	int jump;
	int shield;
	int telepathy;
	int nextPoint;
	std::string name;
	bool dead;
	bool esc;
	bool* esp;
	//�v���C���[�̃X�e�[�^�X������z��
	int* ability;
	//��
	std::vector<item> drug_list;
	//�A�C�e��
	std::vector<item> item_list;
	//��̂���
	std::vector<item> seed_list;
	int item_count;
	item geti;
	int i;
public:
	Player(int* handle,int hendle1,int hendle2,int hendle3,char* p_name,int p_hit,int p_saiko,int p_defense,int p_speed,int p_jukurendo);
	Player();
	bool UpDateMove(int movex,int movey);//�ړ��Ɋւ���X�V
	bool UpDateSrc(int up,int down,int right,int left,bool menumode);//�ړ����̃L�����̕\���Ɋւ���X�V
	//�v���C���[�̍��W��`����֐�
	int getPlayerx();
	int getPlayery();
	//�v���C���[�̌�����`����֐�
	int getplayervec();
	//�v���C���[�̉摜��n���֐�
	int getSrc();
	//�v���C���[�̂Ђ��Ƃ��v�Z����֐�
	void hitdamage(int damage);
	//�v���C���[�̂��������v�Z����֐�
	void useSaiko(int use);
	//�v���C���[�̌o���l���v�Z����֐�
	void levelup(int point);
	//�v���C���[�̂������v�Z����֐�
	void shopping(int gold);
	//�v���C���[�̕����ύX����֐�
	void setArms(int arm);
	//�v���C���[�̖h���ύX����֐�
	void setGuard(int guard_s);
	//�v���C���[�����ԂɂȂ��Ă���ǂ�����`����֐�
	bool getMate();
	void becameMate();
	//�v���C���[����Ԉُ�ɂ���֐�
	void becomeError(int error);
	//�v���C���[�̖��n���֐�
	std::vector<item> getDrugList();
	//����������ɉ�����֐�
	bool setDrug(std::string drug);
	//�v���C���[�̃A�C�e����n���֐�
	std::vector<item> getItemList();
	//�A�C�e�����������ɉ�����֐�
	bool setItem(std::string item_p);
	//������̌���n���֐�
	std::vector<item> getSeedList();
	//������̂��Ƃ��������ɉ�����֐�
	bool setSeed(std::string seed);
	//�X�e�[�^�X��`����֐�
	int gethit();
	int getmaxhit();
	int getsaiko();
	int getmaxsaiko();
	int getspeed();
	int getjukurenndo();
	int getkeikenti();
	int getlevel();
	int getstate();
	int getdefense();
	int getarms();
	int getguard();
	int getgold();
	int getjump();
	bool* getesp();
	int getpk();
	int getshield();
	int gettelepathy();
	int getNextPoint();
	bool getDead();
	bool getEsc();
	void becomeEsc();
	std::string getname();
	int* getability();
	void Initialize() override;    //�������������I�[�o�[���C�h�B
    void Finalize() override ;        //�I���������I�[�o�[���C�h�B
    void Update() override;        //�X�V�������I�[�o�[���C�h�B
	void Update(int* playerPointDef);
    void Draw() override;            //�`�揈�����I�[�o�[���C�h�B
};
#endif