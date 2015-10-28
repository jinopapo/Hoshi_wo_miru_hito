#include "DxLib.h"
#include "Mobu.h"
#include <string>

Mobu::Mobu(){
}

Mobu::Mobu(char* word,int* handle,int mobux,int mobuy,bool m_move){
	words = word;
	x = mobux;
	y = mobuy;
	fieldx = mobux;
	fieldy = mobuy;
	movevec = 0;
	count = 0;
	movecount = 0;
	mobumovex = 0;
	mobumovey = 0;
	for(int i=0;i<16;i++,handle++){
		src[i] = *handle;
	}
	srcSelect = 8;
	mobumove = false;
	hide = true;
	movespeed = 2;
	move = m_move;
}

void Mobu::Initialize(){
}

void Mobu::Update(){	
}

void Mobu::Update1(int playerx,int playery,int playervec,int field,bool menu,bool talk){
	//extern bool move;
	extern int cell;
	if(!hide && !menu && move){
		if(count >= 60){
			count = 0;
			if(rand() % 2 == 1){
				mobumove = true;
				movevec = rand() % 5;
			}
		}
		count++;
		if(mobumove){
			switch(movevec){
			case 1:
				if(field != 0 && field < 8 && (playery != y + 1 || playerx != x)){
					srcSelect = 8;
					mobumovey += movespeed;
					if(mobumovey == cell){
						mobumove = false;
						y++;
						mobumovey = 0;
					}
				}
				else{
					mobumove = false;
				}
				break;
			case 2:
				if(field != 0 && field < 8 && (playery != y - 1 || playerx != x )){
					srcSelect = 0;
					mobumovey -= movespeed;
					if(mobumovey == -cell){
						mobumove = false;
						y--;
						mobumovey = 0;
					}
				}
				else{
					mobumove = false;
				}
				break;
			case 3:
				if(field != 0 && field < 8 && (playerx != x + 1 || playery != y)){
					srcSelect = 12;
					mobumovex += movespeed;
					if(mobumovex == cell){
						mobumove = false;
						x++;
						mobumovex = 0;
					}
				}
				else{
					mobumove = false;
				}
				break;
			case 4:
				if(field != 0 && field < 8 && (playerx != x - 1 || playery != y)){
					srcSelect = 4;
					mobumovex -= movespeed;
					if(mobumovex == -cell){
						mobumove = false;
						x--;
						mobumovex = 0;
					}
				}
				else{
					mobumove = false;
				}
				break;
			default:
				mobumove = false;
				break;
			}
		}

	}
	if(talk){
		if(playervec == 0 && playerx == x && playery == y + 1){
			srcSelect = 8;
		}
		else if(playervec == 4 && playerx == x + 1 && playery == y){
			srcSelect = 12;
		}
		else if(playervec == 8 && playerx == x && playery == y - 1){
			srcSelect = 0;
		}
		else if(playervec == 12 && playerx == x - 1 && playery == y){
			srcSelect = 4;
		}
	}
	fieldx = x - playerx;
	fieldy = y - playery;
	if(abs(fieldx) < 9 || abs(fieldy) < 9){
		hide = false;
	}
	else{
		hide = true;
	}
}

void Mobu::Draw(){
}

void Mobu::Draw1(int movex,int movey){
	extern int cell;
	//ÃŽ~ó‘Ô
	if(!hide){
		if(!mobumove){
			movecount = 0;
			DrawGraph(cell*7+cell/2 + fieldx*cell + movex,cell*7+cell/2 + fieldy*cell + movey,src[srcSelect],TRUE );
		}
		//ˆÚ“®’†
		else{
			movecount++;
			DrawGraph(cell*7+cell/2 + fieldx*cell + movex + mobumovex,cell*7+cell/2 + fieldy*cell + movey + mobumovey,src[srcSelect + movecount/4%4],TRUE );
		}
	}
}

int Mobu::getnextx(){
	switch(movevec){
	case 3:
		return x + 1;
		break;
	case 4:
		return x - 1;
		break;
	default:
		return x;
		break;
	}
}

int Mobu::getnexty(){
	switch(movevec){
	case 1:
		return y + 1;
		break;
	case 2:
		return y - 1;
		break;
	default:
		return y;
		break;
	}
}

int Mobu::getx(){
	return x;
}

int Mobu::gety(){
	return y;
}

std::string Mobu::getWords(){
	return words;
}