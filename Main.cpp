#include "DxLib.h"
#include "Field.h"
#include "Key.h"
#include "Player.h"
#include <string>

#include "SceneMgr.h"

int count = 0;
int fpsc = 0;
int cell=32;
bool move = false; //移動中であることを伝える関数
bool change = false;//ステージを移動したことを伝える関数
bool debbattle = false;
std::string BANPEI = "hogehoge";

void fps(){
    int i;
    static int t=0,ave=0,f[60];
 
    f[fpsc%60]=GetNowCount()-t;
    t=GetNowCount();
    if(fpsc%60==59){
        ave=0;
        for(i=0;i<60;i++)
            ave+=f[i];
        ave/=60;
    }
    if(ave!=0){
        DrawFormatString(0, 0,GetColor(255,255,255),"%.1fFPS",1000.0/(double)ave);
    }
    return;
}

int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int){
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen( DX_SCREEN_BACK ); //ウィンドウモード変更と初期化と裏画面設定
	SetGraphMode(512,512,16) ;//ディスプレイの大きさの設定

	SceneMgr sceneMgr;
    sceneMgr.Initialize();


	while( ScreenFlip()==0 && ProcessMessage()==0 && ClearDrawScreen()==0 && gpUpdateKey()==0 ){
        sceneMgr.Update();  //更新
        sceneMgr.Draw();    //描画
		fps();
		if(Keyboard_Get(KEY_INPUT_F1) == 1){
			debbattle = !debbattle;
		}
		if(debbattle){
		    DrawFormatString(0, 10,GetColor(255,255,255),"battle:true");
		}
		fpsc++;
	}

	sceneMgr.Finalize();
	DxLib_End();	// DXライブラリ終了処理
	return 0;
}