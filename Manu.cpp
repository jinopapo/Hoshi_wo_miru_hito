#include "DxLib.h"
#include "Key.h"
#include "Menu.h"
#include <string>
#include <regex>

#define REIGAN 30
#define HAIPURUGAN 80
#define HERUBURASU 120
#define RAGURANJA 300
#define JAIROSP 420
#define PURAZUMAHOU 500
#define ABENJA 20
#define PARANOIYA 120
#define DESUTETA 200
#define START_STAGE 0
#define MAMUSU 1
#define DEUSU 2

void Menu::Initialize(int *ability,std::string p_name){
	src1 = LoadGraph("menu1.png");
	src2 = LoadGraph("key.png");
	src3 = LoadGraph("menu2.png");
	src4 = LoadGraph("menu3.png");
	src5 = LoadGraph("menu4.png");
	src6 = LoadGraph("menu5.png");
	src7 = LoadGraph("Menu6.png");
	src9 = LoadGraph("menu7.png");
	src8 = LoadGraph("battle3.png");
	src10 = LoadGraph("menu8.png");
	src11 = LoadGraph("menu9.png");
	src12 = LoadGraph("menu10.png");
	white = GetColor(255,255,255);
	menumode = false;
	words = "hogehoge";
	talk = false;
	status = false;
	state = *ability;
	level = *(ability + 1);
	hit = *(ability + 2);
	maxhit = *(ability + 3);
	saiko = *(ability + 4);
	maxsaiko = *(ability + 5);
	defense = *(ability + 6);
	speed = *(ability + 7);
	jukurenndo = *(ability + 8);
	keikenti = *(ability + 9);
	arm = *(ability + 10);
	guard = *(ability + 11);
	gold = *(ability + 12);
	pk = *(ability + 13);
	jump = *(ability + 14);
	telepathy = *(ability + 15);
	shield = *(ability + 16);
	nextPoint = *(ability + 17);
	name = p_name;
	word = new char[3]; 
	party = new Player[4];
	arms = new int[4];
	newLine = false;
	talkEnd = false;
	i = 0;
	j = 0;
	k = 0;
	l = 0;
	recovery = 0;
	rebirth = 0;
	cursor = 265;
	cursortarget = 0;
	shopping = 0;
	talknow = false;
	gathermode = false;
	gather = 0;
	seed_name = "hogehoge";
	itemmode = false;
	item_w = 0;
	chem = 0;
	trash = false;
}

void Menu::Initialize(){
}

