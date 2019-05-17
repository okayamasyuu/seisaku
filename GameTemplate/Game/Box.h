#pragma once
class Box : public IGameObject
{
public:
	Box();
	~Box();
	bool Start();
	void Update();
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	CVector3 m_position = CVector3::Zero;
	CVector3 m_moveSpeed = CVector3::Zero;
	CCharacterController m_charaCon; //キャラクターコントローラー
	CPhysicsStaticObject  m_PSObject;
	CPhysicsDynamicObject m_PDO;
};

