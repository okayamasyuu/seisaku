#include "stdafx.h"
#include "GameOver.h"


GameOver::GameOver()
{
}


GameOver::~GameOver()
{
	DeleteGO(m_sprite);
}
bool GameOver::Start()
{
	m_sprite = NewGO<prefab::CSpriteRender>(0);
	m_sprite->Init(L"sprite/mu.dds", 150, 150);
	return true;
}
