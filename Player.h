#ifndef __PLAYER_H_INCLUDED__
#define __PLAYER_H_INCLUDED__

#include "DxLib.h"
#include "Task.h"
#include <string>
#include <vector>
#include "Item.h"


class Player:public Task{
private:
	//プレイヤーのブロック上の位置
	int playerx;
	int playery;
	//プレイヤーの画像の変数
	int src[16];
	int src1;
	int src2;
	int src3;
	//プレイヤーの画像を切り替える変数
	int srcSelect;
	int count;
	//そのプレイヤーが使用可能伝える関数
	bool mate;
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
	int arms;
	int guard;
	int gold;
	int pk;
	int jump;
	int shield;
	int telepathy;
	int nextPoint;
	std::string name;
	bool dead;
	bool esc;
	bool* esp;
	//プレイヤーのステータスを入れる配列
	int* ability;
	//薬
	std::vector<item> drug_list;
	//アイテム
	std::vector<item> item_list;
	//薬のもと
	std::vector<item> seed_list;
	int item_count;
	item geti;
	int i;
public:
	Player(int* handle,int hendle1,int hendle2,int hendle3,char* p_name,int p_hit,int p_saiko,int p_defense,int p_speed,int p_jukurendo);
	Player();
	bool UpDateMove(int movex,int movey);//移動に関する更新
	bool UpDateSrc(int up,int down,int right,int left,bool menumode);//移動中のキャラの表示に関する更新
	//プレイヤーの座標を伝える関数
	int getPlayerx();
	int getPlayery();
	//プレイヤーの向きを伝える関数
	int getplayervec();
	//プレイヤーの画像を渡す関数
	int getSrc();
	//プレイヤーのひっとを計算する関数
	void hitdamage(int damage);
	//プレイヤーのさいこを計算する関数
	void useSaiko(int use);
	//プレイヤーの経験値を計算する関数
	void levelup(int point);
	//プレイヤーのお金を計算する関数
	void shopping(int gold);
	//プレイヤーの武器を変更する関数
	void setArms(int arm);
	//プレイヤーの防具を変更する関数
	void setGuard(int guard_s);
	//プレイヤーが仲間になっているどうかを伝える関数
	bool getMate();
	void becameMate();
	//プレイヤーを状態異常にする関数
	void becomeError(int error);
	//プレイヤーの薬を渡す関数
	std::vector<item> getDrugList();
	//薬を持ち物に加える関数
	bool setDrug(std::string drug);
	//プレイヤーのアイテムを渡す関数
	std::vector<item> getItemList();
	//アイテムを持ち物に加える関数
	bool setItem(std::string item_p);
	//くすりの元を渡す関数
	std::vector<item> getSeedList();
	//くすりのもとを持ち物に加える関数
	bool setSeed(std::string seed);
	//ステータスを伝える関数
	int gethit();
	int getmaxhit();
	int getsaiko();
	int getmaxsaiko();
	int getspeed();
	int getjukurenndo();
	int getkeikenti();
	int getlevel();
	int getstate();
	int getdefense();
	int getarms();
	int getguard();
	int getgold();
	int getjump();
	bool* getesp();
	int getpk();
	int getshield();
	int gettelepathy();
	int getNextPoint();
	bool getDead();
	bool getEsc();
	void becomeEsc();
	std::string getname();
	int* getability();
	void Initialize() override;    //初期化処理をオーバーライド。
    void Finalize() override ;        //終了処理をオーバーライド。
    void Update() override;        //更新処理をオーバーライド。
	void Update(int* playerPointDef);
    void Draw() override;            //描画処理をオーバーライド。
};
#endif