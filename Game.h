#ifndef __GAME_H_INCLUDED__
#define __GAME_H_INCLUDED__

#pragma once

#include "BaseScene.h"
#include "ISceneChanger.h"
#include "Player.h"
#include "Field.h"
#include "StageMgr.h"
#include "Menu.h"
#include "Battle.h"

//�Q�[����ʃN���X
class Game : public BaseScene {

private:
	int field1,field2,field3;
	Field field;
	Player player;
	Player* players;
	int* playerpoint;
	Field mamusu;
	StageMgr stageMgr;
	Menu menu;
	Battle battle;
	bool battlemode;
	int count;
	bool dead;
	int src1,src2;
	int white;
	int playercount;
	int nowplayer;
	int i;
public :
    Game::Game(ISceneChanger* changer);
    void Initialize() override;    //�������������I�[�o�[���C�h�B
    void Finalize() override;        //�I���������I�[�o�[���C�h�B
    void Update() override;        //�X�V�������I�[�o�[���C�h�B
    void Draw() override;            //�`�揈�����I�[�o�[���C�h�B

};

#endif