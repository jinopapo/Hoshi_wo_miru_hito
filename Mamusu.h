#ifndef __MAMUSU_H_INCLUDED__
#define __MAMUSU_H_INCLUDED__

#pragma once

#include "BaseStage.h"
#include "ISceneChanger.h"
#include "Field.h"
#include "Mobu.h"
#include <string>

class Mamusu : public BaseStage {

private:
	int field1,field2,field3,field4,field5,field6,field7,field8,field9,field10,field11;
	Field field;
	Mobu *mobu;
	int mobus;
	int i;
public :
    Mamusu::Mamusu(ISceneChanger* changer);
    void Initialize() override;    //初期化処理をオーバーライド。
    void Finalize() override;        //終了処理をオーバーライド。
    void Update() override;        //更新処理をオーバーライド。
	void Update(Player player,bool menumode,bool talk,bool tele);
    void Draw(int playerx,int playery) override; //描画処理をオーバーライド。
	int Fieldmovex() override;
	int Fieldmovey() override;
	int* PlayerPointDef() override;
	std::string getWords(int playerx,int playery,int playervec) override;
	bool GoBattle(int playerx,int playery) override;
};
#endif