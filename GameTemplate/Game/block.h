#pragma once

class block : public IGameObject
{
public:
	block();
	~block();
	bool Start();
	void Update();
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	CSkinModelData m_skinModelData;
	CSkinModel m_skinModel;
	CVector3 m_position = CVector3::Zero;
	CVector3 m_moveSpeed = CVector3::Zero;
	CQuaternion m_rotation = CQuaternion::Identity;
	CVector3 scale;
	CPhysicsStaticObject  m_PSObject;
	//CCharacterController m_charaCon; //キャラクターコントローラー
	int block_count = 1; //ブロックのコイン
	int time = 0;

	
};

