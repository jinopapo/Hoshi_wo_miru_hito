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
	Field hoge("field1.csv",field1,field2,field3,field4,field5,field6,field7,field8,field9,field10,field11,76,59);//最初のステージ
	field = hoge;
	count = 0;
}

void StartStage::Update(Player player,bool menumode,bool talk,bool tele){
	if(player.getPlayerx() == 14 && player.getPlayery() == 29){//まむす村の座標に来たら
		mSceneChanger->ChangeScene(eScene_Mamusu);//シーンをメニューに変更
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

//描写
void StartStage::Draw(int playerx,int playery){
	field.Drow(playerx,playery);
}

//ブロック移動の座標を伝える関数
int StartStage::Fieldmovex(){
	return field.getmovex();
}
int StartStage::Fieldmovey(){
	return field.getmovey();
}

//プレイヤーの初期地点を伝える関数
int* StartStage::PlayerPointDef(){
	playerPointDef[0] = 15;
	playerPointDef[1] = 29;
	playerPointDef[2] = 8;
	return playerPointDef;
}

//セリフを取得する関数
std::string StartStage::getWords(int playerx,int playery,int playervec){
	extern std::string BANPEI;
	return "hogehoge";
}

//戦闘に入ったことを伝える関数
bool StartStage::GoBattle(int playerx,int playery){
	extern int cell;
	extern bool debbattle;
	if(playerx == 14 && playery == 29 ){//まむす村の座標に来たら
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