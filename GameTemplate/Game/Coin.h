#pragma once
#include <block.h>
#include <Player.h>
class Coin : public IGameObject
{
public:
	Coin();
	~Coin();
	bool Start();
	void Update();
	prefab::CSkinModelRender* m_skinmodelRender = nullptr;
	CVector3 m_position = CVector3::Zero;
	CVector3 m_moveSpeed = CVector3::Zero;
	CQuaternion m_rotation = CQuaternion::Identity;
	prefab::CFontRender* fon = nullptr;
	CVector3 scale;
	int m_time = 0;
};

