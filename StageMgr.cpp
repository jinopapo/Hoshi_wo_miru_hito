#include "DxLib.h"
#include "StartStage.h"
#include "StageMgr.h"
#include "Mamusu.h"
#include "deusu.h"
#include <string>

StageMgr::StageMgr() : 
    mNextScene(eScene_None) //次のシーン管理変数
{
    mScene = (BaseStage*) new StartStage(this);
}

//初期化
void StageMgr::Initialize(){
    mScene->Initialize();
	nowStage = 0;
}

//終了処理
void StageMgr::Finalize(){
    mScene->Finalize();
}

//更新
void StageMgr::Update(Player player,bool menumode,bool talk,bool tele){
	extern bool change;
    if(mNextScene != eScene_None){    //次のシーンがセットされていたら
        mScene->Finalize();//現在のシーンの終了処理を実行
        delete mScene;
        switch(mNextScene){       //シーンによって処理を分岐
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
        mNextScene = eScene_None;    //次のシーン情報をクリア
        mScene->Initialize();    //シーンを初期化
    }

    mScene->Update(player,menumode,talk,tele); //シーンの更新
}
void StageMgr::Update(){
}

//描画
void StageMgr::Draw(int playerx,int playery){
    mScene->Draw(playerx,playery); //シーンの描画
}
void StageMgr::Draw(){
}

// 引数 nextScene にシーンを変更する
void StageMgr::ChangeScene(eScene NextScene){
    mNextScene = NextScene;    //次のシーンをセットする
}

//ブロック間の移動中の座標を渡す変数
int StageMgr::Fieldmovex(){
	return mScene->Fieldmovex();
}
int StageMgr::Fieldmovey(){
	return mScene->Fieldmovey();
}

//Fieldから受け取ったプレイヤーの初期地点を渡す関数
int* StageMgr::PlayerPointDef(){
	return mScene->PlayerPointDef();
}

//Fieldからモブキャラのセリフをとってくる。モブキャラが指定した場所にいなければnullを返す
std::string StageMgr::getWords(int playerx,int playery,int playervec){
	return mScene->getWords(playerx,playery,playervec);
}

//戦闘に入ることを伝える関数
bool StageMgr::GoBattle(int playerx,int playery){
	return mScene->GoBattle(playerx,playery);
}

int StageMgr::getNowStage(){
	return nowStage;
}