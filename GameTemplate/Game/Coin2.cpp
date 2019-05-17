#include "stdafx.h"
#include "Coin2.h"
#include "block.h"
#include "Game.h"

Coin2::Coin2()
{
}


Coin2::~Coin2()
{
	DeleteGO(m_skinModelRender);
}
bool Coin2::Start()
{
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/backgound/coinG.cmo");
	return true;
}
void Coin2::Update()
{
	m_position += m_movespeed;
	m_time++;
	if (m_time == 50) {
		DeleteGO(this);
	}
	
	m_skinModelRender->SetPosition(m_position);
	
}
