#include "DxLib.h"
#include "Game.h"
#include "Op.h"
#include "SceneMgr.h"

SceneMgr::SceneMgr() : 
    mNextScene(eScene_None) //次のシーン管理変数
{
    mScene = (BaseScene*) new Op(this);
}

//初期化
void SceneMgr::Initialize(){
    mScene->Initialize();
}

//終了処理
void SceneMgr::Finalize(){
    mScene->Finalize();
}

//更新
void SceneMgr::Update(){
    if(mNextScene != eScene_None){    //次のシーンがセットされていたら
        mScene->Finalize();//現在のシーンの終了処理を実行
        delete mScene;
        switch(mNextScene){       //シーンによって処理を分岐
		case eScene_Game:
            mScene = (BaseScene*) new Game(this);
            break;
		case eScene_Op:
			mScene = (BaseScene*) new Op(this);
			break;
       }
        mNextScene = eScene_None;    //次のシーン情報をクリア
        mScene->Initialize();    //シーンを初期化
    }

    mScene->Update(); //シーンの更新
}

//描画
void SceneMgr::Draw(){
    mScene->Draw(); //シーンの描画
}

// 引数 nextScene にシーンを変更する
void SceneMgr::ChangeScene(eScene NextScene){
    mNextScene = NextScene;    //次のシーンをセットする
}