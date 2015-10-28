#include "Field.h"
#include "Player.h"
#include "DxLib.h"
#include "Key.h"
#include "Mobu.h"
#include "stdlib.h"

//ループ用の変数
int i;
int j;
int x;
int y;
int moveSpeed = 2;//移動速度


Field::Field(char* file,int field1,int field2,int field3,int field4,int field5,int field6,int field7,int field8,int field9,int field10,int field11,int f_height,int f_width){
	//ブロック間の移動
	movex=0;
	movey=0;
	jampcell=0;
	//ファイルの読み込み
	FILE *fp;
	fp=fopen(file,"r");
	src[0]=field1;
	src[1]=field2;
	src[2]=field3;
	src[3]=field4;
	src[4]=field5;
	src[5]=field6;
	src[6]=field7;
	src[7]=field8;
	src[8]=field9;
	src[9]=field10;
	src[10]=field11;
	width = f_width;
	height = f_height;
	arrays = new int*[width];
	for(i = 0;i < width;i++){
		arrays[i] = new int[height];
	}
	//読み込んだcsvにしたがってステージを構成
	for(int j=0;j<height;j++){
		for(int i=0;i<width;i++){
			char c;
			do{c=(getc(fp));}
			while(c==','||c=='\n'||c=='\r');
			int calc = 0;
			do { calc = (c - '0') + (calc*10);}
			while(isdigit(c=getc(fp)));
			arrays[i][j] = calc;
		}
	}
	moveplayer = true;
	fclose(fp);
}

//ファイルが読み込めなかった用
bool Field::Error(char* file){
	FILE* fp;
	fp = fopen( file, "r" );
	if( file == NULL ){
		( "%sファイルが開けません¥n", file );
		return false;
	}else{
		return true;
	}
}

//更新
void Field::UpDate(Player player,bool *move,bool menumode){
	extern int cell;
	//キー入力によってステージを移動させる
	if(moveplayer){
		if(!*move && !menumode){
			if(Keyboard_Get(KEY_INPUT_UP) >= 1){
				while((arrays[player.getPlayerx()][player.getPlayery() - jampcell - 1] == 0 
				   || arrays[player.getPlayerx()][player.getPlayery() - jampcell - 1] >= 8 )
				   && jampcell != player.getjump()){
					jampcell++;
				}
				if(arrays[player.getPlayerx()][player.getPlayery() - jampcell - 1] != 0 
				&& arrays[player.getPlayerx()][player.getPlayery() - jampcell- 1] < 8 ){
					movey = moveSpeed; 
					*move = true;
				}else{
					jampcell = 0;
				}
			}
			else if(Keyboard_Get(KEY_INPUT_DOWN) >= 1){
				while((arrays[player.getPlayerx()][player.getPlayery() + jampcell + 1] == 0 
				   || arrays[player.getPlayerx()][player.getPlayery() + jampcell + 1] >= 8) 
				   && jampcell != player.getjump()){
					jampcell++;
				}
				if(arrays[player.getPlayerx()][player.getPlayery() + jampcell + 1] != 0 
				&& arrays[player.getPlayerx()][player.getPlayery() + jampcell + 1] < 8 ){
					movey = -moveSpeed; 
					*move = true;
				}else{
					jampcell = 0;
				}
			}
			else if(Keyboard_Get(KEY_INPUT_RIGHT) >= 1){
				while((arrays[player.getPlayerx() + jampcell + 1][player.getPlayery()] == 0 
				   || arrays[player.getPlayerx() + jampcell + 1][player.getPlayery()] >= 8) 
				   && jampcell != player.getjump()){
					jampcell++;
				}
				if(arrays[player.getPlayerx() + jampcell + 1][player.getPlayery()] != 0 
				&& arrays[player.getPlayerx() + jampcell + 1][player.getPlayery()] < 8 ){
					movex = -moveSpeed; 
					*move = true;
				}else{
					jampcell = 0;
				}
			}
			else if(Keyboard_Get(KEY_INPUT_LEFT) >= 1){
				while((arrays[player.getPlayerx() - jampcell - 1][player.getPlayery()] == 0 
				   || arrays[player.getPlayerx() - jampcell - 1][player.getPlayery()] >= 8) 
				   && jampcell != player.getjump()){
					jampcell++;
				}
				if(arrays[player.getPlayerx() - jampcell - 1][player.getPlayery()] != 0 
				&& arrays[player.getPlayerx() - jampcell - 1][player.getPlayery()] < 8 ){
					movex = moveSpeed; 
					*move = true;
				}else{
					jampcell = 0;
				}
			}
		}
		else{
			if(abs(movex) >= cell || abs(movey) >= cell){
				if(jampcell == 0){
				movex = 0;
				movey = 0;
				*move = false;
				}else{
					if(movex > 0){
						movex = moveSpeed;
					}else if(movex < 0){
						movex = -moveSpeed;
					}
					if(movey > 0){
						movey = moveSpeed;
					}else if(movey < 0){
						movey = -moveSpeed;
					}
					jampcell--;
				}
			}
			if(movex > 0){
				movex += moveSpeed;
			}
			else if(movex < 0){
				movex -= moveSpeed;
			}
			else if(movey > 0){
				movey += moveSpeed;
			}
			else if(movey < 0){
				movey -= moveSpeed;
			}
		}
	}
}

//描写
void Field::Drow(int playerx,int playery){
	extern int cell;
	//ブロック間の移動のために見えないとこにも描写しておく
	for(j=-9,y=0;j<=9;j++,y++){
		for(i=-9,x=0;i<=9;i++,x++){
			DrawGraph(-3*cell/2+cell*x+movex,-3*cell/2+cell*y+movey,src[arrays[playerx + i][playery + j]],TRUE);
		}
	}
}

//プレイヤーをブロック移動させる
int Field::getmovex(){
	return movex;
}
int Field::getmovey(){
	return movey;
}

//モブキャラの進む方向に壁がないか調べる
int Field::getnoise(int x,int y){
	return arrays[x][y];
}

int Field::getjampcell(){
	return jampcell;
}

//すべてのモブキャラの座標と比べてモブキャラと被らないようにする
void Field::getcharpoint(int x,int y,int playerx,int playery){
	extern bool move;
	if(movey > 0 && playery - 1 == y && playerx ==x){
		moveplayer = false;
		movey = 0;
		move = false;
	}
	else if(movey < 0 && playery + 1 == y && playerx == x){
		moveplayer = false;
		movey = 0;
		move = false;
	}
	else if(movex < 0 && playerx + 1 == x && playery == y){
		moveplayer =false;
		movex = 0;
		move = false;
	}
	else if(movex > 0 && playerx - 1 == x && playery == y){
		moveplayer = false;
		movex = 0;
		move = false;
	}
}
void Field::moveplayerreset(){
	moveplayer = true;
}

void Field::Initialize(){
}

void Field::Draw(){
}

void Field::Update(){
}

Field::Field(){
}


void Field::Finalize(){
	for(i = 0;i < width;i++){
		delete [] arrays[i];
	}
	delete [] arrays;
}