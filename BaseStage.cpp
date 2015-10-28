#include "BaseStage.h"
#include "DxLib.h"
#include <string>

//������
BaseStage::BaseStage(ISceneChanger* changer) : 
    mImageHandle(0) {
    mSceneChanger = changer;
}

//�I������
void BaseStage::Finalize(){
    DeleteGraph(mImageHandle);
}

//�X�V
void BaseStage::Update(Player player,bool menumode,bool talk,bool tele){
}

//�`��
void BaseStage::Draw(){
    DrawGraph(0,0,mImageHandle,FALSE);
}
void BaseStage::Draw(int playerx,int playery){
}

//�u���b�N�Ԃ̈ړ��̍��W��`����֐�
int BaseStage::Fieldmovex(){
	return 0;
}
int BaseStage::Fieldmovey(){
	return 0;
}

//�v���C���[�̏����n�_��`����֐�
int* BaseStage::PlayerPointDef(){
	return playerPointDef;
}

//���u�L�����̃Z���t���擾����֐�
std::string BaseStage::getWords(int playerx,int playery,int playervec){
	return "";
}

//�퓬�ɂ͂��������Ƃ�`����֐�
bool BaseStage::GoBattle(int playerx,int playery){
	return false;
}
