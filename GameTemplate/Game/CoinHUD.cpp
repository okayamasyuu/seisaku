#include "stdafx.h"
#include "CoinHUD.h"
#include "CoinHUD.h"
#include "Game.h"

CoinHUD::CoinHUD()
{
}


CoinHUD::~CoinHUD()
{
	DeleteGO(Cfont);
}
bool CoinHUD::Start()
{
	Cfont = NewGO<prefab::CFontRender>(0);
	Cfont->SetShadowParam(true, 2.0f, CVector4::Black);
	ga = FindGO<Game>("game");
	
	return true;
}
void CoinHUD::Update()
{
	wchar_t tex[256];
	swprintf(tex, L"%02d–‡", ga->C_count);
	Cfont->SetText(tex);
	Cfont->SetPosition({ 320.0f, 300.0f }); //ˆÊ’u
}
