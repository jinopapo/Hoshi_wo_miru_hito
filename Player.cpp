#include "DxLib.h"
#include "Player.h"
#include <string>

//�ړ��̍X�V
bool Player::UpDateMove(int movex,int movey){
	//�u���b�N�ړ�
	extern int cell;
	if(movex == cell){
		playerx--;
		if(state == 1){
			hit -= 10;
		}
	}
	else if(movex == -cell){
		playerx++;
		if(state == 1){
			hit -= 10;
		}
	}
	if(movey == cell){
		playery--;
		if(state == 1){
			hit -= 10;
		}
	}
	else if(movey == -cell){
		playery++;
		if(state == 1){
			hit -= 10;
		}
	}
	return true;
}

//�L�[�ɉ������L�����̉摜�̍X�V
bool Player::UpDateSrc(int up,int down,int right,int left,bool menumode){
	extern bool move;
	if(!move && !menumode){
		if(up >= 1){
			srcSelect = 0;
		}
		else if(down >= 1){
			srcSelect = 8;
		}
		else if(left >= 1){
			srcSelect = 4;
		}
		else if(right >= 1){
			srcSelect = 12;
		}
	}
	return true;
}

//�X�e�[�W�ړ��������̃v���C���[�̈ʒu�̏�����
void Player::Update(int* playerPointDef){
	extern bool change;
	if(change){
		playerx = *playerPointDef;
		playerPointDef++;
		playery = *playerPointDef;
		playerPointDef++;
		srcSelect = *playerPointDef;
		change=false;
	}
}

//������
Player::Player(int* handle,int handle1,int handle2,int handle3,char* p_name,int p_hit,int p_saiko,int p_defense,int p_speed,int p_jukurendo){
	playerx = 15;
	playery = 29;
	srcSelect = 8;
	hit = p_hit;
	maxhit = hit;
	saiko = p_saiko;
	maxsaiko = saiko;
	speed = p_speed;
	jukurenndo = p_jukurendo;
	keikenti = 0;
	level = 0;
	state = 0;
	defense = p_defense;
	name = p_name;
	src1 = handle1;
	src2 = handle2;
	src3 = handle3;
	for(i=0;i<16;i++,handle++){
		src[i] = *handle;
	} 
	arms = 0;
	guard = 0;
	gold = 0;
	jump = 0;
	pk = 0;
	telepathy = 0;
	shield = 0;
	nextPoint = 10;
	ability = new int[18];
	esp = new bool[8];
	for(i = 0;i < 8;i++){
		esp[i] = true;
	}
	dead = false;
	mate = false;
	esc = false;
}

//private�Ńv���C���[�̃u���b�N��̈ʒu���������炻���n���p
int Player::getPlayery(){
	return playery;
}
int Player::getPlayerx(){
	return  playerx;
}

void Player::Draw(){
	extern int cell;
	extern bool move;
	//�Î~���
	if(!move){
		count=0;
		DrawGraph(cell*7+cell/2,cell*7+cell/2,src[srcSelect],TRUE );
	}
	//�ړ���
	else{
		count++;
		DrawGraph(cell*7+cell/2,cell*7+cell/2,src[srcSelect + count/4%4],TRUE );
	}
}

//�v���C���[�̌����Ă������`����֐�
int Player::getplayervec(){
	return srcSelect;
}

//�v���C���[�̉摜��n���֐�
int Player::getSrc(){
	if(level < 7){
		return src1;
	}else if(level <14){
		return src2;
	}else{
		return src3;
	}
}

//�v���C���[�̂Ђ��Ƃ��v�Z����֐�
void Player::hitdamage(int damage){
	hit -= damage;
	if(hit <= 0){
		dead = true;
		hit = 0;
	}else{
		dead = false;
	}
}
//�v���C���[�̂��������v�Z����֐�
void Player::useSaiko(int use){
	saiko -= use;
}

