#ifndef __BASESTAGE_H_INCLUDED__
#define __BASESTAGE_H_INCLUDED__

#pragma once

#include "Task.h"
#include "ISceneChanger.h"
#include "Player.h"
#include <string>

//シーンの基底クラス。
class BaseStage : public Task {

protected:
    int mImageHandle;               //画像ハンドル格納用変数
    ISceneChanger* mSceneChanger;    //クラス所有元にシーン切り替えを伝えるインターフェイス
	int playerPointDef[3]; //プレイヤーの初期地点を入れる配列

public :
    BaseStage(ISceneChanger* changer);
    virtual ~BaseStage(){}
    virtual void Initialize() override {}    //初期化処理をオーバーライド。
    virtual void Finalize() override ;        //終了処理をオーバーライド。
    virtual void Update() override {}        //更新処理をオーバーライド。
	virtual void Update(Player player,bool menumode,bool talk,bool tele);
    virtual void Draw() override ;            //描画処理をオーバーライド。
	virtual void Draw(int palyerx,int playery);
	virtual int Fieldmovex();//ブロック移動の座標を伝える関数
	virtual int Fieldmovey();
	virtual int* PlayerPointDef();//プレイヤーの初期地点を伝える関数
	virtual std::string getWords(int playerx,int playery,int playervec);
	virtual bool GoBattle(int playerx,int playery);
};

#endif

