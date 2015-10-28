#ifndef __MENU_H_INCLUDED__
#define __MENU_H_INCLUDED__

#include "DxLib.h"
#include "Task.h"
#include "Player.h"
#include <string>
#include <regex>
#include <vector>
#include "Item.h"


class Menu:public Task{
private:
	int i,j,k,l;
	int x,y;
	bool menumode;
	bool write;
	bool talk;
	bool status;
	int src1,src2,src3,src4,src5,src6,src7,src8,src9,src10,src11,src12;
	int white;
	char* word;
	std::string words;
	//回復させるときに条件を回す変数
	int recovery;
	//回復の時のカーソルの座標
	int cursor;
	//復活させるときのフラグ
	int rebirth;
	//薬剤師の条件を回す変数
	int chem;
	//買い物をする時の会話の状態を回す変数
	int shopping;
	//プレイヤーのステータス
	int hit;
	int maxhit;
	int saiko;
	int maxsaiko;
	int speed;
	int jukurenndo;
	int keikenti;
	int level;
	int state;
	int defense;
	int arm;
	int guard;
	int gold;
	std::string name;
	int pk;
	int jump;
	int telepathy;
	int shield;
	//次のレベルまでに必要な経験値
	int nextPoint;
	//会話中に改ページさせる変数
	bool newLine;
	//会話の終了を伝える変数
	bool talkEnd;
	//カーソルのあたっているプレイヤーを示す変数
	int  cursortarget;
	//　武器屋で売ってる武器を入れる配列
	int* arms;
	std::string buyer_arms_words;
	//プレイヤーのパーティーを入れる配列
	Player* party;
	//会話してたことを残す変数
	bool talknow;
	//きのみを採取するモード
	bool gathermode;
	//きのみを採取出来たかどうか
	bool gatherget;
	//きのみの名前
	std::string seed_name;
	//きのみを採取するウィンドウを回す変数
	int gather;
	//持ち物を表示するための配列
	std::vector<item> item_list;
	//持ち物表示モード
	bool itemmode;
	//薬を表示するための配列
	std::vector<item> drug_list;
	//薬表示モード
	bool drugmode;
	//アイテムのウィンドウを回す変数
	int item_w;
	//調合リスト
	std::vector<std::string> chem_list;
	//出来た薬のなまえ
	std::string drug_name;
	bool trash;
	int BANPEI;
	std::vector<item>::iterator it;
public:
	Menu();
	void Initialize() override;
	void Initialize(int* ability,std::string name);    //初期化処理をオーバーライド。
    void Finalize() override ;        //終了処理をオーバーライド。
    void Update() override;        //更新処理をオーバーライド。
	void Update(std::string mobuwords,int count,int* ability,Player* player,int playercount,int nowstage,int nowplayer);
    void Draw() override;            //描画処理をオーバーライド。
	bool getMenu();
	bool gettalk();
};


#endif