//�v���C���[�̌o���l���v�Z����֐�
void Player::levelup(int point){
	if(level != 30){
		keikenti += point;
		nextPoint -= point;
		if(nextPoint <= 0){
			level++;	
			switch(level){
			case 1:
				nextPoint = 27 - abs(nextPoint);
				maxhit += 100;
				maxsaiko += 25;
				defense++;
				jukurenndo += 4;
				esp[0] = true; 
				if(name == "�݂Ȃ�"){
					pk++;
				}else if(name == "����"){
					jump++;
				}else if(name == "�݂�"){
					shield++;
				}else{
					telepathy++;
				}
				break;
			case 2:
				nextPoint = 58 - abs(nextPoint);
				maxhit += 160;
				maxsaiko += 45;
				defense++;
				jukurenndo += 2;
				esp[1] = true; 
				break;
			case 3:
				nextPoint = 103 - abs(nextPoint);
				maxhit += 230;
				maxsaiko += 60;
				defense++;
				jukurenndo += 2;
				if(name == "�݂Ȃ�"){
					pk++;
				}else if(name == "����"){
					jump++;
				}else if(name == "�݂�"){
					shield++;
				}else{
					telepathy++;
				}
				break;
			case 4:
				nextPoint = 162 - abs(nextPoint);
				maxhit += 270;
				maxsaiko += 90;
				defense++;
				jukurenndo += 2;
				if(name == "�݂Ȃ�"){
					jump++;
				}else if(name == "����"){
					shield++;
				}else if(name == "�݂�"){
					telepathy++;
				}else{
					pk++;
				}
				break;
			case 5:
				nextPoint = 235 - abs(nextPoint);
				if(name == "�݂Ȃ�"){
					pk++;
				}else if(name == "����"){
					jump++;
				}else if(name == "�݂�"){
					shield++;
				}else{
					telepathy++;
				}
				break;
			case 6:
				nextPoint = 322 - abs(nextPoint);
				esp[2] = true;
				break;
			case 7:
				nextPoint = 423 - abs(nextPoint);
				if(name == "�݂Ȃ�"){
					pk++;
				}else if(name == "����"){
					jump++;
				}else if(name == "�݂�"){
					shield++;
				}else{
					telepathy++;
				}
				break;
			case 8:
				nextPoint = 538 - abs(nextPoint);
				esp[3] = true;
				break;
			case 9:
				nextPoint = 667 - abs(nextPoint);
				if(name == "�݂Ȃ�"){
					shield++;
					pk++;
				}else if(name == "����"){
					telepathy++;
					jump++;
				}else if(name == "�݂�"){
					pk++;
					shield++;
				}else{
					jump++;
					telepathy++;
				}
				break;
			case 10:
				nextPoint = 810 - abs(nextPoint);
				esp[4] = true;
				break;
			case 11:
				nextPoint = 967 - abs(nextPoint);
				if(name == "�݂Ȃ�"){
					pk++;
				}else if(name == "����"){
					jump++;
				}else if(name == "�݂�"){
					shield++;
				}else{
					telepathy++;
				}
				break;
			case 12:
				nextPoint = 1138 - abs(nextPoint);
				if(name == "�݂Ȃ�"){
					jump++;
				}else if(name == "����"){
					shield++;
				}else if(name == "�݂�"){
					telepathy++;
				}else{
					pk++;
				}
				break;
			case 13:
				nextPoint = 1323 - abs(nextPoint);
				if(name == "�݂Ȃ�"){
					shield++;
				}else if(name == "����"){
					telepathy++;
				}else if(name == "�݂�"){
					pk++;
				}else{
					jump++;
				}
				break;
			case 14:
				nextPoint = 1522 - abs(nextPoint);
				if(name == "�݂Ȃ�"){
					telepathy++;
				}else if(name == "����"){
					pk++;
				}else if(name == "�݂�"){
					jump++;
				}else{
					shield++;
				}
				break;
			case 15:
				nextPoint = 1735 - abs(nextPoint);
				break;
			case 16:
				nextPoint = 1962 - abs(nextPoint);
				esp[5] = true;
				if(name == "�݂Ȃ�"){
					jump++;
				}else if(name == "����"){
					shield++;
				}else if(name == "�݂�"){
					telepathy++;
				}else{
					pk++;
				}
				break;
			case 17:
				nextPoint = 2203 - abs(nextPoint);
				if(name == "�݂Ȃ�"){
					shield++;
				}else if(name == "����"){
					telepathy++;
				}else if(name == "�݂�"){
					pk++;
				}else{
					jump++;
				}
				break;
			case 18:
				nextPoint = 2458 - abs(nextPoint);
				if(name == "�݂Ȃ�"){
					telepathy++;
				}else if(name == "����"){
					pk++;
				}else if(name == "�݂�"){
					jump++;
				}else{
					shield++;
				}
				break;
			case 19:
				nextPoint = 2733 - abs(nextPoint);
				break;
			case 20:
				nextPoint = 3010 - abs(nextPoint);
				break;
			case 21:
				nextPoint = 3307 - abs(nextPoint);
				break;
			case 22:
				nextPoint = 3618 - abs(nextPoint);
				break;
			case 23:
				nextPoint = 3900 - abs(nextPoint);
				break;
			case 24:
				nextPoint = 4282 - abs(nextPoint);
				break;
			case 25:
				nextPoint = 4635 - abs(nextPoint);
				break;
			case 26:
				nextPoint = 5002 - abs(nextPoint);
				break;
			case 27:
				nextPoint = 5383 - abs(nextPoint);
				break;
			case 28:
				nextPoint = 5778 - abs(nextPoint);
				break;
			case 29:
				nextPoint = 6187 - abs(nextPoint);
				break;
			}
		}
	}
}

