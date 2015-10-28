#ifndef __MENU_H_INCLUDED__
#define __MENU_H_INCLUDED__

#include "DxLib.h"
#include "Task.h"
#include "Player.h"
#include <string>
#include <regex>
#include <vector>
#include "Item.h"


class Menu:public Task{
private:
	int i,j,k,l;
	int x,y;
	bool menumode;
	bool write;
	bool talk;
	bool status;
	int src1,src2,src3,src4,src5,src6,src7,src8,src9,src10,src11,src12;
	int white;
	char* word;
	std::string words;
	//�񕜂�����Ƃ��ɏ������񂷕ϐ�
	int recovery;
	//�񕜂̎��̃J�[�\���̍��W
	int cursor;
	//����������Ƃ��̃t���O
	int rebirth;
	//��܎t�̏������񂷕ϐ�
	int chem;
	//�����������鎞�̉�b�̏�Ԃ��񂷕ϐ�
	int shopping;
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
	int arm;
	int guard;
	int gold;
	std::string name;
	int pk;
	int jump;
	int telepathy;
	int shield;
	//���̃��x���܂łɕK�v�Ȍo���l
	int nextPoint;
	//��b���ɉ��y�[�W������ϐ�
	bool newLine;
	//��b�̏I����`����ϐ�
	bool talkEnd;
	//�J�[�\���̂������Ă���v���C���[�������ϐ�
	int  cursortarget;
	//�@���퉮�Ŕ����Ă镐�������z��
	int* arms;
	std::string buyer_arms_words;
	//�v���C���[�̃p�[�e�B�[������z��
	Player* party;
	//��b���Ă����Ƃ��c���ϐ�
	bool talknow;
	//���݂̂��̎悷�郂�[�h
	bool gathermode;
	//���݂̂��̎�o�������ǂ���
	bool gatherget;
	//���݂̖̂��O
	std::string seed_name;
	//���݂̂��̎悷��E�B���h�E���񂷕ϐ�
	int gather;
	//��������\�����邽�߂̔z��
	std::vector<item> item_list;
	//�������\�����[�h
	bool itemmode;
	//���\�����邽�߂̔z��
	std::vector<item> drug_list;
	//��\�����[�h
	bool drugmode;
	//�A�C�e���̃E�B���h�E���񂷕ϐ�
	int item_w;
	//�������X�g
	std::vector<std::string> chem_list;
	//�o������̂Ȃ܂�
	std::string drug_name;
	bool trash;
	int BANPEI;
	std::vector<item>::iterator it;
public:
	Menu();
	void Initialize() override;
	void Initialize(int* ability,std::string name);    //�������������I�[�o�[���C�h�B
    void Finalize() override ;        //�I���������I�[�o�[���C�h�B
    void Update() override;        //�X�V�������I�[�o�[���C�h�B
	void Update(std::string mobuwords,int count,int* ability,Player* player,int playercount,int nowstage,int nowplayer);
    void Draw() override;            //�`�揈�����I�[�o�[���C�h�B
	bool getMenu();
	bool gettalk();
};


#endif