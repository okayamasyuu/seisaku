#pragma once
class hata : public IGameObject
{
public:
	hata();
	~hata();
	bool Start();
	void Update();
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	CVector3 m_position = CVector3::Zero;
	CPhysicsStaticObject  m_PSObject;
	CVector3 scale;
};

