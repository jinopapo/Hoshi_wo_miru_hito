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
	Field hoge("deusu.csv",field1,field2,field3,field4,field5,field6,field7,field8,field9,field10,field11,51,50);//最初のステージ
	field = hoge;
	int src[16];
	LoadDivGraph("mobu1.png",16,4,4,32,32,src);//主人公の素材
	mobus = 7;
	mobu = new Mobu[mobus];
	Mobu hige("わたしたちが、かかっている　びょうきはBりんすきんびょう　と　いうらしいわ",src,15,35,true);
	Mobu hige1("くしょん　くしょん",src,27,19,true);
	Mobu hige2("ねつが　でて　くるしい。",src,27,34,true);
	Mobu hige3("みなみよ　おおきくなったな！Bおまえが　ちいさいころ、あーくＣＩＴＹからBつれてきたのは、このわたしだ。Bこの　むらは、なぞの　びょうげんきんでBみなが　やんでいる。Bぜひ　ちからをかしてくれ。BおまえがさがしているＪＵＭＰのうりょくを　もつ　しょうねんはBみなみの　ちかに。とらわれているぞ。Bみつけたら　また　くるがよいぞ。",src,23,29,true);
	Mobu hige4("あいむ　の　くすりは、Bあえのみ、るくのみ、えくのみ　のBじゅんばんで、ちょうごうすることが　できる。",src,14,27,true);
	Mobu hogehoge("びょうきを　なおすにはBあいむ　の　くすりが、ひつようだ。",src,38,27,true);
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
	if(player.getPlayerx() < 10  || player.getPlayery() < 10 ||player.getPlayerx() >=40  || player.getPlayery() >= 41){//村の外に出たら元に戻す
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
void Deusu::Update(){
}
//描写
void Deusu::Draw(int playerx,int playery){
	field.Drow(playerx,playery);
	for(i = 0;i < mobus;i++){
		mobu[i].Draw1(field.getmovex(),field.getmovey());
	}
}

//ブロック間の移動の座標を渡す関数
int Deusu::Fieldmovex(){
	return field.getmovex();
}
int Deusu::Fieldmovey(){
	return field.getmovey();
}

//プレイヤーの初期地点を伝える関数
int* Deusu::PlayerPointDef(){
	playerPointDef[0] = 19;
	playerPointDef[1] = 11;
	playerPointDef[2] = 8;
	return playerPointDef;
}

//セリフを取得する関数
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

//戦闘に入ったこと知らせる関数
bool Deusu::GoBattle(int playerx,int playery){
	return false;
}

void Deusu::Finalize(){
	delete [] mobu;
	field.Finalize();
}