#ifndef __DEUSU_H_INCLUDED__
#define __DEUSU_H_INCLUDED__

#pragma once

#include "BaseStage.h"
#include "ISceneChanger.h"
#include "Field.h"
#include "Mobu.h"
#include <string>

class Deusu : public BaseStage {

private:
	int field1,field2,field3,field4,field5,field6,field7,field8,field9,field10,field11;
	Field field;
	Mobu *mobu;
	int mobus;
	int i;
public :
    Deusu::Deusu(ISceneChanger* changer);
    void Initialize() override;    //�������������I�[�o�[���C�h�B
    void Finalize() override;        //�I���������I�[�o�[���C�h�B
    void Update() override;        //�X�V�������I�[�o�[���C�h�B
	void Update(Player player,bool menumode,bool talk,bool tele);
    void Draw(int playerx,int playery) override; //�`�揈�����I�[�o�[���C�h�B
	int Fieldmovex() override;
	int Fieldmovey() override;
	int* PlayerPointDef() override;
	std::string getWords(int playerx,int playery,int playervec) override;
	bool GoBattle(int playerx,int playery) override;
};
#endif