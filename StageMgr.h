#ifndef __STAGE_H_INCLUDED__
#define __STAGE_H_INCLUDED__

#pragma once

#include "BaseStage.h"
#include "ISceneChanger.h"
#include "Player.h"
#include <string>

class StageMgr:public ISceneChanger, Task{

private:
    BaseStage* mScene    ;    //�V�[���Ǘ��ϐ�
    eScene mNextScene;    //���̃V�[���Ǘ��ϐ�
	int nowStage;
public :
	StageMgr();
    void Initialize() override;    //�������������I�[�o�[���C�h�B
    void Finalize() override;        //�I���������I�[�o�[���C�h�B
    void Update() override;        //�X�V�������I�[�o�[���C�h�B
	void Update(Player player,bool menumode,bool talk,bool tele);
    void Draw() override;            //�`�揈�����I�[�o�[���C�h�B
	void Draw(int playerx,int playery);
	int Fieldmovex();
	int Fieldmovey();
	std::string getWords(int playerx,int playery,int playervec);
	bool GoBattle(int playerx,int playery);
	// ���� nextScene �ɃV�[����ύX����
    void ChangeScene(eScene NextScene) override;
	//�X�e�[�W���ς�������ɏ����l��n���l�̊֐�
	int* PlayerPointDef();
	//���݂̃X�e�[�W��`����֐�
	int getNowStage();
};

#endif