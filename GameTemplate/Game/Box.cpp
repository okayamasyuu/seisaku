#include "stdafx.h"
#include "Box.h"


Box::Box()
{
}


Box::~Box()
{
	DeleteGO(m_skinModelRender);
}
bool Box::Start()
{
	m_position.x = -200;
	//�L�����N�^�[�R���g���[���[���������B
	m_charaCon.Init(
		25.0,        //���a �傫��
		100.0,       //����
		m_position
	);

	
	m_skinModelRender=NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modeldata/backgound/box.cmo");
	CVector3 scale;
	scale = { 2.0f, 7.0f, 2.0f };

	//m_moveSpeed.x = 305;

	m_skinModelRender->SetScale(scale);
	m_skinModelRender->SetPosition(m_position);
	m_PSObject.CreateMesh(m_position, CQuaternion::Identity, scale, m_skinModelRender);
	
	return true;
}
void Box::Update()
{
	/*m_position += m_moveSpeed;
	
	if (m_position.x < -400) {
		m_position.x += 50;
	}
	if (m_position.x > -100) {
		m_position.x -= 55;
	}*/

	m_position = m_charaCon.Execute(m_moveSpeed);//�L�����R���Ɉړ����x��^����

	m_skinModelRender->SetPosition(m_position);
}
