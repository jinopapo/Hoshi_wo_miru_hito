#include "Op.h"
#include "Key.h"
#include "DxLib.h"

Op::Op(ISceneChanger* changer): BaseScene(changer){
}

void Op::Initialize(){
	src = LoadGraph("OP.png");
	src1 = LoadGraph("key.png");
	keyx = 170;
	keyy = 375;
}

void Op::Update(){
	if(Keyboard_Get(KEY_INPUT_DOWN) == 1 && keyy != 410){
		keyy = 410; 
	}
	if(Keyboard_Get(KEY_INPUT_UP) == 1 && keyy != 375){
		keyy = 375; 
	}
	if(Keyboard_Get(KEY_INPUT_SPACE) == 1 && keyy == 375){
		mSceneChanger->ChangeScene(eScene_Game);//シーンをメニューに変更
	}	
}

void Op::Draw(){
	DrawGraph(0,0,src,TRUE);
	DrawGraph(keyx,keyy,src1,TRUE);
}

