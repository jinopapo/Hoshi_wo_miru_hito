#ifndef __FIELD_H_INCLUDED__
#define __FIELD_H_INCLUDED__

#include "DxLib.h"
#include "Player.h"
#include "Task.h"
#include "Mobu.h"

class Field:public Task{
private:
	//フィールドの変数
	int** arrays;
	//フィールドの素材の変数
	int src[11];
	//ブロック間の移動の変数
	int movex;
	int movey;
	int width;
	int height;
	bool moveplayer;
	int jampcell;
public:
	Field(char* file,int filed1,int field2,int field3,int field4,int field5,int field6,int field7,int field8,int field9,int field10,int field11,int height,int widht);
	Field();
	bool Error(char* file);
	void UpDate(Player player,bool *move,bool menumode); 
	void Drow(int playerx,int playery);
	int	getmovex();
	int getmovey();
	int getjampcell();
	int getnoise(int x,int y);
	void getcharpoint(int x,int y,int playerx,int playery);
	void moveplayerreset();
	void Initialize() override;    //初期化処理をオーバーライド。
    void Finalize() override ;        //終了処理をオーバーライド。
    void Update() override;        //更新処理をオーバーライド。
    void Draw() override;            //描画処理をオーバーライド。
};
#endif