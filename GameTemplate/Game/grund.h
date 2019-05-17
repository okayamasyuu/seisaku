#pragma once
class grund  : public IGameObject 
{
public:
	grund();
	~grund();
	bool Start();
	void Update();
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	CPhysicsStaticObject m_phyStaticObject;
	CVector3 m_position = CVector3::Zero;
	CVector3 scale;

};