//�v���C���[�̂����˂��v�Z����֐�
void Player::shopping(int price){
	gold += price;
}

//�v���C���[�̕����ύX����֐�
void Player::setArms(int arm){
	arms = arm;
}

//�v���C���[�̖h���ύX����֐�
void Player::setGuard(int guard_s){
	guard = guard_s;
}

//�v���C���[�̒��ԂɊւ���֐�
//���̃L�������g�p�\���`����֐�
bool Player::getMate(){
	return mate;
}
//���̃v���C���[���g�p�\�ɂ���֐�
void Player::becameMate(){
	mate = true;
}

//�v���C���[����Ԉُ�ɂ���֐�
void Player::becomeError(int error){
	state = error;
}
//�v���C���[�̂������n���֐�
std::vector<item> Player::getDrugList(){
	return drug_list;
}

//�������ɂ������������֐�
bool Player::setDrug(std::string drug){
	for(i = 0,item_count = 0;i < drug_list.size();i++){
		item_count += drug_list[i].count;
		if(drug == drug_list[i].name){
			if(seed_list[i].count < 4){
				seed_list[i].count++;
				return true;
			}
			else{
				return false;
			}
		}
	}
	if(item_count == 32){
		return false;
	}else{
		 geti.count = 1;
		 geti.name = drug;
		drug_list.push_back(geti);
		return true;
	}
}

//�v���C���[�̎�������n���֐�
std::vector<item> Player::getItemList(){
	return item_list;
}

//�������ɃA�C�e����������֐�
bool Player::setItem(std::string item_p){
	for(i = 0,item_count = 0;i < item_list.size();i++){
		item_count += item_list[i].count;
		if(item_p == item_list[i].name){
			item_list[i].count++;
			return true;
		}
	}
	if(item_count == 32){
		return false;
	}else{
		 geti.count = 1;
		 geti.name = item_p;
		item_list.push_back(geti);
		return true;
	}
}

//������̂��Ƃ�n���֐�
std::vector<item> Player::getSeedList(){
	return seed_list;
}

//��̂��Ƃ��������ɉ�����֐�
bool Player::setSeed(std::string seed){
	for(i = 0,item_count = 0;i < seed_list.size();i++){
		item_count += seed_list[i].count;
		if(seed == seed_list[i].name){
			if(seed_list[i].count < 4){
				seed_list[i].count++;
				return true;
			}
			else{
				return false;
			}
		}
	}
	if(item_count == 32){
		return false;
	}else{
		 geti.count = 1;
		 geti.name = seed;
		seed_list.push_back(geti);
		return true;
	}
}

bool Player::getEsc(){
	return esc;
}

void Player::becomeEsc(){
	esc = !esc;
}

//�v���C���[�̃X�e�[�^�X��`����֐�
int Player::gethit(){
	return hit;
}
int Player::getmaxhit(){
	return maxhit;
}
int Player::getsaiko(){
	return saiko;
}
int Player::getmaxsaiko(){
	return maxsaiko;
}
int Player::getspeed(){
	return speed;
}
int Player::getjukurenndo(){
	return jukurenndo;
}
int Player::getkeikenti(){
	return keikenti;
}
int Player::getlevel(){
	return level;
}
int Player::getstate(){
	return state;
}
int Player::getdefense(){
	return defense;
}
std::string Player::getname(){
	return name;
}
int Player::getarms(){
	return arms;
}
int Player::getguard(){
	return guard;
}
int Player::getgold(){
	return gold;
}
int Player::getjump(){
	return jump;
}
bool* Player::getesp(){
	return esp;
}
int Player::getpk(){
	return pk;
}
int Player::getshield(){
	return shield;
}
int Player::gettelepathy(){
	return telepathy;
}
int* Player::getability(){
	ability[0] = state;
	ability[1] = level;
	ability[2] = hit;
	ability[3] = maxhit;
	ability[4] = saiko;
	ability[5] = maxsaiko;
	ability[6] = defense;
	ability[7] = speed;
	ability[8] = jukurenndo;
	ability[9] = keikenti;
	ability[10] = arms;
	ability[11] = guard;
	ability[12] = gold;
	ability[13] = pk;
	ability[14] = jump;
	ability[15] = telepathy;
	ability[16] = shield;
	ability[17] = nextPoint;
	return ability;
}
bool Player::getDead(){
	return dead;
}

int Player::getNextPoint(){
	return nextPoint;
}

void Player::Update(){
}

void Player::Initialize(){
}

Player::Player(){
}

void Player::Finalize(){
	delete [] ability;
	delete [] esp;
}