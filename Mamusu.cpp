#include "DxLib.h"
#include "Mamusu.h"
#include "Field.h"
#include "Key.h"

Mamusu::Mamusu(ISceneChanger* changer) : BaseStage(changer) {
}

void Mamusu::Initialize(){
	field1 = LoadGraph("umi.png");
	field2 = LoadGraph("ki1.png");
	field3 = LoadGraph("sougenn1.png");
	field4 = LoadGraph("miti.png");
	field5 = LoadGraph("tairu.png");
	field6 = LoadGraph("yougann.png");
	field7 = LoadGraph("hatti.png");
	field8 = LoadGraph("hatti1.png");
	field9 = LoadGraph("burokku.png");
	field10 = LoadGraph("burokku1.png");
	field11 = LoadGraph("burokku2.png");
	Field hoge("mamusu.csv",field1,field2,field3,field4,field5,field6,field7,field8,field9,field10,field11,50,51);//�ŏ��̃X�e�[�W
	field = hoge;
	int src[16];
	LoadDivGraph("mobu1.png",16,4,4,32,32,src);//��l���̑f��
	mobus = 10;
	mobu = new Mobu[mobus];
	Mobu hige("�܂ނ��̂ނ�ցA�悤�����BB�����Ɂ@����΁A���񂺂�ł��B",src,23,12,true);
	Mobu hige1("�����ЂƂ̂ނ�@�ł����@�́@�݂�Ȃ́AB�Ȃ��́@�т傤���ŁA�@������Ă���",src,24,11,true);
	Mobu hige2("�ނ�́@���������@�݂��Ȃ��̂́A�݂�Ȃ�B��������@���킹�ā@���������AB�����Ă��邩��ł�",src,27,38,true);
	Mobu hige3("��΂���́@������́AB��ނ̂݁@�����̂݁@�邭�݂̂́@�����΂��B���傤��������Ɓ@�ł���B",src,16,26,true);
	Mobu hige4("���̂����́A�S�ɂ�@������ā@�����Ȃ��ƁAB�����񂾁BB������@���ǂ��Ă������̂��A���Ȃ��B",src,39,37,true);
	Mobu hogehoge("nurse",src,20,38,true);
	Mobu rebirth("rebirth",src,13,34,true);
	Mobu higehige("buyer_arms",src,12,12,false);
	Mobu buyer_guard("buyer_guard",src,12,17,false);
	Mobu chemist("chemist",src,22,20,false);
	mobu[0] = hige;
	mobu[1] = hogehoge;
	mobu[2] = higehige;
	mobu[3] = buyer_guard;
	mobu[4] = chemist;
	mobu[5] = rebirth;
	mobu[6] = hige1;
	mobu[7] = hige2;
	mobu[8] = hige3;
	mobu[9] = hige4;
}

void Mamusu::Update(Player player,bool menumode,bool talk,bool tele){
	if(player.getPlayerx() <10  || player.getPlayery() < 10 ||player.getPlayerx() >=41  || player.getPlayery() >= 40){//���̊O�ɏo���猳�ɖ߂�
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
void Mamusu::Update(){
}
//�`��
void Mamusu::Draw(int playerx,int playery){
	field.Drow(playerx,playery);
	for(i = 0;i < mobus;i++){
		mobu[i].Draw1(field.getmovex(),field.getmovey());
	}
}

//�u���b�N�Ԃ̈ړ��̍��W��n���֐�
int Mamusu::Fieldmovex(){
	return field.getmovex();
}
int Mamusu::Fieldmovey(){
	return field.getmovey();
}

//�v���C���[�̏����n�_��`����֐�
int* Mamusu::PlayerPointDef(){
	playerPointDef[0] = 23;
	playerPointDef[1] = 10;
	playerPointDef[2] = 8;
	return playerPointDef;
}

//�Z���t���擾����֐�
std::string Mamusu::getWords(int playerx,int playery,int playervec){
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
bool Mamusu::GoBattle(int playerx,int playery){
	return false;
}

void Mamusu::Finalize(){
	delete [] mobu;
	field.Finalize();
}