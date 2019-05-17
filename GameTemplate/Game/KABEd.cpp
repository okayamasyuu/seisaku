#include "stdafx.h"
#include "KABEd.h"
#include "Player.h"
#include "Enemy.h"
#include "Enemy2.h"
#include "Game.h"

KABEd::KABEd()
{
}


KABEd::~KABEd()
{
	DeleteGO(m_skinModelRender);
}
bool KABEd::Start()
{
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/backgound/kabe.cmo");



	m_skinModelRender->SetScale(scale);
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetRotation(m_rot);
	m_phyStaticObject.CreateMesh(m_position, m_rot, scale, m_skinModelRender);

	return true;
}
void KABEd::Update()
{
	m_position += m_moveSpeed;
	//エネミーを倒したら、一定数
	Game* gam = FindGO<Game>("game");
	if (gam->C_count >= 10) {
		DeleteGO(this);
		/*m_position.y += 3;
		if (m_position.y < 100) {
			m_moveSpeed.y = 0;
		}*/
	}
	m_skinModelRender->SetPosition(m_position);
}
