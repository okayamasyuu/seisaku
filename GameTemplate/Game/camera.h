#pragma once
#include  "Player.h"
class camera : public IGameObject
{
public:
	camera();
	~camera();
	bool Start();
	void Update();
	CVector3 m_position = CVector3::Zero; //ç¿ïW
	CVector3 target;
	CVector3 camePos;
	//Player * play = nullptr;
};

