#include "BaseStage.h"
#include "DxLib.h"
#include <string>

//初期化
BaseStage::BaseStage(ISceneChanger* changer) : 
    mImageHandle(0) {
    mSceneChanger = changer;
}

//終了処理
void BaseStage::Finalize(){
    DeleteGraph(mImageHandle);
}

//更新
void BaseStage::Update(Player player,bool menumode,bool talk,bool tele){
}

//描写
void BaseStage::Draw(){
    DrawGraph(0,0,mImageHandle,FALSE);
}
void BaseStage::Draw(int playerx,int playery){
}

//ブロック間の移動の座標を伝える関数
int BaseStage::Fieldmovex(){
	return 0;
}
int BaseStage::Fieldmovey(){
	return 0;
}

//プレイヤーの初期地点を伝える関数
int* BaseStage::PlayerPointDef(){
	return playerPointDef;
}

//モブキャラのセリフを取得する関数
std::string BaseStage::getWords(int playerx,int playery,int playervec){
	return "";
}

//戦闘にはいったことを伝える関数
bool BaseStage::GoBattle(int playerx,int playery){
	return false;
}
