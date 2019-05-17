#include "stdafx.h"
#include "kabe.h"
#include "Player.h"
#include "Enemy.h"
#include "Enemy2.h"

kabe::kabe()
{
}


kabe::~kabe()
{
	DeleteGO(m_skinModelRender);
}
bool kabe::Start()
{
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/backgound/kabe.cmo");

	enemy_count = 0;

	m_skinModelRender->SetScale(scale);
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetRotation(m_rot);
	m_phyStaticObject.CreateMesh(m_position, m_rot, scale, m_skinModelRender);

	return true;
}
void kabe::Update()
{
	m_position += m_moveSpeed;
	//エネミーを倒したら、一定数
	if (enemy_count == 4) {
		DeleteGO(this);
		/*m_position.y += 3;
		if (m_position.y < 100) {
			m_moveSpeed.y = 0;
		}*/
	}
	m_skinModelRender->SetPosition(m_position);
}
