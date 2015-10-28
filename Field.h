#ifndef __FIELD_H_INCLUDED__
#define __FIELD_H_INCLUDED__

#include "DxLib.h"
#include "Player.h"
#include "Task.h"
#include "Mobu.h"

class Field:public Task{
private:
	//�t�B�[���h�̕ϐ�
	int** arrays;
	//�t�B�[���h�̑f�ނ̕ϐ�
	int src[11];
	//�u���b�N�Ԃ̈ړ��̕ϐ�
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
	void Initialize() override;    //�������������I�[�o�[���C�h�B
    void Finalize() override ;        //�I���������I�[�o�[���C�h�B
    void Update() override;        //�X�V�������I�[�o�[���C�h�B
    void Draw() override;            //�`�揈�����I�[�o�[���C�h�B
};
#endif