#include "StageMgr.h"
#include "Game.h"
#include "DxLib.h"
#include "Field.h"
#include "Player.h"
#include "Key.h"
#include "Menu.h"


Game::Game(ISceneChanger* changer) : BaseScene(changer) {
}

//初期化
void Game::Initialize(){
	int src[16];
	LoadDivGraph("minami_f.png",16,4,4,32,32,src);//主人公の素材
	players = new Player[4];
	Player minami(src,LoadGraph("minami.png"),LoadGraph("minami2.png"),LoadGraph("minami3.png"),"みなみ",50,30,0,8,10);
	players[0] = minami;
	players[0].becameMate();
	Player siba(src,LoadGraph("siba.png"),LoadGraph("shiba2.png"),LoadGraph("shiba3.png"),"しば",50,30,1,28,20);
	players[1] = siba;
	players[2] = siba;
	players[3] = siba;
	players[1].becameMate();
	stageMgr.Initialize();
	menu.Initialize(players[0].getability(),players[0].getname());
	battle.Initialize();
	battlemode = false;
	count = 0;
	dead = false;
	src1 = LoadGraph("menu2.png");
	src2 = LoadGraph("Dead.png");
	white = GetColor(255,255,255);
	playercount = 2;
	nowplayer = 0;
	players[0].setItem("かーど");
	playerpoint = new int[3];
}

//更新
void Game::Update(){
	extern bool move,change;		
	//更新
	if(!battlemode && !dead){
		if(Keyboard_Get(KEY_INPUT_ESCAPE) == 1){
			playerpoint[0] = players[nowplayer].getPlayerx();
			playerpoint[1] = players[nowplayer].getPlayery();
			playerpoint[2] = players[nowplayer].getplayervec();
			do{
				nowplayer++;
				if(nowplayer == 4){
					nowplayer = 0;
					break;
				}
			}while(!players[nowplayer].getMate());
			change = true;
			players[nowplayer].Update(playerpoint);
		}
		menu.Update(stageMgr.getWords(players[nowplayer].getPlayerx(),players[nowplayer].getPlayery(),players[nowplayer].getplayervec()),count,players[nowplayer].getability(),players,playercount,stageMgr.getNowStage(),nowplayer);
		players[nowplayer].UpDateMove(stageMgr.Fieldmovex(),stageMgr.Fieldmovey());
		players[nowplayer].UpDateSrc(Keyboard_Get(KEY_INPUT_UP),Keyboard_Get(KEY_INPUT_DOWN),Keyboard_Get(KEY_INPUT_RIGHT),Keyboard_Get(KEY_INPUT_LEFT),menu.getMenu());
		battlemode = stageMgr.GoBattle(players[nowplayer].getPlayerx(),players[nowplayer].getPlayery());
		stageMgr.Update(players[nowplayer],menu.getMenu(),menu.gettalk(),false);
		players[nowplayer].Update(stageMgr.PlayerPointDef());
		count++;
		if(count ==60){
			count = 0;
		}
	}
	else if(!dead){
		battle.Update(players,stageMgr.getNowStage(),count,playercount);
		if(battle.EndBattle()){
			battlemode = false;
			if(battle.getTele()){
				stageMgr.Update(players[nowplayer],menu.getMenu(),menu.gettalk(),battle.getTele());
			}
		}
		if(battle.getDead()){
			dead = true;
		}
	}
	else if(Keyboard_Get(KEY_INPUT_SPACE) == 1){
		mSceneChanger->ChangeScene(eScene_Op);//死んだらOpに戻る
		dead = false;
	}
}

//描画
void Game::Draw(){
	extern int cell;
	if(!battlemode){		
		stageMgr.Draw(players[nowplayer].getPlayerx(),players[nowplayer].getPlayery());
		players[nowplayer].Draw();
		menu.Draw();
	}
	else{
		battle.Draw();
	}
	if(dead){
		stageMgr.Draw(players[nowplayer].getPlayerx(),players[nowplayer].getPlayery());
		DrawGraph(cell*7+cell/2,cell*7+cell/2,src2,TRUE);
		DrawGraph(0,342,src1,TRUE);
		DrawFormatString(40,382,white,"この　みじゅくもの！");
		DrawFormatString(40,400,white,"ぜいいん、しんでしまうとは・・・");
		DrawFormatString(40,418,white,"もういちど　でなおしてこい！");
	}
}

void Game::Finalize(){
	players[nowplayer].Finalize();
	stageMgr.Finalize();
	menu.Finalize();
	battle.Finalize();
	//delete [] players;
}