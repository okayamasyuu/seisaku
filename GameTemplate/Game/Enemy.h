#pragma once
#include "tkEngine/physics/tkPhysicsGhostObject.h"
#include "Game.h"
class Enemy :public IGameObject
{
public:
	Enemy();
	~Enemy();
	bool Start();
	void Update();
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	CVector3 m_position = CVector3::Zero; //座標
	CQuaternion m_rotion = CQuaternion::Identity; //回転
	CVector3 m_moveSpeed = CVector3::Zero; //移動速度
	CCharacterController  m_charaCon; //キャラクターコントローラー
	CVector3 scale;
	CPhysicsStaticObject  m_PSObject;
	CPhysicsGhostObject m_ghostobj;
	int enemy_hp = 3;//敵の体力
	CVector3  ghostPosi = CVector3::Zero;
	CVector3 m_ghostmove = CVector3::Zero;
};

