#ifndef __STAGE_H_INCLUDED__
#define __STAGE_H_INCLUDED__

#pragma once

#include "BaseStage.h"
#include "ISceneChanger.h"
#include "Player.h"
#include <string>

class StageMgr:public ISceneChanger, Task{

private:
    BaseStage* mScene    ;    //シーン管理変数
    eScene mNextScene;    //次のシーン管理変数
	int nowStage;
public :
	StageMgr();
    void Initialize() override;    //初期化処理をオーバーライド。
    void Finalize() override;        //終了処理をオーバーライド。
    void Update() override;        //更新処理をオーバーライド。
	void Update(Player player,bool menumode,bool talk,bool tele);
    void Draw() override;            //描画処理をオーバーライド。
	void Draw(int playerx,int playery);
	int Fieldmovex();
	int Fieldmovey();
	std::string getWords(int playerx,int playery,int playervec);
	bool GoBattle(int playerx,int playery);
	// 引数 nextScene にシーンを変更する
    void ChangeScene(eScene NextScene) override;
	//ステージが変わった時に初期値を渡す様の関数
	int* PlayerPointDef();
	//現在のステージを伝える関数
	int getNowStage();
};

#endif