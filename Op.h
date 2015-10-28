#ifndef __OP_H_INCLUDED__
#define __OP_H_INCLUDED__

#pragma once

#include "BaseScene.h"
#include "ISceneChanger.h"

class Op : public BaseScene {
	private:
		int src,src1;
		int keyx,keyy;
	public :
    Op::Op(ISceneChanger* changer);
    void Initialize() override;    //�������������I�[�o�[���C�h�B
//    void Finalize() override;        //�I���������I�[�o�[���C�h�B
    void Update() override;        //�X�V�������I�[�o�[���C�h�B
    void Draw() override;            //�`�揈�����I�[�o�[���C�h�B

};

#endif