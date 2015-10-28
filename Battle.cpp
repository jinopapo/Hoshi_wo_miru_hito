#include "Battle.h"
#include "DxLib.h"
#include "Enemy.h"
#include "Key.h"
#include <new>
#include <time.h>
#define STANDBY 90
#define PLAYER_STANDBY 99
#define PLAYER_TARGET_SELECT 80
#define PLAYER_ESP_STANDBY 92
#define ESP_LESS 98
#define PLAYER_ATTACK 91
#define ENEMY_ATTACK 93
#define WIN 94
#define SELECT_STATE 95
#define STATE_KARIU 96
#define LOSE 97
#define STATE 89
#define WIN_ESC 88
#define PLAYER_SELECT_TELEPORT 87
#define SELECT_LIST 86
#define CURSOR_E 24
#define FAINT 5
#define FSHIELD 6
#define SHIELD 7
#define SSHIELD 4
#define MSHIELD 2
#define MINDKILL 3
#define CONFUSION 1

void Battle::Initialize(){
	srand((unsigned)time( NULL ));
	src = LoadGraph("Battle.png");
	src1 = LoadGraph("battle1.png");
	src2 = LoadGraph("battle2.png");
	src3 = LoadGraph("key.png");
	src4 = LoadGraph("battle3.png");
	src5 = LoadGraph("battle4.png");
	src6 = LoadGraph("battle5.png");
	src7 = LoadGraph("batke.png");
	src8 = LoadGraph("menu3.png");
	src9 = LoadGraph("menu4.png");
	src10 = LoadGraph("menu5.png");
	src11 = LoadGraph("battle6.png");
	hit = new int[4];
	for(i = 0;i < 4;i++){
		hit[i] = -1;
	}
	white = GetColor(255,255,255);
	encount  = false;
	enemy = new Enemy[8];
	esp = new bool[8];
	for(i = 0;i < 8;i++){
		esp[i] = false;
	}
	//������o���l�A�����ˁA�h��A�U���AHP�A����U���̗L���A�푰
	Enemy janku = Enemy(LoadGraph("janku.png"),"�����",3,5,0,6,2,false,2);
	Enemy hurakka = Enemy(LoadGraph("hurakka.png"),"�ӂ����",5,6,0,8,3,false,2);
	Enemy saramanndo = Enemy(LoadGraph("saramanndo.png"),"����܂��",5,7,0,10,4,true,4);
	Enemy beruzebabu = Enemy(LoadGraph("beruzebabu.png"),"�ׂ邺�ł�",6,8,1,11,5,true,4);
	Enemy ramuji = Enemy(LoadGraph("ramuji.png"),"��ނ�",7,10,1,11,6,false,1);
	Enemy cheisa = Enemy(LoadGraph("cheisa.png"),"��������",10,14,2,12,8,true,1);
	Enemy kurasha = Enemy(LoadGraph("kurasha.png"),"���������",12,14,2,12,10,true,1);
	Enemy hukkatu = Enemy(LoadGraph("hukkatu.png"),"�ӂ�������",14,18,2,12,12,true,3);
	enemy[0] = janku;
	enemy[1] = hurakka;
	enemy[2] = saramanndo;
	enemy[3] = beruzebabu;
	enemy[4] = ramuji;
	enemy[5] = cheisa;
	enemy[6] = kurasha;
	enemy[7] = hukkatu;
	count = 0;
	window = STANDBY;
	cursor = 174;
	cursor1 = 174;
	playertarget = 0;
	name = "";
	enemytarget = -2;
	draw = false;
	playercount = 0;
	battle = false;
	encountenemy = new Enemy[4];
	point = 0;
	gold = 0;
	dead = false;
	guard = false;
	dead_end =false;
	nowplayer = 0;
	use = 0;
	power = 0;
	p_src =new int[4];
	for(i = 0;i < 4;i++){
		p_src[i] = 0; 
	}
	mp = 0;
	attack_end = false;
	power_select = false;
	tele = false;
	mem = 0;
	BANPEI = -1;
	playertarget = 0;
	for(i = 0;i < 4;i++){
		def[i] = 0; 
	}
	for(i = 0;i < 4;i++){
		sdef[i] = 0; 
	}	
}

bool Battle::include(int i){
	for(int a = 0;a < p_list.size();a++){
		if(p_list[a] == i){
			return false;
		}
	}
	return true;
}

