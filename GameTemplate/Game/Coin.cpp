#include "stdafx.h"
#include "Coin.h"
#include "Player.h"
#include "block.h"
#include "Game.h"

Coin::Coin()
{
}


Coin::~Coin()
{
	DeleteGO(m_skinmodelRender);
}
bool Coin::Start()
{
	m_skinmodelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinmodelRender->Init(L"modelData/backgound/coinG.cmo");
	m_skinmodelRender->SetShadowCasterFlag(true);

	scale.x = 2.0f;
	scale.y = 2.0f;
	scale.z = 2.0f;
	
	m_skinmodelRender->SetScale(scale);
	m_skinmodelRender->SetPosition(m_position);

	return true;
}
void Coin::Update()
{
	//コインをとる
	QueryGOs<Player>("プレイヤー", [&](Player* pl)->bool {
		CVector3 diff = pl->m_position - m_position;
		if (diff.Length() < 100.0f) {
			Game* ga = FindGO<Game>("game");
			ga->C_count++;
			//効果音
			auto ss = NewGO<prefab::CSoundSource>(0);
			ss->Init(L"sound/coinGet.wav");
			ss->Play(false);

			DeleteGO(this);
		}
		return true;
	});

	CQuaternion Rot;
	Rot.SetRotationDeg(
		{ 0.0f, 1.0, 0.0 },
		3.0f);
	m_rotation *= Rot;
	m_skinmodelRender->SetRotation(m_rotation);
}
