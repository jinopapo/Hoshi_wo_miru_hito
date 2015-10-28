#ifndef __MOBU_H_INCLUDED__
#define __MOBU_H_INCLUDED__

#include "DxLib.h"
#include "Task.h"
#include <string>

class Mobu:public Task{
private:
	int x,y;
	int fieldx,fieldy;
	std::string words;
	int src[16];
	int i;
	int count,movecount;
	int srcSelect;
	int mobumovex,mobumovey,movevec;
	bool mobumove,hide;
	int movespeed;
	bool move;
public:
	Mobu(char* word,int *handle,int mobux,int mobuy,bool move);
	Mobu();
	void Initialize() override;    //�������������I�[�o�[���C�h�B
    //void Finalize() override ;        //�I���������I�[�o�[���C�h�B
    void Update() override;        //�X�V�������I�[�o�[���C�h�B
	void Update1(int playerx,int playery,int playervec,int field,bool menu,bool talk);
    void Draw() override;            //�`�揈�����I�[�o�[���C�h�B
	void Draw1(int movex,int movey);
	int getnextx();
	int getnexty();
	int getx();
	int gety();
	std::string getWords();
};


#endif