#pragma once
class KABEd : public IGameObject
{
public:
	KABEd();
	~KABEd();
	bool Start();
	void Update();
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	CPhysicsStaticObject m_phyStaticObject;
	CVector3 m_position = CVector3::Zero;
	CQuaternion m_rot = CQuaternion::Identity;
	CVector3 m_moveSpeed = CVector3::Zero;
	CVector3 scale;
};

