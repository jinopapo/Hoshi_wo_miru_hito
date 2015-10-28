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
    void Initialize() override;    //初期化処理をオーバーライド。
//    void Finalize() override;        //終了処理をオーバーライド。
    void Update() override;        //更新処理をオーバーライド。
    void Draw() override;            //描画処理をオーバーライド。

};

#endif