#include "DxLib.h"
#include "StartStage.h"
#include "StageMgr.h"
#include "Mamusu.h"
#include "deusu.h"
#include <string>

StageMgr::StageMgr() : 
    mNextScene(eScene_None) //���̃V�[���Ǘ��ϐ�
{
    mScene = (BaseStage*) new StartStage(this);
}

//������
void StageMgr::Initialize(){
    mScene->Initialize();
	nowStage = 0;
}

//�I������
void StageMgr::Finalize(){
    mScene->Finalize();
}

//�X�V
void StageMgr::Update(Player player,bool menumode,bool talk,bool tele){
	extern bool change;
    if(mNextScene != eScene_None){    //���̃V�[�����Z�b�g����Ă�����
        mScene->Finalize();//���݂̃V�[���̏I�����������s
        delete mScene;
        switch(mNextScene){       //�V�[���ɂ���ď����𕪊�
		case eScene_StartStage:
            mScene = (BaseStage*) new StartStage(this);
			change = true;
			nowStage = 0;
            break;
		case eScene_Mamusu:
            mScene = (BaseStage*) new Mamusu(this);
			change = true;
			nowStage = 1;
            break;
		case eScene_Deusu:
            mScene = (BaseStage*) new Deusu(this);
			change = true;
			nowStage = 2;
            break;
       }
        mNextScene = eScene_None;    //���̃V�[�������N���A
        mScene->Initialize();    //�V�[����������
    }

    mScene->Update(player,menumode,talk,tele); //�V�[���̍X�V
}
void StageMgr::Update(){
}

//�`��
void StageMgr::Draw(int playerx,int playery){
    mScene->Draw(playerx,playery); //�V�[���̕`��
}
void StageMgr::Draw(){
}

// ���� nextScene �ɃV�[����ύX����
void StageMgr::ChangeScene(eScene NextScene){
    mNextScene = NextScene;    //���̃V�[�����Z�b�g����
}

//�u���b�N�Ԃ̈ړ����̍��W��n���ϐ�
int StageMgr::Fieldmovex(){
	return mScene->Fieldmovex();
}
int StageMgr::Fieldmovey(){
	return mScene->Fieldmovey();
}

//Field����󂯎�����v���C���[�̏����n�_��n���֐�
int* StageMgr::PlayerPointDef(){
	return mScene->PlayerPointDef();
}

//Field���烂�u�L�����̃Z���t���Ƃ��Ă���B���u�L�������w�肵���ꏊ�ɂ��Ȃ����null��Ԃ�
std::string StageMgr::getWords(int playerx,int playery,int playervec){
	return mScene->getWords(playerx,playery,playervec);
}

//�퓬�ɓ��邱�Ƃ�`����֐�
bool StageMgr::GoBattle(int playerx,int playery){
	return mScene->GoBattle(playerx,playery);
}

int StageMgr::getNowStage(){
	return nowStage;
}