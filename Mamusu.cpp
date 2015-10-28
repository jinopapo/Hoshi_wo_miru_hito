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
	Field hoge("mamusu.csv",field1,field2,field3,field4,field5,field6,field7,field8,field9,field10,field11,50,51);//最初のステージ
	field = hoge;
	int src[16];
	LoadDivGraph("mobu1.png",16,4,4,32,32,src);//主人公の素材
	mobus = 10;
	mobu = new Mobu[mobus];
	Mobu hige("まむすのむらへ、ようこそ。Bここに　いれば、あんぜんです。",src,23,12,true);
	Mobu hige1("もうひとつのむら　でうす　の　みんなは、Bなぞの　びょうきで、　たおれている",src,24,11,true);
	Mobu hige2("むらの　すがたが　みえないのは、みんなのBちからを　あわせて　すがたを、Bけしているからです",src,27,38,true);
	Mobu hige3("りばいるの　くすりは、Bやむのみ　あえのみ　るくのみの　じゅんばんでBちょうごうすると　できる。",src,16,26,true);
	Mobu hige4("このさきは、４にん　そろって　いかないと、Bきけんだ。Bだれも　もどってきたものが、いない。",src,39,37,true);
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
	if(player.getPlayerx() <10  || player.getPlayery() < 10 ||player.getPlayerx() >=41  || player.getPlayery() >= 40){//村の外に出たら元に戻す
		mSceneChanger->ChangeScene(eScene_StartStage);//シーンをメニューに変更
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
//描写
void Mamusu::Draw(int playerx,int playery){
	field.Drow(playerx,playery);
	for(i = 0;i < mobus;i++){
		mobu[i].Draw1(field.getmovex(),field.getmovey());
	}
}

//ブロック間の移動の座標を渡す関数
int Mamusu::Fieldmovex(){
	return field.getmovex();
}
int Mamusu::Fieldmovey(){
	return field.getmovey();
}

//プレイヤーの初期地点を伝える関数
int* Mamusu::PlayerPointDef(){
	playerPointDef[0] = 23;
	playerPointDef[1] = 10;
	playerPointDef[2] = 8;
	return playerPointDef;
}

//セリフを取得する関数
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

//戦闘に入ったこと知らせる関数
bool Mamusu::GoBattle(int playerx,int playery){
	return false;
}

void Mamusu::Finalize(){
	delete [] mobu;
	field.Finalize();
}