void Battle::Update(Player* player,int nowStage,int count,int member){
	//�G���J�E���g���̒���
	if(!encount){
		battle = true;
		enemycount = rand() % 20;
		if(enemycount < 12){
			enemycount = 1;
		}else if(enemycount < 18){
			enemycount = 2;
		}else if(enemycount < 19){
			enemycount = 3;
		}else if(enemycount < 20){
			enemycount = 4;
		}
	//�o������G�̐ݒ�
		switch(nowStage){
		case 0:
			for(i = 0;i < enemycount;i++){
				encountenemy[i] = enemy[rand() % 8];
				encountenemy[i].Initialize(32 + i* 112 + i/2 * 16 ,16);
			}
			break;
		}
		for(i = 0;i < 4;i++){
			if(player[i].getMate()){
				p_src[i] = player[i].getSrc();
			}
		}
		party = player;
		encount = true; 
		tele = false;
	}
	//�퓬���̃��[�v
	switch(window){
	case STANDBY:
		if(encount && Keyboard_Get(KEY_INPUT_SPACE) >= 1){
			if(member == 1){
				window = SELECT_STATE;
			}else{
				window = SELECT_LIST;
				p_list.clear();
				playertarget = 0;
			}
		}
		break;
	case SELECT_LIST:
		if(mem == 0){
			for(int a = 0;a < 4;a++){
				if(party[a].getMate() && !party[a].getEsc() && !party[a].getDead()){
					mem++;
				}
			}
			while(party[playertarget].getEsc() || party[playertarget].getDead()){
				playertarget++;
			}
		}
		if(Keyboard_Get(KEY_INPUT_UP) == 1 && playertarget > 0 /*&& BANPEI == playertarget*/){
			BANPEI = playertarget;
			do{
				playertarget--;
			}while(playertarget > 0 && (party[playertarget].getDead() || !party[playertarget].getMate() || player[nowplayer].getEsc() || !include(playertarget)));
			if(playertarget == 0 && (party[playertarget].getDead() || party[playertarget].getEsc() || !include(playertarget))){
				playertarget =BANPEI;
			}else{
				cursor -= 24;
			}
		}else if(Keyboard_Get(KEY_INPUT_DOWN) == 1 && playertarget < 4/* && BANPEI == playertarget*/){
			BANPEI = playertarget;
			do{
				playertarget++;
			}while(playertarget < 4 && (party[playertarget].getDead() || player[nowplayer].getEsc() || !party[playertarget].getMate() || !include(playertarget)));
			if(playertarget == 4){
				playertarget = BANPEI;
			}else{
				cursor += 24;
			}
		}else if(Keyboard_Get(KEY_INPUT_SPACE) == 1){
			cursor = 174;
			p_list.push_back(playertarget);
			playercount++;
			if(playercount == mem){
				window = SELECT_STATE;
				nowplayer = p_list[0];
				playercount = 0;
			}
			for(playertarget = 0;playertarget < 4;playertarget++){
				if(include(playertarget)){
					break;
				}
			}
		}
		break;
	case SELECT_STATE:
		/*while(!player[nowplayer].getMate() || player[nowplayer].getDead() || player[nowplayer].getEsc()){
			nowplayer++;
		}*/
		switch(player[nowplayer].getstate()){
		case 0:
			window = PLAYER_STANDBY;
			break;
		case 1:
			error_mesage = "�͂т傤���ł������Ȃ�";
			name = player[nowplayer].getname();
			window = STATE_KARIU;
			break;
		}
		break;
	case STATE_KARIU:
		if(Keyboard_Get(KEY_INPUT_SPACE) == 1){
			playercount++;
			if(playercount == p_list.size()){
				mem = 0;
				playercount = 0;
				enemytarget = 0;
				p_list.clear();
				window = ENEMY_ATTACK;
				while(enemytarget < enemycount  && (encountenemy[enemytarget].getDead() || encountenemy[enemytarget].getEsc())){
					enemytarget++;
				}
			}else{
				nowplayer = p_list[playercount];
				window = SELECT_STATE;
			}
			/*window = SELECT_STATE;
			do{
				nowplayer++;
				if(nowplayer > 3){
					window = ENEMY_ATTACK;
					enemytarget = 0;
					while(enemytarget < enemycount  && encountenemy[enemytarget].getDead()){
						enemytarget++;
					}
					break;
				}
			}while((!player[nowplayer].getMate() || player[nowplayer].getDead()) && nowplayer < 4);*/
		}
		break;
	case PLAYER_STANDBY:
		if(Keyboard_Get(KEY_INPUT_DOWN) == 1 && cursor < 270){
			cursor += 24;
		}
		else if(Keyboard_Get(KEY_INPUT_UP) == 1 && cursor > 174){
			cursor -= 24;
		}
		else if(Keyboard_Get(KEY_INPUT_SPACE) == 1 && cursor == 198){
			window = PLAYER_TARGET_SELECT;
			playeraction = "��������";
			cursor1 = cursor;
			cursor = 174;
			playertarget = 0;
			while(encountenemy[playertarget].getDead() || encountenemy[playertarget].getEsc()){
				cursor += 24;
				playertarget++;
			}
		}
		else if(Keyboard_Get(KEY_INPUT_SPACE) == 1 && cursor == 174){
			if(player[nowplayer].getlevel() != 0 || player[nowplayer].getsaiko() <10){
				cursor1 = cursor;
				cursor = 174;
				window = PLAYER_ESP_STANDBY;
				power = 0;
				playertarget = 0;
				cursor = 90;
				esp = player[nowplayer].getesp();			
			}else{
				window =ESP_LESS;
			}

		}
		else if(Keyboard_Get(KEY_INPUT_SPACE) == 1 && cursor == 222){
			window = PLAYER_ATTACK;
			name = player[nowplayer].getname();
			guard = true;
			enemytarget = 0;
		}
		else if(Keyboard_Get(KEY_INPUT_SPACE) == 1 && cursor == 270){
			state = player[nowplayer].getstate();
			level = player[nowplayer].getlevel();
			hit_p = player[nowplayer].gethit();
			maxhit = player[nowplayer].getmaxhit();;
			saiko = player[nowplayer].getsaiko();
			maxsaiko = player[nowplayer].getmaxsaiko();
			defense = player[nowplayer].getdefense();
			speed = player[nowplayer].getspeed();
			jukurenndo = player[nowplayer].getjukurenndo();
			keikenti = player[nowplayer].getkeikenti();
			arm = player[nowplayer].getarms();
			guard_p = player[nowplayer].getgold();
			gold_p = player[nowplayer].getguard();
			pk = player[nowplayer].getpk();
			jump = player[nowplayer].getjump();
			telepathy = player[nowplayer].gettelepathy();
			shield = player[nowplayer].gettelepathy();
			nextPoint = player[nowplayer].getNextPoint();
			name = player[nowplayer].getname();
			window = STATE;
		}
		break;
	case STATE:
		if(Keyboard_Get(KEY_INPUT_SPACE) == 1){
			window = PLAYER_STANDBY;
		}
		break;
	case ESP_LESS:
		if(Keyboard_Get(KEY_INPUT_SPACE) == 1){
			window = PLAYER_STANDBY;
		}
		break;
	case PLAYER_ESP_STANDBY:
		if(!power_select){
			if(Keyboard_Get(KEY_INPUT_DOWN) == 1 && playertarget < 7 && esp[playertarget + 1]){
				cursor += CURSOR_E;
				playertarget++;
			}
			else if(Keyboard_Get(KEY_INPUT_UP) == 1 &&  playertarget != 0){
				playertarget--;
				cursor -= CURSOR_E;
			}
			else if(Keyboard_Get(KEY_INPUT_SPACE) == 1){
				switch(playertarget){
				case 0:
					switch(nowplayer){
					case 0:
						playeraction = "�������ځ[��";
						break;
					case 1:
						playeraction = "�Ă�ہ[��";
						break;
					case 2:
						playeraction = "���[���";
						break;
					case 3:
						playeraction = "�Ă�ς�";
						break;
					}
					break;
				case 1:
					switch(nowplayer){
					case 0:
						playeraction = "�������͂肯�[��";
						break;
					case 1:
						playeraction = "�΂ǂĂ�ہ[��";
						break;
					case 2:
						playeraction = "�����イ���˂�";
						break;
					case 3:
						playeraction = "�łӂ܂����";
						break;
					}
					break;
				case 2:
					switch(nowplayer){
					case 0:
						playeraction = "�ӂ���������[";
						break;
					case 1:
						playeraction = "�΂ǂ����[";
						break;
					case 2:
						playeraction = "�΂ǂ��[���";
						break;
					case 3:
						playeraction = "���ӂ܂����";
						break;
					}
					break;
				case 3:
					switch(nowplayer){
					case 0:
						playeraction = "�Ă�ہ[��";
						break;
					case 1:
						playeraction = "���[���";
						break;
					case 2:
						playeraction = "�Ă�ς�";
						break;
					case 3:
						playeraction = "�������ځ[��";
						break;
					}
					break;
				case 4:
					switch(nowplayer){
					case 0:
						playeraction = "�ӂ�����������";
						break;
					case 1:
						playeraction = "�΂ǂЁ[��";
						break;
					case 2:
						playeraction = "�˂����[���";
						break;
					case 3:
						playeraction = "�܂���ǂ���";
						break;
					}
					break;
				case 5:
					switch(nowplayer){
					case 0:
						playeraction = "�΂ǂĂ�ہ[��";
						break;
					case 1:
						playeraction = "�����イ���˂�";
						break;
					case 2:
						playeraction = "�łӂ܂����";
						break;
					case 3:
						playeraction = "�������͂肯�[��";
						break;
					}
					break;
				case 6:
					switch(nowplayer){
					case 0:
						playeraction = "��������������";
						break;
					case 1:
						playeraction = "�ɂイ����";
						break;
					case 2:
						playeraction = "���������[���";
						break;
					case 3:
						playeraction = "�΂ǂĂ�ς�";
						break;
					}
					break;
				case 7:
					switch(nowplayer){
					case 0:
						playeraction = "�������ӂ����Ȃ�";
						break;
					case 1:
						playeraction = "�ӂ�Ă�ہ[��";
						break;
					case 2:
						playeraction = "�݂�[���[���";
						break;
					case 3:
						playeraction = "�΂ǂ����[��";
						break;
					}
					break;
				}
				power_select = true;
			}
		}
		else{
			if(playeraction == "�������ځ[��"){
				mp = 10;
			}else if(playeraction == "�Ă�ہ[��"){
				mp = 15;
			}else if(playeraction == "���[���"){
				mp = 20;
			}else if(playeraction == "�΂ǂĂ�ہ[��"){
				mp = 25;
			}else if(playeraction == "�Ă�ς�"){
				mp = 30;
			}else if(playeraction == "�������͂肯�[��"){
				mp = 35;
			}else if(playeraction == "�΂ǂ����["  || playeraction == "�łӂ܂����"){
				mp = 40;
			}else if(playeraction == "�ӂ���������["  || playeraction == "�����イ���˂�"  || playeraction == "���ӂ܂����"){
				mp = 50;
			}else if(playeraction == "�΂ǂ��[���"  || playeraction == "�܂���ǂ���"){
				mp = 60;
			}else if(playeraction == "�΂ǂЁ[��"){
				mp = 70;
			}else if(playeraction == "�ӂ�����������"  || playeraction == "�˂����[���"  || playeraction == "�΂ǂĂ�ς�"){
				mp = 80;
			}else if(playeraction == "�΂ǂ����[��"  || playeraction == "�ɂイ����"  || playeraction == "���������[���"){
				mp = 100;
			}else if(playeraction == "��������������" || playeraction == "�ӂ�Ă�ہ[��"){
				mp = 110;
			}else if(playeraction == "�݂�[���[���"){
				mp = 130;
			}else if(playeraction == "�������ӂ����Ȃ�"){
				mp = 150;
			}
			if(mp > player[nowplayer].getsaiko()){
				playeraction = "esp";
				window = PLAYER_ATTACK;
				damage = 0;
				enemytarget = 0;
				mp = 0;
				power_select = false;
			}
			use = player[nowplayer].getsaiko() - (power + 1) * mp;
			if(Keyboard_Get(KEY_INPUT_RIGHT) == 1 && power < 3 && player[nowplayer].getsaiko() >= (power + 2) * mp){
				power++;
			}
			else if(Keyboard_Get(KEY_INPUT_LEFT) == 1 && power > 0){
				power--;
			}else if(Keyboard_Get(KEY_INPUT_SPACE) == 1){
				player[nowplayer].useSaiko((power + 1) * mp);	
				cursor = 174;
				if(playeraction == "�Ă�ہ[��" || playeraction == "���[���" || playeraction == "�����イ���˂�" || playeraction == "���ӂ܂����"){
					window = PLAYER_SELECT_TELEPORT;
				}else{
					window = PLAYER_TARGET_SELECT;
				}
				if(playeraction == "�ɂイ����"){
					damage = 0;
					for(i = 0;i < 4;i++){
						if(party[i].getMate()){
							party[i].becomeError(0);
							damage = -3;
						}
					}
					window = PLAYER_ATTACK;
					name = player[nowplayer].getname();
					enemytarget = 0;
				}
				power_select = false;
				playertarget = 0;
				while(encountenemy[playertarget].getDead() || encountenemy[playertarget].getEsc()){
					cursor += 24;
					playertarget++;
				}
			}
		}
		break;
	case PLAYER_SELECT_TELEPORT:
		if(Keyboard_Get(KEY_INPUT_DOWN) == 1){
			BANPEI = cursor;
			BANPEI1 =  playertarget;
			do{
				playertarget++;
				cursor +=24;
			}while(playertarget < 4 && (player[playertarget].getDead() || player[playertarget].getEsc() || !player[playertarget].getMate()));
			if(player[playertarget].getDead() || player[playertarget].getEsc()){
				cursor = BANPEI;
				playertarget = BANPEI1;
			}
		}else if(Keyboard_Get(KEY_INPUT_UP) == 1 && cursor > 174){
			BANPEI = cursor;
			BANPEI1 = playertarget;
			do{
				playertarget--;
				cursor -= 24;
			}while(playertarget != 0 && (player[playertarget].getDead() || player[playertarget].getEsc() || !player[playertarget].getMate()));
			if(player[playertarget].getDead() || player[playertarget].getEsc()){
				cursor = BANPEI;
				playertarget = BANPEI1;
			}
		}else if(Keyboard_Get(KEY_INPUT_SPACE) == 1){
			window = PLAYER_ATTACK;
			name = player[nowplayer].getname();
			enemytarget = -2;
			if(playeraction == "�Ă�ہ[��"){
				if(power - rand() % 4 >= 0){
					damage = -1;
				}else{
					damage = -2;
				}
			}else if(playeraction == "���ӂ܂����"){
				if(player[playertarget].gethit() + 60*(power + 1) > player[playertarget].getmaxhit()){
					damage = player[playertarget].getmaxhit() - player[playertarget].gethit() + 60*(power + 1);
				}else{
					damage = -60*(power + 1);
				}
			}else if(playeraction == "���[���"){
				damage = 0;
				sdef[playertarget] = 5* (power + 1);
			}else if(playeraction == "�����イ���˂�"){
				damage = 0;
				def[playertarget] += 5* (power + 1);
			}
		}
		break;
	case PLAYER_TARGET_SELECT:
		if(Keyboard_Get(KEY_INPUT_DOWN) == 1 && cursor < 174 + (enemycount - 1) * 24){
			BANPEI = cursor;
			BANPEI1 = playertarget;
			do{
				playertarget++;
				cursor +=24;
			}while(playertarget != enemycount - 1 && (encountenemy[playertarget].getDead() || encountenemy[playertarget].getEsc()));
			if(encountenemy[playertarget].getDead() || encountenemy[playertarget].getEsc()){
				cursor = BANPEI;
				playertarget = BANPEI1;
			}
		}
		else if(Keyboard_Get(KEY_INPUT_UP) == 1 && cursor > 174){
			BANPEI = cursor;
			BANPEI1 = playertarget;
			do{
				playertarget--;
				cursor -= 24;
			}while(playertarget != 0 && (encountenemy[playertarget].getDead() || encountenemy[playertarget].getEsc()));
			if(encountenemy[playertarget].getDead() || encountenemy[playertarget].getEsc()){
				cursor = BANPEI;
				playertarget = BANPEI1;
			}
		}
		else if(Keyboard_Get(KEY_INPUT_SPACE) == 1){
				window = PLAYER_ATTACK;
				if(playeraction == "��������"){
					if(player[nowplayer].getarms() == 0){
						damage = rand() % 4;
					}
				}else if(playeraction == "�������ځ[��"){
					damage = (power + 1) - encountenemy[playertarget].getDefense();
					if(damage < 0){
						damage = 0;
					}
				}else if(playeraction == "�������͂肯�[��"){
					damage = 2*(power + 1) - encountenemy[playertarget].getDefense();
					if(damage < 0){
						damage = 0;
					}
				}else if(playeraction == "�ӂ���������["){
					damage = 4*(power + 1) - encountenemy[playertarget].getDefense();
					if(damage < 0){
						damage = 0;
					}
				}else if(playeraction == "�ӂ�����������"){
					if(encountenemy[playertarget].getRace() == 3){
						damage = 1.25*5*(power + 1) - encountenemy[playertarget].getDefense();
					}else{
						damage = 5*(power + 1) - encountenemy[playertarget].getDefense();
					}
					if(damage < 0){
						damage = 0;
					}
				}else if(playeraction == "��������������"){
					if(encountenemy[playertarget].getRace() == 2){
						damage = 1.25*9*(power + 1) - encountenemy[playertarget].getDefense();
					}else{
						damage = 9*(power + 1) - encountenemy[playertarget].getDefense();
					}
					if(damage < 0){
						damage = 0;
					}
				}else if(playeraction == "�������ӂ����Ȃ�"){
					if(encountenemy[playertarget].getRace() == 4){
						damage = 1.25*12*(power + 1) - encountenemy[playertarget].getDefense();
					}else{
						damage = 12*(power + 1) - encountenemy[playertarget].getDefense();
					}
					if(damage < 0){
						damage = 0;
					}
				}else if(playeraction == "�΂ǂĂ�ہ[��"){
					damage = 0;
					if(encountenemy[playertarget].getHP()  < 3*(power + 1)){
						encountenemy[playertarget].becomeEsc();
					}
				}else if(playeraction == "�΂ǂ����["){
					if(encountenemy[playertarget].getRace() == 2 ||encountenemy[playertarget].getRace() == 4){
						damage = 0;
					}else{
						if(encountenemy[playertarget].getHP()  < 5*(power + 1)){
							damage = 0;
							encountenemy[playertarget].becomeState(FAINT);
						}else{
							damage = 5*(power + 1) - encountenemy[playertarget].getDefense();
							if(damage < 0){
								damage = 0;
							}
						}
					}
				}else if(playeraction == "�΂ǂЁ[��"){
					if(encountenemy[playertarget].getHP()  < 10*(power + 1)){
						damage = 0;
						encountenemy[playertarget].becomeState(FAINT);
					}else{
						damage = 10*(power + 1) - encountenemy[playertarget].getDefense();
						if(damage < 0){
							damage = 0;
						}
					}
				}
				else if(playeraction == "�΂ǂ��[���"){
					damage = 0;
					if(encountenemy[playertarget].getHP()  < 10*(power + 1)){
						encountenemy[playertarget].becomeState(FSHIELD);
					}
				}
				else if(playeraction == "�˂����[���"){
					damage = 0;
					if(encountenemy[playertarget].getHP()  < 10*(power + 1) && encountenemy[playertarget].getRace() != 2){
						encountenemy[playertarget].becomeState(SHIELD);
					}
				}
				else if(playeraction == "���������[���"){
					damage = 0;
					if(encountenemy[playertarget].getHP()  < 10*(power + 1) && encountenemy[playertarget].getRace() == 2){
						encountenemy[playertarget].becomeState(SSHIELD);
					}
				}else if(playeraction == "�݂�[���[���"){
					damage = 0;
					if(encountenemy[playertarget].getHP()  < 10*(power + 1)){
						encountenemy[playertarget].becomeState(MSHIELD);
					}
				}else if(playeraction == "�Ă�ς�"){
					if(encountenemy[playertarget].getHP()  < 7*(power + 1)){
						if(encountenemy[playertarget].getHP() == 1){
							damage = 1;
						}else{
							damage = encountenemy[playertarget].getHP()/2;
						}
					}else{
						damage = 0;
					}
				}else if(playeraction == "�܂���ǂ���"){
					damage = 0;
					if(encountenemy[playertarget].getHP()  < 10 + 20*power){
						encountenemy[playertarget].becomeState(MINDKILL);
					}
				}else if(playeraction == "�΂ǂĂ�ς�"){
					damage = 0;
					if(encountenemy[playertarget].getHP()  < 10*(power + 1)){
						encountenemy[playertarget].becomeState(CONFUSION);
					}
				}else if(playeraction == "�΂ǂ����[��"){
					if(encountenemy[playertarget].getHP()  < 6 + 5*power){
						damage = encountenemy[playertarget].getHP();
					}else if(encountenemy[playertarget].getHP()  < 11 + 5*power){
						damage = 0;
						encountenemy[playertarget].becomeState(FAINT);
					}
				}
				name = player[nowplayer].getname();
				enemytarget = -2;
		}
		break;
	case PLAYER_ATTACK:
		if(Keyboard_Get(KEY_INPUT_SPACE) == 1){
			if(enemytarget == -2){
				if(damage < 0){
					if(damage == -2){
						battle = false;
						playercount = 0;
						point = 0;
						gold = 0;
						cursor = 174;
						nowplayer = 0;
						encount = false;
						window = STANDBY;
						for(i = 0;i < 4;i++){
							if(player[i].getEsc()){
								player[i].becomeEsc();
							}
						}
						tele = true;
					}else if(damage == -1){
						player[playertarget].becomeEsc();
						for(i = 0;i < 4;i++){
							if(!player[i].getDead() && !player[i].getEsc() && player[i].getMate()){
								break;
							}
						}
						if(i == 4){
							battle = false;
							point = 0;
							gold = 0;
							cursor = 174;
							nowplayer = 0;
							encount = false;
							playercount = 0;
							window = STANDBY;
							for(i = 0;i < 4;i++){
								if(player[i].getEsc()){
									player[i].becomeEsc();
								}
							}
						}else{
							enemytarget = 0;
							cursor = 174;
							/*do{
								nowplayer++;
							}while((!player[nowplayer].getMate() || player[nowplayer].getDead() || player[nowplayer].getEsc()) && nowplayer < 4);*/
							playercount++;
							if(playercount != p_list.size()){
								nowplayer = p_list[playercount];
								window = SELECT_STATE;						
							}
							else{
								while(enemytarget < enemycount  && (encountenemy[enemytarget].getDead() || encountenemy[enemytarget].getEsc())){
									enemytarget++;
								}
								mem = 0;
								playercount = 0;
								p_list.clear();
								window = ENEMY_ATTACK;
							}
						}
					}else{
						party[playertarget].hitdamage(damage);
						enemytarget = 0;
						cursor = 174;
						/*do{
							nowplayer++;
						}while((!player[nowplayer].getMate() || player[nowplayer].getDead() || player[nowplayer].getEsc()) && nowplayer < 4);*/
						playercount++;
						if(playercount != p_list.size()){
							nowplayer = p_list[playercount];
							window = SELECT_STATE;						
						}
						else{
							while(enemytarget < enemycount  && (encountenemy[enemytarget].getDead() || encountenemy[enemytarget].getEsc())){
								enemytarget++;
							}
							mem = 0;
							playercount = 0;
							p_list.clear();
							window = ENEMY_ATTACK;
						}
					}
				}else{
					if(encountenemy[playertarget].getState() != FSHIELD || playeraction != "esp" || playeraction != "�ɂイ����"){
						encountenemy[playertarget].Update(damage);
					}
					if(!encountenemy[playertarget].getDead() && !encountenemy[playertarget].getEsc()){
						enemytarget = 0;
						cursor = 174;
						/*do{
							nowplayer++;
						}while((!player[nowplayer].getMate() || player[nowplayer].getDead() || player[nowplayer].getEsc()) && nowplayer < 4);*/
						playercount++;
						if(playercount != p_list.size()){
							nowplayer = p_list[playercount];
							window = SELECT_STATE;						
						}
						else{
							while(enemytarget < enemycount  && (encountenemy[enemytarget].getDead() || encountenemy[enemytarget].getEsc())){
								enemytarget++;
							}
							mem = 0;
							playercount = 0;
							p_list.clear();
							window = ENEMY_ATTACK;
						}
					}
					else{
						for(i = 0;(encountenemy[i].getDead() || encountenemy[i].getEsc()) && i < enemycount;i++);
						if(i == enemycount){
							window = WIN;
							for(i = 0;i < enemycount;i++){
								if(!encountenemy[i].getEsc()){
									point += encountenemy[i].getPoint();
									gold += encountenemy[i].getGold();
								}
							}
							for(i = 0;i < 4;i++){
								if(player[i].getMate()){
									player[i].levelup(point);
									player[i].shopping(gold);
								}
							}
						}else{
							if(playeraction == "�΂ǂĂ�ہ[��"){
								enemytarget = 0;
							}
							enemytarget++;
						}
					}
				}
			}else{
				/*do{
					nowplayer++;
				}while((!player[nowplayer].getMate() || player[nowplayer].getDead() || player[nowplayer].getEsc()) && nowplayer < 4);*/
				playercount++;
				if(playercount != p_list.size()){
					nowplayer = p_list[playercount];
					window = SELECT_STATE;
					cursor = 174;
				}
				else{
					if(enemytarget != 0){
						enemytarget = 0;
					}
					while(enemytarget < enemycount  && (encountenemy[enemytarget].getDead() || encountenemy[enemytarget].getEsc())){
						enemytarget++;
					}
					mem = 0;
					playercount = 0;
					p_list.clear();
					window = ENEMY_ATTACK;
				}
				if(guard){
					guard = false;
				}
			}
		}
		break;
	case ENEMY_ATTACK:
		if(!draw || Keyboard_Get(KEY_INPUT_SPACE) == 1){
			if(dead){
				dead = false;
			}
			if(draw){
				do{
					enemytarget++;
				}while(enemytarget < enemycount  && (encountenemy[enemytarget].getDead() || encountenemy[enemytarget].getEsc()));
			}
			else{
				draw = true;
			}
			if(enemytarget < enemycount){
				if(encountenemy[enemytarget].getState() < 5){
					if(encountenemy[enemytarget].getState() == CONFUSION){
						do{
							damaged_player = rand() % 4;
						}
						while(encountenemy[damaged_player].getDead() || encountenemy[damaged_player].getEsc());
					}else{
						do{
							damaged_player = rand() % 4;
						}
						while(!player[damaged_player].getMate() || player[damaged_player].getDead() || player[damaged_player].getEsc());
					}
					if(!encountenemy[enemytarget].getSaiko()){
						encountenemy[enemytarget].setAttackName("��������");
					}
					else if(encountenemy[enemytarget].getName() == "����܂��"){
						if(encountenemy[enemytarget].getHP() == 1 && rand() % 5 == 0){
							encountenemy[enemytarget].setAttackName("�ɂ���");
						}else if(rand() % 10 == 0 && encountenemy[enemytarget].getState() != SSHIELD){
							encountenemy[enemytarget].setAttackName("���肤");
						}else{
							encountenemy[enemytarget].setAttackName("��������");
						}
					}
					else if(encountenemy[enemytarget].getName() == "�ׂ邺�ł�" 
						|| encountenemy[enemytarget].getName() == "��������"
						|| encountenemy[enemytarget].getName() == "���������")
						if(encountenemy[enemytarget].getHP() == 1 && rand() % 5 == 0){
							encountenemy[enemytarget].setAttackName("�ɂ���");
						}else{
							encountenemy[enemytarget].setAttackName("��������");
						}
						if(encountenemy[enemytarget].getAttackName() == "��������"){
							name = player[damaged_player].getname();	
							if(encountenemy[enemytarget].getState() == CONFUSION){
								damage = encountenemy[enemytarget].getDamage(encountenemy[damaged_player].getDefense());
								encountenemy[damaged_player].Update(damage);
							}else if(encountenemy[enemytarget].getState() == MSHIELD){
								damage = encountenemy[enemytarget].getDamage(encountenemy[enemytarget].getDefense());
								encountenemy[enemytarget].Update(damage);
							}else{
								damage = encountenemy[enemytarget].getDamage(player[damaged_player].getdefense() + def[damaged_player] + sdef[damaged_player]);
								player[damaged_player].hitdamage(damage);
							}
						}else if(encountenemy[enemytarget].getAttackName() == "���肤"){
							player[damaged_player].becomeError(1);
							name = player[damaged_player].getname();
						}else if(encountenemy[enemytarget].getAttackName() == "�ɂ���"){
							encountenemy[enemytarget].becomeEsc();
							for(i = 0;i < enemycount;i++){
								if(!encountenemy[i].getDead() && !encountenemy[i].getEsc()){
									break;
								}
							}
							if(i == enemycount){
								window = WIN_ESC;
								for(i = 0;i < enemycount;i++){
								if(!encountenemy[i].getEsc()){
									point += encountenemy[i].getPoint();
									gold += encountenemy[i].getGold();
								}
							}
							for(i = 0;i < 4;i++){
								if(player[i].getMate()){
									player[i].levelup(point);
									player[i].shopping(gold);
								}
							}
						}
					}
					if(player[damaged_player].getDead()){
						dead = true;
						int k;
						for(j = 0;player[j].getMate() && j < 4;j++);
						for(i = 0;player[i].getDead() && i < 4;i++);
						for(k = 0;player[k].getEsc() && player[k].getDead() && k < 4;k++);
						if(j == k){
							battle = false;
							point = 0;
							gold = 0;
							cursor = 174;
							nowplayer = 0;
							encount = false;
							window = STANDBY;
							for(i = 0;i < 4;i++){
								if(player[i].getEsc()){
									player[i].becomeEsc();
								}
							}
						}
						if(i == j){
							window = LOSE;
						}
					}
				}else{
					encountenemy[enemytarget].becomeState(0);
				}
			}else{
				window = SELECT_LIST;
				cursor = 174;
				draw = false;
				nowplayer = 0;
				for(int a = 0;a < 4;a++){
					sdef[a] = 0;
				}
				p_list.clear();
				playertarget = 0;
			}
		}
		break;
	case WIN_ESC:
		if(Keyboard_Get(KEY_INPUT_SPACE) == 1){
			window = WIN;
		}
		break;
	case WIN:
		if(Keyboard_Get(KEY_INPUT_SPACE) == 1){
			battle = false;
			point = 0;
			gold = 0;
			cursor = 174;
			nowplayer = 0;
			encount = false;
			window = STANDBY;
			p_list.clear();
			playertarget = 0;
			mem = 0;
			playercount = 0;
		}
		break;
	case LOSE:
		if(Keyboard_Get(KEY_INPUT_SPACE) == 1){
			battle = false;
			dead_end = true;
		}
		break;
	}
	for(i = 0;i < 4;i++){
		if(p_src[i] != 0){
			hit[i] = player[i].gethit();
		}
	}
}