void Menu::Update(std::string mobuwords,int count,int* ability,Player* player,int playercount,int nowstage,int nowplayer){
	party = player;
	talknow = false;

	//������X�e�[�W�ɗ����Ă邫�݂̂�ݒ肷��
	switch(nowstage){
	case START_STAGE:
		break;
	case MAMUSU:
		if(player[nowplayer].getPlayerx() == 10 && player[nowplayer].getPlayery() == 28){
			if(seed_name == "hogehoge"){
				menumode = true;
				gathermode = true;
				seed_name = "��ނ̂�"; 
			}
		}
		else if(player[nowplayer].getPlayerx() == 21 && player[nowplayer].getPlayery() == 30){
			if(seed_name == "hogehoge"){
				menumode = true;
				gathermode = true;
				seed_name = "�邭��̂�";
			}
		}
		else{
			seed_name = "hogehoge";
		}
		break;
	case DEUSU:
		if(player[nowplayer].getPlayerx() == 39 && player[nowplayer].getPlayery() == 17){
			if(seed_name == "hogehoge"){
				menumode = true;
				gathermode = true;
				seed_name = "�����̂�"; 
			}
		}
		else{
			seed_name = "hogehoge";
		}
		break;
	}

	//�A�C�e���\�����[�h
	if(itemmode){
		switch(item_w){
		case 0:
			if(Keyboard_Get(KEY_INPUT_UP) && cursor == 192){
				cursor = 160;
			}else if(Keyboard_Get(KEY_INPUT_DOWN) && cursor == 160){
				cursor = 192;
			}
			if(Keyboard_Get(KEY_INPUT_SPACE) == 1){
				if(cursor == 160){
					item_w = 1;
					item_list = player[nowplayer].getItemList();
					name = "��������";
				}
				else{
					item_w = 1;
					item_list = player[nowplayer].getSeedList();
					name = "������̂���";
				}
			}
			break;
		case 1:
			if(Keyboard_Get(KEY_INPUT_SPACE) == 1){
				itemmode = false;
				menumode = false;
				talknow = true;
				item_w = 0;
				cursor = 265;
			}
			break;
		}
	}


	//��\�����[�h
	if(drugmode && Keyboard_Get(KEY_INPUT_SPACE) == 1){
		drugmode = false;
		menumode = false;
		talknow = true;
		cursor = 265;
	}

	if(trash){
		if(player[nowplayer].getItemList().size() == 0){
			if(Keyboard_Get(KEY_INPUT_SPACE) == 1){
				trash = false;
			}
		}else{
			if(Keyboard_Get(KEY_INPUT_UP) == 1 && /*it != player[nowplayer].getItemList().begin()*/cursortarget > 0){
				//it--;
				cursortarget--;
			}else if(Keyboard_Get(KEY_INPUT_DOWN) == 1 && /*it != player[nowplayer].getItemList().end()*/cursortarget < player[nowplayer].getItemList().size() - 1){
				//it++;
				cursortarget++;
			}else if(Keyboard_Get(KEY_INPUT_SPACE) == 1){
				player[nowplayer].getItemList().erase(player[nowplayer].getItemList().begin() + cursortarget);
				trash = false;
				menumode = false;
				talknow = true;
				cursor = 265;
			}else if(Keyboard_Get(KEY_INPUT_ESCAPE) == 1){
				trash = false;
				menumode = false;
				talknow = true;
				cursor = 265;
			}
		}
	}


	//���̂ݍ̎惂�[�h
	if(gathermode){
		switch(gather){
		case 0:
			if(Keyboard_Get(KEY_INPUT_UP) == 1){
				cursor = 265;
			}else if(Keyboard_Get(KEY_INPUT_DOWN) == 1){
				cursor = 283;
			}else if(Keyboard_Get(KEY_INPUT_SPACE) == 1 && cursor == 265){
				gather = 1;
				gatherget = player[nowplayer].setSeed(seed_name);
			}else if(Keyboard_Get(KEY_INPUT_SPACE) == 1 && cursor == 283){
				menumode = false;
				gathermode =false;
				talknow = true;
				cursor = 265;
			}
			break;
		case 1:
			if(Keyboard_Get(KEY_INPUT_SPACE) == 1){
				menumode = false;
				gathermode =false;
				talknow = true;
				cursor = 265;
				gather = 0;
			}
			break;
		}
	}

	//��b���I���������̏���
	if(talkEnd && Keyboard_Get(KEY_INPUT_SPACE) == 1){
		talk = false;
		menumode = false;
		words = "hogehoge";
		menumode = false;
		talkEnd = false;
		newLine = false;
		talknow = true;
		l = 0;
	}


	//��b�̏���
	//�񕜃T�C�L�b�J�[�Ƙb���Ă��鎞
	if(talk && words == "nurse"){
		switch(recovery){
		case 0:
			if(Keyboard_Get(KEY_INPUT_SPACE) == 1 && cursor == 265){
				recovery = 1;
				cursor = 175;
			}
			else if(Keyboard_Get(KEY_INPUT_SPACE) == 1 && cursor == 283){
				recovery = 3;
			}else if(Keyboard_Get(KEY_INPUT_UP) == 1){
				cursor = 265;
			}else if(Keyboard_Get(KEY_INPUT_DOWN) == 1){
				cursor = 283;
			}
			break;
		case 1:
			if(Keyboard_Get(KEY_INPUT_UP) == 1 && cursortarget > 0){
				do{
					cursortarget--;
				}while(cursortarget > 0 && party[cursortarget-1].getDead() && party[cursortarget-1].getMate());
				cursor -= 24;
			}else if(Keyboard_Get(KEY_INPUT_DOWN) == 1 && cursortarget < playercount){
				BANPEI = cursortarget;
				do{
					cursortarget++;
				}while(cursortarget < playercount + 1 && party[cursortarget-1].getDead() && party[cursortarget-1].getMate());
				if(cursortarget == playercount + 1){
					cursortarget = BANPEI;
				}else{
					cursor += 24;
				}
			}else if(Keyboard_Get(KEY_INPUT_SPACE) == 1 && cursortarget != 0){
				party[cursortarget-1].hitdamage(party[cursortarget-1].gethit() - party[cursortarget-1].getmaxhit());
				party[cursortarget-1].useSaiko(party[cursortarget-1].getsaiko() - party[cursortarget-1].getmaxsaiko());
			}else if(Keyboard_Get(KEY_INPUT_SPACE) == 1){
				recovery = 2;
			}
			break;
		case 2:
			if(Keyboard_Get(KEY_INPUT_SPACE) == 1){
				recovery = 0;
				cursortarget = 0;
				cursor = 265;
				menumode = false;
				talknow = true;
				talk = false;
				words = "hogehoge";
			}
			break;
		case 3:
			if(Keyboard_Get(KEY_INPUT_SPACE) == 1){
				recovery = 4;
			}
			break;
		case 4:
			if(Keyboard_Get(KEY_INPUT_SPACE) == 1){
				recovery = 0;
				cursortarget = 0;
				cursor = 265;
				menumode = false;
				talknow = true;
				talk = false;
				words = "hogehoge";
			}
			break;
		}
	}
	//���
	else if(talk && words == "buyer"){
		/*switch(shopping){
		case 0:

		}*/
	}
	//���퉮�Ƙb���Ă��鏈��
	else if(talk && words == "buyer_arms"){
		switch(shopping){
		case 0:
			if(Keyboard_Get(KEY_INPUT_SPACE) == 1 && cursor == 265){
				shopping = 1;
				cursor = 70;
				switch(nowstage){
				case 1:
					arms[0] = REIGAN;
					arms[1] = HAIPURUGAN;
					arms[2] = HERUBURASU;
					arms[3] = RAGURANJA;
					break;
				}
				buyer_arms_words = "���Ȃ��@�Ɂ@���ɂ����@�ł��B";
			}else if(Keyboard_Get(KEY_INPUT_SPACE) == 1 && cursor == 283){
				shopping = 2;
			}
			else if(Keyboard_Get(KEY_INPUT_UP) == 1){
				cursor = 265;
			}else if(Keyboard_Get(KEY_INPUT_DOWN) == 1){
				cursor = 283;
			}
			break;
		case 1:
			if(Keyboard_Get(KEY_INPUT_UP) == 1 && cursor > 70){
				cursor -= 30;
			}
			else if(Keyboard_Get(KEY_INPUT_DOWN) == 1 && cursor <160 ){
				cursor += 30;
			}
			else if(Keyboard_Get(KEY_INPUT_SPACE) == 1){
				if(player[nowplayer].getgold() < arms[(cursor - 70)/30]){
					buyer_arms_words = "�����ˁ@���@����܂���B";
				}else{
					buyer_arms_words = "�܂��ǂ���B";
					player[nowplayer].shopping(-arms[(cursor - 70)/30]);
					player[nowplayer].setArms(arms[(cursor - 70)/30]);
				}
			}
			break;
		case 2:
			if(Keyboard_Get(KEY_INPUT_SPACE) == 1){
				talk = false;
				menumode = false;
				cursor = 265;
				words = "hogehoge";
				shopping = 0;
				talknow = true;
			}
			break;
		}
	}
	//�h��Ƙb���Ă��鎞
	else if(talk && words == "buyer_guard"){
		switch(shopping){
		case 0:
			if(Keyboard_Get(KEY_INPUT_SPACE) == 1 && cursor == 265){
				shopping = 1;
				cursor = 70;
				switch(nowstage){
				case 1:
					arms[0] = ABENJA;
					arms[1] = PARANOIYA;
					arms[2] = DESUTETA;
					break;
				}
				buyer_arms_words = "���Ȃ��@�Ɂ@���ɂ����@�ł��B";
			}else if(Keyboard_Get(KEY_INPUT_SPACE) == 1 && cursor == 283){
				shopping = 2;
			}
			else if(Keyboard_Get(KEY_INPUT_UP) == 1){
				cursor = 265;
			}else if(Keyboard_Get(KEY_INPUT_DOWN) == 1){
				cursor = 283;
			}
			break;
		case 1:
			if(Keyboard_Get(KEY_INPUT_UP) == 1 && cursor > 70){
				cursor -= 30;
			}
			else if(Keyboard_Get(KEY_INPUT_DOWN) == 1 && cursor <130 ){
				cursor += 30;
			}
			else if(Keyboard_Get(KEY_INPUT_SPACE) == 1){
				if(player[nowplayer].getgold() < arms[(cursor - 70)/30]){
					buyer_arms_words = "�����ˁ@���@����܂���B";
				}else{
					buyer_arms_words = "�܂��ǂ���B";
					player[nowplayer].shopping(-arms[(cursor - 70)/30]);
					player[nowplayer].setGuard(arms[(cursor - 70)/30]);
				}
			}
			break;
		case 2:
			if(Keyboard_Get(KEY_INPUT_SPACE) == 1){
				talk = false;
				menumode = false;
				cursor = 265;
				words = "hogehoge";
				shopping = 0;
				talknow = true;
			}
			break;
		}
	}
	//��܎t�Ƙb������
	else if(talk && words == "chemist"){
		switch(chem){
		case 0:
			if(Keyboard_Get(KEY_INPUT_SPACE) == 1){
				if(cursor == 265){
					if(player[nowplayer].getgold() < 15){
						chem = 7;
					}else if(player[nowplayer].getSeedList().size() < 3){
						chem = 8;
					}else{
						chem = 1;
						cursor = 25;
						item_list = player[nowplayer].getSeedList();
					}
				}else{
					cursor = 265;
					words = "hogehoge";
					menumode = false;
					talk = false;
					talknow = true;
				}
			}else if(Keyboard_Get(KEY_INPUT_UP) == 1){
				cursor = 265;
			}else if(Keyboard_Get(KEY_INPUT_DOWN) == 1){
				cursor = 283;
			}
			break;
		case 1:
			if(Keyboard_Get(KEY_INPUT_SPACE) == 1){
				chem_list.push_back(item_list[(cursor - 25)/20].name);
				item_list[(cursor - 25)/20].count--;
			}else if(Keyboard_Get(KEY_INPUT_UP) == 1 && cursor != 25){
				cursor += 20;
			}else if(Keyboard_Get(KEY_INPUT_DOWN) == 1 && (cursor - 25)/20 < item_list.size()){
				cursor -=20;
			}
			if(chem_list.size() == 3){
				chem = 2;
			}
			break;
		case 2:
			if(chem_list[0] == "���Ƃ̂�" && chem_list[1] == "�����̂�"  && chem_list[2] == "�����̂�"){
				drug_name = "�͂��ρ[";
				if(!player[nowplayer].setDrug(drug_name)){
					drug_name = "hogehoge";
				}
			}else if(chem_list[0] == "�����̂�" && chem_list[1] == "��ނ̂�"  && chem_list[2] == "�����̂�"){
				drug_name = "�������";
				if(!player[nowplayer].setDrug(drug_name)){
					drug_name = "hogehoge";
				}
			}else if(chem_list[0] == "�䂩�̂�" && chem_list[1] == "�����̂�"  && chem_list[2] == "��ނ̂�"){
				drug_name = "��ǂ����";
				if(!player[nowplayer].setDrug(drug_name)){
					drug_name = "hogehoge";
				}
			}else if(chem_list[0] == "�����̂�" && chem_list[1] == "�����̂�"  && chem_list[2] == "�邭�̂�"){
				drug_name = "��ǂ�";
				if(!player[nowplayer].setDrug(drug_name)){
					drug_name = "hogehoge";
				}
			}else if(chem_list[0] == "�����̂�"){
				if(chem_list[1] == "�邭�̂�" && chem_list[2] == "�����̂�"){
					drug_name = "������";
					if(!player[nowplayer].setDrug(drug_name)){
						drug_name = "hogehoge";
					}
				}
				else if(chem_list[1] == "�����̂�" && chem_list[2] == "��ނ̂�"){
					drug_name = "�͂���";
					if(!player[nowplayer].setDrug(drug_name)){
						drug_name = "hogehoge";
					}				}
			}else if(chem_list[0] == "��ނ̂�"){
				if(chem_list[1] == "�邭�̂�" && chem_list[2] == "�����̂�"){
					drug_name = "���肤";
					if(!player[nowplayer].setDrug(drug_name)){
						drug_name = "hogehoge";
					}				}
				else if(chem_list[1] == "�����̂�" && chem_list[2] == "�邭�̂�"){
					drug_name = "��΂���";
					if(!player[nowplayer].setDrug(drug_name)){
						drug_name = "hogehoge";
					}
				}
			}else{
				drug_name = "hoge";
			}
			chem = 3;
			break;
		case 3:
			if(Keyboard_Get(KEY_INPUT_SPACE) == 1){
				menumode = false;
				talk = false;
				talknow = true;
				words = "hogehoge";
				cursor = 265;
				chem = 0;
			}
			break;
		case 7:
			if(Keyboard_Get(KEY_INPUT_SPACE) == 1){
				menumode = false;
				talk = false;
				talknow = true;
				words = "hogehoge";
				cursor = 265;
				chem = 0;
			}
			break;
		case 8:
			if(Keyboard_Get(KEY_INPUT_SPACE) == 1){
				menumode = false;
				talk = false;
				talknow = true;
				words = "hogehoge";
				cursor = 265;
				chem = 0;
			}
			break;
		}
	}
	//�h�����Ƙb�����Ƃ�
	else if(talk && words == "rebirth"){
		switch(rebirth){
		case 0:
			if(Keyboard_Get(KEY_INPUT_SPACE) == 1 && cursor == 265){
				rebirth = 1;
				cursor = 175;
			}
			else if(Keyboard_Get(KEY_INPUT_SPACE) == 1 && cursor == 283){
				rebirth = 3;
			}else if(Keyboard_Get(KEY_INPUT_UP) == 1){
				cursor = 265;
			}else if(Keyboard_Get(KEY_INPUT_DOWN) == 1){
				cursor = 283;
			}
			break;
		case 1:
			drug_list = party[nowplayer].getDrugList();
			for(i = 0;i < drug_list.size();i++){
				if(drug_list[i].name == "��΂���"){
					break;
				}
			}
			if(drug_list.size() == 0 || i == drug_list.size()){
				rebirth = 3;
			}else if(Keyboard_Get(KEY_INPUT_UP) == 1 && cursortarget > 0){
				do{
					cursortarget--;
				}while(cursortarget > 0 && !party[cursortarget-1].getDead());
				cursor -= 24;
			}else if(Keyboard_Get(KEY_INPUT_DOWN) == 1 && cursortarget < playercount){
				do{
					cursortarget++;
				}while(cursortarget < playercount && !party[cursortarget-1].getDead());
				cursor += 24;
			}else if(Keyboard_Get(KEY_INPUT_SPACE) == 1 && cursortarget != 0){
				party[cursortarget-1].hitdamage(party[cursortarget-1].gethit() - party[cursortarget-1].getmaxhit());
				party[cursortarget-1].useSaiko(party[cursortarget-1].getsaiko() - party[cursortarget-1].getmaxsaiko());
				drug_list[i].count--;
				rebirth = 2;
			}else if(Keyboard_Get(KEY_INPUT_SPACE) == 1){
				rebirth = 2;
			}
			break;
		case 2:
			if(Keyboard_Get(KEY_INPUT_SPACE) == 1){
				rebirth = 0;
				cursortarget = 0;
				cursor = 265;
				menumode = false;
				talknow = true;
				talk = false;
				words = "hogehoge";
			}
			break;
		case 3:
			if(Keyboard_Get(KEY_INPUT_SPACE) == 1){
				rebirth = 0;
				cursortarget = 0;
				cursor = 265;
				menumode = false;
				talknow = true;
				talk = false;
				words = "hogehoge";
			}
			break;
		}		
	}
	//��b�ŉ��s���K�v�Ȏ�
	else if(talk && Keyboard_Get(KEY_INPUT_SPACE) == 1){
		newLine = true;
	}


	//�X�e�[�^�X�m�F��ʂ̏I������
	if(status && Keyboard_Get(KEY_INPUT_SPACE) == 1){
		status = false;
		menumode = false;
		talknow = true;
	}


	//���j���[�̃J�[�\���ړ��ƃ��[�h�I��
	if(menumode && !talk && !status && !itemmode && !drugmode && !trash){
		if(Keyboard_Get(KEY_INPUT_DOWN) == 1 && y < 96){
			y += 32;
		}
		else if(Keyboard_Get(KEY_INPUT_UP) == 1 && y > 32){
			y -= 32;
		}
		else if(Keyboard_Get(KEY_INPUT_RIGHT) == 1 && x == 16){
			x = 112;
		}
		else if(Keyboard_Get(KEY_INPUT_LEFT) == 1 && x == 112){
			x = 16;
		}
		//��b���[�h�N��
		else if(Keyboard_Get(KEY_INPUT_SPACE) == 1 && x == 16 && y == 32){
			words = mobuwords;
			talk = true;
			if(words == "hogehoge"){
				talkEnd = true;
			}
		}
		else if(Keyboard_Get(KEY_INPUT_SPACE) == 1 && x == 112 && y == 64){
			cursortarget = 0;
			cursor = 160;
			trash = true;
			if(player[nowplayer].getItemList().size() > 0){
				item_list = player[nowplayer].getItemList();
				//it = player[nowplayer].getItemList().begin();
			}
			cursortarget = 0;
		}
		//�A�C�e���\�����[�h�N��
		else if(Keyboard_Get(KEY_INPUT_SPACE) == 1 && x == 112 && y == 96){
			itemmode = true;
			cursor = 160;
		}
		//��\�����[�h�N��
		else if(Keyboard_Get(KEY_INPUT_SPACE) == 1 && x == 16 && y == 64){
			drugmode =true;
			drug_list = player[nowplayer].getDrugList();
		}
		//�X�e�[�^�X�\�����[�h�N��
		else if(Keyboard_Get(KEY_INPUT_SPACE) == 1 && x == 16 && y == 96){
			status = true;
			player[nowplayer].getability();
			state = *ability;
			level = *(ability +1);
			hit = *(ability + 2);
			maxhit = *(ability + 3);
			saiko = *(ability + 4);
			maxsaiko = *(ability + 5);
			defense = *(ability + 6);
			speed = *(ability + 7);
			jukurenndo = *(ability + 8);
			keikenti = *(ability + 9);
			arm = *(ability + 10);
			guard = *(ability + 11);
			gold = *(ability + 12);
			pk = *(ability + 13);
			jump = *(ability + 14);
			telepathy = *(ability + 15);
			shield = *(ability + 16);
			nextPoint = *(ability + 17);
			name = player[nowplayer].getname();
		}
	}


	//���j���[�̋N��
	if(Keyboard_Get(KEY_INPUT_SPACE) == 1 && !menumode && !talk && !status && count != 0 && !talknow){
		menumode = true;
		x=16;
		y=32;
	}
	//���j���[�̏I��
	else if(Keyboard_Get(KEY_INPUT_ESCAPE) >= 1 /*&& !talk*/){
		menumode = false;
		talk = false;
		status = false;
		gathermode = false;
		itemmode = false;
		drugmode = false;
		words = "hogehoge";
		cursor = 265;
		recovery = 0;
		shopping = 0;
		cursortarget = 0;
		item_w = 0;
	}
}

