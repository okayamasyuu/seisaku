#pragma once
#include <Game.h>
#include <Coin.h>
#include <camera.h>
class Player : public IGameObject
{
public:
	Player();
	~Player();
	bool Start();
	void Update();
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	CVector3 m_position = CVector3::Zero; //座標
	CVector3 m_moveSpeed = CVector3::Zero; //移動速度
	CQuaternion rotat = CQuaternion::Identity;
	CCharacterController m_charaCon; //キャラクターコントローラー
	prefab::CFontRender* font = nullptr; //フォント
	CVector3 m_moveSpeedX = CVector3::Zero;
	CVector3 m_moveSpeedZ = CVector3::Zero;
	int hp = 50;  //ライフ 
	float angle;
	int timer = 0;
	int time = 0;//ジャンプ中
	CVector3 scale;
	int Junp_flag = false;

	///*int Player::GetHP() {
	//	return hp; 
	//}*/

private:
	//int hp = 50;  //ライフ 

};

