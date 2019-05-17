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
	CVector3 m_position = CVector3::Zero; //���W
	CVector3 m_moveSpeed = CVector3::Zero; //�ړ����x
	CQuaternion rotat = CQuaternion::Identity;
	CCharacterController m_charaCon; //�L�����N�^�[�R���g���[���[
	prefab::CFontRender* font = nullptr; //�t�H���g
	CVector3 m_moveSpeedX = CVector3::Zero;
	CVector3 m_moveSpeedZ = CVector3::Zero;
	int hp = 50;  //���C�t 
	float angle;
	int timer = 0;
	int time = 0;//�W�����v��
	CVector3 scale;
	int Junp_flag = false;

	///*int Player::GetHP() {
	//	return hp; 
	//}*/

private:
	//int hp = 50;  //���C�t 

};