void Battle::Draw(){
	DrawGraph(0,0,src,TRUE);
	DrawFormatString(0,30,white,"%d",playercount);
	DrawFormatString(0,45,white,"%d",mem);
	for(i = 0;i < 4;i++){
		if(p_src[i] != 0 && !party[i].getEsc() && !party[i].getDead()){
			DrawGraph(34 + i* 114 + i/2 * 16,370,p_src[i],TRUE);
		}
	}
	for(i = 0;i < 4;i++){
		if(hit[i] > 0 && !party[i].getEsc() && !party[i].getDead()){
			DrawFormatString(110 + i* 117 + i/2 * 16,470,white,"%d",hit[i] / 10);
		}
	}
	for(i = 0;i < enemycount;i++){
			encountenemy[i].Draw();
	}
	DrawGraph(16,160,src1,TRUE);
	switch(window){
	case STANDBY:
		if(enemycount == 1){
			DrawFormatString(40,184,white,"%s�ɂƂ���ł������B",encountenemy[0].getName().c_str());
		}
		else{
			DrawFormatString(40,184,white,"%s�����ɂƂ���ł������B",encountenemy[0].getName().c_str());
		}
		break;
	case STATE_KARIU:
		DrawFormatString(40,184,white,"%s%s",name.c_str(),error_mesage.c_str());
		break;
	case SELECT_LIST:
		DrawGraph(250,150,src4,TRUE);
		DrawFormatString(306,174,white,"�����΂�H");
		i = 0;
		for(int a = 0;a < 4;a++){
			if(!party[a].getDead() && !party[a].getEsc() && party[a].getMate() && include(a)){
				DrawFormatString(306,198 + 24*i,white,party[a].getname().c_str());
				i++;
			}
		}
		DrawGraph(279,24+cursor,src3,TRUE);
		break;
	case PLAYER_STANDBY:
		DrawGraph(16,150,src2,TRUE);
		DrawGraph(45,cursor,src3,TRUE);
		DrawFormatString(56,155,white,"�b�n�l�l�`�m�c");
		DrawFormatString(72,174,white,"�d�r�o");
		DrawFormatString(72,198,white,"��������");
		DrawFormatString(72,222,white,"�ӂ���");
		DrawFormatString(72,246,white,"������");
		DrawFormatString(72,270,white,"������");
		break;
	case PLAYER_SELECT_TELEPORT:
		DrawGraph(16,150,src2,TRUE);
		DrawGraph(45,cursor1,src3,TRUE);
		DrawFormatString(56,155,white,"�b�n�l�l�`�m�c");
		DrawFormatString(72,174,white,"�d�r�o");
		DrawFormatString(72,198,white,"��������");
		DrawFormatString(72,222,white,"�ӂ���");
		DrawFormatString(72,246,white,"������");
		DrawFormatString(72,270,white,"������");
		DrawGraph(250,150,src4,TRUE);
		DrawFormatString(306,174,white,"����ɁH");
		for(i = 0;i < 4;i++){
			if(!party[i].getDead() && !party[i].getEsc() && party[i].getMate()){
				DrawFormatString(306,198 + 24*i,white,party[i].getname().c_str());
			}
		}
		DrawGraph(279,24+cursor,src3,TRUE);
		break;
	case PLAYER_TARGET_SELECT:
		DrawGraph(16,150,src2,TRUE);
		DrawGraph(45,cursor1,src3,TRUE);
		DrawFormatString(56,155,white,"�b�n�l�l�`�m�c");
		DrawFormatString(72,174,white,"�d�r�o");
		DrawFormatString(72,198,white,"��������");
		DrawFormatString(72,222,white,"�ӂ���");
		DrawFormatString(72,246,white,"������");
		DrawFormatString(72,270,white,"������");
		DrawGraph(250,150,src4,TRUE);
		DrawFormatString(306,174,white,"����ɁH");
		for(i = 0;i < enemycount;i++){
			if(!encountenemy[i].getDead() && !encountenemy[i].getEsc()){
				DrawFormatString(306,198 + 24*i,white,encountenemy[i].getName().c_str());
			}
		}
		DrawGraph(279,24+cursor,src3,TRUE);
		break;
	case STATE:
		DrawGraph(0,0,src7,TRUE);
		DrawGraph(300,5,src8,TRUE);
		DrawGraph(10,330,src9,TRUE);			
		DrawGraph(10,80,src10,TRUE);
		DrawFormatString(375,10,white,name.c_str());
		switch(state){
		case 0:
			DrawFormatString(320,45,white,"�@�@�@���炾:�ӂ�");
			break;
		}
		DrawFormatString(320,80,white,"�@�@�@��ׂ�:%d",level);
		DrawFormatString(320,115,white,"�@�@�Ђ��Ɨ�:%d",hit_p);
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
		switch(guard_p){
		case 0:
			DrawFormatString(30,385,white,"�@�ڂ���:�Ȃɂ��Ȃ�");
			break;
		}
		DrawFormatString(30,420,white,"���[���:%d",gold_p);
		DrawFormatString(65,83,white,"�d�r�o");
		DrawFormatString(30,120,white,"�Ԃꂢ���@%d",pk);
		DrawFormatString(30,165,white,"�����Ձ@%d",jump);
		DrawFormatString(30,210,white,"�Ă�ς��@%d",telepathy);
		DrawFormatString(30,255,white,"���[��ǁ@%d",shield);
		break;
	case ESP_LESS:
		DrawFormatString(40,184,white,"�������́@���@����܂���");
		break;
	case PLAYER_ESP_STANDBY:
		DrawGraph(0,0,src5,TRUE);
		DrawGraph(320,cursor,src3,TRUE);
		DrawFormatString(370,65,white,"�d�r�o");
		if(esp[0]){
			switch(nowplayer){
			case 0:
				DrawFormatString(340,90,white,"�������ځ[��");
				break;
			case 1:
				DrawFormatString(340,90,white,"�Ă�ہ[��");
				break;
			case 2:
				DrawFormatString(340,90,white,"���[���");
				break;
			case 3:
				DrawFormatString(340,90,white,"�Ă�ς�");
				break;
			}
		}
		if(esp[1]){
			switch(nowplayer){
			case 0:
				DrawFormatString(340,90 + CURSOR_E,white,"�������͂肯�[��");	
				break;
			case 1:
				DrawFormatString(340,90 + CURSOR_E,white,"�ڂǂĂ�ہ[��");
				break;
			case 2:
				DrawFormatString(340,90 + CURSOR_E,white,"�����イ���˂�");
				break;
			case 3:
				DrawFormatString(340,90 + CURSOR_E,white,"�łӂ܂����");
				break;
			}
		}
		if(esp[2]){
			switch(nowplayer){
			case 0:
				DrawFormatString(340,90 + CURSOR_E * 2,white,"�ӂ���������[");	
				break;
			case 1:
				DrawFormatString(340,90 + CURSOR_E * 2,white,"�΂ǂ����[");	
				break;
			case 2:
				DrawFormatString(340,90 + CURSOR_E * 2,white,"�΂ǂ��[���");	
				break;
			case 3:
				DrawFormatString(340,90 + CURSOR_E * 2,white,"���ӂ܂����");	
				break;
			}
		}
		if(esp[3]){
			switch(nowplayer){
			case 0:
				DrawFormatString(340,90 + CURSOR_E * 3,white,"�Ă�ہ[��");
				break;
			case 1:
				DrawFormatString(340,90 + CURSOR_E * 3,white,"���[���");
				break;
			case 2:
				DrawFormatString(340,90 + CURSOR_E * 3,white,"�Ă�ς�");
				break;
			case 3:
				DrawFormatString(340,90 + CURSOR_E * 3,white,"�������ځ[��");
				break;
			}
		}
		if(esp[4]){
			switch(nowplayer){
			case 0:
				DrawFormatString(340,90 + CURSOR_E * 4,white,"�ӂ�����������");
				break;
			case 1:
				DrawFormatString(340,90 + CURSOR_E * 4,white,"�΂ǂЁ[��");
				break;
			case 2:
				DrawFormatString(340,90 + CURSOR_E * 4,white,"�˂����[���");
				break;
			case 3:
				DrawFormatString(340,90 + CURSOR_E * 4,white,"�܂���ǂ���");
				break;
			}
		}
		if(esp[5]){
			switch(nowplayer){
			case 0:
				DrawFormatString(340,90 + CURSOR_E * 5,white,"�ڂǂĂ�ہ[��");
				break;
			case 1:
				DrawFormatString(340,90 + CURSOR_E * 5,white,"�����イ���˂�");
				break;
			case 2:
				DrawFormatString(340,90 + CURSOR_E * 5,white,"�łӂ܂����");
				break;
			case 3:
				DrawFormatString(340,90 + CURSOR_E * 5,white,"�������͂肯�[��");
				break;
			}
		}
		if(esp[6]){
			switch(nowplayer){
			case 0:
				DrawFormatString(340,90 + CURSOR_E * 6,white,"��������������");
				break;
			case 1:
				DrawFormatString(340,90 + CURSOR_E * 6,white,"�ɂイ����");
				break;
			case 2:
				DrawFormatString(340,90 + CURSOR_E * 6,white,"���������[���");
				break;
			case 3:
				DrawFormatString(340,90 + CURSOR_E * 6,white,"�΂ǂĂ�ς�");
				break;
			}
		}
		if(esp[7]){
			switch(nowplayer){
			case 0:
				DrawFormatString(340,90 + CURSOR_E * 7,white,"�������ӂ����Ȃ�");
				break;
			case 1:
				DrawFormatString(340,90 + CURSOR_E * 7,white,"�ӂ�Ă�ہ[��");
				break;
			case 2:
				DrawFormatString(340,90 + CURSOR_E * 7,white,"�݂�[���[���");
				break;
			case 3:
				DrawFormatString(340,90 + CURSOR_E * 7,white,"�΂ǂ����[��");
				break;
			}
		}
		if(power_select){
			DrawGraph(100,350,src6,TRUE);
			DrawFormatString(120,370,white,"�������͂����߂Ă�������");
			DrawFormatString(120,388,white,"�������́F%d",use);
			for(i = 0;i < power + 1;i++){
				DrawGraph(120 + 47 * i,408,src11,TRUE);
			}
		}
		break;
	case PLAYER_ATTACK:
			if(guard){
				DrawFormatString(40,184,white,"%s�́A�@�݂��܂����B",name.c_str());
			}
			else{
				if(damage < 0){
					DrawFormatString(40,184,white,"%s�́A�@%s���������B",name.c_str(),playeraction.c_str());
					if(damage == -2){
						DrawFormatString(40,208,white,"�Ă�ہ[�Ƃ́A�����Ăɂ���܂���@�����ς������B");
						DrawFormatString(40,232,white,"���Ȃ��́@�Ă�ہ[�Ƃ��@����Ƃ�[��");
						DrawFormatString(40,256,white,"�ł��Ȃ��Ȃ���	");
					}else{
						DrawFormatString(40,208,white,"%s�́A%s�Ɂ@�������������B",party[playertarget].getname().c_str(),playeraction.c_str());
					}
				}else{
					if(encountenemy[playertarget].getState() != FSHIELD){
						if(playeraction == "esp"){
							DrawFormatString(40,184,white,"�������́@���@����܂���");
						}
						if(playeraction == "��������"){
							DrawFormatString(40,184,white,"%s�́@%s�Ɂ@%s�������B",name.c_str(),encountenemy[playertarget].getName().c_str(),playeraction.c_str());
						}else if(playeraction != "esp"){
							DrawFormatString(40,184,white,"%s�́@%s���������B",name.c_str(),playeraction.c_str());
						}
						if(damage == 0){
							if(playeraction == "��������"){
								DrawFormatString(40,208,white,"�������@���߁[�����A�@���������Ȃ������B",damage);
							}else if(playeraction == "�Ă�ς�"){
								DrawFormatString(40,208,white,"%s�́@���Ⴍ�Ă���@�݂���̂�",encountenemy[playertarget].getName().c_str());
								DrawFormatString(40,232,white,"�����ς������B");
							}else if(playeraction == "�܂���ǂ���"){
								if(encountenemy[playertarget].getState() == MINDKILL){
									DrawFormatString(40,208,white,"%s�́A���������͂��ւ���",encountenemy[playertarget].getName().c_str());
								}else{
									DrawFormatString(40,208,white,"%s�ɂ́A�����Ȃ�����",encountenemy[playertarget].getName().c_str());
								}
							}else if(playeraction == "�΂ǂĂ�ς�"){
								if(encountenemy[playertarget].getState() == CONFUSION){
									DrawFormatString(40,208,white,"%s���@�Ȃ��܂Ɂ@����̂�",encountenemy[playertarget].getName().c_str());
									DrawFormatString(40,232,white,"������������");
								}else{
									DrawFormatString(40,208,white,"�������@%s���@�Ȃ��܂ɂ���̂�",encountenemy[playertarget].getName().c_str());
									DrawFormatString(40,232,white,"�����ς�����");
								}
							}else if(playeraction == "�΂ǂ����[��"){
								if(encountenemy[playertarget].getState() == FAINT){
									DrawFormatString(40,208,white,"%s���@�Ȃ��܂Ɂ@����̂�",encountenemy[playertarget].getName().c_str());
									DrawFormatString(40,232,white,"������������");
								}else{
									DrawFormatString(40,208,white,"�������@%s�ɂ́@�����Ȃ�����",encountenemy[playertarget].getName().c_str());
								}
							}else if(playeraction == "���[���"){
								DrawFormatString(40,208,white,"%s�́@�ڂ������傭���@�T�@���������B",party[playertarget].getname().c_str());
							}else if(playeraction == "�����イ���˂�"){
								DrawFormatString(40,208,white,"%s�́@����Ƃ��̂��������イ�@�ڂ������傭��",party[playertarget].getname().c_str());
								DrawFormatString(40,232,white,"�T�@�ӂ���B");
							}else if(playeraction == "�΂ǂ��[���"){
								if(encountenemy[playertarget].getState() == FSHIELD){
									DrawFormatString(40,208,white,"%s�Ɂ@�������񂵁[��ǂ��@������̂�",encountenemy[playertarget].getName().c_str());
									DrawFormatString(40,232,white,"������������");
								}else{
									DrawFormatString(40,208,white,"�������@�������񂵁[��ǂ�");
									DrawFormatString(40,232,white,"�݂��ނ̂Ɂ@�����ς�����");
								}
							}else if(playeraction == "���������[���"){
								if(encountenemy[playertarget].getState() == SHIELD){
									DrawFormatString(40,208,white,"%s�Ɂ@�������񂵁[��ǂ��@������̂�",encountenemy[playertarget].getName().c_str());
									DrawFormatString(40,232,white,"������������");
								}else{
									DrawFormatString(40,208,white,"�������@�������񂵁[��ǂ�");
									DrawFormatString(40,232,white,"�݂��ނ̂Ɂ@�����ς�����");
								}
							}else if(playeraction == "�˂����[���"){
								if(encountenemy[playertarget].getState() == SHIELD){
									DrawFormatString(40,208,white,"%s�Ɂ@�������񂵁[��ǂ��@������̂�",encountenemy[playertarget].getName().c_str());
									DrawFormatString(40,232,white,"������������");
								}else{
									DrawFormatString(40,208,white,"�������@�������񂵁[��ǂ�");
									DrawFormatString(40,232,white,"�݂��ނ̂Ɂ@�����ς�����");
								}
							}else if(playeraction == "�݂�[���[���"){
								DrawFormatString(40,208,white,"%s�Ɂ@�݂�[���[��ǂ��@������̂�",encountenemy[playertarget].getName().c_str());
								if(encountenemy[playertarget].getState() == MSHIELD){
									DrawFormatString(40,232,white,"������������");
								}else{
									DrawFormatString(40,232,white,"�����ς�����");
								}
							}else if(playeraction == "�΂ǂĂ�ہ[��"){
								if(encountenemy[playertarget].getEsc()){
									DrawFormatString(40,208,white,"%s�́@�ق��̂΂���Ɂ@�Ƃ΂����",encountenemy[playertarget].getName().c_str());
									DrawFormatString(40,232,white,"���Ȃ��Ȃ���");
								}else{
									DrawFormatString(40,208,white,"�������A%s�Ɂ@����܂����",encountenemy[playertarget].getName().c_str());
									DrawFormatString(40,232,white,"�����ς�����");
								}
							}else if(playeraction == "�΂ǂ����["){
								if(encountenemy[playertarget].getState() == FAINT){
									DrawFormatString(40,208,white,"%s�́A�܂��́@��������",encountenemy[playertarget].getName().c_str());
									DrawFormatString(40,232,white,"�Ȃ��Ȃ�A���������B");
								}else{
									DrawFormatString(40,208,white,"%s�́A�܂��́@��������",encountenemy[playertarget].getName().c_str());
									DrawFormatString(40,232,white,"�Ȃ��Ȃ������A�ւ����Ł@�����ɂ����B");
								}
							}else if(playeraction == "�ɂイ�����["){
									DrawFormatString(40,208,white,"�������A�Ȃɂ�������Ȃ�����");
							}else if(playeraction == "�΂ǂЁ[��"){
								DrawFormatString(40,208,white,"%s�́@�܂��́@�˂�",encountenemy[playertarget].getName().c_str());
								DrawFormatString(40,232,white,"���イ������ �����Ȃ��@�������Ȃ��Ȃ���");
							}else if(playeraction != "esp"){
								DrawFormatString(40,208,white,"�����ā@%d�@�́@���߁[�����@���������B",damage);
							}
						}else{
							if(playeraction == "�΂ǂ����["){
								DrawFormatString(40,208,white,"%s�́A�܂��́@�˂������Ȃ�",encountenemy[playertarget].getName().c_str());
								DrawFormatString(40,232,white,"%d�@�́@���߁[�����@�������B",damage);
							}else if(playeraction == "�΂ǂ����["){
								DrawFormatString(40,208,white,"%s�́A�܂��́@��������",encountenemy[playertarget].getName().c_str());
								DrawFormatString(40,232,white,"�Ȃ��Ȃ�@%d�@�́@���߁[�����@�������B",damage);
							}else if(playeraction == "���ӂ܂����"){
								DrawFormatString(40,208,white,"%d�@�Ђ��Ɨ͂��@%d�@�ӂ����B",party[playertarget].getname().c_str(),damage);
								DrawFormatString(40,232,white,"�Ȃ��Ȃ�@%d�@�́@���߁[�����@�������B",damage);
							}else if(playeraction == "�Ă�ς�"){
								DrawFormatString(40,208,white,"%s�́@���Ⴍ�Ă���@�݂���̂�",encountenemy[playertarget].getName().c_str());
								DrawFormatString(40,232,white,"������������",damage);
							}else{
								DrawFormatString(40,208,white,"�����ā@%d�@�́@���߁[�����@���������B",damage);
							}
						}
						if(enemytarget == -1&& encountenemy[playertarget].getDead()){
							DrawFormatString(40,232,white,"%s�����������B",encountenemy[playertarget].getName().c_str());
						}
					}else{
						DrawFormatString(40,184,white,"%s�́@���[��ǂɁ@�܂����Ă���B",encountenemy[playertarget].getName().c_str());
					}
				}
			}
			break;
	case ENEMY_ATTACK:
		if(draw){
			if(encountenemy[enemytarget].getState() < 5){
				if(encountenemy[enemytarget].getAttackName() == "��������"){
					DrawFormatString(40,184,white,"%s�́@%s�Ɂ@%s�������B",encountenemy[enemytarget].getName().c_str(),name.c_str(),encountenemy[enemytarget].getAttackName().c_str());
					DrawFormatString(40,208,white,"�����ā@%d�@�́@���߁[�����@���������B",damage);
					if(dead){
						DrawFormatString(40,232,white,"%s�͂���ł��܂����B",name.c_str());
						if(dead_end){
							DrawFormatString(40,256,white,"���񂢂�@����ł��܂����B");
						}
					}
				}else{
					DrawFormatString(40,184,white,"%s�́@�������Ă���B",encountenemy[enemytarget].getName().c_str());
				}
			}
			else if(encountenemy[enemytarget].getAttackName() == "���肤"){
				DrawFormatString(40,184,white,"%s�͂��肤���Ȃ������B",encountenemy[enemytarget].getName().c_str());
				DrawFormatString(40,208,white,"%s�́A���炾���イ�Ɂ@���ނ������������B",name.c_str(),damage);
			}
			else if(encountenemy[enemytarget].getAttackName() == "�ɂ���"){
				DrawFormatString(40,184,white,"%s�͂ɂ��������B",encountenemy[enemytarget].getName().c_str());
			}
		}
		break;
	case WIN_ESC:
		DrawFormatString(40,184,white,"%s�͂ɂ��������B",encountenemy[enemytarget].getName().c_str());
		break;
	case WIN:
		DrawFormatString(40,184,white,"�Ă����@����߂@�������B");
		DrawFormatString(40,208,white,"�@�@�@�@�@%d�̂������񂿂��ӂ����B",point);
		DrawFormatString(40,232,white,"�Ă��̂��炾����A");
		DrawFormatString(40,256,white,"�@�@�@�@�@%d���[��ǂ��݂����B",gold);
		break;
	case LOSE:
		if(encountenemy[enemytarget].getAttackName() == "��������"){
			DrawFormatString(40,184,white,"%s�́@%s�Ɂ@%s�������B",encountenemy[enemytarget].getName().c_str(),name.c_str(),encountenemy[enemytarget].getAttackName().c_str());
			DrawFormatString(40,208,white,"�����ā@%d�@�́@���߁[�����@���������B",damage);
			if(dead){
				DrawFormatString(40,232,white,"%s�͂���ł��܂����B",name.c_str());
				DrawFormatString(40,256,white,"���񂢂�@����ł��܂����B");
			}
		}
		break;
	}
}

//�퓬�I����m�点��֐�
bool Battle::EndBattle(){
	return !battle;
}

bool Battle::getTele(){
	return tele;
}

void Battle::Finalize(){
	delete [] enemy;
	delete [] encountenemy;
	delete [] p_src;
	delete [] hit;
}

bool Battle::getDead(){
	return dead_end;
}