void Menu::Update(){
}

void Menu::Draw(){
	extern int cell;
	if(menumode && !gathermode){
		DrawGraph(0,0,src1,TRUE);
		DrawGraph(x,y,src2,TRUE);
		DrawFormatString( 32, 0, white, "�b�n�l�l�`�m�c");
		DrawFormatString( 32, 32,white, "�͂Ȃ�");
		DrawFormatString(32,64,white,"������");
		DrawFormatString(32,96,white,"������");
		DrawFormatString(128,32,white,"�d�r�o");
		DrawFormatString(128,64,white,"���Ă�");
		DrawFormatString(128,96,white,"��������");
		if(words != "hogehoge"){
			DrawGraph(0,342,src3,TRUE);
			if(words == "nurse"){
				switch(recovery){
				case 0:
					DrawGraph(330,250,src7,TRUE);
					DrawFormatString(40,382,white,"�݂Ȃ���@����ɂ��́B");
					DrawFormatString(40,400,white,"�킽���̂��Ƃ́@���͂Ȃ����܂������H");
					DrawFormatString(362,267,white,"�͂�");
					DrawFormatString(362,285,white,"������");
					DrawGraph(340,cursor,src2,TRUE);
					break;
				case 1:
					DrawGraph(300,150,src8,TRUE);
					DrawFormatString(356,174,white,"�Ȃ����Ȃ�");
					j = 0;
					for(i = 0;i < 4;i++){
						if(party[i].getMate() && !party[i].getDead()){
							DrawFormatString(356,198 + 24 * j,white,party[i].getname().c_str());
							j++;
						}
					}
					DrawGraph(324,cursor,src2,TRUE);
					DrawFormatString(40,382,white,"����@���@�����ӂ��@�����܂����H�B");
					break;
				case 2:
					DrawFormatString(40,382,white,"�܂��@�ǂ���");
					break;
				case 3:
					DrawFormatString(40,382,white,"�킽���́@�̂���傭�́A�@���[��ǁ@�ł��B");
					DrawFormatString(40,400,white,"�킽���́@�킩���Ȃ��̂�");
					DrawFormatString(40,418,white,"���Ȃ��́@�Ȃ��܂Ɂ@�Ȃ�܂���B");
					DrawFormatString(40,436,white,"�������@�����������炾���@�Ȃ������Ƃ́A");
					DrawFormatString(40,454,white,"�ł��܂��B");
					break;
				case 4:
					DrawFormatString(40,382,white,"���[��CITY�Ɂ@�킽���Ɓ@���Ȃ���������A");
					DrawFormatString(40,400,white,"���@����Ȃ̂����A�@�Ƃ炦���Ă����B");
					DrawFormatString(40,418,white,"���̂��Ȃ�@�����Ɓ@�Ȃ��܂Ɂ@�Ȃ��āA");
					DrawFormatString(40,436,white,"�����ł��傤�B");
					break;				
				}
			}
			else if(words == "rebirth"){
				switch(rebirth){
				case 0:
					DrawGraph(330,250,src7,TRUE);
					DrawFormatString(40,382,white,"���܂��́A�͂��߂ā@�����Ɂ@�����̂��@�H");
					DrawFormatString(362,267,white,"�͂�");
					DrawFormatString(362,285,white,"������");
					DrawGraph(340,cursor,src2,TRUE);
					break;
				case 1:
					DrawGraph(300,150,src8,TRUE);
					DrawFormatString(356,174,white,"�Ȃ����Ȃ�");
					k = 0;
					for(j = 0;j < 4;j++){
						if(party[i].getMate() && party[i].getDead()){
							DrawFormatString(356,198 + 24 * k,white,party[j].getname().c_str());
							k++;
						}
					}
					DrawGraph(324,cursor,src2,TRUE);
					DrawFormatString(40,382,white,"����@���@���������炷�H�B");
					break;
				case 2:
					DrawFormatString(40,382,white,"�܂��@�ǂ���");
					break;
				case 3:
					DrawFormatString(40,382,white,"��΂���@�́@��������A�킵�́@�Ƃ����");
					DrawFormatString(40,400,white,"�����Ă���΁@���񂾂��̂��A���������炷");
					DrawFormatString(40,418,white,"���Ƃ��ł���B");
					break;		
				}
			}else if(words == "buyer_arms"){
				switch(shopping){
				case 0:
					DrawGraph(330,250,src9,TRUE);
					DrawGraph(345,cursor,src2,TRUE);	
					DrawFormatString(40,382,white,"��������Ⴂ�܂�");
					DrawFormatString(40,400,white,"�܂��@����@�����ꂽ�@�Ԃ��@���A�@����܂���B");
					DrawFormatString(367,267,white,"����");
					DrawFormatString(367,285,white,"����Ȃ�");
					break;
				case 1:
					DrawGraph(250,50,src10,TRUE);
					DrawGraph(270,cursor,src2,TRUE);
					DrawFormatString(40,382,white,buyer_arms_words.c_str());
					for(i = 0;i < 4;i++){
						switch(arms[i]){
						case REIGAN:
							DrawFormatString(290,70 + 30*i,white,"�ꂢ����         30");
							break;
						case HAIPURUGAN:
							DrawFormatString(290,70 + 30*i,white,"�͂��Ղ邪��     80");
							break;
						case HERUBURASU:
							DrawFormatString(290,70 + 30*i,white,"�ւ�Ԃ炷       120");
							break;
						case RAGURANJA:
							DrawFormatString(290,70 + 30*i,white,"�炮��񂶂�     300");
							break;
						}
					}
					break;
				case 2:
					DrawFormatString(40,382,white,"�܂��@�ǂ���");
					break;
				}
			}else if(words == "buyer_guard"){
				switch(shopping){
				case 0:
					DrawGraph(330,250,src9,TRUE);
					DrawGraph(345,cursor,src2,TRUE);	
					DrawFormatString(40,382,white,"��������Ⴂ�܂�");
					DrawFormatString(40,400,white,"�܂��@����@�����ꂽ�@�ڂ����@���A�@����܂���B");
					DrawFormatString(367,267,white,"����");
					DrawFormatString(367,285,white,"����Ȃ�");
					break;
				case 1:
					DrawGraph(250,50,src10,TRUE);
					DrawGraph(270,cursor,src2,TRUE);
					DrawFormatString(40,382,white,buyer_arms_words.c_str());
					for(i = 0;i < 3;i++){
						switch(arms[i]){
						case ABENJA:
							DrawFormatString(290,70 + 30*i,white,"���ׂ񂶂�       20");
							break;
						case PARANOIYA:
							DrawFormatString(290,70 + 30*i,white,"�ς�̂���       100");
							break;
						case DESUTETA:
							DrawFormatString(290,70 + 30*i,white,"�ł��ā[��       200");
							break;
						}
					}
					break;
				case 2:
					DrawFormatString(40,382,white,"�܂��@�ǂ���");
					break;
				}
			}
			//��܎t�̉�b�̕`��
			else if(words == "chemist"){
				switch(chem){
				case 0:
					DrawGraph(330,250,src9,TRUE);
					DrawGraph(345,cursor,src2,TRUE);
					DrawFormatString(40,382,white,"��������Ⴂ");
					DrawFormatString(40,400,white,"�P�T���[��ǁ@�Ł@������@���A�@���傤�������܂�");
					DrawFormatString(362,267,white,"�͂炤");
					DrawFormatString(362,285,white,"�͂��Ȃ�");
					break;
				case 1:
					DrawGraph(310,0,src12,TRUE);
					DrawGraph(335,cursor,src2,TRUE);
					DrawFormatString(360,5,white,"������̂���");
					DrawFormatString(40,382,white,"%d�߁@�́@������̂��Ɓ@���@�����ł��������B",chem_list.size() + 1);
					break;
				case 3:
					if(drug_name == "hoge"){
						DrawFormatString(40,382,white,"�Ȃɂ��@�ł��܂���ł����B");
					}
					else if(drug_name == "hogehoge"){
						DrawFormatString(40,382,white,"������@���@�����ς��ł��B");
					}
					else{
						DrawFormatString(40,382,white,"%s�@���@�ł��܂����B",drug_name.c_str());
					}
					break;
				case 7:
					DrawFormatString(40,382,white,"�����ˁ@���@����܂���B");
					break;
				case 8:
					DrawFormatString(40,382,white,"������̂��Ɓ@���@�R�@�Ȃ��Ƃ���܂���B");
					break;
				}
			}
			else{
				if(newLine && k == 4){
					j = l;
					k = 0;
					newLine = false;
				}
				while(j < (int)words.length() && k < 5){
					switch(words[j]){
					case 'B':
						k++;
						j++;
						i = 0;
						break;
					default:
						if(i ==24 ){
							i = 0;
							k++;
						}
						word[0] = words[j];
						word[1] = words[j+1];
						word[2] = '\0';
						j += 2;
						DrawFormatString(40 + 18*i,382 + 18*k,white,word);
						i++;
						l = j + 1;
					}
				}
				if(j >= (int)words.length()){
					talkEnd = true;
					k = 0;
					j = 0;
					i = 0;
				}
			}
		}else if(talk){
			DrawGraph(0,342,src3,TRUE);
			DrawFormatString(40,382,white,"����@���@���܂���B");
		}

		//�A�C�e���\�����[�h
		if(itemmode){
			DrawGraph(0,128,src11,TRUE);
			DrawGraph(16,cursor,src2,TRUE);
			DrawFormatString(64,128,white,"���񂽂�");
			DrawFormatString(32,160,white,"��������");
			DrawFormatString(32,192,white,"������̂���");
			if(item_w == 1){
				if(item_list.size() != 0){
					DrawGraph(300,5,src4,TRUE);
					DrawFormatString(350,10,white,name.c_str());
					for(i = 0;i < item_list.size();i++){
						DrawFormatString(320,45 + 35*i,white,item_list[i].name.c_str());
						DrawFormatString(450,45 + 35*i,white,"%d",item_list[i].count);
					}
				}
				else{
					DrawGraph(0,342,src3,TRUE);
					DrawFormatString(40,382,white,"�Ȃɂ��@�����Ă��܂���B");
				}
			}
		}

		//��\�����[�h
		if(drugmode){
			if(drug_list.size() != 0){
				DrawGraph(300,5,src4,TRUE);
				DrawFormatString(350,10,white,name.c_str());
				for(i = 0;i < drug_list.size();i++){
					DrawFormatString(320,45 + 35*i,white,drug_list[i].name.c_str());
					DrawFormatString(450,45 + 35*i,white,"%d",drug_list[i].count);
				}
			}
			else{
				DrawGraph(0,342,src3,TRUE);
				DrawFormatString(40,382,white,"�Ȃɂ��@�����Ă��܂���B");
			}			
		}

		if(trash){
			if(item_list.size() != 0){	
				DrawGraph(300,5,src4,TRUE);
				DrawGraph(320,45 + 35 * cursortarget,src2,TRUE);
				DrawFormatString(350,10,white,"�ǂ�����Ă܂����H");
				for(i = 0;i < item_list.size();i++){
					DrawFormatString(340,45 + 35*i,white,item_list[i].name.c_str());
					DrawFormatString(450,45 + 35*i,white,"%d",item_list[i].count);
				}
			}
			else{
				DrawGraph(0,342,src3,TRUE);
				DrawFormatString(40,382,white,"�Ȃɂ��@�����Ă��܂���B");
			}
		}

		//�X�e�[�^�X�\�����[�h
		if(status){
			DrawGraph(300,5,src4,TRUE);
			DrawGraph(10,330,src5,TRUE);			
			DrawGraph(10,80,src6,TRUE);
			DrawFormatString(375,10,white,name.c_str());
			switch(state){
			case 0:
				DrawFormatString(320,45,white,"�@�@�@���炾:�ӂ�");
				break;
			}
			DrawFormatString(320,80,white,"�@�@�@��ׂ�:%d",level);
			DrawFormatString(320,115,white,"�@�@�Ђ��Ɨ�:%d",hit);
			DrawFormatString(320,150,white,"�l�`�w�Ђ���:%d",maxhit);
			DrawFormatString(320,185,white,"�@�@��������:%d",saiko);
			DrawFormatString(320,220,white,"�l�`�w������:%d",maxsaiko);
			DrawFormatString(320,255,white,"�@�ڂ������:%d",defense);
			DrawFormatString(320,290,white,"�@�@���΂₳:%d",speed);
			DrawFormatString(320,325,white,"���キ����:%d",jukurenndo);
			DrawFormatString(320,360,white,"�@��������:%d",keikenti);
			DrawFormatString(320,395,white,"�@�@�m�d�w�s:%d",nextPoint);
			switch(arm){
			case 0:
				DrawFormatString(30,350,white,"�@�@�Ԃ�:�Ȃɂ��Ȃ�");
				break;
			}
			switch(guard){
			case 0:
				DrawFormatString(30,385,white,"�@�ڂ���:�Ȃɂ��Ȃ�");
				break;
			}
			DrawFormatString(30,420,white,"���[���:%d",gold);
			DrawFormatString(65,83,white,"�d�r�o");
			DrawFormatString(30,120,white,"�Ԃꂢ���@%d",pk);
			DrawFormatString(30,165,white,"�����Ձ@%d",jump);
			DrawFormatString(30,210,white,"�Ă�ς��@%d",telepathy);
			DrawFormatString(30,255,white,"���[��ǁ@%d",shield);
		}

	//���̂ݍ̎惂�[�h
	}else if(gathermode){
		DrawGraph(0,342,src3,TRUE);
		switch(gather){			
		case 0:
			DrawGraph(330,250,src7,TRUE);
			DrawFormatString(40,382,white,"%s���@�Ȃ��Ă��܂��B",seed_name.c_str());
			DrawFormatString(40,400,white,"�Ƃ�܂����H");
			DrawFormatString(362,267,white,"�͂�");
			DrawFormatString(362,285,white,"������");
			DrawGraph(340,cursor,src2,TRUE);
			break;
		case 1:
			if(gatherget){
				DrawFormatString(40,382,white,"%s���@�Ăɂ��ꂽ�B",seed_name.c_str());
			}
			else{
				DrawFormatString(40,382,white,"�����@���Ă܂���B",seed_name.c_str());
			}
			break;
		}
	}
}


bool Menu::getMenu(){
	return menumode;
}

bool Menu::gettalk(){
	return talk;
}

Menu::Menu(){
}

void Menu::Finalize(){
	delete [] word; 
	delete [] party;
	delete [] arms;
}