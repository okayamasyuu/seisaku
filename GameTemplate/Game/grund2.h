#pragma once
class grund2 : public IGameObject
{
public:
	grund2();
	~grund2();
	bool Start();
	void Update();
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	CPhysicsStaticObject m_phyStaticObject;
	CVector3 m_position = CVector3::Zero;
	CQuaternion m_rot = CQuaternion::Identity;
	CVector3 scale;
};

