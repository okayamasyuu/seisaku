#pragma once
class Coin2 : public IGameObject
{
public:
	Coin2();
	~Coin2();
	bool Start();
	void Update();
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	CVector3 m_position = CVector3::Zero;
	CVector3 m_movespeed = CVector3::Zero;
	int m_time = 0;
};

