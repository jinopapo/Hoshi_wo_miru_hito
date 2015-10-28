#include "DxLib.h"
#include "StartStage.h"
#include "Field.h"
#include "Key.h"
#include <string>

StartStage::StartStage(ISceneChanger* changer) : BaseStage(changer) {
}

void StartStage::Initialize(){
	field1 = LoadGraph("umi1.png");
	field2 = LoadGraph("ki1.png");
	field3 = LoadGraph("sougenn1.png");
	field4 = LoadGraph("tuti1.png");
	field5 = LoadGraph("mati.png");
	field6 = LoadGraph("hatti.png");
	field7 = LoadGraph("miti1.png");
	field8 = LoadGraph("yougann.png");
	field9 = LoadGraph("umiaka.png");
	field10 = LoadGraph("burokku2.png");
	field11 = LoadGraph("yougann.png");
	Field hoge("field1.csv",field1,field2,field3,field4,field5,field6,field7,field8,field9,field10,field11,76,59);//�ŏ��̃X�e�[�W
	field = hoge;
	count = 0;
}

void StartStage::Update(Player player,bool menumode,bool talk,bool tele){
	if(player.getPlayerx() == 14 && player.getPlayery() == 29){//�܂ނ����̍��W�ɗ�����
		mSceneChanger->ChangeScene(eScene_Mamusu);//�V�[�������j���[�ɕύX
	}else if(player.getPlayerx() == 18 && player.getPlayery() == 14){
		mSceneChanger->ChangeScene(eScene_Deusu);
	}
	if(tele){
		mSceneChanger->ChangeScene(eScene_StartStage);
	}
	extern bool move;
	field.UpDate(player,&move,menumode);
	if(count == 60){
		count = 0;
	}
	count++;
}
void StartStage::Update(){
}

//�`��
void StartStage::Draw(int playerx,int playery){
	field.Drow(playerx,playery);
}

//�u���b�N�ړ��̍��W��`����֐�
int StartStage::Fieldmovex(){
	return field.getmovex();
}
int StartStage::Fieldmovey(){
	return field.getmovey();
}

//�v���C���[�̏����n�_��`����֐�
int* StartStage::PlayerPointDef(){
	playerPointDef[0] = 15;
	playerPointDef[1] = 29;
	playerPointDef[2] = 8;
	return playerPointDef;
}

//�Z���t���擾����֐�
std::string StartStage::getWords(int playerx,int playery,int playervec){
	extern std::string BANPEI;
	return "hogehoge";
}

//�퓬�ɓ��������Ƃ�`����֐�
bool StartStage::GoBattle(int playerx,int playery){
	extern int cell;
	extern bool debbattle;
	if(playerx == 14 && playery == 29 ){//�܂ނ����̍��W�ɗ�����
		return false;
	}
	else if((field.getmovex() == cell || field.getmovey() == cell) && field.getjampcell() == 0
		&& debbattle){
		if(count % 6 == 0){
			return true;
		}
		else{
			return false;
		}
	}
	else{
		return false;
	}
}

void StartStage::Finalize(){
	field.Finalize();
}