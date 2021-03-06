#include "Enemy.h"
#include "DxLib.h"

Enemy::Enemy(int e_src,std::string e_name,int e_point,int e_gold,int e_defense,int e_attack,int e_hit,bool e_saiko,int e_race){
		src = e_src;
		hit = e_hit;
		maxhit = hit;
		defense = e_defense;
		attack = e_attack;
		name = e_name;
		dead = false;
		point = e_point;
		gold = e_gold;
		saiko = e_saiko;
		esc = false;
		state = 0;
		race = e_race;
}

Enemy::Enemy(){
}

void Enemy::Initialize(int e_x,int e_y){
	x = e_x;
	y = e_y;
}

void Enemy::Update(int damage){
	hit -= damage;
	if(hit <= 0){
		dead = true;
	}
}

void Enemy::Draw(){
	if(!dead && !esc){
		DrawGraph(x,y,src,TRUE);
	}
}

int Enemy::getRace(){
	return race;
}

//プレイヤーに当てるダメージを渡す関数
int Enemy::getDamage(int p_defense){
	if(attack - p_defense < 0){
		return 0;
	}
	else{
		return attack - p_defense + attack*(rand() % 4)/10;
	}
}

int Enemy::getDefense(){
	return defense;
}

int Enemy::getHP(){
	return hit;
}

void Enemy::becomeEsc(){
	esc = !esc; 
}

bool Enemy::getEsc(){
	return esc;
}

void Enemy::becomeState(int error){
	state = error;
	if(state == 3){
		attack = attack/2;
	}
}

int Enemy::getState(){
	return state;
}

//敵キャラの名前を渡す関数
std::string Enemy::getName(){
	return name;
}

//敵キャラの攻撃に名前を伝える関数
std::string Enemy::getAttackName(){
	return attack_name;
}

//敵キャラを初期化する関数
void Enemy::Encount(){
	hit = maxhit;
	dead = false;
}

//敵キャラの生死を伝える関数
bool Enemy::getDead(){
	return dead;
}

//経験値を与える関数
int Enemy::getPoint(){
	return point;
}

//お金を与える関数
int Enemy::getGold(){
	return gold;
}

//特殊攻撃があるかどうかを返す関数
bool Enemy::getSaiko(){
	return saiko;
}

//攻撃の名前を決定する関数
void Enemy::setAttackName(std::string a_name){
	attack_name = a_name;
}

void* Enemy::operator new(size_t size, void* buf){ return buf; }
void Enemy::operator delete(void* p, void* buf){}