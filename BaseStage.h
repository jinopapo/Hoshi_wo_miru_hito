#ifndef __BASESTAGE_H_INCLUDED__
#define __BASESTAGE_H_INCLUDED__

#pragma once

#include "Task.h"
#include "ISceneChanger.h"
#include "Player.h"
#include <string>

//�V�[���̊��N���X�B
class BaseStage : public Task {

protected:
    int mImageHandle;               //�摜�n���h���i�[�p�ϐ�
    ISceneChanger* mSceneChanger;    //�N���X���L���ɃV�[���؂�ւ���`����C���^�[�t�F�C�X
	int playerPointDef[3]; //�v���C���[�̏����n�_������z��

public :
    BaseStage(ISceneChanger* changer);
    virtual ~BaseStage(){}
    virtual void Initialize() override {}    //�������������I�[�o�[���C�h�B
    virtual void Finalize() override ;        //�I���������I�[�o�[���C�h�B
    virtual void Update() override {}        //�X�V�������I�[�o�[���C�h�B
	virtual void Update(Player player,bool menumode,bool talk,bool tele);
    virtual void Draw() override ;            //�`�揈�����I�[�o�[���C�h�B
	virtual void Draw(int palyerx,int playery);
	virtual int Fieldmovex();//�u���b�N�ړ��̍��W��`����֐�
	virtual int Fieldmovey();
	virtual int* PlayerPointDef();//�v���C���[�̏����n�_��`����֐�
	virtual std::string getWords(int playerx,int playery,int playervec);
	virtual bool GoBattle(int playerx,int playery);
};

#endif

