#include "stdafx.h"
#include "Clear.h"


Clear::Clear()
{
}


Clear::~Clear()
{
	DeleteGO(m_spriteRender);
}
bool Clear::Start()
{
	m_spriteRender= NewGO<prefab::CSpriteRender>(0);
	m_spriteRender->Init(L"sprite/GAMECLEAR.dds",500, 150);

	return true;
}
