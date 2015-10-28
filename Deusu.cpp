#include "DxLib.h"
#include "deusu.h"
#include "Field.h"
#include "Key.h"

Deusu::Deusu(ISceneChanger* changer) : BaseStage(changer) {
}

void Deusu::Initialize(){
	field1 = LoadGraph("umi.png");
	field2 = LoadGraph("sougenn1.png");
	field3 = LoadGraph("miti.png");
	field4 = LoadGraph("tairu.png");
	field5 = LoadGraph("ki1.png");
	field6 = LoadGraph("yougann.png");
	field7 = LoadGraph("hatti.png");
	field8 = LoadGraph("hatti1.png");
	field9 = LoadGraph("burokku.png");
	field10 = LoadGraph("burokku1.png");
	field11 = LoadGraph("burokku2.png");
	Field hoge("deusu.csv",field1,field2,field3,field4,field5,field6,field7,field8,field9,field10,field11,51,50);//�ŏ��̃X�e�[�W
	field = hoge;
	int src[16];
	LoadDivGraph("mobu1.png",16,4,4,32,32,src);//��l���̑f��
	mobus = 7;
	mobu = new Mobu[mobus];
	Mobu hige("�킽���������A�������Ă���@�т傤����B��񂷂���т傤�@�Ɓ@�����炵����",src,15,35,true);
	Mobu hige1("�������@�������",src,27,19,true);
	Mobu hige2("�˂��@�łā@���邵���B",src,27,34,true);
	Mobu hige3("�݂Ȃ݂�@���������Ȃ����ȁIB���܂����@������������A���[���b�h�s�x����B��Ă����̂́A���̂킽�����BB���́@�ނ�́A�Ȃ��́@�т傤���񂫂��B�݂Ȃ��@���ł���BB���Ё@������������Ă���BB���܂����������Ă���i�t�l�o�̂���傭���@���@���傤�˂��B�݂Ȃ݂́@�����ɁB�Ƃ���Ă��邼�BB�݂�����@�܂��@���邪�悢���B",src,23,29,true);
	Mobu hige4("�����ށ@�́@������́AB�����̂݁A�邭�̂݁A�����̂݁@��B�����΂�ŁA���傤�������邱�Ƃ��@�ł���B",src,14,27,true);
	Mobu hogehoge("�т傤�����@�Ȃ����ɂ�B�����ށ@�́@�����肪�A�Ђ悤���B",src,38,27,true);
	Mobu buyer("buyer",src,23,18,true);
	/*Mobu higehige("buyer_arms",src,28,39,false);
	Mobu buyer_guard("buyer_guard",src,12,17,false);
	Mobu chemist("chemist",src,22,20,false);*/
	mobu[0] = hige;
	mobu[1] = hige1;
	mobu[2] = hige2;
	mobu[3] = hige3;
	mobu[4] = hige4;
	mobu[5] = hogehoge;
	mobu[6] = buyer;
	/*mobu[7] = hige2;
	mobu[8] = hige3;
	mobu[9] = hige4;*/
}

void Deusu::Update(Player player,bool menumode,bool talk,bool tele){
	if(player.getPlayerx() < 10  || player.getPlayery() < 10 ||player.getPlayerx() >=40  || player.getPlayery() >= 41){//���̊O�ɏo���猳�ɖ߂�
		mSceneChanger->ChangeScene(eScene_StartStage);//�V�[�������j���[�ɕύX
	}
	extern bool move;
	field.UpDate(player,&move,menumode);
	for(i = 0;i < mobus;i++){
		mobu[i].Update1(player.getPlayerx(),player.getPlayery(),player.getplayervec(),field.getnoise(mobu[i].getnextx(),mobu[i].getnexty()),menumode,talk);
	}
	field.moveplayerreset();
	for(i = 0;i < mobus;i++){
		field.getcharpoint(mobu[i].getx(),mobu[i].gety(),player.getPlayerx(),player.getPlayery());
	}
}
void Deusu::Update(){
}
//�`��
void Deusu::Draw(int playerx,int playery){
	field.Drow(playerx,playery);
	for(i = 0;i < mobus;i++){
		mobu[i].Draw1(field.getmovex(),field.getmovey());
	}
}

//�u���b�N�Ԃ̈ړ��̍��W��n���֐�
int Deusu::Fieldmovex(){
	return field.getmovex();
}
int Deusu::Fieldmovey(){
	return field.getmovey();
}

//�v���C���[�̏����n�_��`����֐�
int* Deusu::PlayerPointDef(){
	playerPointDef[0] = 19;
	playerPointDef[1] = 11;
	playerPointDef[2] = 8;
	return playerPointDef;
}

//�Z���t���擾����֐�
std::string Deusu::getWords(int playerx,int playery,int playervec){
	extern std::string BANPEI;
	switch(playervec){
	case 0:
		for(i = 0;i < mobus;i++){
			if(playerx == mobu[i].getx() && playery - 1 == mobu[i].gety()){
				return mobu[i].getWords();
			}

		}
	case 4:
		for(i = 0;i < mobus;i++){
			if(playerx - 1 == mobu[i].getx() && playery == mobu[i].gety()){
				return mobu[i].getWords();
			}

		}
	case 8:
		for(i = 0;i < mobus;i++){
			if(playerx == mobu[i].getx() && playery + 1 == mobu[i].gety()){
				return mobu[i].getWords();
			}

		}
	case 12:
		for(i = 0;i < mobus;i++){
			if(playerx + 1 == mobu[i].getx() && playery == mobu[i].gety()){
				return mobu[i].getWords();
			}
		}
	}
	return "hogehoge";
}

//�퓬�ɓ��������ƒm�点��֐�
bool Deusu::GoBattle(int playerx,int playery){
	return false;
}

void Deusu::Finalize(){
	delete [] mobu;
	field.Finalize();
}